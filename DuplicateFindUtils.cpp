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

#include <filesystem>
#include "Options.h"
#include "Size.h"

namespace DupeDetect
{
	bool isDirectoryEntryValid(const std::filesystem::directory_entry &entry)
	{
		auto min = Options::optionFound("minsize") ? getByteSizeFromString(Options::getOpt<std::string>("minsize")) : 0;
		auto max = Options::optionFound("maxsize") ? getByteSizeFromString(Options::getOpt<std::string>("maxsize"))
												   : std::numeric_limits<uintmax_t>::max();

		if (entry.is_regular_file())
		{
			auto size = entry.file_size();
			if (size > min && size < max)
			{
				return true;
			}
		}
		return false;
	}
}
