//
// Created by dor on 24/07/2020.
//

#ifndef DATASTRUCTURES_ALGORITHMS_ARRAY_LIST_HPP
#define DATASTRUCTURES_ALGORITHMS_ARRAY_LIST_HPP

#include <memory>
#include <initializer_list>
#include <cassert>

template<typename T>
class ArrayListConstIterator;

template<typename T>
class ArrayList {
public:
    static const int DEFAULT_INITIAL_CAPACITY;

public:
    ArrayList(int initial_capacity = DEFAULT_INITIAL_CAPACITY,
              int min_capacity = DEFAULT_INITIAL_CAPACITY);
    ArrayList(const std::initializer_list<T>&);
    template<typename Iterator>
    ArrayList(const Iterator&,
              const Iterator&,
              int initial_capacity = DEFAULT_INITIAL_CAPACITY,
              int min_capacity = DEFAULT_INITIAL_CAPACITY);
    virtual ~ArrayList() = default;
    ArrayList(const ArrayList&);
    ArrayList(ArrayList&&) noexcept = default;
    ArrayList& operator=(ArrayList);

    // Insertion & Removal
    void push_back(const T&);
    template<typename Iterator>
    void push_back(Iterator, const Iterator&);
    void pop_back();

    // Retrieval
    [[nodiscard]] const T& back() const;
    [[nodiscard]] const T& operator[](int) const;
    [[nodiscard]] T& operator[](int);

    // Status
    [[nodiscard]] int length() const;
    [[nodiscard]] int capacity() const;

    // Iteration
    [[nodiscard]] ArrayListConstIterator<T> begin() const;
    [[nodiscard]] ArrayListConstIterator<T> end() const;
    [[nodiscard]] ArrayListConstIterator<T> cbegin() const;
    [[nodiscard]] ArrayListConstIterator<T> cend() const;

public:
    template<typename S>
    friend void swap(ArrayList<S>&, ArrayList<S>&) noexcept;

private:
    std::unique_ptr<T[]> m_array;
    int m_length{};
    int m_capacity{};
    int m_min_capacity{};

private:
    void extend();
    void shrink();
};

template<typename T>
const int ArrayList<T>::DEFAULT_INITIAL_CAPACITY = 4;

template<typename T>
bool operator==(const ArrayList<T>&, const ArrayList<T>&);

template<typename T>
void swap(ArrayList<T>&, ArrayList<T>&) noexcept;

template<typename T>
class ArrayListConstIterator {
private:
    ArrayListConstIterator(const ArrayList<T>&, int position);

public:
    ArrayListConstIterator() = default;
    ArrayListConstIterator(const ArrayListConstIterator&) = default;
    ArrayListConstIterator(ArrayListConstIterator&&) noexcept = default;
    virtual ~ArrayListConstIterator() = default;
    ArrayListConstIterator& operator=(const ArrayListConstIterator&) = default;
    ArrayListConstIterator& operator=(ArrayListConstIterator&&) = default;

public:
    using difference_type = int;
    using value_type = T;
    using pointer = T*;
    using reference = const value_type&;
    using iterator_category = std::random_access_iterator_tag;

public:
    ArrayListConstIterator& operator++();
    ArrayListConstIterator operator++(int);
    ArrayListConstIterator& operator--();
    ArrayListConstIterator operator--(int);
    const T& operator*() const;
    const T* operator->() const;
    ArrayListConstIterator& operator+=(difference_type);
    difference_type operator-(const ArrayListConstIterator&);
    ArrayListConstIterator& operator-=(difference_type);
    reference operator[](difference_type) const;

public:
    friend class ArrayList<T>;
    template<typename S>
    friend bool operator==(const ArrayListConstIterator<S>&, const ArrayListConstIterator<S>&);

private:
    const ArrayList<T>* m_array;
    difference_type m_position;
};

template<typename T>
bool operator==(const ArrayListConstIterator<T>&, const ArrayListConstIterator<T>&);

template<typename T>
bool operator!=(const ArrayListConstIterator<T>&, const ArrayListConstIterator<T>&);

template<typename T>
bool operator<(const ArrayListConstIterator<T>&, const ArrayListConstIterator<T>&);

template<typename T>
bool operator>(const ArrayListConstIterator<T>&, const ArrayListConstIterator<T>&);

template<typename T>
bool operator<=(const ArrayListConstIterator<T>&, const ArrayListConstIterator<T>&);

template<typename T>
bool operator>=(const ArrayListConstIterator<T>&, const ArrayListConstIterator<T>&);

