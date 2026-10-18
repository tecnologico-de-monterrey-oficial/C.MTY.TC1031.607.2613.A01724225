#pragma once
#include <iostream>

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
