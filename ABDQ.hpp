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
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

public:
    // Big 5
    ABDQ() : capacity_(4), size_(0), front_(0), back_(0), data_(new T[4]) {}
    explicit ABDQ(std::size_t capacity) : capacity_(capacity), size_(0), front_(0), back_(0), data_(new T[capacity]) {}
    ABDQ(const ABDQ& other) : capacity_(other.capacity_), size_(other.getSize()), front_(other.front_), back_(other.back_) {
        data_ = new T[capacity_];
        for (size_t i = 0; i < size_; i++) {
            data_[i] = other.data_[i];
        }
    }
    ABDQ(ABDQ&& other) noexcept : capacity_(other.capacity_), size_(other.size_), front_(other.front_), back_(other.back_), data_(other.data_) {
        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
    }
    ABDQ& operator=(const ABDQ& other) {
        if (this == &other) {
            return *this;
        }
        delete[] data_;
        data_ = new T[other.capacity_];
        for (size_t i = 0; i < other.getSize(); i++) {
            data_[i] = other.data_[i];
        }
        capacity_ = other.capacity_;
        size_ = other.getSize();
        front_ = other.front_;
        back_ = other.back_;

        return *this;
    }
    ABDQ& operator=(ABDQ&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        delete[] data_;
        data_ = other.data_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;

        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
        return *this;
    
    }
    ~ABDQ() {
        delete[] data_;
        capacity_ = 0;
        size_ = 0;
        front_ = 0;
        back_ = 0;
    }

    // Insertion
    void pushFront(const T& item) override {
        if (capacity_ == size_) {
            capacity_ *= SCALE_FACTOR;
            T* data2 = new T[capacity_];
            for (size_t i = 0; i < size_; i++) {
                data2[i] = data_[(front_ + i) % (capacity_ / SCALE_FACTOR)];
            }
            delete[] data_;
            data_ = data2;
            front_ = 0;
            back_ = size_;
        }
        front_ = (front_ - 1 + capacity_) % capacity_;
        size_++;
        data_[front_] = item;
    }
    void pushBack(const T& item) override {
        if (capacity_ == size_) {
            capacity_ *= SCALE_FACTOR;
            T* data2 = new T[capacity_];
            for (size_t i = 0; i < size_; i++) {
                data2[i] = data_[(front_ + i) % (capacity_ / SCALE_FACTOR)];
            }
            delete[] data_;
            data_ = data2;
            front_ = 0;
            back_ = size_;
        }
        data_[back_] = item;
        back_ = (back_ + 1) % capacity_;
        size_++;
    }

    // Deletion
    T popFront() override {
        if (size_ == 0) {
            throw std::runtime_error("");
        }
        T data = data_[front_];
        front_ = (front_ + 1) % capacity_;
        size_--;
        return data;
    }
    T popBack() override {
        if (size_ == 0) {
            throw std::runtime_error("");
        }
        back_ = (back_ - 1 + capacity_) % capacity_;
        size_--;
        return data_[back_];
    }

    // Access
    const T& front() const override {
        if (size_ == 0) {
            throw std::runtime_error("");
        }
        return data_[front_];
    }
    const T& back() const override {
        if (size_ == 0) {
            throw std::runtime_error("");
        }
        return data_[(back_ - 1 + capacity_) % capacity_];
    }

    // Getters
    std::size_t getSize() const noexcept override {
        return size_;
    }

};
