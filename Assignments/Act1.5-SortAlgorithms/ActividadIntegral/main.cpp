#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct Registro {
    long long fechaHora;
    string lineaOriginal;

    bool operator<(const Registro &otro) const {
        return fechaHora < otro.fechaHora;
    }

    bool operator>(const Registro &otro) const {
        return fechaHora > otro.fechaHora;
    }

    bool operator<=(const Registro &otro) const {
        return fechaHora <= otro.fechaHora;
    }
};

int numeroMes(const string &mes) {
    if (mes == "Jan") return 1;
    if (mes == "Feb") return 2;
    if (mes == "Mar") return 3;
    if (mes == "Apr") return 4;
    if (mes == "May") return 5;
    if (mes == "Jun") return 6;
    if (mes == "Jul") return 7;
    if (mes == "Aug") return 8;
    if (mes == "Sep") return 9;
    if (mes == "Oct") return 10;
    if (mes == "Nov") return 11;
    if (mes == "Dec") return 12;

    return 0;
}

long long crearClaveFecha(
    int anio,
    int mes,
    int dia,
    int hora,
    int minuto,
    int segundo
) {
    long long clave = anio;

    clave = clave * 100 + mes;
    clave = clave * 100 + dia;
    clave = clave * 100 + hora;
    clave = clave * 100 + minuto;
    clave = clave * 100 + segundo;

    return clave;
}

vector<Registro> leerArchivo(const string &nombreArchivo) {
    ifstream archivo(nombreArchivo);
    vector<Registro> registros;

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo: " << nombreArchivo << '\n';
        return registros;
    }

    string linea;

    while (getline(archivo, linea)) {
        if (linea.empty()) {
            continue;
        }

        istringstream entrada(linea);
        string mesTexto;
        string horaTexto;
        int dia;
        int anio;

        entrada >> mesTexto >> dia >> anio >> horaTexto;

        int mes = numeroMes(mesTexto);

        if (entrada.fail() || mes == 0 || horaTexto.size() != 8) {
            cout << "Linea invalida: " << linea << '\n';
            continue;
        }

        int hora = stoi(horaTexto.substr(0, 2));
        int minuto = stoi(horaTexto.substr(3, 2));
        int segundo = stoi(horaTexto.substr(6, 2));

        Registro registro;
        registro.fechaHora = crearClaveFecha(
            anio,
            mes,
            dia,
            hora,
            minuto,
            segundo
        );
        registro.lineaOriginal = linea;

        registros.push_back(registro);
    }

    return registros;
}

bool guardarArchivo(
    const string &nombreArchivo,
    const vector<Registro> &registros
) {
    ofstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cout << "No se pudo crear el archivo: " << nombreArchivo << '\n';
        return false;
    }

    for (const Registro &registro : registros) {
        archivo << registro.lineaOriginal << '\n';
    }

    return true;
}

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
