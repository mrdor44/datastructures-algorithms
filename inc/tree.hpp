//
// Created by dor on 02/07/2020.
//

#ifndef DATASTRUCTURES_ALGORITHMS_TREE_HPP
#define DATASTRUCTURES_ALGORITHMS_TREE_HPP

#include <memory>
#include <functional>
#include "list.hpp"
#include "queue.hpp"

template<typename T>
class Tree {
public:
    explicit Tree(const T&);
    virtual ~Tree() = default;

    class Node;

    using NodePtr = std::shared_ptr<Node>;

    const NodePtr& root() const;
    void do_preorder(const std::function<void(const T&)>&) const;

private:
    NodePtr m_root;
};

template<typename T>
class Tree<T>::Node {
public:
    virtual ~Node() = default;
    NodePtr add_child(const T&);
    const List<NodePtr>& children() const;

private:
    friend class Tree<T>;

    explicit Node(const T&);
    static NodePtr create(const T&);

public:
    T value;

private:
    List<NodePtr> m_children;
};

template<typename T>
Tree<T>::Tree(const T& value) : m_root(Node::create(value)) {}

template<typename T>
Tree<T>::Node::Node(const T& value) : value(value), m_children() {}

template<typename T>
const typename Tree<T>::NodePtr& Tree<T>::root() const {
    return m_root;
}

template<typename T>
typename Tree<T>::NodePtr Tree<T>::Node::create(const T& value) {
    return std::shared_ptr<Node>(new Node(value));
}

template<typename T>
typename Tree<T>::NodePtr Tree<T>::Node::add_child(const T& child_value) {
    m_children.push_back(create(child_value));
    return m_children.back();
}

template<typename T>
const List<typename Tree<T>::NodePtr>& Tree<T>::Node::children() const {
    return m_children;
}

template<typename T>
void Tree<T>::do_preorder(const std::function<void(const T&)>& function) const {
    Queue<NodePtr> queue;
    queue.enqueue(root());

    while (!queue.is_empty()) {
        const NodePtr& node = queue.next();
        function(node->value);
        queue.enqueue(node->children());
        queue.dequeue();
    }
}

#endif //DATASTRUCTURES_ALGORITHMS_TREE_HPP
