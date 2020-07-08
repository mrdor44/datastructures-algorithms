//
// Created by dor on 09/06/2020.
//

#ifndef DATASTRUCTURES_ALGORITHMS_LIST_HPP
#define DATASTRUCTURES_ALGORITHMS_LIST_HPP

#include <memory>
#include <stdexcept>
#include <sstream>

template<typename T>
class List {
public:
    List();
    virtual ~List();

    void push_front(const T&);
    void pop_front();
    void push_back(const T&);
    void pop_back();

    void insert(int index, const T&);
    void erase(int index);
    void clear();
    [[nodiscard]] int length() const;
    [[nodiscard]] bool is_empty() const;

    const T& operator[](int) const;
    const T& front() const;
    const T& back() const;

    struct Node;
    using NodePtr = std::shared_ptr<Node>;

    class const_iterator {
    protected:
        explicit const_iterator(const NodePtr&);

    public:
        virtual ~const_iterator() = default;

        bool operator!=(const const_iterator&) const;
        const_iterator& operator++();
        const T& operator*() const;

        friend class List<T>;

    private:
        NodePtr m_node;
    };

    const_iterator begin() const;
    const_iterator end() const;

    struct Node {
        T value;
        NodePtr next;
        NodePtr prev;

        Node() = default;
        Node(const T& value, const NodePtr& next, const NodePtr& prev);
    };

private:
    NodePtr m_first_dummy;
    NodePtr m_last_dummy;
    int m_length;

private:
    NodePtr get_node(int) const;
    void insert_before(const NodePtr& node, const T& value);
    void erase(const NodePtr);
};

template<typename T>
bool operator==(const List<T>& list1, const List<T>& list2) {
    if (list1.length() != list2.length()) {
        return false;
    }
    auto e1 = list1.begin();
    auto e2 = list2.begin();
    for (int i = 0; i < list1.length(); ++i) {
        if (*e1 != *e2) {
            return false;
        }
    }
    return true;
}

template<typename T>
List<T>::Node::Node(const T& value, const NodePtr& next, const NodePtr& prev)
        : value(value), next(next), prev(prev) {}

template<typename T>
List<T>::List() :
        m_first_dummy(std::make_shared<Node>()),
        m_last_dummy(std::make_shared<Node>()),
        m_length(0) {
    m_first_dummy->next = m_last_dummy;
    m_last_dummy->prev = m_first_dummy;
}

template<typename T>
List<T>::~List() {
    clear();
}

template<typename T>
List<T>::const_iterator::const_iterator(const List::NodePtr& node) : m_node(node) {}

template<typename T>
void List<T>::push_front(const T& value) {
    insert(0, value);
}

template<typename T>
void List<T>::pop_front() {
    erase(0);
}

template<typename T>
void List<T>::push_back(const T& value) {
    insert_before(m_last_dummy, value);
}

template<typename T>
void List<T>::pop_back() {
    erase(m_last_dummy->prev);
}

template<typename T>
void List<T>::insert(int index, const T& value) {
    if (index > m_length) {
        std::ostringstream message;
        message << "insert(" << index << "), m_length=" << m_length;
        throw std::out_of_range(message.str());
    }
    insert_before(get_node(index), value);
}

template<typename T>
void List<T>::erase(int index) {
    if (index >= m_length) {
        std::ostringstream message;
        message << "erase(" << index << "), m_length=" << m_length;
        throw std::out_of_range(message.str());
    }
    erase(get_node(index));
}

template<typename T>
void List<T>::clear() {
    while (length() > 0) {
        erase(0);
    }
}

template<typename T>
int List<T>::length() const {
    return m_length;
}

template<typename T>
bool List<T>::is_empty() const {
    return length() == 0;
}

template<typename T>
const T& List<T>::operator[](int index) const {
    return get_node(index)->value;
}

template<typename T>
const T& List<T>::front() const {
    return (*this)[0];
}

template<typename T>
const T& List<T>::back() const {
    return m_last_dummy->prev->value;
}

template<typename T>
bool List<T>::const_iterator::operator!=(const List::const_iterator& other) const {
    return m_node != other.m_node;
}

template<typename T>
typename List<T>::const_iterator& List<T>::const_iterator::operator++() {
    m_node = m_node->next;
    return *this;
}

template<typename T>
const T& List<T>::const_iterator::operator*() const {
    return m_node->value;
}

template<typename T>
typename List<T>::const_iterator List<T>::begin() const {
    return const_iterator(m_first_dummy->next);
}

template<typename T>
typename List<T>::const_iterator List<T>::end() const {
    return const_iterator(m_last_dummy);
}

template<typename T>
typename List<T>::NodePtr List<T>::get_node(int index) const {
    NodePtr node = m_first_dummy->next;
    for (int i = 0; i < index; ++i) {
        node = node->next;
    }
    return node;
}

template<typename T>
void List<T>::insert_before(const NodePtr& node, const T& value) {
    NodePtr new_node = std::make_shared<Node>(value, node, node->prev);
    node->prev = new_node;
    new_node->prev->next = new_node;
    ++m_length;
}

template<typename T>
void List<T>::erase(const NodePtr node) {
    node->next->prev = node->prev;
    node->prev->next = node->next;
    --m_length;
}

#endif //DATASTRUCTURES_ALGORITHMS_LIST_HPP
