#pragma once
#include "ConsoleUtils.h"

// Template Class for Pair
template <typename T1, typename T2>
class Pair {
private:
    T1 first;
    T2 second;

public:
    // Constructors and Destructors
    Pair();
    Pair(const Pair& other);
    Pair(const T1& firstValue, const T2& secondValue);
    ~Pair();
    // Accessors
    T1 getFirst() const;
    T2 getSecond() const;
    //Operators
    Pair& operator=(const Pair& other);
    bool operator==(const Pair& other) const;
    bool operator!=(const Pair& other) const;
    bool operator<(const Pair& other) const;
    bool operator>(const Pair& other) const;
    // Mutators
    void setFirst(const T1& value);
    void setSecond(const T2& value);

};

// Constructors and Destructors

template <typename T1, typename T2>
Pair<T1, T2>:: ~Pair() {
    second.~T2();
}

template <typename T1, typename T2>
Pair<T1, T2>::Pair() : first(T1()), second(T2()) {}

template <typename T1, typename T2>
Pair<T1, T2>::Pair(const Pair& other) : first(other.first), second(other.second) {}

template <typename T1, typename T2>
Pair<T1, T2>::Pair(const T1& firstValue, const T2& secondValue)
    : first(firstValue), second(secondValue) {}


// Accessors
template <typename T1, typename T2>
T1 Pair<T1, T2>::getFirst() const {
    return first;
}

template <typename T1, typename T2>
T2 Pair<T1, T2>::getSecond() const {
    return second;
}


// Operators
template <typename T1, typename T2>
Pair<T1, T2>& Pair<T1, T2>:: operator=(const Pair& other)
{
    if (this != &other) {
        first = other.first;
        second = other.second;
    }
    return *this;
}

template <typename T1, typename T2>
bool Pair<T1, T2>::operator==(const Pair<T1, T2>& other) const {
    return second == other.second;
}

template <typename T1, typename T2>
bool Pair<T1, T2>::operator!=(const Pair<T1, T2>& other) const {
    return !(*this == other);
}

template <typename T1, typename T2>
bool Pair<T1, T2>::operator<(const Pair<T1, T2>& other) const {
    return second < other.second;
}

template <typename T1, typename T2>
bool Pair<T1, T2>::operator>(const Pair<T1, T2>& other) const {
    return second > other.second;
}


// Mutators
template <typename T1, typename T2>
void Pair<T1, T2>::setFirst(const T1& value) {
    first = value;
}

template <typename T1, typename T2>
void Pair<T1, T2>::setSecond(const T2& value) {
    second = value;
}