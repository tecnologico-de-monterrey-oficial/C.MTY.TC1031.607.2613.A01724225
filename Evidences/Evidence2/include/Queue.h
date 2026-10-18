#pragma once
#include <iostream>
#include "LinkedList.h"

// Fila sobre la lista: entra por el final, sale por el inicio
template <typename T>
class Queue {
    LinkedList<T> l;
public:
    void enqueue(T v) { l.addLast(v); }
    bool dequeue() {
        if (!l.removeFirst()) { std::cout << "Fila vacia: no se puede hacer dequeue\n"; return false; }
        return true;
    }
    T* front() {
        T* p = l.first();
        if (!p) std::cout << "Fila vacia: no hay frente\n";
        return p;
    }
    bool isEmpty() const { return l.isEmpty(); }
    int size() const { return l.size(); }
    void print() const { l.print(); }
};
