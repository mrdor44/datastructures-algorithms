//
// Created by dor on 02/07/2020.
//

#ifndef DATASTRUCTURES_ALGORITHMS_NODE_HPP
#define DATASTRUCTURES_ALGORITHMS_NODE_HPP

#include <memory>

template<typename T>
struct Node;
template<typename T> using NodePtr = std::shared_ptr<Node<T>>;

template<typename T>
struct Node {
    T value;
    NodePtr<T> next;
    NodePtr<T> prev;

    Node() = default;
    Node(const T& value, const NodePtr<T> next, const NodePtr<T> prev);
};

template<typename T>
Node<T>::Node(const T& value, const NodePtr<T> next, const NodePtr<T> prev)
        : value(value), next(next), prev(prev) {}

#endif //DATASTRUCTURES_ALGORITHMS_NODE_HPP
