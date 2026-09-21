#include <iostream>
#include <utility>
#include <vector>

using namespace std;

template <typename T>
vector<T> swapSort(vector<T> v) {
    for (size_t i = 0; i + 1 < v.size(); i++) {
        for (size_t j = i + 1; j < v.size(); j++) {
            if (v[j] < v[i]) {
                swap(v[j], v[i]);
            }
        }
    }

    return v;
}

template <typename T>
vector<T> selectionSort(vector<T> v) {
    for (size_t i = 0; i + 1 < v.size(); i++) {
        size_t index = i;

        for (size_t j = i + 1; j < v.size(); j++) {
            if (v[j] < v[index]) {
                index = j;
            }
        }

        if (index != i) {
            swap(v[i], v[index]);
        }
    }

    return v;
}

template <typename T>
vector<T> bubbleSort(vector<T> v) {
    for (size_t i = 1; i < v.size(); i++) {
        bool huboCambio = false;

        for (size_t j = 0; j < v.size() - i; j++) {
            if (v[j] > v[j + 1]) {
                swap(v[j], v[j + 1]);
                huboCambio = true;
            }
        }

        if (!huboCambio) {
            break;
        }
    }

    return v;
}

template <typename T>
vector<T> insertionSort(vector<T> v) {
    for (size_t i = 1; i < v.size(); i++) {
        size_t j = i;

        while (j > 0 && v[j] < v[j - 1]) {
            swap(v[j], v[j - 1]);
            j--;
        }
    }

    return v;
}

template <typename T>
int part(vector<T> &v, int inicio, int final) {
    T pivot = v[inicio];
    int i = inicio + 1;

    for (int j = inicio + 1; j <= final; j++) {
        if (v[j] <= pivot) {
            swap(v[i], v[j]);
            i++;
        }
    }

    swap(v[inicio], v[i - 1]);
    return i - 1;
}

template <typename T>
void quickSort(vector<T> &v, int inicio, int final) {
    if (inicio < final) {
        int pivote = part(v, inicio, final);
        quickSort(v, inicio, pivote - 1);
        quickSort(v, pivote + 1, final);
    }
}

template <typename T>
vector<T> shellSort(vector<T> v) {
    for (size_t salto = v.size() / 2; salto > 0; salto /= 2) {
        for (size_t i = salto; i < v.size(); i++) {
            T actual = v[i];
            size_t j = i;

            while (j >= salto && actual < v[j - salto]) {
                v[j] = v[j - salto];
                j -= salto;
            }

            v[j] = actual;
        }
    }

    return v;
}

template <typename T>
void combinar(vector<T> &v, size_t izquierda, size_t mitad, size_t derecha) {
    vector<T> temporal;
    temporal.reserve(derecha - izquierda + 1);

    size_t i = izquierda;
    size_t j = mitad + 1;

    while (i <= mitad && j <= derecha) {
        if (v[i] <= v[j]) {
            temporal.push_back(v[i]);
            i++;
        } else {
            temporal.push_back(v[j]);
            j++;
        }
    }

    while (i <= mitad) {
        temporal.push_back(v[i]);
        i++;
    }

    while (j <= derecha) {
        temporal.push_back(v[j]);
        j++;
    }

    for (size_t k = 0; k < temporal.size(); k++) {
        v[izquierda + k] = temporal[k];
    }
}

template <typename T>
void mergeSortAux(vector<T> &v, size_t izquierda, size_t derecha) {
    if (izquierda >= derecha) {
        return;
    }

    size_t mitad = izquierda + (derecha - izquierda) / 2;
    mergeSortAux(v, izquierda, mitad);
    mergeSortAux(v, mitad + 1, derecha);
    combinar(v, izquierda, mitad, derecha);
}

template <typename T>
vector<T> mergeSort(vector<T> v) {
    if (!v.empty()) {
        mergeSortAux(v, 0, v.size() - 1);
    }

    return v;
}

int main() {
    return 0;
}
