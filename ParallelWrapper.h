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

#ifndef DUPEDETECT_PARALLELWRAPPER_H
#define DUPEDETECT_PARALLELWRAPPER_H

#include <algorithm>
#include <execution>
#ifdef __APPLE__
#include <dispatch/dispatch.h>
#include <utility>
#endif

namespace DupeDetect
{
	/**
	 * System independence wrapper around a parallel for loop
	 *
	 * @note On systems other than MacOS, this simply dispatches the arguments to the standard library parallel
	 * for implementation. On MacOS, it uses Grand Central Dispatch to queue up the closure with each item in the
	 * span.
	 *
	 * @tparam iterator_t iterator type
	 * @tparam closure_t closure type, gets run on every object defined betwen the start and end iterators
	 * @param start the start of span of items to iterate over
	 * @param end past the end iterator for the items to iterate over
	 * @param closure closure to run over every item iterated over. Must be thread-safe in its context
	 */
    template <class iterator_t, class closure_t>
    void parallelFor(iterator_t&& start, iterator_t&& end, closure_t&& closure)
    {
#ifndef __APPLE__
        std::for_each(std::execution::par, std::forward<iterator_t>(start), std::forward<iterator_t>(end), std::forward<closure_t>(closure));
#else
        dispatch_queue_t main_q = dispatch_queue_create("parallel for", nullptr);

        for(iterator_t itr = start; itr != end; itr++)
        {
            auto&& item = *itr;
            dispatch_async(main_q, ^{ closure(std::forward<decltype(item)>(item)); });
        }

        dispatch_sync(main_q, ^{});
#endif
    }
}

#endif //DUPEDETECT_PARALLELWRAPPER_H
