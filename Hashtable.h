#pragma once
#include <string>
#include <iostream>
#include "LinkedList.h"
#include "ConsoleUtils.h"
using namespace std;

const int TableSize = 12697;

template <typename T>
class HashTable {
private:
    int numberOfElements;

public:
    LinkedList<T> buckets[TableSize];

    //Constructors and Destructors
    HashTable();
    ~HashTable();
    // Methods
    void insert(T* to_add, int sum);
    int hash(int sum) const;
    int getnumberofelments();
};

//Constructors and Destructors
template <typename T>
HashTable<T>::HashTable() {
    numberOfElements = 0;
}

template <typename T>
HashTable<T>::~HashTable() {

    for (int i = 0; i < TableSize; ++i) {
        buckets[i].clear();
    }
    numberOfElements = 0;
}

//Methods

template <typename T>
int HashTable<T>::hash(int sum) const {
    return sum % TableSize;
}

template<typename T>
inline int HashTable<T>::getnumberofelments()
{
    return numberOfElements;
}

template <typename T>
void HashTable<T>::insert(T* to_add, int sum) {

    int index = hash(sum);
    buckets[index].append(to_add);
    numberOfElements++;
}