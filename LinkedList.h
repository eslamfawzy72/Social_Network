#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <exception> 
#include "Pair.h"
#include "PriorityQueue.h"
#include "ConsoleUtils.h"
using namespace std;

enum classification {
    NANN, Friends, Closefriends, Family
};

template <typename T>
class LinkedList {
private:

    int listSize; // Number of elements in the list

public:

    class accessnode {

    public:
        T* OG_NODE;
        classification relation;
        accessnode* next;
        // constructors and destructors
        accessnode() : OG_NODE(nullptr), relation(0), next(nullptr) {}
        accessnode(T* x) {
            this->OG_NODE = x;
            this->next = nullptr;
            this->relation = NANN;
        }
        accessnode(const accessnode& other) {
            this->OG_NODE = other.OG_NODE;
            this->relation = other.relation;
            this->next = nullptr;
        }
        //setters and getters
        void set_relation(classification rel) {
            this->relation = rel;
        }
        ~accessnode() {

            OG_NODE = nullptr;
            next = nullptr;
        }
        classification get_relation() { return relation; }
        //operators
        friend bool operator<(const accessnode& lhs, const accessnode& rhs) {
            return lhs.relation < rhs.relation;
        }
        friend bool operator>(const accessnode& lhs, const accessnode& rhs) {
            return lhs.relation > rhs.relation;
        }
        friend bool operator==(const accessnode& lhs, const accessnode& rhs) {
            return (lhs.OG_NODE == rhs.OG_NODE) &&
                (lhs.relation == rhs.relation) &&
                (lhs.next == rhs.next);
        }
        friend bool operator!=(const accessnode& lhs, const accessnode& rhs) {
            return !(lhs == rhs);
        }
        accessnode& operator=(const accessnode& other) {
            if (this != &other) { // Avoid self-assignment
                // Copy OG_NODE pointer (shallow copy)
                this->OG_NODE = other.OG_NODE;

                // Copy relation value
                this->relation = other.relation;

                // Reset next pointer to nullptr (do not copy linked structure)
                this->next = nullptr;
            }
            return *this; // Return *this to allow chaining
        }
    };

    // Constructors and destructors
    accessnode* head;
    accessnode* tail;
    LinkedList();
    LinkedList(const LinkedList& other);
    ~LinkedList();
    // List operations
    void operator=(const LinkedList<T>& other);
    //Methods
    int size() const;
    bool empty() const;
    void classify(string username);
    void sort();
    void append(T* node_to_add);
    void remove(const T& value);
    void IterateByIndex() const;
    T* search_by_index(int index);
    void clear();

};


//constructors and destructors
template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), listSize(0) {}

template <typename T>
LinkedList<T>::~LinkedList() {
    clear();
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList& other) : head(nullptr) {
    if (!other.head) {
        return;
    }
    head = new accessnode(other.head->OG_NODE);
    accessnode* current = head;
    accessnode* otherCurrent = other.head->next;
    while (otherCurrent) {
        current->next = new accessnode(otherCurrent->OG_NODE);
        current = current->next;
        otherCurrent = otherCurrent->next;
    }
}

// List operations
template <typename T>
void LinkedList<T>:: operator=(const LinkedList<T>& other) {
    if (other.head == nullptr) {
        head = nullptr;
        return;
    }
    head = new accessnode(*(other.head));
    accessnode* temp1 = head;
    accessnode* temp2 = other.head;
    while (temp2 && temp2->next) {
        temp1->next = new accessnode(*(temp2->next));
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
}

//Methods
template <typename T>
int LinkedList<T>::size() const {
    return listSize;
}

template <typename T>
bool LinkedList<T>::empty() const {
    return listSize == 0;
}

template<typename T>
inline void LinkedList<T>::classify(string username)
{
    accessnode* temp = head;
    while ((temp->OG_NODE->getUsername() != username) && temp->next != nullptr) {
        temp = temp->next;
    }

    ConsoleUtils::setConsoleColor(8);
    cout << "Classify your Friend\n[1]Friend\n[2]Close Friend\n[3]Family\n";
    short x;
    cin >> x;
    if (x == 1) {
        temp->set_relation(Friends);

    }
    else if (x == 2) {
        temp->set_relation(Closefriends);

    }
    else if (x == 3) {
        temp->set_relation(Family);

    }
    else {
        ConsoleUtils::setConsoleColor(4);
        cout << "Invalid";
    }
    return;
}

template <typename T>
void LinkedList<T>::append(T* node_to_add) {
    accessnode* node = new accessnode(node_to_add);
    if (tail != 0) {
        tail->next = node;
    }
    else {
        head = node;
    }

    tail = node;
    listSize++;
}

template <typename T>
void LinkedList<T>::IterateByIndex() const {
    accessnode* temp = head;
    int index = 1;
    while (temp) {
        ConsoleUtils::setConsoleColor(8);
        cout << "[" << index << "] " << *(temp->OG_NODE) <<"->" << temp->get_relation() << endl;
        temp = temp->next;
        index++;
    }
}

template <typename T>
T* LinkedList<T>::search_by_index(int index) {
    if (!head) {
        ConsoleUtils::setConsoleColor(4);
        throw std::out_of_range::out_of_range("The list is empty.");
    }

    if (index < 1 || index > listSize) {
        ConsoleUtils::setConsoleColor(4);
        throw out_of_range("Index out of range.");
    }

    accessnode* temp = head;
    int currentIndex = 1;
    while (currentIndex < index) {
        temp = temp->next;
        currentIndex++;
    }

    return temp->OG_NODE;
}

template <typename T>
void LinkedList<T>::remove(const T& value) {
    try {
        if (this->empty()) {
            ConsoleUtils::setConsoleColor(4);
            throw std::out_of_range("List is empty");
        }

        // Handle the case where the value is at the head
        while (head && *(head->OG_NODE) == value) {
            accessnode* temp = head;
            head = head->next;
            delete temp;
            --listSize;
        }

        if (!head) {
            tail = nullptr;
            return;
        }

        // Handle other cases
        accessnode* current = head;
        while (current->next) {
            if (*(current->next->OG_NODE) == value) {
                accessnode* temp = current->next;
                current->next = current->next->next;
                delete temp;
                --listSize;
                if (!current->next) {
                    tail = current;
                }
            }
            else {
                current = current->next;
            }
        }
    }
    catch (const std::out_of_range& e) {
        ConsoleUtils::setConsoleColor(4);
        std::cerr << "Error: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        ConsoleUtils::setConsoleColor(4);
        std::cerr << "Unexpected error: " << e.what() << std::endl;
    }
    catch (...) {
        ConsoleUtils::setConsoleColor(4);
        std::cerr << "An unknown error occurred." << std::endl;
    }
}

template <typename T>
void LinkedList<T>::clear() {

    while (head) {
        accessnode* temp = head;

        head = head->next;

        delete temp;

    }
    listSize = 0;

}

template <typename T>
void LinkedList<T>::sort() {
    if (!head || !head->next) {
        return;
    }

    bool swapped;
    do {
        swapped = false;
        accessnode* current = head;
        accessnode* prev = nullptr;

        while (current && current->next) {
            if (current->relation < current->next->relation) {

                accessnode* temp = current->next;
                current->next = temp->next;
                temp->next = current;

                if (prev) {
                    prev->next = temp;
                }
                else {
                    head = temp;
                }

                swapped = true;
                prev = temp;
            }
            else {
                prev = current;
                current = current->next;
            }
        }
    } while (swapped);


    accessnode* temp = head;
    while (temp && temp->next) {
        temp = temp->next;
    }
    tail = temp;
}


#endif // LINKEDLIST_H