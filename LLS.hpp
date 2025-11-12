#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLS : public StackInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLS();

    // Insertion
    void push(const T& item) override;

    // Deletion
    T pop() override;

    // Access
    T peek() const override;

    //Getters
    std::size_t getSize() const noexcept override;
};

template<typename T>
LLS<T>::LLS() : list(LinkedList<T>()) {}

template<typename T>
void LLS<T>::push(const T& item) {
    list.addTail(item);
}

template<typename T>
T LLS<T>::pop() {
    if (list.getCount() == 0)
        throw std::runtime_error("no elements");
    T temp = list.getTail() -> data;
    list.removeTail();
    return temp;
}

template<typename T>
T LLS<T>::peek() const {
    if (list.getCount() == 0)
        throw std::runtime_error("no elements");
    T temp = list.getTail() -> data;
    return temp;
}

template<typename T>
std::size_t LLS<T>::getSize() const noexcept {
    return list.getCount();
}