#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T>{

    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;

public:
    // Constructors + Big 5
    ABQ();
    explicit ABQ(const size_t capacity);
    ABQ(const ABQ& other);
    ABQ& operator=(const ABQ& rhs);
    ABQ(ABQ&& other) noexcept;
    ABQ& operator=(ABQ&& rhs) noexcept;
    ~ABQ() noexcept override;

    // Getters
    [[nodiscard]] size_t getSize() const noexcept override;
    [[nodiscard]] size_t getMaxCapacity() const noexcept;

    void PrintForward() const;
    void PrintReverse() const;

    // Insertion
    void enqueue(const T& data) override;

    // Access
    T peek() const override;

    // Deletion
    T dequeue() override;

    void resize();
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
ABQ<T>::ABQ() : capacity_(1), curr_size_(0), array_(new T[1     ]){}

template<typename T>
void ABQ<T>::enqueue(const T& data) {
    if (++curr_size_ > capacity_)
        resize();
    for (int i = curr_size_-2; i > 0; i++)
        array_[i + 1] = array_[i];
    array_[0] = data;
}

template<typename T>
ABQ<T>::ABQ(const size_t capacity) : capacity_(capacity), curr_size_(0), array_(new T[capacity]) {}

template<typename T>
ABQ<T>& ABQ<T>::operator=(const ABQ<T>& rhs) {
    if (this == &rhs)
        return *this;

    this -> capacity_ = rhs.capacity_;
    delete[] this -> array_;

    this -> array_ = new T[capacity_];

    for (int i = 0; i < rhs.curr_size_; i++) {
        array_[i] = rhs.array_[i];
    }

    return *this;
}

template<typename T>
ABQ<T>::ABQ(const ABQ& other) : capacity_(other.capacity_), curr_size_(0), array_(new T[other.capacity]) {
    for (int i = 0; i < other.curr_size_; i++) {
        this -> push(other.array_[i]);
    }
}

template<typename T>
ABQ<T>::ABQ(ABQ&& other) noexcept : capacity_(other.capacity_), curr_size_(other.curr_size_), array_(other.array_) {
    other.capacity_ = 0;
    other.curr_size_ = 0;
    other.array_ = nullptr;
}

template<typename T>
ABQ<T>& ABQ<T>::operator=(ABQ&& rhs) noexcept {
    if (this == &rhs)
        return *this;

    delete[] array_;

    this -> capacity_ = rhs.capacity_;
    this -> curr_size_ = rhs.curr_size_;
    this -> array_ = rhs.array_;

    rhs.capacity_ = 0;
    rhs.curr_size_ = 0;
    array_ = nullptr;

    return *this;
}

template<typename T>
ABQ<T>::~ABQ() noexcept {
    delete[] array_;
    capacity_ = 0;
    curr_size_ = 0;
}

template<typename T>
[[nodiscard]] size_t ABQ<T>::getSize() const noexcept {
    return curr_size_;
}

template<typename T>
[[nodiscard]] size_t ABQ<T>::getMaxCapacity() const noexcept {
    return capacity_;
}
