//
// Created by Aidan Haile on 29/6/21.
//

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
