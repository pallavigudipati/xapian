/** \file  hashtable.h
 *  \brief HashTable
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

#ifndef XAPIAN_INCLUDED_HASHTABLE_H
#define XAPIAN_INCLUDED_HASHTABLE_H

#include <xapian/visibility.h>
#include <xapian.h>

#include <string>
#include <vector>

namespace Xapian {

class XAPIAN_VISIBILITY_DEFAULT HashTable : public PrefixMatcher {
  public:
	HashTable() { }
	std::vector<std::string> get_matches(std::string term) { }
	std::vector<std::string> get_sorted_matches(std::string term) { }
	void build_matcher(Database db) { }
};

}

#endif // XAPIAN_INCLUDED_HASHTABLE_H
