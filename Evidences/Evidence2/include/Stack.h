#pragma once
#include <iostream>
#include "LinkedList.h"

// Pila sobre la lista: el tope es el inicio
template <typename T>
class Stack {
    LinkedList<T> l;
public:
    void push(T v) { l.addFirst(v); }
    bool pop() {
        if (!l.removeFirst()) { std::cout << "Pila vacia: no se puede hacer pop\n"; return false; }
        return true;
    }
    T* peek() {
        T* p = l.first();
        if (!p) std::cout << "Pila vacia: no hay tope\n";
        return p;
    }
    bool isEmpty() const { return l.isEmpty(); }
    int size() const { return l.size(); }
    void print() const { l.print(); }
};
