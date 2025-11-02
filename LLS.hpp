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
    LLS() {};

    // Insertion
    void push(const T& item) override {
        list.AddHead(item);
    }

    // Deletion
    T pop() override {
        if (!list.getHead()) {
            throw std::runtime_error("");
        }
        T head = list.getHead()->data;
        list.RemoveHead();
        return head;
    }

    // Access
    T peek() const override {
        if (!list.getHead()) {
            throw std::runtime_error("");
        }
        return list.getHead()->data;
    }

    //Getters
    std::size_t getSize() const noexcept override {
        return list.getCount();
    }
};