#pragma once
#include <iostream>
#include <stdexcept> 
#include "ConsoleUtils.h"
using namespace std;

template <typename T>

class Vector {
private:
    T* data;
    int capacity;
    int size;
    void resize(int newCapacity);
public:
    // Constructors and Destructor
    Vector();
    void destroy_elements();
    ~Vector();
    // Operators
    T& operator[](int index);
    const T& operator[](int index) const;
    //getters
    int getSize() const;
    int getCapacity() const;
    // Methods
    bool empty() const;
    void push_back(const T& value);
    void pop_back();
    void clear();
    bool contains(const T& value);
    void display() const;
    void erase(const T& value);
    T* begin();
    const T* begin() const;

};



// Constructors and Destructors

template <typename T>
Vector<T>::Vector() : data(nullptr), capacity(10), size(0) {
    data = new T[10];
}

template <typename T>
void Vector<T>::destroy_elements() {
    for (int i = 0; i < size; ++i) {
        data[i].~T();
    }
}

template <typename T>
Vector<T>::~Vector() {
    destroy_elements();
    if (data != nullptr) {
        delete[] data;
    }
}

// Operators
template <typename T>
T& Vector<T>::operator[](int index) {
    if (index >= size) {
        ConsoleUtils::setConsoleColor(4);
        throw std::out_of_range("Index out of range.");
    }
    return data[index];
}

template <typename T>
const T& Vector<T>::operator[](int index) const {
    if (index >= size) {
        ConsoleUtils::setConsoleColor(4);
        throw std::out_of_range("Index out of range.");
    }
    return data[index];
}


//Methods
template <typename T>
void Vector<T>::resize(int newCapacity) {
    T* newData = new T[newCapacity];

    for (int i = 0; i < size; i++) {
        newData[i] = data[i];
    }
    if (data) {
        delete[] data;
    }
    data = newData;
    capacity = newCapacity;
}


template <typename T>
int Vector<T>::getSize() const {
    return size;
}

template <typename T>
int Vector<T>::getCapacity() const {
    return capacity;
}

template <typename T>
bool Vector<T>::empty() const {
    return size == 0;
}



template <typename T>
void Vector<T>::push_back(const T& value) {

    if (size == capacity) {
        int newCapacity = (capacity == 0) ? 1 : capacity * 2;
        resize(newCapacity);
    }
    data[size++] = value;
}

template <typename T>
void Vector<T>::pop_back() {
    if (empty()) {
        ConsoleUtils::setConsoleColor(4);
        throw std::out_of_range("Cannot pop from an empty vector.");
    }
    size--;
}

template <typename T>
void Vector<T>::clear() {
    delete[] data;
    data = nullptr;
    size = 0;
    capacity = 0;
}

template <typename T>
inline bool Vector<T>::contains(const T& value) {

    for (int i = 0; i < size; ++i) {
        if (data[i] == value) {
            return true;
        }
    }
    return false;
}

template <typename T>
void Vector<T>::display() const {
    if (this->getSize() == 0) {
        ConsoleUtils::setConsoleColor(4);
        cout << "no people you may know";
    }
    cout << "Vector: ";
    for (int i = 0; i < size; i++) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void Vector<T>::erase(const T& value) {

    int index = -1;
    for (int i = 0; i < size; ++i) {
        if (data[i] == value) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        throw std::out_of_range("Value not found in the vector.");
    }
    for (int i = index; i < size - 1; ++i) {
        data[i] = data[i + 1];
    }
    --size;
}


template <typename T>
T* Vector<T>::begin() {
    return data;
}

template <typename T>
const T* Vector<T>::begin() const {
    return data;
}