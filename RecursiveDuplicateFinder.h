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

#ifndef DIRECTORYDUPLICATEDETECTOR_H
#define DIRECTORYDUPLICATEDETECTOR_H

#include <map>
#include <string>
#include <vector>
#include <tuple>
#include <filesystem>
#include <mutex>

#include "DuplicateFinder.h"

class Blake3Hash;

namespace DupeDetect
{
/**
 * A Recursive duplicate finder. Will recursively go through every subdirectory in the given root folder
 * and make a list of all duplicate files found
 */
	class RecursiveDuplicateFinder : public DuplicateFinder
	{
	public:

		/**
		 * Constructor specifying the root directory for the search
		 * @param dirPath the root directory to be searched
		 */
		explicit RecursiveDuplicateFinder(const std::string& dirPath);

		/**
		 * Finds the duplicates in the given root directory
		 * @see DuplicateFinder::findDuplicates
		 */
		std::vector<std::vector<std::filesystem::path>> findDuplicates() override;

	private:

		std::vector<std::filesystem::path> paths;
	};
}

#endif // DIRECTORYDUPLICATEDETECTOR_H
