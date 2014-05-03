/** @file trie.cc
 * @brief Trie Implementation.
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

#include "xapian/trie.h"
#include "/usr/local/WordNet-3.0/include/wn.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

namespace Xapian {

Trie::Trie() {
// FILL something??
}

void
Trie::add_term(std::string term) {
	// cout << "In add_term: " << term << endl;
	struct trie_node *curr_node = &root;
	for (unsigned int i = 0; i < term.size(); ++i) {
		if (curr_node->children.size()) {
			for (vector<trie_node *>::iterator it = curr_node->children.begin();
					it != curr_node->children.end(); ++it) {
				if ((*it)->value == term[i]) {
					curr_node = *it;
					break;
				} else if(it + 1 == curr_node->children.end() && 
							(*it)->value < term[i]) {
					struct trie_node *new_node = new trie_node();
					new_node->value = term[i];
					curr_node->children.push_back(new_node);
					curr_node = curr_node->children.back();
					break;	
				} else if ((*it)->value > term[i]) {
					struct trie_node *new_node = new trie_node();
					new_node->value = term[i];
					it = curr_node->children.insert(it, new_node);
					curr_node = *it;
					break;	
				}
			}
		} else {
			struct trie_node *new_node = new trie_node();
			new_node->value = term[i];
			curr_node->children.push_back(new_node);
			curr_node = curr_node->children[0];
		}	
	}
	curr_node->is_child = true;
	curr_node->frequency += 1;
}

struct trie_node *
Trie::search_term(std::string term) {
	struct trie_node *curr_node = &root;
	for (unsigned int i = 0; i < term.size(); ++i) {
		for (vector<trie_node *>::iterator it = curr_node->children.begin();
				it != curr_node->children.end(); ++it) {
			if ((*it)->value == term[i]) {
				curr_node = *it;
				break;
			} else if(it + 1 == curr_node->children.end() || 
					  (*it)->value > term[i]) {
				return NULL;
			}
		}	
	}
	return curr_node;
}

vector<std::string> 
Trie::get_subtree(std::string term) {
	struct trie_node *start = search_term(term);
	vector<string> subtree;
	if (start && (start->children).size()) {
		for (vector<trie_node *>::iterator it = start->children.begin();
				it != start->children.end(); ++it) {
			std::string child_term = term;
			child_term.push_back((*it)->value);
			vector<std::string> child_tree = get_subtree(child_term);
			if ((*it)->is_child) {
				subtree.push_back(child_term);
			}
			subtree.reserve(subtree.size() + child_tree.size());
			subtree.insert(subtree.end(), child_tree.begin(), child_tree.end());
		}
	}


	return subtree;
}

bool SortByFrequency(pair<string, int> i, pair<string, int> j) {
	return i.second > j.second;
}

vector<std::string>
Trie::get_sorted_subtree(std::string term) {
	vector<string> raw_subtree = get_subtree(term);
	vector<pair<string, int> > subtree_nodes;
	for (unsigned int i = 0; i < raw_subtree.size(); ++i) {
		struct trie_node* node = search_term(raw_subtree[i]);
		subtree_nodes.push_back(make_pair(raw_subtree[i], node->frequency));
	}
	sort(subtree_nodes.begin(), subtree_nodes.end(), SortByFrequency);
	vector<string> subtree;
	for (unsigned int i = 0; i < subtree_nodes.size(); ++i) {
		subtree.push_back(subtree_nodes[i].first);
	}
	return subtree;
}

void
Trie::build_tree(Database db) {
	string logname = "/home/pallavi/POSE/xapian/xapian-core/logs/" 
						+ db.get_uuid();
	// cout << "Log file: " << logname << endl; 
	std::ifstream logfile(logname.c_str(), std::ifstream::in);
	string query;
	while (getline(logfile, query)) {
		this->add_term(query);
		// cout << "building " << query << endl;
	}
	logfile.close();
}

}
