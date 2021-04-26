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

#ifndef DUPEDETECT_SIZE_H
#define DUPEDETECT_SIZE_H

#include <string>

namespace DupeDetect
{
	/**
	 * Retrieves the size in bytes specified by this string
	 * @param str the string containing the byte size i.e 100mb
	 * @return the size, in bytes, this string represents
	 */
	uintmax_t getByteSizeFromString(const std::string& str);
}

#endif //DUPEDETECT_SIZE_H
