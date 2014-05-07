/** @file prefixmatcherfactory.cc
 * @brief Prefix Matcher Factory
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

#include "xapian/prefixmatcherfactory.h"
#include "/usr/local/WordNet-3.0/include/wn.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

namespace Xapian {

PrefixMatcher *
PrefixMatcherFactory::get_prefix_matcher(PrefixMatcherType type) {
	PrefixMatcher *matcher;
	switch (type) {
		case TRIE:
			matcher = new Xapian::Trie();
			break;
		case HASHTABLE:
			matcher = new Xapian::HashTable();
			break;
	}
	return matcher;
}

}
