#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLQ : public QueueInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLQ();

    // Insertion
    void enqueue(const T& item) override;

    // Deletion
    T dequeue() override;

    // Access
    T peek() const override;

    // Getter
    std::size_t getSize() const noexcept override;

};


template<typename T>
LLQ<T>::LLQ() : list(LinkedList<T>()) {}

template<typename T>
void LLQ<T>::enqueue(const T& item) {
    list.addHead(item);
}

template<typename T>
T LLQ<T>::dequeue() {
    if (list.getCount() == 0)
        throw std::runtime_error("no elements");
    T temp = list.getTail() -> data;
    list.removeTail();
    return temp;
}

template<typename T>
T LLQ<T>::peek() const {
    if (list.getCount() == 0)
        throw std::runtime_error("no elements");
    T temp = list.getTail() -> data;
    return temp;
}

template<typename T>
std::size_t LLQ<T>::getSize() const noexcept {
    return list.getCount();
}