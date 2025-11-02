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
    ABQ() : capacity_(1), curr_size_(0), array_(new T[capacity_]) {}
    explicit ABQ(const size_t capacity) : capacity_(capacity), curr_size_(0), array_(new T[capacity]) {}
    ABQ(const ABQ& other) : capacity_(other.getMaxCapacity()), curr_size_(other.getSize()), array_(new T[other.capacity_]) {
        for (size_t i = 0; i < other.getSize(); i++) {
            array_[i] = other.array_[i];
        }
    }
    ABQ& operator=(const ABQ& rhs) {
        if (this == &rhs) {
            return *this;
        }
        delete[] array_;
        array_ = new T[rhs.getMaxCapacity()];
        for (size_t i = 0; i < rhs.getSize(); i++) {
            array_[i] = rhs.array_[i];
        }
        capacity_ = rhs.getMaxCapacity();
        curr_size_ = rhs.getSize();
        return *this;
    }
    ABQ(ABQ&& other) noexcept : capacity_(other.capacity_), curr_size_(other.curr_size_), array_(other.array_) {
        other.capacity_ = 0;
        other.curr_size_ = 0;
        other.array_ = nullptr;
    
    }
    ABQ& operator=(ABQ&& rhs) noexcept {
        if (this == &rhs) {
            return *this;
        }
        delete[] array_;
        array_ = rhs.array_;
        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;

        rhs.capacity_ = 0;
        rhs.curr_size_ = 0;
        rhs.array_ = nullptr;
        return *this;

    }
    ~ABQ() noexcept {
        delete[] array_;
        capacity_ = 0;
        curr_size_ = 0;
    }

    // Getters
    [[nodiscard]] size_t getSize() const noexcept override {
        return curr_size_;
    }
    [[nodiscard]] size_t getMaxCapacity() const noexcept {
        return capacity_;
    }
    [[nodiscard]] T* getData() const noexcept {
        return array_;
    }

    // Insertion
    void enqueue(const T& data) override {
        if (capacity_ == curr_size_) {
            capacity_ *= scale_factor_;
            T* array2 = new T[capacity_];
            for (size_t i = 0; i < curr_size_; i++) {
                array2[i] = array_[i];
            }
            delete[] array_;
            array_ = array2;
        }
        array_[curr_size_] = data;
        curr_size_++;
    }

    // Access
    T peek() const override {
        if (curr_size_ == 0) {
            throw std::runtime_error("");
        }
        return array_[0];
    }

    // Deletion
    T dequeue() override {
        if (curr_size_ == 0) {
            throw std::runtime_error("");
        }
        T front = array_[0];
        for (size_t i = 1; i < curr_size_; i++) {
            array_[i - 1] = array_[i];
        }
        curr_size_--;
        if (curr_size_ <= (capacity_ / 4) && capacity > 1) {
            capacity_ /= 2;
            if (capacity_ == 0) {
                capacity_ = 1;
            }
            T* data2 = new T[capacity_];
            for (size_t i = 0; i < curr_size_; i++) {
                data2[i] = array_[i];
            }
            delete[] array_;
            array_ = data2;
        }
        return front;
    }

};
