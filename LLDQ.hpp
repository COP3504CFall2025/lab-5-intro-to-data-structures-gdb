#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <utility>



template <typename T>
class LLDQ : public DequeInterface<T> {
private:
    LinkedList<T> list;

public:
    // Constructor
    LLDQ() {}

    // Core Insertion Operations
    void pushFront(const T& item) override {
        list.AddHead(item);
    }
    void pushBack(const T& item) override {
        list.AddTail(item);
    }

    // Core Removal Operations
    T popFront() override {
        if (!list.getHead()) {
            throw std::runtime_error("");
        }
        T head = list.getHead()->data;
        list.RemoveHead();
        return head;
    }
    T popBack() override {
        if (!list.getTail()) {
            throw std::runtime_error("");
        }
        T tail = list.getTail()->data;
        list.RemoveTail();
        return tail;
    }

    // Element Accessors
    const T& front() const override {
        if (!list.getHead()) {
            throw std::runtime_error("");
        }
        return list.getHead()->data;
    }
    const T& back() const override {
        if (!list.getTail()) {
            throw std::runtime_error("");
        }
        return list.getTail()->data;
    }

    // Getter
    std::size_t getSize() const noexcept override {
        return list.getCount();
    }
};






