#include <array>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <utility>
#include <vector>

using namespace std;

template <typename T>
vector<T> swapSort(vector<T> v, long long *comparaciones = nullptr, long long *intercambios = nullptr) {
    long long comp = 0;
    long long inter = 0;
    for (size_t i = 0; i + 1 < v.size(); i++) {
        for (size_t j = i + 1; j < v.size(); j++) {
            comp++;
            if (v[j] < v[i]) {
                swap(v[j], v[i]);
                inter++;
            }
        }
    }
    if (comparaciones != nullptr) {
        *comparaciones = comp;
    }
    if (intercambios != nullptr) {
        *intercambios = inter;
    }
    return v;
}

template <typename T>
vector<T> selectionSort(vector<T> v, long long *comparaciones = nullptr, long long *intercambios = nullptr) {
    long long comp = 0;
    long long inter = 0;
    for (size_t i = 0; i + 1 < v.size(); i++) {
        size_t index = i;
        for (size_t j = i + 1; j < v.size(); j++) {
            comp++;
            if (v[j] < v[index]) {
                index = j;
            }
        }
        if (index != i) {
            swap(v[i], v[index]);
            inter++;
        }
    }
    if (comparaciones != nullptr) {
        *comparaciones = comp;
    }
    if (intercambios != nullptr) {
        *intercambios = inter;
    }
    return v;
}

template <typename T>
vector<T> bubbleSort(vector<T> v, long long *comparaciones = nullptr, long long *intercambios = nullptr) {
    long long comp = 0;
    long long inter = 0;
    for (size_t i = 1; i < v.size(); i++) {
        bool cambio = false;
        for (size_t j = 0; j < v.size() - i; j++) {
            comp++;
            if (v[j] > v[j + 1]) {
                swap(v[j], v[j + 1]);
                inter++;
                cambio = true;
            }
        }
        if (!cambio) {
            break;
        }
    }
    if (comparaciones != nullptr) {
        *comparaciones = comp;
    }
    if (intercambios != nullptr) {
        *intercambios = inter;
    }
    return v;
}