template<typename T>
ArrayListConstIterator<T> operator+(ArrayListConstIterator<T>, typename ArrayListConstIterator<T>::difference_type);

template<typename T>
ArrayListConstIterator<T> operator+(typename ArrayListConstIterator<T>::difference_type, ArrayListConstIterator<T>);

template<typename T>
ArrayListConstIterator<T> operator-(ArrayListConstIterator<T>, typename ArrayListConstIterator<T>::difference_type);

template<typename T>
typename ArrayListConstIterator<T>::difference_type operator-(const ArrayListConstIterator<T>&,
                                                              const ArrayListConstIterator<T>&);

template<typename T>
void swap(ArrayListConstIterator<T>&, ArrayListConstIterator<T>&) noexcept;

template<typename T>
ArrayList<T>::ArrayList(int initial_capacity, int min_capacity):
        m_array(new T[initial_capacity]),
        m_length(0),
        m_capacity(initial_capacity),
        m_min_capacity(min_capacity) {}

template<typename T>
ArrayList<T>::ArrayList(const std::initializer_list<T>& list) :
        ArrayList(list.begin(), list.end(), DEFAULT_INITIAL_CAPACITY) {}

template<typename T>
template<typename Iterator>
ArrayList<T>::ArrayList(const Iterator& begin, const Iterator& end, int initial_capacity, int min_capacity) :
        ArrayList(initial_capacity, min_capacity) {
    push_back(begin, end);
}

template<typename T>
ArrayList<T>::ArrayList(const ArrayList& other) :
        ArrayList(other.begin(), other.end(), 1.5 * other.capacity(), other.m_min_capacity) {}

template<typename T>
ArrayList<T>& ArrayList<T>::operator=(ArrayList<T> rhs) {
    swap(*this, rhs);
    return *this;
}

template<typename T>
void ArrayList<T>::push_back(const T& value) {
    if (m_length == capacity()) {
        extend();
    }
    m_array[m_length] = value;
    ++m_length;
}

template<typename T>
template<typename Iterator>
void ArrayList<T>::push_back(Iterator begin, const Iterator& end) {
    for (; begin != end; ++begin) {
        push_back(*begin);
    }
}

template<typename T>
void ArrayList<T>::pop_back() {
    --m_length;
    m_array[m_length] = T();
    if (capacity() == m_min_capacity) {
        // If we're at minimal capacity, we don't want to shrink
        return;
    }
    assert(capacity() > m_min_capacity);
    assert(capacity() / 2 >= m_min_capacity);
    if (m_length < capacity() / 2) {
        shrink();
    }
}

template<typename T>
const T& ArrayList<T>::back() const {
    return m_array[m_length - 1];
}

template<typename T>
const T& ArrayList<T>::operator[](int index) const {
    return m_array[index];
}

template<typename T>
T& ArrayList<T>::operator[](int index) {
    return m_array[index];
}

template<typename T>
int ArrayList<T>::length() const {
    return m_length;
}

template<typename T>
int ArrayList<T>::capacity() const {
    return m_capacity;
}

template<typename T>
ArrayListConstIterator<T> ArrayList<T>::begin() const {
    return ArrayListConstIterator<T>(*this, 0);
}

template<typename T>
ArrayListConstIterator<T> ArrayList<T>::end() const {
    return ArrayListConstIterator<T>(*this, m_length);
}

template<typename T>
ArrayListConstIterator<T> ArrayList<T>::cbegin() const {
    return ArrayListConstIterator<T>(*this, 0);
}

template<typename T>
ArrayListConstIterator<T> ArrayList<T>::cend() const {
    return ArrayListConstIterator<T>(*this, m_length);
}

template<typename T>
void ArrayList<T>::extend() {
    *this = ArrayList<T>(cbegin(), cend(), 2 * m_capacity, m_min_capacity);
}

template<typename T>
void ArrayList<T>::shrink() {
    *this = ArrayList<T>(cbegin(), cend(), m_capacity / 2, m_min_capacity);
}

template<typename T>
bool operator==(const ArrayList<T>& lhs, const ArrayList<T>& rhs) {
    if (lhs.length() != rhs.length()) {
        return false;
    }
    auto it1 = lhs.cbegin();
    auto it2 = rhs.cbegin();
    for (; it1 != lhs.cend(); ++it1, ++it2) {
        assert(it2 != rhs.cend());
        if (*it1 != *it2) {
            return false;
        }
    }
    return true;
}

