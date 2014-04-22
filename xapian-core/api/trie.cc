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

#include <string>
#include <vector>

using namespace std;

namespace Xapian {

Trie::Trie() {
// FILL something??
}

void
Trie::add_term(std::string term) {
	struct trie_node *curr_node = &root;
	for (unsigned int i = 0; i < term.size(); ++i) {
		for (vector<trie_node *>::iterator it = curr_node->children.begin();
				it != curr_node->children.end(); ++it) {
			if ((*it)->value == term[i]) {
				curr_node = *it;
				break;
			} else if(it + 1 == curr_node->children.end() || 
					  (*it)->value > term[i]) {
				struct trie_node *new_node = new trie_node();
				new_node->value = term[i];
				curr_node->children.insert(it, new_node);
				curr_node = *it;
				break;	
			}
		}	
	}
	curr_node->is_child = true;
}

bool
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
				return false;
			}
		}	
	}
	return true;
}

}
