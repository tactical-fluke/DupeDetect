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

#include "RecursiveDuplicateFinder.h"

#include <utility>
#include <filesystem>
#include "Blake3Hash.h"
#include "Options.h"
#include "DuplicateFindUtils.h"

namespace DupeDetect
{
	RecursiveDuplicateFinder::RecursiveDuplicateFinder(const std::string& dirPath)
	{
		std::filesystem::recursive_directory_iterator it(dirPath);

		for (const auto &path : it)
		{
			if (it->is_regular_file())
			{
				paths.push_back(path);
			}
		}
	}

	std::vector<std::vector<std::filesystem::path>> RecursiveDuplicateFinder::findDuplicates()
	{
		return DupeDetect::findDuplicates(paths.cbegin(), paths.cend(), Blake3_hashFile);
	}
}
