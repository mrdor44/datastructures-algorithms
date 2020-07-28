//
// Created by dor on 02/07/2020.
//

#ifndef DATASTRUCTURES_ALGORITHMS_GRAPH_HPP
#define DATASTRUCTURES_ALGORITHMS_GRAPH_HPP

#include <memory>
#include "list.hpp"
#include "queue.hpp"
#include "stack.hpp"
#include "graph_scanner.hpp"

template<typename T>
class Graph {
public:
    Graph() = default;
    virtual ~Graph() = default;
    Graph(const Graph&) = delete;
    Graph(Graph&&) noexcept = default;

    class Node;
    using NodePtr = std::shared_ptr<Node>;
    class Scanner;
    class BFSScanner;
    class DFSScanner;

    NodePtr add_root(const T&);
    const List<NodePtr>& roots() const;
    BFSScanner bfs() const;
    DFSScanner dfs() const;

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
    [[nodiscard]] bool is_visited() const;
    bool& is_visited();

private:
    friend class Graph<T>;

    explicit Node(const T&);
    static NodePtr create(const T&);

public:
    T value;

private:
    List<NodePtr> m_neighbors;
    bool m_visited;
};

template<typename T>
class Graph<T>::Scanner : public GraphScanner<T> {
protected:
    explicit Scanner(const Graph&);
    virtual ~Scanner() = default;

protected:
    const Graph& m_graph;
};

template<typename T>
class Graph<T>::BFSScanner : public Graph<T>::Scanner {
private:
    explicit BFSScanner(const Graph&);
    friend class Graph<T>;

public:
    virtual ~BFSScanner() = default;
    void apply(const std::function<void(const T&)>& function) const override;
};

template<typename T>
class Graph<T>::DFSScanner : public Graph<T>::Scanner {
private:
    explicit DFSScanner(const Graph&);
    friend class Graph<T>;

public:
    virtual ~DFSScanner() = default;
    void apply(const std::function<void(const T&)>& function) const override;
};

template<typename T>
typename Graph<T>::NodePtr Graph<T>::add_root(const T& value) {
    m_roots.push_back(Node::create(value));
    return m_roots.back();
}

template<typename T>
const List<typename Graph<T>::NodePtr>& Graph<T>::roots() const {
    return m_roots;
}

template<typename T>
typename Graph<T>::NodePtr Graph<T>::Node::create(const T& value) {
    return std::shared_ptr<Node>(new Node(value));
}

template<typename T>
Graph<T>::Node::Node(const T& value) : value(value), m_neighbors(), m_visited(false) {}

template<typename T>
Graph<T>::Scanner::Scanner(const Graph& graph) : m_graph(graph) {}

template<typename T>
Graph<T>::BFSScanner::BFSScanner(const Graph& graph) : Scanner(graph) {}

template<typename T>
Graph<T>::DFSScanner::DFSScanner(const Graph& graph) : Scanner(graph) {}

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

template<typename T>
bool Graph<T>::Node::is_visited() const {
    return m_visited;
}

template<typename T>
bool& Graph<T>::Node::is_visited() {
    return m_visited;
}

template<typename T>
typename Graph<T>::BFSScanner Graph<T>::bfs() const {
    return Graph::BFSScanner(*this);
}

template<typename T>
typename Graph<T>::DFSScanner Graph<T>::dfs() const {
    return Graph::DFSScanner(*this);
}

template<typename T>
void Graph<T>::BFSScanner::apply(const std::function<void(const T&)>& function) const {
    Queue<NodePtr> queue;

    const List<NodePtr>& roots = this->m_graph.roots();
    if (roots.is_empty()) {
        return;
    }

    bool unvisited = roots[0]->is_visited();
    bool visited = not unvisited;

    for (queue.enqueue(roots.begin(), roots.end()); !queue.is_empty(); queue.dequeue()) {
        const NodePtr& node = queue.next();
        if (node == nullptr or node->is_visited() == visited) {
            continue;
        }
        assert(node->is_visited() == unvisited);
        function(node->value);
        node->is_visited() = visited;
        queue.enqueue(node->neighbors().begin(), node->neighbors().end());
    }
}

template<typename T>
void Graph<T>::DFSScanner::apply(const std::function<void(const T&)>& function) const {
    Stack<NodePtr> to_visit;

    const List<NodePtr>& roots = this->m_graph.roots();
    if (roots.is_empty()) {
        return;
    }

    bool unvisited = roots[0]->is_visited();
    bool visited = not unvisited;

    for (to_visit.push(roots.begin(), roots.end()); !to_visit.is_empty();) {
        const NodePtr node = to_visit.top();
        to_visit.pop();
        if (node == nullptr or node->is_visited() == visited) {
            continue;
        }
        assert(node->is_visited() == unvisited);
        function(node->value);
        node->is_visited() = visited;
        to_visit.push(node->neighbors().begin(), node->neighbors().end());
    }
}

#endif //DATASTRUCTURES_ALGORITHMS_GRAPH_HPP
