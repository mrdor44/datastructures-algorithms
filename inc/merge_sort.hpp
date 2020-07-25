//
// Created by dor on 24/07/2020.
//

#ifndef DATASTRUCTURES_ALGORITHMS_MERGE_SORT_HPP
#define DATASTRUCTURES_ALGORITHMS_MERGE_SORT_HPP

template<typename Container>
static Container merge_sort(const Container&, int begin, int end);

template<typename Container>
static Container merge(const Container&, const Container&);

template<typename Container>
Container merge_sort(const Container& container) {
    return merge_sort(container, 0, container.size());
}

template<typename Container>
static Container merge_sort(const Container& container, int begin, int end) {
    if (begin > end) {
        return Container();
    }
    if (begin == end) {
        Container result;
        result.push_back(container[begin]);
        return result;
    }
    const int middle = (begin + end) / 2;
    Container left = merge_sort(container, begin, middle);
    Container right = merge_sort(container, middle, end);
    return merge(left, right);
}

template<typename Container>
static Container merge(const Container& c1, const Container& c2) {
    Container result;
    auto it1 = c1.cbegin();
    auto it2 = c2.cbegin();
    while (it1 != c1.cend() && it2 != c2.cend()) {
        if (*it1 > *it2) {
            result.push_back(*it1);
            ++it1;
        }
        assert(*it2 >= *it1);
        result.push_back(*it2);
        ++it2;
    }
    for (; it1 != c1.cend(); ++it1) {
        result.push_back(*it1);
    }
    for (; it2 != c2.cend(); ++it2) {
        result.push_back(*it2);
    }
    return result;
}

#endif //DATASTRUCTURES_ALGORITHMS_MERGE_SORT_HPP
