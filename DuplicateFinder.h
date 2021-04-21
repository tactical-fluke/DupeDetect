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

#ifndef DUPEDETECT_DUPLICATEFINDER_H
#define DUPEDETECT_DUPLICATEFINDER_H

#include <vector>
#include <string>
#include <map>
#include <mutex>

#include "Blake3Hash.h"

namespace DupeDetect
{
	/**
	 * Interface for a general duplicate finder.
	 * Provides some standard utilities required of a duplicate finder
	 */
	class DuplicateFinder
	{
	public:
		/**
		 * Finds duplicates in the given structure defined by children classes
		 */
		virtual std::vector<std::vector<std::filesystem::path>> findDuplicates() = 0;

		virtual ~DuplicateFinder() = default;
	};
}

#endif //DUPEDETECT_DUPLICATEFINDER_H
