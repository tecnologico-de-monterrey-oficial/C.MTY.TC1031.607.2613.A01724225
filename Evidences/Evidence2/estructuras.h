#pragma once
#include <iostream>

// Lista ligada simple con head y tail
template <typename T>
class LinkedList {
    struct Node { T v; Node* next; };
    Node *head = nullptr, *tail = nullptr;
    int n = 0;

public:
    LinkedList() {}
    LinkedList(const LinkedList&) = delete;            // evita doble delete
    LinkedList& operator=(const LinkedList&) = delete;
    ~LinkedList() { while (n) removeFirst(); }

    void addFirst(T v) {
        head = new Node{v, head};
        if (!tail) tail = head;
        n++;
    }
    void addLast(T v) {
        Node* x = new Node{v, nullptr};
        if (tail) tail->next = x; else head = x;
        tail = x;
        n++;
    }
    // false si estaba vacia (no truena)
    bool removeFirst() {
        if (!head) return false;
        Node* t = head;
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
        for (Node* p = head; p; p = p->next) std::cout << p->v << (p->next ? ", " : "");
        std::cout << "] (" << n << " elementos)\n";
    }
};

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

// Lista doblemente ligada; los nodos son publicos para insertar/borrar "a partir de un nodo dado"
template <typename T>
class DoublyLinkedList {
public:
    struct Node { T v; Node *prev, *next; };

    DoublyLinkedList() {}
    DoublyLinkedList(const DoublyLinkedList&) = delete;
    DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;
    ~DoublyLinkedList() { while (head) remove(head); }

    Node* addFirst(T v) {
        Node* x = new Node{v, nullptr, head};
        if (head) head->prev = x; else tail = x;
        head = x;
        n++;
        return x;
    }
    Node* addLast(T v) {
        Node* x = new Node{v, tail, nullptr};
        if (tail) tail->next = x; else head = x;
        tail = x;
        n++;
        return x;
    }
    Node* insertAfter(Node* p, T v) {
        if (!p) { std::cout << "Nodo nulo: no se puede insertar\n"; return nullptr; }
        Node* x = new Node{v, p, p->next};
        if (p->next) p->next->prev = x; else tail = x;
        p->next = x;
        n++;
        return x;
    }
    bool remove(Node* p) {
        if (!p) { std::cout << "Nodo nulo: no se puede eliminar\n"; return false; }
        if (p->prev) p->prev->next = p->next; else head = p->next;
        if (p->next) p->next->prev = p->prev; else tail = p->prev;
        delete p;
        n--;
        return true;
    }
    Node* getHead() const { return head; }
    Node* getTail() const { return tail; }
    int size() const { return n; }

    // Revisa si ya esta ordenada segun less (estable: iguales cuentan como ordenados)
    template <typename Less>
    bool isSorted(Less less) const {
        for (Node* p = head; p && p->next; p = p->next)
            if (less(p->next->v, p->v)) return false;
        return true;
    }

    // Merge Sort sobre los mismos nodos (solo se reenlazan, no se copia nada).
    // comps cuenta comparaciones; maxDepth la profundidad maxima de recursion.
    template <typename Less>
    void mergeSort(Less less, long long& comps, int& maxDepth) {
        comps = 0;
        maxDepth = 0;
        head = msort(head, less, comps, 1, maxDepth);
        Node* prev = nullptr;
        for (Node* p = head; p; p = p->next) { p->prev = prev; prev = p; }
        tail = prev;
    }

private:
    template <typename Less>
    static Node* msort(Node* h, Less& less, long long& comps, int depth, int& maxDepth) {
        if (depth > maxDepth) maxDepth = depth;
        if (!h || !h->next) return h;
        // mitad: slow termina al final de la primera mitad
        Node *slow = h, *fast = h->next;
        while (fast && fast->next) { slow = slow->next; fast = fast->next->next; }
        Node* right = slow->next;
        slow->next = nullptr;
        Node* a = msort(h, less, comps, depth + 1, maxDepth);
        Node* b = msort(right, less, comps, depth + 1, maxDepth);

        Node dummy{T(), nullptr, nullptr};
        Node* t = &dummy;
        while (a && b) {
            comps++;
            if (less(b->v, a->v)) { t->next = b; b = b->next; }  // empate: sale a (estable)
            else                  { t->next = a; a = a->next; }
            t = t->next;
        }
        t->next = a ? a : b;
        return dummy.next;
    }

public:
    void printForward() const {
        std::cout << "Adelante: [";
        for (Node* p = head; p; p = p->next) std::cout << p->v << (p->next ? ", " : "");
        std::cout << "] (" << n << " elementos)\n";
    }
    void printBackward() const {
        std::cout << "Atras:    [";
        for (Node* p = tail; p; p = p->prev) std::cout << p->v << (p->prev ? ", " : "");
        std::cout << "] (" << n << " elementos)\n";
    }

private:
    Node *head = nullptr, *tail = nullptr;
    int n = 0;
};
