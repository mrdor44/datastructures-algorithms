//
// Created by dor on 09/06/2020.
//

#ifndef DATASTRUCTURES_ALGORITHMS_LIST_HPP
#define DATASTRUCTURES_ALGORITHMS_LIST_HPP

#include <memory>
#include "node.hpp"

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

    const T& operator[](int) const;
    const T& front() const;

private:
    NodePtr<T> m_first_dummy;
    NodePtr<T> m_last_dummy;
    int m_length;

private:
    NodePtr<T> get_node(int) const;
    void insert_before(const NodePtr<T>& node, const T& value);
    void erase(const NodePtr<T>);
};

template<typename T>
List<T>::List() :
        m_first_dummy(std::make_shared<Node<T>>()),
        m_last_dummy(std::make_shared<Node<T>>()),
        m_length(0) {
    m_first_dummy->next = m_last_dummy;
    m_last_dummy->prev = m_first_dummy;
}

template<typename T>
List<T>::~List() {
    clear();
}

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
    insert_before(get_node(index), value);
}

template<typename T>
void List<T>::erase(int index) {
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
const T& List<T>::operator[](int index) const {
    return get_node(index)->value;
}

template<typename T>
const T& List<T>::front() const {
    return (*this)[0];
}

template<typename T>
NodePtr<T> List<T>::get_node(int index) const {
    NodePtr<T> node = m_first_dummy->next;
    for (int i = 0; i < index; ++i) {
        node = node->next;
    }
    return node;
}

template<typename T>
void List<T>::insert_before(const NodePtr<T>& node, const T& value) {
    NodePtr<T> new_node = std::make_shared<Node<T>>(value, node, node->prev);
    node->prev = new_node;
    new_node->prev->next = new_node;
    ++m_length;
}

template<typename T>
void List<T>::erase(const NodePtr<T> node) {
    node->next->prev = node->prev;
    node->prev->next = node->next;
    --m_length;
}

#endif //DATASTRUCTURES_ALGORITHMS_LIST_HPP
