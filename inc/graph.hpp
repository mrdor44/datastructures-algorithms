//
// Created by dor on 02/07/2020.
//

#ifndef DATASTRUCTURES_ALGORITHMS_GRAPH_HPP
#define DATASTRUCTURES_ALGORITHMS_GRAPH_HPP

#include <memory>
#include "list.hpp"

template<typename T>
class Graph {
public:
    explicit Graph(const T&);
    virtual ~Graph() = default;

    using Node = Graph;
    using NodePtr = std::shared_ptr<Node>;

    static NodePtr create(const T&);

    NodePtr add_neighbor(const T&);
    void add_neighbor(const NodePtr&);
    NodePtr neighbor(int);

public:
    T value;

private:
    List<NodePtr> m_neighbors;
};

template<typename T>
typename Graph<T>::NodePtr Graph<T>::create(const T& value) {
    return std::make_shared<Node>(value);
}

template<typename T>
Graph<T>::Graph(const T& value) : value(value) {}

template<typename T>
typename Graph<T>::NodePtr Graph<T>::add_neighbor(const T& value) {
    m_neighbors.push_back(std::make_shared<Node>(value));
    return m_neighbors.back();
}

template<typename T>
void Graph<T>::add_neighbor(const NodePtr& neighbor) {
    m_neighbors.push_back(neighbor);
}

template<typename T>
typename Graph<T>::NodePtr Graph<T>::neighbor(int index) {
    return m_neighbors[index];
}

#endif //DATASTRUCTURES_ALGORITHMS_GRAPH_HPP
