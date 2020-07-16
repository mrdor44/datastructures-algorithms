//
// Created by dor on 02/07/2020.
//

#ifndef DATASTRUCTURES_ALGORITHMS_TREE_HPP
#define DATASTRUCTURES_ALGORITHMS_TREE_HPP

#include <memory>
#include <functional>
#include "queue.hpp"
#include "stack.hpp"

template<typename T>
class Tree {
public:
    class Node;
    using NodePtr = std::shared_ptr<Node>;
    class Scanner;
    class PreorderScanner;
    class PostorderScanner;
    class InorderScanner;
    class BFSScanner;

    static NodePtr create(const T&);
    static PreorderScanner preorder(const NodePtr& root);
    static PostorderScanner postorder(const NodePtr& root);
    static InorderScanner inorder(const NodePtr& root);
    static BFSScanner bfs(const NodePtr& root);

public:
    Tree() = delete;
    ~Tree() = delete;
};

template<typename T>
class Tree<T>::Node {
public:
    virtual ~Node() = default;
    const NodePtr& set_left(const T&);
    const NodePtr& set_right(const T&);

private:
    friend class Tree<T>;

    explicit Node(const T&);
    static NodePtr create(const T&);

public:
    T value;

private:
    NodePtr m_left;
    NodePtr m_right;
};

template<typename T>
class Tree<T>::Scanner {
public:
    explicit Scanner(const NodePtr&);
    virtual ~Scanner() = default;

    virtual void apply(const std::function<void(const T&)>&) const = 0;
    template<typename Container>
    Container collect();

protected:
    const NodePtr& m_root;
};

template<typename T>
class Tree<T>::PreorderScanner : public Tree<T>::Scanner {
public:
    explicit PreorderScanner(const NodePtr&);
    virtual ~PreorderScanner() = default;

    void apply(const std::function<void(const T&)>&) const override;
};

template<typename T>
class Tree<T>::PostorderScanner : public Tree<T>::Scanner {
public:
    explicit PostorderScanner(const NodePtr&);
    virtual ~PostorderScanner() = default;

    void apply(const std::function<void(const T&)>& function) const override;
};

template<typename T>
class Tree<T>::InorderScanner : public Tree<T>::Scanner {
public:
    explicit InorderScanner(const NodePtr&);
    virtual ~InorderScanner() = default;

    void apply(const std::function<void(const T&)>& function) const override;
};

template<typename T>
class Tree<T>::BFSScanner : public Tree<T>::Scanner {
public:
    explicit BFSScanner(const NodePtr&);
    virtual ~BFSScanner() = default;

    void apply(const std::function<void(const T&)>& function) const override;
};

template<typename T>
typename Tree<T>::NodePtr Tree<T>::create(const T& value) {
    return Node::create(value);
}

template<typename T>
Tree<T>::Node::Node(const T& value) : value(value), m_left(), m_right() {}

template<typename T>
Tree<T>::Scanner::Scanner(const NodePtr& root) : m_root(root) {}

template<typename T>
Tree<T>::PreorderScanner::PreorderScanner(const NodePtr& root) : Scanner(root) {}

template<typename T>
Tree<T>::PostorderScanner::PostorderScanner(const NodePtr& root) : Scanner(root) {}

template<typename T>
Tree<T>::InorderScanner::InorderScanner(const NodePtr& root) : Scanner(root) {}

template<typename T>
Tree<T>::BFSScanner::BFSScanner(const NodePtr& root) : Scanner(root) {}

template<typename T>
typename Tree<T>::NodePtr Tree<T>::Node::create(const T& value) {
    return std::shared_ptr<Node>(new Node(value));
}

template<typename T>
const typename Tree<T>::NodePtr& Tree<T>::Node::set_left(const T& child_value) {
    m_left = create(child_value);
    return m_left;
}

template<typename T>
const typename Tree<T>::NodePtr& Tree<T>::Node::set_right(const T& child_value) {
    m_right = create(child_value);
    return m_right;
}

template<typename T>
typename Tree<T>::PreorderScanner Tree<T>::preorder(const NodePtr& root) {
    return PreorderScanner(root);
}

template<typename T>
typename Tree<T>::PostorderScanner Tree<T>::postorder(const Tree::NodePtr& root) {
    return PostorderScanner(root);
}

template<typename T>
typename Tree<T>::InorderScanner Tree<T>::inorder(const Tree::NodePtr& root) {
    return InorderScanner(root);
}

template<typename T>
typename Tree<T>::BFSScanner Tree<T>::bfs(const Tree::NodePtr& root) {
    return BFSScanner(root);
}

template<typename T>
void Tree<T>::PreorderScanner::apply(const std::function<void(const T&)>& function) const {
    Stack<NodePtr> to_visit;

    for (to_visit.push(this->m_root); !to_visit.is_empty();) {
        const NodePtr node = to_visit.top();
        to_visit.pop();
        if (node == nullptr) {
            continue;
        }
        function(node->value);
        to_visit.push(node->m_right);
        to_visit.push(node->m_left);
    }
}

template<typename T>
void Tree<T>::PostorderScanner::apply(const std::function<void(const T&)>& function) const {
    enum class NextVisit {
        LEFT,
        RIGHT,
        SELF
    };

    Stack<std::pair<NodePtr, NextVisit>> to_visit;
    to_visit.push(std::make_pair(this->m_root, NextVisit::LEFT));

    while (not to_visit.is_empty()) {
        const std::pair<NodePtr, NextVisit> node_visit = to_visit.top();
        to_visit.pop();

        const NodePtr& node = node_visit.first;
        if (node == nullptr) {
            continue;
        }

        switch (node_visit.second) {
        case NextVisit::LEFT:
            to_visit.push(std::make_pair(node, NextVisit::RIGHT));
            to_visit.push(std::make_pair(node->m_left, NextVisit::LEFT));
            break;
        case NextVisit::RIGHT:
            to_visit.push(std::make_pair(node, NextVisit::SELF));
            to_visit.push(std::make_pair(node->m_right, NextVisit::LEFT));
            break;
        case NextVisit::SELF:
            function(node->value);
            break;
        }
    }
}

template<typename T>
void Tree<T>::InorderScanner::apply(const std::function<void(const T&)>& function) const {
    Stack<NodePtr> to_visit;
    NodePtr current = this->m_root;

    while (current != nullptr or not to_visit.is_empty()) {
        while (current != nullptr) {
            to_visit.push(current);
            current = current->m_left;
        }

        assert(current == nullptr);
        if (not to_visit.is_empty()) {
            current = to_visit.top();
            to_visit.pop();
            function(current->value);
            current = current->m_right;
        }
    }
}

template<typename T>
void Tree<T>::BFSScanner::apply(const std::function<void(const T&)>& function) const {
    Queue<NodePtr> queue;

    for (queue.enqueue(this->m_root); !queue.is_empty(); queue.dequeue()) {
        const NodePtr& node = queue.next();
        if (node == nullptr) {
            continue;
        }
        function(node->value);
        queue.enqueue(node->m_left);
        queue.enqueue(node->m_right);
    }
}

template<typename T>
template<typename Container>
Container Tree<T>::Scanner::collect() {
    Container container;
    apply([&](const T& item) { container.push_back(item); });
    return container;
}

#endif //DATASTRUCTURES_ALGORITHMS_TREE_HPP
