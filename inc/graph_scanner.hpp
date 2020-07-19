//
// Created by dor on 16/07/2020.
//

#ifndef DATASTRUCTURES_ALGORITHMS_GRAPH_SCANNER_HPP
#define DATASTRUCTURES_ALGORITHMS_GRAPH_SCANNER_HPP

#include <functional>

template<typename T>
class GraphScanner {
public:
    virtual ~GraphScanner() = default;

    virtual void apply(const std::function<void(const T&)>&) const = 0;
    template<typename Container>
    Container collect();
};

template<typename T>
template<typename Container>
Container GraphScanner<T>::collect() {
    Container container;
    apply([&](const T& item) { container.push_back(item); });
    return container;
}

#endif //DATASTRUCTURES_ALGORITHMS_GRAPH_SCANNER_HPP
