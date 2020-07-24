//
// Created by dor on 09/06/2020.
//

#ifndef DATASTRUCTURES_ALGORITHMS_LIST_HPP
#define DATASTRUCTURES_ALGORITHMS_LIST_HPP

#include <memory>
#include <stdexcept>
#include <sstream>
#include <initializer_list>
#include <cassert>

template<typename T>
class ListConstIterator;

template<typename T>
class List {
public:
    List();
    List(const std::initializer_list<T>&);
    template<typename Iterator>
    List(const Iterator& begin, const Iterator& end);
    List(const List&);
    List(List&&) noexcept;
    virtual ~List();
    List& operator=(List);

    void push_front(const T&);
    void pop_front();
    template<typename Iterator>
    void push_front(const Iterator& start, const Iterator& end);
    void push_back(const T&);
    template<typename Iterator>
    void push_back(Iterator begin, const Iterator& end);
    void pop_back();
    List& operator+=(const List&);

    void insert(int index, const T&);
    void erase(int index);
    void clear();
    [[nodiscard]] int length() const;
    [[nodiscard]] bool is_empty() const;

    const T& operator[](int) const;
    const T& front() const;
    const T& back() const;

    template<typename S>
    friend void swap(List<S>&, List<S>&) noexcept;

    // Iteration
    ListConstIterator<T> begin() const;
    ListConstIterator<T> end() const;
    ListConstIterator<T> cbegin() const;
    ListConstIterator<T> cend() const;

    // Node
    struct Node;
    using NodePtr = std::shared_ptr<Node>;

    struct Node {
        T value;
        NodePtr next;
        NodePtr prev;

        Node() = default;
        Node(const T& value, const NodePtr& next, const NodePtr& prev);

        Node(const Node&) = delete;
        Node& operator=(const Node&) = delete;
    };

private:
    NodePtr m_first_dummy;
    NodePtr m_last_dummy;
    int m_length{};

private:
    NodePtr get_node(int) const;
    void insert_before(const NodePtr& node, const T& value);
    void erase(const NodePtr);
};

template<typename T>
class ListConstIterator {
protected:
    explicit ListConstIterator(const typename List<T>::NodePtr&);

public:
    ListConstIterator(const ListConstIterator&) = default;
    ListConstIterator(ListConstIterator&&) noexcept = default;
    virtual ~ListConstIterator() = default;
    ListConstIterator& operator=(const ListConstIterator&) = default;
    ListConstIterator& operator=(ListConstIterator&&) noexcept = default;

    template<typename S>
    friend bool operator==(const ListConstIterator<S>&, const ListConstIterator<S>&);
    ListConstIterator& operator++();
    const T& operator*() const;

    friend class List<T>;

public:
    using difference_type = int;
    using value_type = T;
    using pointer = value_type*;
    using reference = value_type&;
    using iterator_category = std::input_iterator_tag;

private:
    typename List<T>::NodePtr m_node;
};

template<typename T>
void swap(List<T>& list1, List<T>& list2) noexcept;

template<typename T>
inline List<T> operator+(List<T>, const List<T>&);

template<typename T>
bool operator!=(const ListConstIterator<T>&, const ListConstIterator<T>&);

template<typename T>
bool operator==(const List<T>& list1, const List<T>& list2) {
    if (list1.length() != list2.length()) {
        return false;
    }
    auto e1 = list1.begin();
    auto e2 = list2.begin();
    for (; e1 != list1.end(); ++e1, ++e2) {
        assert(e2 != list2.end());
        if (*e1 != *e2) {
            return false;
        }
    }
    return true;
}

template<typename T>
bool operator!=(const List<T>& list1, const List<T>& list2) {
    return !(list1 == list2);
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
List<T>::List(const std::initializer_list<T>& list) : List(list.begin(), list.end()) {}

template<typename T>
template<typename Iterator>
List<T>::List(const Iterator& begin, const Iterator& end) : List() {
    push_back(begin, end);
}

template<typename T>
List<T>::List(const List& other) : List(other.begin(), other.end()) {}


template<typename T>
List<T>::List(List&& other) noexcept : List() {
    swap(*this, other);
}

template<typename T>
List<T>::~List() {
    clear();
}

template<typename T>
List<T>& List<T>::operator=(List<T> other) {
    swap(*this, other);
    return *this;
}

template<typename T>
ListConstIterator<T>::ListConstIterator(const typename List<T>::NodePtr& node) : m_node(node) {}

template<typename T>
void List<T>::push_front(const T& value) {
    insert(0, value);
}

template<typename T>
template<typename Iterator>
void List<T>::push_front(const Iterator& start, const Iterator& end) {
    List<T> new_elements(start, end);
    *this = new_elements + *this;
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
template<typename Iterator>
void List<T>::push_back(Iterator begin, const Iterator& end) {
    for (; begin != end; ++begin) {
        push_back(*begin);
    }
}

template<typename T>
void List<T>::pop_back() {
    erase(m_last_dummy->prev);
}

template<typename T>
List<T>& List<T>::operator+=(const List<T>& rhs) {
    push_back(rhs.begin(), rhs.end());
    return *this;
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
void swap(List<T>& list1, List<T>& list2) noexcept {
    std::swap(list1.m_first_dummy, list2.m_first_dummy);
    std::swap(list1.m_last_dummy, list2.m_last_dummy);
    std::swap(list1.m_length, list2.m_length);
}

template<typename T>
inline List<T> operator+(List<T> lhs, const List<T>& rhs) {
    return lhs += rhs;
}

template<typename T>
bool operator!=(const ListConstIterator<T>& lhs, const ListConstIterator<T>& rhs) {
    return !(lhs == rhs);
}

template<typename S>
bool operator==(const ListConstIterator<S>& lhs, const ListConstIterator<S>& rhs) {
    return lhs.m_node == rhs.m_node;
}

template<typename T>
ListConstIterator<T>& ListConstIterator<T>::operator++() {
    m_node = m_node->next;
    return *this;
}

template<typename T>
const T& ListConstIterator<T>::operator*() const {
    return m_node->value;
}

template<typename T>
ListConstIterator<T> List<T>::begin() const {
    return ListConstIterator<T>(m_first_dummy->next);
}

template<typename T>
ListConstIterator<T> List<T>::end() const {
    return ListConstIterator<T>(m_last_dummy);
}

template<typename T>
ListConstIterator<T> List<T>::cbegin() const {
    return ListConstIterator<T>(m_first_dummy->next);
}

template<typename T>
ListConstIterator<T> List<T>::cend() const {
    return ListConstIterator<T>(m_last_dummy);
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
#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedValue" // Clang mistakes this as unused
    new_node->prev->next = new_node;
#pragma clang diagnostic pop
    ++m_length;
}

template<typename T>
void List<T>::erase(const NodePtr node) {
    node->next->prev = node->prev;
#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedValue" // Clang mistakes this as unused
    node->prev->next = node->next;
#pragma clang diagnostic pop
    --m_length;
}

#endif //DATASTRUCTURES_ALGORITHMS_LIST_HPP
