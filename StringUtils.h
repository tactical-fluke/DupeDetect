/*
 * 	DupeDetect: small terminal application to find duplicate files
 *  Copyright (C) 2021  Aidan Haile
 *
 *	This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef DUPEDETECT_STRINGUTILS_H
#define DUPEDETECT_STRINGUTILS_H

#include <string>
#include <algorithm>

namespace StringUtils
{
	/**
	 * checks if str starts with prefix
	 * @param str the string to check the start of
	 * @param prefix the prefix to check for at the start of str
	 * @return true if str starts with prefix. false otherwise
	 */
	bool startsWith(const std::string &str, const std::string &prefix);
}

#endif //DUPEDETECT_STRINGUTILS_H
