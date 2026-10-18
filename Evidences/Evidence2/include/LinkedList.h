#pragma once
#include <iostream>
#include "Node.h"

// Lista ligada simple con head y tail
template <typename T>
class LinkedList {
    Node<T> *head = nullptr, *tail = nullptr;
    int n = 0;

public:
    LinkedList() {}
    LinkedList(const LinkedList&) = delete;            // evita doble delete
    LinkedList& operator=(const LinkedList&) = delete;
    ~LinkedList() { while (n) removeFirst(); }

    void addFirst(T v) {
        head = new Node<T>{v, head};
        if (!tail) tail = head;
        n++;
    }
    void addLast(T v) {
        Node<T>* x = new Node<T>{v, nullptr};
        if (tail) tail->next = x; else head = x;
        tail = x;
        n++;
    }
    // false si estaba vacia (no truena)
    bool removeFirst() {
        if (!head) return false;
        Node<T>* t = head;
        head = head->next;
        if (!head) tail = nullptr;
        delete t;
        n--;
        return true;
    }
    T* first() { return head ? &head->v : nullptr; }
    int size() const { return n; }
    bool isEmpty() const { return n == 0; }
    void print() const {
        std::cout << "[";
        for (Node<T>* p = head; p; p = p->next) std::cout << p->v << (p->next ? ", " : "");
        std::cout << "] (" << n << " elementos)\n";
    }
};
