#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;                 // underlying dynamic array
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_ = 0;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

public:
    // Big 5
    ABDQ();
    explicit ABDQ(std::size_t capacity);
    ABDQ(const ABDQ& other);
    ABDQ(ABDQ&& other) noexcept;
    ABDQ& operator=(const ABDQ& rhs);
    ABDQ& operator=(ABDQ&& rhs) noexcept;
    ~ABDQ() override;

    // Insertion
    void pushFront(const T& item) override;
    void pushBack(const T& item) override;

    // Deletion
    T popFront() override;
    T popBack() override;

    // Access
    const T& front() const override;
    const T& back() const override;

    void PrintForward() const;
    void PrintReverse() const;

    void resize(int cap);

    // Getters
    std::size_t getSize() const noexcept override;

};

template<typename T>
void ABDQ<T>::resize(int cap) {
    if (cap == 0)
        capacity_++;
    else
        capacity_ = cap;
    T* new_arr = new T[capacity_];
    for (int i = 0; static_cast<size_t>(i) < size_; i++) {
        new_arr[i] = data_[i];
    }
    delete[] data_;
    data_ = new_arr;
}

template<typename T>
const T& ABDQ<T>::front() const {
    return front_;
}

template<typename T>
const T& ABDQ<T>::back() const {
    return back_;
}

template<typename T>
std::size_t ABDQ<T>::getSize() const noexcept {
    return size_;
}

template<typename T>
ABDQ<T>::ABDQ() : capacity_(4), size_(0), data_(new T[4]), front_(0), back_(0) {}

template<typename T>
ABDQ<T>::ABDQ(const size_t capacity) : capacity_(capacity), size_(0), data_(new T[capacity]), front_(0), back_(0) {}

template<typename T>
ABDQ<T>& ABDQ<T>::operator=(const ABDQ<T>& rhs) {
    if (this == &rhs)
        return *this;

    this -> capacity_ = rhs.capacity_;
    this -> size_ = rhs.size_;
    this -> front_ = rhs.front_;
    this -> back_ = rhs.back_;

    delete[] this -> data_;
    this -> data_ = new T[capacity_];

    for (int i = 0; i < rhs.size_; i++) {
        data_[i] = rhs.data_[i];
    }

    return *this;
}

template<typename T>
ABDQ<T>::ABDQ(const ABDQ& other) : capacity_(other.capacity_), size_(other.size_), data_(new T[other.capacity_]), front_(other.front_), back_(other.back_) {
    for (int i = 0; i < other.size_; i++) {
        this -> data_[i] = (other.data_[i]);
    }
}

template<typename T>
ABDQ<T>::ABDQ(ABDQ&& other) noexcept : capacity_(other.capacity_), size_(other.size_), data_(other.data_), front_(other.front_), back_(other.back_) {
    other.capacity_ = 0;
    other.size_ = 0;
    other.front_ = 0;
    other.back_ = 0;
    other.data_ = nullptr;
}

template<typename T>
ABDQ<T>& ABDQ<T>::operator=(ABDQ&& rhs) noexcept {
    if (this == &rhs)
        return *this;

    delete[] data_;

    this -> capacity_ = rhs.capacity_;
    this -> size_ = rhs.size_;
    this -> data_ = rhs.data_;
    this -> front_ = rhs.front_;
    this -> back_ = rhs.back_;

    rhs.capacity_ = 0;
    rhs.size_ = 0;
    rhs.front_ = 0;
    rhs.back_ = 0;
    rhs.data_ = nullptr;

    return *this;
}

template<typename T>
ABDQ<T>::~ABDQ() {
    delete[] data_;
    front_ = 0;
    back_ = 0;
    capacity_ = 0;
    size_ = 0;
}

template<typename T>
void ABDQ<T>::PrintForward() const {
    for (int i = 0; i < size_; i++) {
        std::cout << data_[i] << std::endl;
    }
}

template<typename T>
void ABDQ<T>::PrintReverse() const {
    for (int i = size_ - 1; i >= 0; i--) {
        std::cout << data_[i] << std::endl;
    }
}

template<typename T>
void ABDQ<T>::pushFront(const T& item) {
    if (size_ + 1 >= capacity_)
        resize(capacity_*2);
    for (int i = size_-1; i >= 0; i--)
        data_[i+1] = data_[i];

    size_++;
    back_++;
    data_[0] = item;
}

template<typename T>
void ABDQ<T>::pushBack(const T& item) {
    if (size_ >= capacity_)
        resize(capacity_*2);
    data_[back_++] = item;
    size_++;
}

template<typename T>
T ABDQ<T>::popFront() {
    if (size_ == 0)
        throw std::runtime_error("No elements in the array");
    T item = data_[0];
    for (int i = --size_; i >= 1; i--)
        data_[i-1] = data_[i];
    data_[size_] = 0;
    if (size_*4 <= capacity_)
        resize(capacity_/2);
    back_--;
    return item;
}

template<typename T>
T ABDQ<T>::popBack() {
    if (size_ == 0)
        throw std::runtime_error("No elements in the array");
    T item = data_[--size_] ;
    data_[size_] = 0;
    if (size_*4 <= capacity_)
        resize(capacity_/2);
    back_--;
    return item;
}