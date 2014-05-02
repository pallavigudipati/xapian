/** @file synonymexpansion.cc
 * @brief Expansion of queries using synonyms.
 */
/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 */

#include "xapian/synonymexpansion.h"
#include "wordnet/wn.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

using namespace std;

namespace Xapian {

    SynonymExpand::SynonymExpand(std::string input_query) {
        original_query = input_query;
        vector<string> query_words;

        //cout << stopper.get_description();

        // Parse the query string to produce a Xapian::Query object.
        Xapian::QueryParser qp;
        Xapian::Stem stemmer("english");
        qp.set_stemmer(stemmer); // stemming
        qp.set_stemming_strategy(Xapian::QueryParser::STEM_SOME);
        qp.set_stopper(new PopulatedSimpleStopper()); // stop word removal
        Xapian::Query query = qp.parse_query(original_query);

        cout << "Parsed query is: " << query.get_description() << endl;

        string stripped_query_string = "";
        for (Xapian::TermIterator it = query.get_terms_begin();
                it != query.get_terms_end();
                ++it) {
            string term = *it;
            // Remove Z in front of terms added by Xapian
            stripped_query_string += term.substr(1, term.length()-1) + " ";
        }


        boost::algorithm::split(query_words, stripped_query_string,
                boost::algorithm::is_any_of(" "));
        for (unsigned i = 0; i < query_words.size(); ++i) {
            cout << query_words[i] << endl;
        }

        //cout << "Opening wordnet database" << endl;

        int check = wninit();
        if (check != 0) {
            cout << "ERROR: WordNet Database not accessible." << endl;
        }

        //cout << "Database open" << endl;

        // limits
        int num_synsets = 2;
        int num_synonyms = 1;

        // find synonyms for each word i
        for (unsigned i = 0; i < query_words.size(); ++i) {

            // this weird bit is because c_str() returns a const char *
            // in_wn() expects a non-const char *
            char *word = new char[query_words[i].length()];
            strcpy(word, query_words[i].c_str());
            //cout << "word=" << word << endl;

            unsigned noun_in_wn = in_wn(word, NOUN);
            //cout << "noun_in_wn=" << noun_in_wn << endl;
            if (noun_in_wn) {
                SynsetPtr synsets = findtheinfo_ds(word, NOUN, SYNS, ALLSENSES);

                // for each sense of the word
                SynsetPtr sptr = synsets;
                for (int j = 0; j < num_synsets && sptr != NULL; ++j, sptr = sptr->nextss) {
                    char **synonyms = sptr->words;

                    // for each word that is a synonym in this sense
                    for (int k = 0, l = 0; k < sptr->wcount && l < num_synonyms; ++k) {
                        cout << synonyms[k] << endl;
                        string synonym(synonyms[k]);
                        if (synonym == query_words[i])
                            continue;
                        string res(original_query);
                        res.replace( res.find(query_words[i]), query_words[i].length(), synonym );
                        cout << res << endl;
                        results.push_back(res);
                        ++l;
                    }

                }
                free_syns(synsets);
            }
            delete word;
        }

    }

}
