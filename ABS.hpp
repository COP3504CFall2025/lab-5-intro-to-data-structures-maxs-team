#pragma once

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
public:
    // Big 5 + Parameterized Constructor
    ABS();
    explicit ABS(const size_t capacity);
    ABS(const ABS& other);
    ABS& operator=(const ABS& rhs);
    ABS(ABS&& other) noexcept;
    ABS& operator=(ABS&& rhs) noexcept;
    ~ABS() noexcept override;

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override;

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept;

    void PrintForward() const;
    void PrintReverse() const;

    // Push item onto the stack
    void push(const T& data) override;

    T peek() const override;

    T pop() override;

    void resize(int cap);

private:
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;
};

template<typename T>
void ABS<T>::resize(int cap) {
    if (cap == 0)
        capacity_++;
    else
        capacity_ = cap;
    T* new_arr = new T[capacity_];
    for (int i = 0; static_cast<size_t>(i) < curr_size_; i++) {
        new_arr[i] = array_[i];
    }
    delete[] array_;
    array_ = new_arr;
}

template<typename T>
ABS<T>::ABS() : capacity_(1), curr_size_(0), array_(new T[1]){}

template<typename T>
void ABS<T>::push(const T& data) {
    if (curr_size_ >= capacity_)
        resize(capacity_*scale_factor_);
    array_[curr_size_++] = data;
}

template<typename T>
ABS<T>::ABS(const size_t capacity) : capacity_(capacity), curr_size_(0), array_(new T[capacity]) {}

template<typename T>
ABS<T>& ABS<T>::operator=(const ABS<T>& rhs) {
    if (this == &rhs)
        return *this;

    this -> capacity_ = rhs.capacity_;
    delete[] this -> array_;

    this -> array_ = new T[capacity_];

    for (int i = 0; i < rhs.curr_size_; i++) {
        this -> push(rhs.array_[i]);
    }

    return *this;
}

template<typename T>
ABS<T>::ABS(const ABS& other) : capacity_(other.capacity_), curr_size_(0), array_(new T[0]) {
    for (int i = 0; i < other.curr_size_; i++) {
        this -> push(other.array_[i]);
    }
}

template<typename T>
ABS<T>::ABS(ABS&& other) noexcept : capacity_(other.capacity_), curr_size_(other.curr_size_), array_(other.array_) {
    other.capacity_ = 0;
    other.curr_size_ = 0;
    other.array_ = nullptr;
}

template<typename T>
ABS<T>& ABS<T>::operator=(ABS&& rhs) noexcept {
    if (this == &rhs)
        return *this;

    delete[] this -> array_;

    this -> capacity_ = rhs.capacity_;
    this -> curr_size_ = rhs.curr_size_;
    this -> array_ = rhs.array_;

    rhs.capacity_ = 0;
    rhs.curr_size_ = 0;
    rhs.array_ = nullptr;

    return *this;
}

template<typename T>
ABS<T>::~ABS() noexcept {
    delete[] this -> array_;
    capacity_ = 0;
    curr_size_ = 0;
}

template<typename T>
[[nodiscard]] size_t ABS<T>::getSize() const noexcept {
    return curr_size_;
}

template<typename T>
[[nodiscard]] size_t ABS<T>::getMaxCapacity() const noexcept {
    return capacity_;
}

template<typename T>
void ABS<T>::PrintForward() const {
    for (int i = 0; i < curr_size_; i++) {
        std::cout << array_[i] << std::endl;
    }
}

template<typename T>
void ABS<T>::PrintReverse() const {
    for (int i = curr_size_ - 1; i >= 0; i--) {
        std::cout << array_[i] << std::endl;
    }
}

template<typename T>
T ABS<T>::peek() const {
    if (curr_size_ == 0)
        throw std::runtime_error("No elements in the array");
    return array_[curr_size_ - 1];
}

template<typename T>
T ABS<T>::pop() {
    if (curr_size_ == 0)
        throw std::runtime_error("No elements in the array");
    T data = array_[--curr_size_] ;
    array_[curr_size_] = 0;
    if (curr_size_ <= capacity_/scale_factor_)
        resize(capacity_/scale_factor_);
    return data;
}