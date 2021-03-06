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

#include <stdexcept>
#include <cctype>
#include <algorithm>

#include "Size.h"

namespace
{
	constexpr int intPow(int base, int exponent)
	{
		int ret = 1;
		for(int i = 0; i < exponent; i++)
		{
			ret = ret * base;
		}
		return ret;
	}

	uintmax_t getMultiplierForSuffix(std::string& suffix)
	{
		if(suffix == "b")
			return 1;
		if(suffix == "kb")
			return 1024;
		if(suffix == "Kb")
			return 1000;
		if(suffix == "mb")
			return intPow(1024, 2);
		if(suffix == "Mb")
			return intPow(1000, 2);
		if(suffix == "gb")
			return intPow(1024, 3);
		if(suffix == "Gb")
			return intPow(1000, 3);

		throw std::runtime_error("No such size suffix \"" + suffix + "\" known for byte size");
	}
}

namespace DupeDetect
{
	uintmax_t getByteSizeFromString(const std::string& str)
	{
		auto suffixStart = std::find_if(str.cbegin(), str.cend(), isalpha);

		if(suffixStart == str.cend())
		{
			throw std::runtime_error("no suffix found for byte size");
		}

		auto index = str.find(*suffixStart);
		std::string suffix = str.substr(index);

		auto multiplier = getMultiplierForSuffix(suffix);

		auto base = std::stoi(str.substr(0, index));

		return base * multiplier;
	}
}