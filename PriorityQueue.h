#pragma once

#include "Vector.h"
#include <stdexcept>
#include "ConsoleUtils.h"

using namespace std;

template <typename T>
class PriorityQueue {
private:
    Vector<T> heap;
    bool compare(const T& a, const T& b) const {
        return a > b;
    }

public:
    // Default Constructor
    PriorityQueue();
    // Methods
    bool empty() const;
    int size() const;
    void push(const T& value);
    void pop();
    const T& top() const;
};


// Default Constructor
template <typename T>
PriorityQueue<T>::PriorityQueue() : heap() {}

// Methods
template <typename T>
bool PriorityQueue<T>::empty() const {
    return heap.empty();
}

template <typename T>
int PriorityQueue<T>::size() const {
    return heap.getSize();
}

template <typename T>
void PriorityQueue<T>::push(const T& value) {
    heap.push_back(value);

    for (int i = heap.getSize() - 1; i > 0; --i) {
        if (compare(heap[i], heap[i - 1])) {
            T temp = heap[i];
            heap[i] = heap[i - 1];
            heap[i - 1] = temp;
        }
        else {
            break;
        }
    }
}

template <typename T>
void PriorityQueue<T>::pop() {
    if (empty()) {
        ConsoleUtils::setConsoleColor(4);
        throw std::out_of_range("PriorityQueue is empty.");
    }
    heap.erase(*(heap.begin()));
}

template <typename T>
const T& PriorityQueue<T>::top() const {
    if (empty()) {
        ConsoleUtils::setConsoleColor(4);
        throw std::out_of_range("PriorityQueue is empty.");
    }
    return *(heap.begin());
}