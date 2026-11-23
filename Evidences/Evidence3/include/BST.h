#pragma once
#include <iostream>

// lo que regresa search: cuantas veces aparece y cuantas comparaciones costo
struct Busqueda {
    int contador = 0;
    int comparaciones = 0;
};

// arbol binario de busqueda donde cada nodo lleva un contador
// si la llave ya existe solo se suma uno, no se crea otro nodo
template <typename K>
class BST {
    struct Nodo {
        K llave;
        int contador = 1;
        Nodo* izq = nullptr;
        Nodo* der = nullptr;
        Nodo(const K& k) : llave(k) {}
    };

    Nodo* raiz = nullptr;
    int nodos = 0;

    void borrar(Nodo* n) {
        if (!n) return;
        borrar(n->izq);
        borrar(n->der);
        delete n;
    }

    int altura(Nodo* n) const {
        if (!n) return 0;
        int a = altura(n->izq), b = altura(n->der);
        return 1 + (a > b ? a : b);
    }

    template <typename F>
    void inorden(Nodo* n, F& visita) const {
        if (!n) return;
        inorden(n->izq, visita);
        visita(n->llave, n->contador);
        inorden(n->der, visita);
    }

public:
    BST() {}
    ~BST() { borrar(raiz); }

    // no se copia para no borrar dos veces los mismos nodos
    BST(const BST&) = delete;
    BST& operator=(const BST&) = delete;

    void insert(const K& k) {
        Nodo** actual = &raiz;
        while (*actual) {
            if (k < (*actual)->llave) actual = &(*actual)->izq;
            else if ((*actual)->llave < k) actual = &(*actual)->der;
            else {
                (*actual)->contador++;
                return;
            }
        }
        *actual = new Nodo(k);
        nodos++;
    }

    // cada nodo visitado cuenta como una comparacion
    // si no la encuentra el contador queda en cero
    Busqueda search(const K& k) const {
        Busqueda r;
        Nodo* actual = raiz;
        while (actual) {
            r.comparaciones++;
            if (k < actual->llave) actual = actual->izq;
            else if (actual->llave < k) actual = actual->der;
            else {
                r.contador = actual->contador;
                break;
            }
        }
        return r;
    }

    int size() const { return nodos; }
    bool empty() const { return nodos == 0; }

    // vacio es cero y solo la raiz es uno, igual que en el heap
    int height() const { return altura(raiz); }

    // recorre de menor a mayor y le pasa la llave y su contador a visita
    template <typename F>
    void inorden(F visita) const { inorden(raiz, visita); }

    void imprimir(std::ostream& o = std::cout) const {
        inorden([&o](const K& k, int c) { o << k << " " << c << "\n"; });
    }
};
