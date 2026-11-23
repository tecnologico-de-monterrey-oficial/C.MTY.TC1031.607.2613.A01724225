#pragma once
#include <functional>
#include <vector>
#include "Heap.h"

// ordena metiendo todo al heap y sacando la raiz una por una
// con std::less queda de menor a mayor y con std::greater al reves
// regresa cuantas comparaciones hizo el heap
template <typename T, typename Comp = std::less<T>>
long long heapSort(std::vector<T>& v, Comp comp = Comp()) {
    Heap<T, Comp> h(comp);
    for (const T& x : v) h.push(x);
    for (int i = 0; !h.empty(); i++) {
        v[i] = h.top();
        h.pop();
    }
    return h.getComparaciones();
}
