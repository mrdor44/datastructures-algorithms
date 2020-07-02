//
// Created by dor on 02/07/2020.
//

#ifndef DATASTRUCTURES_ALGORITHMS_STACK_HPP
#define DATASTRUCTURES_ALGORITHMS_STACK_HPP

#include "list.hpp"

template<typename T>
class Queue {
public:
    Queue() = default;
    virtual ~Queue() = default;

    void enqueue(const T&);
    void dequeue();
    const T& next() const;

private:
    List<T> m_list;
};

template<typename T>
void Queue<T>::enqueue(const T& value) {
    m_list.push_back(value);
}

template<typename T>
void Queue<T>::dequeue() {
    m_list.pop_front();
}

template<typename T>
const T& Queue<T>::next() const {
    return m_list.front();
}

#endif //DATASTRUCTURES_ALGORITHMS_STACK_HPP