template<typename T>
void swap(ArrayList<T>& lhs, ArrayList<T>& rhs) noexcept {
    std::swap(lhs.m_array, rhs.m_array);
    std::swap(lhs.m_length, rhs.m_length);
    std::swap(lhs.m_capacity, rhs.m_capacity);
    std::swap(lhs.m_min_capacity, rhs.m_min_capacity);
}

template<typename T>
ArrayListConstIterator<T>::ArrayListConstIterator(const ArrayList<T>& array, int position) :
        m_array(&array),
        m_position(position) {}

template<typename T>
ArrayListConstIterator<T>& ArrayListConstIterator<T>::operator++() {
    ++m_position;
    return *this;
}

template<typename T>
ArrayListConstIterator<T> ArrayListConstIterator<T>::operator++(int) {
    ArrayListConstIterator<T> before = *this;
    ++m_position;
    return before;
}

template<typename T>
ArrayListConstIterator<T>& ArrayListConstIterator<T>::operator--() {
    --m_position;
    return *this;
}

template<typename T>
ArrayListConstIterator<T> ArrayListConstIterator<T>::operator--(int) {
    ArrayListConstIterator<T> before = *this;
    --m_position;
    return before;
}

template<typename T>
const T& ArrayListConstIterator<T>::operator*() const {
    return (*m_array)[m_position];
}

template<typename T>
const T* ArrayListConstIterator<T>::operator->() const {
    return &(*m_array)[m_position];
}

template<typename T>
ArrayListConstIterator<T>& ArrayListConstIterator<T>::operator+=(difference_type distance) {
    m_position += distance;
    return *this;
}

template<typename T>
typename ArrayListConstIterator<T>::difference_type
ArrayListConstIterator<T>::operator-(const ArrayListConstIterator<T>& rhs) {
    return m_position - rhs.m_position;
}

template<typename T>
ArrayListConstIterator<T>& ArrayListConstIterator<T>::operator-=(difference_type distance) {
    m_position -= distance;
    return *this;
}

template<typename T>
typename ArrayListConstIterator<T>::reference
ArrayListConstIterator<T>::operator[](typename ArrayListConstIterator::difference_type distance) const {
    return *(*this + distance);
}

template<typename T>
bool operator==(const ArrayListConstIterator<T>& lhs, const ArrayListConstIterator<T>& rhs) {
    return lhs.m_array == rhs.m_array &&
           lhs.m_position == rhs.m_position;
}

template<typename T>
bool operator!=(const ArrayListConstIterator<T>& lhs, const ArrayListConstIterator<T>& rhs) {
    return !(lhs == rhs);
}

template<typename T>
bool operator<(const ArrayListConstIterator<T>& lhs, const ArrayListConstIterator<T>& rhs) {
    return rhs - lhs > 0;
}

template<typename T>
bool operator>(const ArrayListConstIterator<T>& lhs, const ArrayListConstIterator<T>& rhs) {
    return rhs < lhs;
}

template<typename T>
bool operator<=(const ArrayListConstIterator<T>& lhs, const ArrayListConstIterator<T>& rhs) {
    return !(lhs < rhs);
}

template<typename T>
bool operator>=(const ArrayListConstIterator<T>& lhs, const ArrayListConstIterator<T>& rhs) {
    return !(lhs > rhs);
}

template<typename T>
ArrayListConstIterator<T> operator+(ArrayListConstIterator<T> it,
                                    typename ArrayListConstIterator<T>::difference_type distance) {
    return it += distance;
}

template<typename T>
ArrayListConstIterator<T> operator+(typename ArrayListConstIterator<T>::difference_type distance,
                                    ArrayListConstIterator<T> it) {
    return it + distance;
}

template<typename T>
ArrayListConstIterator<T> operator-(ArrayListConstIterator<T> it,
                                    typename ArrayListConstIterator<T>::difference_type distance) {
    return it -= distance;
}

template<typename T>
typename ArrayListConstIterator<T>::difference_type operator-(const ArrayListConstIterator<T>& lhs,
                                                              const ArrayListConstIterator<T>& rhs) {
    return lhs.operator-(rhs);
}

template<typename T>
void swap(ArrayListConstIterator<T>& lhs, ArrayListConstIterator<T>& rhs) noexcept {
    std::swap(lhs.m_array, rhs.m_array);
    std::swap(lhs.m_position, rhs.m_position);
}

#endif //DATASTRUCTURES_ALGORITHMS_ARRAY_LIST_HPP
