/** \file  trie.h
 *  \brief Trie
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

#ifndef XAPIAN_INCLUDED_TRIE_H
#define XAPIAN_INCLUDED_TRIE_H

#include <xapian/visibility.h>
#include <xapian.h>

#include <string>
#include <vector>

namespace Xapian {

struct XAPIAN_VISIBILITY_DEFAULT trie_node{
	trie_node() {
		value = '\0';
		is_child = false;
		frequency = 0;
	}
	char value;
	bool is_child;
	int frequency;
	std::vector<trie_node *> children;	
};

class XAPIAN_VISIBILITY_DEFAULT Trie : public PrefixMatcher {
  private:
	struct trie_node *root;

  public:
	Trie();
	void add_term(std::string term);
	struct trie_node * search_term(std::string term);
	std::vector<std::string> get_matches(std::string term);
	// Sorted on basis of frequency. Calls get_subtree internally. 
	std::vector<std::string> get_sorted_matches(std::string term);
	void build_matcher(Database db);
};

}

#endif // XAPIAN_INCLUDED_TRIE_H
