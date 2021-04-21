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

#ifndef DUPEDETECT_DEPTHLIMITEDDUPLICATEFINDER_H
#define DUPEDETECT_DEPTHLIMITEDDUPLICATEFINDER_H

#include <vector>
#include <map>
#include <filesystem>
#include <mutex>
#include "Blake3Hash.h"
#include "DuplicateFinder.h"

namespace DupeDetect
{
	/**
	 * A duplicate finder that is limited by depth, and will only search through subdirectories to a specified depth
	 */
	class DepthLimitedDuplicateFinder : public DuplicateFinder
	{
	public:

		/**
		 * Constructor specifying the root directory to search, and the depth at which to search it.
		 * A depth of zero searches no subdirectories
		 * @param root
		 * @param depth
		 */
		DepthLimitedDuplicateFinder(const std::string& root, int depth);

		/**
		 * find the duplicate files in the directory, and to the depth specified of subdirectories
		 * @see DuplicateFinder::findDuplicates
		 */
		std::vector<std::vector<std::filesystem::path>> findDuplicates() override;

	private:

		/**
		 * Maps out a directory, adding it's subdirectories to paths
		 * @param path the path to the subdirectory to traverse
		 * @param depthRemaining the remaining depth to be searched. A depth of 0
		 */
		void traverseDir(const std::string &path, int depthRemaining);

		/**
		 * The paths to search through. At most a depth n specified at construction from the root directory
		 */
		std::vector<std::filesystem::path> paths;
	};
}

#endif //DUPEDETECT_DEPTHLIMITEDDUPLICATEFINDER_H
