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

#include <xapian/base.h>
#include <xapian/visibility.h>

#include <string>
#include <vector>

namespace Xapian {

struct XAPIAN_VISIBILITY_DEFAULT trie_node{
	trie_node() {
		value = '\0';
		is_child = false;
	}
	char value;
	bool is_child;
	std::vector<trie_node *> children;	
};

class XAPIAN_VISIBILITY_DEFAULT Trie {
  public:
    struct trie_node root;

	Trie();
    // ~Trie();
	void add_term(std::string term);
	bool search_term(std::string term);
};

}

#endif // XAPIAN_INCLUDED_TRIE_H