template <typename T>
vector<T> insertionSort(vector<T> v, long long *comparaciones = nullptr, long long *intercambios = nullptr) {
    long long comp = 0;
    long long inter = 0;
    for (size_t i = 1; i < v.size(); i++) {
        size_t j = i;
        while (j > 0) {
            comp++;
            if (!(v[j] < v[j - 1])) {
                break;
            }
            swap(v[j], v[j - 1]);
            inter++;
            j--;
        }
    }
    if (comparaciones != nullptr) {
        *comparaciones = comp;
    }
    if (intercambios != nullptr) {
        *intercambios = inter;
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
            temporal.push_back(v[i++]);
        } else {
            temporal.push_back(v[j++]);
        }
    }
    while (i <= mitad) {
        temporal.push_back(v[i++]);
    }
    while (j <= derecha) {
        temporal.push_back(v[j++]);
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

template <typename T>
void quickSortAux(vector<T> &v, int izquierda, int derecha) {
    int i = izquierda;
    int j = derecha;
    T pivote = v[izquierda + (derecha - izquierda) / 2];
    while (i <= j) {
        while (v[i] < pivote) {
            i++;
        }
        while (v[j] > pivote) {
            j--;
        }
        if (i <= j) {
            swap(v[i], v[j]);
            i++;
            j--;
        }
    }
    if (izquierda < j) {
        quickSortAux(v, izquierda, j);
    }
    if (i < derecha) {
        quickSortAux(v, i, derecha);
    }
}

template <typename T>
vector<T> quickSort(vector<T> v) {
    if (!v.empty()) {
        quickSortAux(v, 0, static_cast<int>(v.size()) - 1);
    }
    return v;
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
void printVect(const vector<T> &v) {
    cout << "\n";
    for (size_t i = 0; i < v.size(); i++) {
        if (i > 0) {
            cout << ", ";
        }
        cout << v[i];
    }
    cout << "\n\n";
}

template <typename T>
vector<T> ordenar(const vector<T> &datos, int algoritmo, long long &comparaciones, long long &intercambios) {
    comparaciones = 0;
    intercambios = 0;
    switch (algoritmo) {
        case 1:
            return swapSort(datos, &comparaciones, &intercambios);
        case 2:
            return bubbleSort(datos, &comparaciones, &intercambios);
        case 3:
            return selectionSort(datos, &comparaciones, &intercambios);
        case 4:
            return insertionSort(datos, &comparaciones, &intercambios);
        case 5:
            return mergeSort(datos);
        case 6:
            return quickSort(datos);
        case 7:
            return shellSort(datos);
        default:
            return datos;
    }
}

template <typename T>
long long medir(const vector<T> &datos, int algoritmo) {
    long long comparaciones;
    long long intercambios;
    auto inicio = chrono::high_resolution_clock::now();
    vector<T> resultado = ordenar(datos, algoritmo, comparaciones, intercambios);
    auto fin = chrono::high_resolution_clock::now();
    if (!resultado.empty()) {
        volatile T valor = resultado[resultado.size() / 2];
        static_cast<void>(valor);
    }
    return chrono::duration_cast<chrono::nanoseconds>(fin - inicio).count();
}

array<vector<int>, 3> crearEnteros(mt19937 &generador) {
    array<vector<int>, 3> listas;
    array<size_t, 3> cantidades = {1000, 10000, 100000};
    uniform_int_distribution<int> distribucion(-100000, 100000);
    for (size_t i = 0; i < listas.size(); i++) {
        listas[i].reserve(cantidades[i]);
        for (size_t j = 0; j < cantidades[i]; j++) {
            listas[i].push_back(distribucion(generador));
        }
    }
    return listas;
}

array<vector<double>, 3> crearReales(mt19937 &generador) {
    array<vector<double>, 3> listas;
    array<size_t, 3> cantidades = {1000, 10000, 100000};
    uniform_real_distribution<double> distribucion(-100000.0, 100000.0);
    for (size_t i = 0; i < listas.size(); i++) {
        listas[i].reserve(cantidades[i]);
        for (size_t j = 0; j < cantidades[i]; j++) {
            listas[i].push_back(distribucion(generador));
        }
    }
    return listas;
}

array<vector<char>, 3> crearCaracteres(mt19937 &generador) {
    array<vector<char>, 3> listas;
    array<size_t, 3> cantidades = {1000, 10000, 100000};
    uniform_int_distribution<int> distribucion('A', 'Z');
    for (size_t i = 0; i < listas.size(); i++) {
        listas[i].reserve(cantidades[i]);
        for (size_t j = 0; j < cantidades[i]; j++) {
            listas[i].push_back(static_cast<char>(distribucion(generador)));
        }
    }
    return listas;
}

int leerOpcion(int minimo, int maximo) {
    int opcion;
    while (!(cin >> opcion) || opcion < minimo || opcion > maximo) {
        if (cin.eof()) {
            exit(0);
        }
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Opcion invalida. Intenta de nuevo: ";
    }
    return opcion;
}

void mostrarAlgoritmos() {
    cout << "1. Swap Sort\n"
         << "2. Bubble Sort\n"
         << "3. Selection Sort\n"
         << "4. Insertion Sort\n"
         << "5. Merge Sort\n"
         << "6. Quick Sort\n"
         << "7. Shell Sort\n";
}

template <typename T>
void ejecutarOrdenamiento(const vector<T> &datos, int algoritmo) {
    long long comparaciones;
    long long intercambios;
    auto inicio = chrono::high_resolution_clock::now();
    vector<T> resultado = ordenar(datos, algoritmo, comparaciones, intercambios);
    auto fin = chrono::high_resolution_clock::now();
    long long tiempo = chrono::duration_cast<chrono::nanoseconds>(fin - inicio).count();
    cout << "Lista ordenada:";
    printVect(resultado);
    cout << "Tiempo: " << tiempo << " nanosegundos\n";
    if (algoritmo <= 4) {
        cout << "Comparaciones: " << comparaciones << "\n";
        cout << "Intercambios: " << intercambios << "\n";
    }
}

template <typename T>
void escribirTiempos(ofstream &archivo, const string &tipo, const array<vector<T>, 3> &listas) {
    array<string, 7> nombres = {"swapSort", "bubbleSort", "selectionSort", "insertionSort", "mergeSort", "quickSort", "shellSort"};
    for (int algoritmo = 1; algoritmo <= 7; algoritmo++) {
        archivo << nombres[algoritmo - 1] << ',' << tipo;
        for (const vector<T> &lista : listas) {
            archivo << ',' << medir(lista, algoritmo);
        }
        archivo << '\n';
        cout << "Completado: " << nombres[algoritmo - 1] << " con " << tipo << "\n";
    }
}

int main() {
    mt19937 generador(random_device{}());
    array<vector<int>, 3> enteros;
    array<vector<double>, 3> reales;
    array<vector<char>, 3> caracteres;
    array<bool, 3> creadas = {false, false, false};
    int opcion = 0;

    while (opcion != 4) {
        cout << "\n1. Crear listas aleatorias\n"
             << "2. Ordenar una lista\n"
             << "3. Generar analisis comparativo CSV\n"
             << "4. Salir\n"
             << "Selecciona una opcion: ";
        opcion = leerOpcion(1, 4);

        if (opcion == 1) {
            cout << "1. int\n2. double\n3. char\nSelecciona el tipo de dato: ";
            int tipo = leerOpcion(1, 3);
            if (tipo == 1) {
                enteros = crearEnteros(generador);
            } else if (tipo == 2) {
                reales = crearReales(generador);
            } else {
                caracteres = crearCaracteres(generador);
            }
            creadas[tipo - 1] = true;
            cout << "Listas de 1000, 10000 y 100000 datos creadas.\n";
        } else if (opcion == 2) {
            cout << "1. int\n2. double\n3. char\nSelecciona el tipo de dato: ";
            int tipo = leerOpcion(1, 3);
            if (!creadas[tipo - 1]) {
                cout << "Primero debes crear las listas de ese tipo.\n";
                continue;
            }
            cout << "1. 1000\n2. 10000\n3. 100000\nSelecciona el tamano: ";
            int tamano = leerOpcion(1, 3);
            mostrarAlgoritmos();
            cout << "Selecciona el algoritmo: ";
            int algoritmo = leerOpcion(1, 7);
            cout << fixed << setprecision(4);
            if (tipo == 1) {
                ejecutarOrdenamiento(enteros[tamano - 1], algoritmo);
            } else if (tipo == 2) {
                ejecutarOrdenamiento(reales[tamano - 1], algoritmo);
            } else {
                ejecutarOrdenamiento(caracteres[tamano - 1], algoritmo);
            }
        } else if (opcion == 3) {
            if (!creadas[0]) {
                enteros = crearEnteros(generador);
                creadas[0] = true;
            }
            if (!creadas[1]) {
                reales = crearReales(generador);
                creadas[1] = true;
            }
            if (!creadas[2]) {
                caracteres = crearCaracteres(generador);
                creadas[2] = true;
            }
            ofstream archivo("tiempos.csv");
            if (!archivo) {
                cout << "No se pudo crear tiempos.csv.\n";
                continue;
            }
            archivo << "algoritmo,tipo_de_dato,tiempo1000,tiempo10000,tiempo100000\n";
            escribirTiempos(archivo, "int", enteros);
            escribirTiempos(archivo, "double", reales);
            escribirTiempos(archivo, "char", caracteres);
            cout << "Analisis guardado en tiempos.csv.\n";
        }
    }
    return 0;
}
