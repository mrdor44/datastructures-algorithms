//
// Created by dor on 24/07/2020.
//

#ifndef DATASTRUCTURES_ALGORITHMS_ARRAY_LIST_HPP
#define DATASTRUCTURES_ALGORITHMS_ARRAY_LIST_HPP

#include <memory>

template<typename T>
class ArrayListConstIterator;

template<typename T>
class ArrayList {
public:
    static const int DEFAULT_INITIAL_CAPACITY;

public:
    explicit ArrayList(int initial_capacity = DEFAULT_INITIAL_CAPACITY);
    template<typename Iterator>
    ArrayList(const Iterator&, const Iterator&, int initial_capacity = DEFAULT_INITIAL_CAPACITY);
    virtual ~ArrayList() = default;
    ArrayList(const ArrayList&) = delete;
    ArrayList(ArrayList&&) noexcept = default;
    ArrayList& operator=(ArrayList);

    // Insertion & Removal
    void push_back(const T&);
    template<typename Iterator>
    void push_back(Iterator, const Iterator&);

    // Retrieval
    const T& operator[](int) const;
    T& operator[](int);

    // Iteration
    [[nodiscard]] ArrayListConstIterator<T> cbegin() const;
    [[nodiscard]] ArrayListConstIterator<T> cend() const;

public:
    template<typename S>
    friend void swap(ArrayList<S>&, ArrayList<S>&) noexcept;

private:
    std::unique_ptr<T[]> m_array;
    int m_length;
    int m_capacity;

private:
    void extend();
};

template<typename T>
const int ArrayList<T>::DEFAULT_INITIAL_CAPACITY = 4;

template<typename T>
void swap(ArrayList<T>&, ArrayList<T>&) noexcept;

template<typename T>
class ArrayListConstIterator {
private:
    ArrayListConstIterator(const ArrayList<T>&, int position);
    virtual ~ArrayListConstIterator() = default;

public:
    ArrayListConstIterator& operator++();
    const T& operator*() const;

public:
    friend class ArrayList<T>;
    template<typename S>
    friend bool operator==(const ArrayListConstIterator<S>&, const ArrayListConstIterator<S>&);

private:
    const ArrayList<T>& m_array;
    int m_position;
};

template<typename T>
bool operator==(const ArrayListConstIterator<T>&, const ArrayListConstIterator<T>&);

template<typename T>
bool operator!=(const ArrayListConstIterator<T>&, const ArrayListConstIterator<T>&);

template<typename T>
ArrayList<T>::ArrayList(int initial_capacity):
        m_array(new T[initial_capacity]),
        m_length(0),
        m_capacity(initial_capacity) {}

template<typename T>
template<typename Iterator>
ArrayList<T>::ArrayList(const Iterator& begin, const Iterator& end, int initial_capacity) :
        ArrayList(initial_capacity) {
    push_back(begin, end);
}

template<typename T>
ArrayList<T>& ArrayList<T>::operator=(ArrayList<T> rhs) {
    swap(*this, rhs);
    return *this;
}

template<typename T>
void ArrayList<T>::push_back(const T& value) {
    if (m_length == m_capacity) {
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
const T& ArrayList<T>::operator[](int index) const {
    return m_array[index];
}

template<typename T>
T& ArrayList<T>::operator[](int index) {
    return m_array[index];
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
    *this = ArrayList<T>(cbegin(), cend(), 2 * m_capacity);
}

template<typename T>
void swap(ArrayList<T>& lhs, ArrayList<T>& rhs) noexcept {
    std::swap(lhs.m_array, rhs.m_array);
    std::swap(lhs.m_length, rhs.m_length);
    std::swap(lhs.m_capacity, rhs.m_capacity);
}

template<typename T>
ArrayListConstIterator<T>::ArrayListConstIterator(const ArrayList<T>& array, int position) :
        m_array(array),
        m_position(position) {}

template<typename T>
ArrayListConstIterator<T>& ArrayListConstIterator<T>::operator++() {
    ++m_position;
    return *this;
}

template<typename T>
const T& ArrayListConstIterator<T>::operator*() const {
    return m_array[m_position];
}

template<typename T>
bool operator==(const ArrayListConstIterator<T>& lhs, const ArrayListConstIterator<T>& rhs) {
    return lhs.m_position == rhs.m_position;
}

template<typename T>
bool operator!=(const ArrayListConstIterator<T>& lhs, const ArrayListConstIterator<T>& rhs) {
    return !(lhs == rhs);
}

#endif //DATASTRUCTURES_ALGORITHMS_ARRAY_LIST_HPP
