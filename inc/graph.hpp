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
    Graph() = default;
    virtual ~Graph() = default;

    class Node;

    using NodePtr = std::shared_ptr<Node>;

    NodePtr add_root(const T&);

private:
    List<NodePtr> m_roots;
};

template<typename T>
class Graph<T>::Node {
public:
    virtual ~Node() = default;
    NodePtr add_neighbor(const T&);
    void add_neighbor(const NodePtr&);
    const NodePtr& neighbor(int) const;
    const List<NodePtr>& neighbors() const;

private:
    friend class Graph<T>;

    explicit Node(const T&);
    static NodePtr create(const T&);

public:
    T value;

private:
    List<NodePtr> m_neighbors;
};

template<typename T>
typename Graph<T>::NodePtr Graph<T>::add_root(const T& value) {
    m_roots.push_back(Node::create(value));
    return m_roots.back();
}

template<typename T>
typename Graph<T>::NodePtr Graph<T>::Node::create(const T& value) {
    return std::shared_ptr<Node>(new Node(value));
}

template<typename T>
Graph<T>::Node::Node(const T& value) : value(value), m_neighbors() {}

template<typename T>
typename Graph<T>::NodePtr Graph<T>::Node::add_neighbor(const T& neighbor_value) {
    add_neighbor(create(neighbor_value));
    return m_neighbors.back();
}

template<typename T>
void Graph<T>::Node::add_neighbor(const NodePtr& neighbor) {
    m_neighbors.push_back(neighbor);
}

template<typename T>
const typename Graph<T>::NodePtr& Graph<T>::Node::neighbor(int index) const {
    return neighbors()[index];
}

template<typename T>
const List<typename Graph<T>::NodePtr>& Graph<T>::Node::neighbors() const {
    return m_neighbors;
}

#endif //DATASTRUCTURES_ALGORITHMS_GRAPH_HPP
