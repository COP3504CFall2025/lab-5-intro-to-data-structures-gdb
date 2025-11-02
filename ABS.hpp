#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
public:
    // Big 5 + Parameterized Constructor
    ABS() : capacity_(1), curr_size_(0), array_(new T[1]) {}
    explicit ABS(const size_t capacity) : capacity_(capacity), curr_size_(0), array_(new T[capacity]) {}
    ABS(const ABS& other) : capacity_(other.capacity_), curr_size_(other.getSize()), array_(new T[other.capacity_]) {
        for (size_t i = 0; i < other.getSize(); i++) {
            array_[i] = other.getData()[i];
        }
    }
    ABS& operator=(const ABS& rhs) {
        if (this == &rhs) {
            return *this;
        }
        delete[] array_;
        array_ = new T[rhs.capacity_];
        for (size_t i = 0; i < rhs.getSize(); i++) {
            array_[i] = rhs.getData()[i];
        }
        capacity_ = rhs.capacity_;
        curr_size_ = rhs.getSize();
        return *this;

    }
    ABS(ABS&& other) noexcept : capacity_(other.capacity_), curr_size_(other.curr_size_), array_(other.array_) {
        other.capacity_ = 0;
        other.curr_size_ = 0;
        other.array_ = nullptr;
    }
    ABS& operator=(ABS&& rhs) noexcept {
        if (this == &rhs) {
            return *this;
        }
        delete[] array_;
        array_ = rhs.array_;
        curr_size_ = rhs.curr_size_;
        capacity_ = rhs.capacity_;

        rhs.array_ = nullptr;
        rhs.curr_size_ = 0;
        rhs.capacity_ = 0;
        return *this;
    }
    ~ABS() noexcept {
        delete[] array_;
        curr_size_ = 0;
        capacity_ = 0;
    }

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override {
        return curr_size_;
    }

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept { 
        return capacity_;
    }

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept {
        return array_;
    }

    // Push item onto the stack
    void push(const T& data) override {
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

    T peek() const override {
        if (curr_size_ == 0) {
            throw std::runtime_error("");
        }
        return array_[curr_size_ - 1];
    }

    T pop() override {
        if (curr_size_ == 0) {
            throw std::runtime_error("");
        }
        curr_size_--;
        T data = array_[curr_size_];
        if (curr_size_ <= (capacity_ / 4) && capacity_ > 1) {
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
        return data;
    }

private:
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;
};
