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

#ifndef DUPEDETECT_DUPLICATEFINDUTILS_H
#define DUPEDETECT_DUPLICATEFINDUTILS_H

#include <execution>
#include <map>
#include <vector>
#include <mutex>

namespace DupeDetect
{
	template<class iterator_t, class hasher_t>
	auto findDuplicates(iterator_t start, iterator_t end, hasher_t&& hasher)
	{
		using hash_t = decltype(hasher(*start));
		using value_t = typename iterator_t::value_type;

		std::map<hash_t, value_t> knownHashes;
		std::map<hash_t, std::vector<value_t>> knownDuplicates;

		std::mutex m;

		std::for_each(std::execution::par, start, end, [&](const value_t& val)
		{
			hash_t hashVal = hasher(val);

			std::lock_guard lock(m);

			auto foundDupe = knownHashes.find(hashVal);

			if(foundDupe == knownHashes.end())
			{
				knownHashes.emplace(std::move(hashVal), val);
			}
			else
			{
				auto duplicates = knownDuplicates.find(hashVal);

				if(duplicates == knownDuplicates.end())
				{
					std::vector<value_t> values;
					values.reserve(2);
					values.push_back(foundDupe->second);
					values.push_back(val);
					knownDuplicates.emplace(std::move(hashVal), std::move(values));
				}
				else
				{
					std::vector<value_t>& values = duplicates->second;
					values.push_back(val);
				}
			}
		});

		std::vector<std::vector<value_t>> ret;
		ret.reserve(knownDuplicates.size());

		std::transform(knownDuplicates.begin(), knownDuplicates.end(), std::back_inserter(ret), [](const auto& values)
		{
			return values.second;
		});
		return ret;
	}
}

#endif //DUPEDETECT_DUPLICATEFINDUTILS_H
