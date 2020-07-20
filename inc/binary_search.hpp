//
// Created by dor on 20/07/2020.
//

#ifndef DATASTRUCTURES_ALGORITHMS_BINARY_SEARCH_HPP
#define DATASTRUCTURES_ALGORITHMS_BINARY_SEARCH_HPP

#include <iterator>
#include <cassert>

namespace dsa {

// Iterator must implement https://en.cppreference.com/w/cpp/named_req/InputIterator
// Iterator may implement https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator
// for constant time performance
template<typename Iterator, typename T>
Iterator binary_search(Iterator begin, const Iterator& end, const T& value) {
    int distance = std::distance(begin, end);
    while (distance > 0) {
        const Iterator middle = begin;
        std::advance(middle, distance / 2);
        if (value < *middle) {
            // We would set end = middle, but that simply means the distance will be halved
            distance /= 2;
            continue;
        }
        if (value == *middle) {
            return middle;
        }
        assert(value > *middle);
        begin = middle;
        distance -= distance / 2;
        distance -= 1;
    }
    return begin;
}

}


#endif //DATASTRUCTURES_ALGORITHMS_BINARY_SEARCH_HPP
