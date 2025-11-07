#pragma once

#include <cstddef>
#include <stdexcept>


template <typename T>
class StackInterface {
public:
    virtual void push(const T& item);
    virtual T pop();
    virtual T peek() const;
    [[nodiscard]] virtual std::size_t getSize() const noexcept;
    virtual ~StackInterface() = 0;
};

template <typename T>
StackInterface<T>::~StackInterface() {}

template <typename T>
class QueueInterface {
public:
    virtual void enqueue(const T& item);
    virtual T dequeue();
    virtual T peek() const;
    virtual std::size_t getSize() const noexcept;
    virtual ~QueueInterface() = 0;
};

template <typename T>
QueueInterface<T>::~QueueInterface() {}

template <typename T>
class DequeInterface {
public:
    virtual void pushFront(const T& item);
    virtual void pushBack(const T& item);
    virtual T popFront();
    virtual T popBack();
    virtual const T& front() const;
    virtual const T& back() const;
    virtual std::size_t getSize() const noexcept;
    virtual ~DequeInterface() = 0;
};

template <typename T>
DequeInterface<T>::~DequeInterface() {}