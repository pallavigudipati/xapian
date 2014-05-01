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
#include "/usr/local/WordNet-3.0/include/wn.h"

#include <iostream>
#include <string>
#include <vector>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

using namespace std;

namespace Xapian {

SynonymExpand::SynonymExpand(std::string query) {
	original_query = query;

	boost::algorithm::split(results, original_query,
							boost::algorithm::is_any_of(" "));
	for (int i = 0; i < results.size(); ++i) {
		cout << results[i] << endl;
	}

	int check = wninit();
	if (check != 0) {
		cout << "ERROR: WordNet Database not accessible." << endl;
	}
	

}

}
