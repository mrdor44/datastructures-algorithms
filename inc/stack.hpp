//
// Created by dor on 02/07/2020.
//

#ifndef DATASTRUCTURES_ALGORITHMS_STACK_HPP
#define DATASTRUCTURES_ALGORITHMS_STACK_HPP

#include "list.hpp"

template<typename T>
class Stack {
public:
    Stack() = default;
    virtual ~Stack() = default;

    void push(const T&);
    void pop();
    const T& top() const;

private:
    List<T> m_list;
};

template<typename T>
void Stack<T>::push(const T& value) {
    m_list.push_front(value);
}

template<typename T>
void Stack<T>::pop() {
    m_list.pop_front();
}

template<typename T>
const T& Stack<T>::top() const {
    return m_list.front();
}

#endif //DATASTRUCTURES_ALGORITHMS_STACK_HPP
