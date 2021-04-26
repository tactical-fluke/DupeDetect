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

#include "DepthLimitedDuplicateFinder.h"
#include "Options.h"
#include "DuplicateFindUtils.h"

#include <utility>
#include <stack>

namespace DupeDetect
{
	DepthLimitedDuplicateFinder::DepthLimitedDuplicateFinder(const std::string& root, int depth) : paths()
	{
		traverseDir(root, depth);
	}

	void DepthLimitedDuplicateFinder::traverseDir(const std::string &filepath, int depthRemaining)
	{
		std::stack<std::pair<std::filesystem::path, int>> stack;
		stack.emplace(filepath, depthRemaining);

		while (!stack.empty())
		{
			auto[path, depth] = stack.top();
			stack.pop();

			std::filesystem::directory_iterator it(path);
			for (const auto &subPath : it)
			{
				if (isDirectoryEntryValid(*it))
				{
					paths.push_back(subPath);
				}
				else if (subPath.is_directory())
				{
					if (depth - 1 >= 0)
					{
						stack.emplace(subPath, depth - 1);
					}
				}
			}
		}
	}

	std::vector<std::vector<std::filesystem::path>> DepthLimitedDuplicateFinder::findDuplicates()
	{
		return DupeDetect::findDuplicates(paths.cbegin(), paths.cend(), Blake3_hashFile);
	}
}
