#pragma once

// Nodo de la lista ligada simple (tambien lo usan la Pila y la Fila a traves de ella)
template <typename T>
struct Node {
    T v;
    Node* next;
};
