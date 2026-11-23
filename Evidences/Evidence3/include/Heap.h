#pragma once
#include <functional>
#include <stdexcept>
#include <vector>

// heap binario guardado en un vector
// el comparador dice si a debe quedar arriba de b
// con std::greater queda como maxheap y con std::less como minheap
template <typename T, typename Comp = std::less<T>>
class Heap {
    std::vector<T> datos;
    Comp comp;
    long long comparaciones = 0;

    // compara usando el comparador y lleva la cuenta
    bool arriba(const T& a, const T& b) {
        comparaciones++;
        return comp(a, b);
    }

    // el nuevo elemento sube mientras le gane a su padre
    void subir(int i) {
        while (i > 0) {
            int padre = (i - 1) / 2;
            if (!arriba(datos[i], datos[padre])) break;
            std::swap(datos[i], datos[padre]);
            i = padre;
        }
    }

    // la raiz baja cambiandose por el mejor de sus hijos
    void bajar(int i) {
        int n = datos.size();
        while (true) {
            int izq = 2 * i + 1, der = 2 * i + 2, mejor = i;
            if (izq < n && arriba(datos[izq], datos[mejor])) mejor = izq;
            if (der < n && arriba(datos[der], datos[mejor])) mejor = der;
            if (mejor == i) break;
            std::swap(datos[i], datos[mejor]);
            i = mejor;
        }
    }

public:
    Heap(Comp c = Comp()) : comp(c) {}

    void push(const T& v) {
        datos.push_back(v);
        subir(datos.size() - 1);
    }

    // quita la raiz, regresa false si el heap estaba vacio
    bool pop() {
        if (datos.empty()) return false;
        datos[0] = datos.back();
        datos.pop_back();
        if (!datos.empty()) bajar(0);
        return true;
    }

    const T& top() const {
        if (datos.empty()) throw std::out_of_range("heap vacio, no hay top");
        return datos[0];
    }

    int size() const { return datos.size(); }
    bool empty() const { return datos.empty(); }

    // cuenta niveles, vacio es cero y solo la raiz es uno
    int height() const {
        int h = 0;
        for (int n = datos.size(); n > 0; n /= 2) h++;
        return h;
    }

    long long getComparaciones() const { return comparaciones; }
    void reiniciarComparaciones() { comparaciones = 0; }
};

template <typename T>
using MaxHeap = Heap<T, std::greater<T>>;

template <typename T>
using MinHeap = Heap<T, std::less<T>>;
