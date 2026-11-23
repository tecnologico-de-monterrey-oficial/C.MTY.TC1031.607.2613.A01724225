#include <chrono>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include "../include/BST.h"
#include "../include/Heap.h"
#include "../include/IP.h"
#include "../include/Registro.h"

using namespace std;

// lee el archivo, valida cada linea y cuenta las ips con el bst
// regresa false si no se pudo abrir
bool cargar(const string& archivo, vector<Registro>& registros, BST<IP>& ips, int& omitidas) {
    ifstream f(archivo);
    if (!f) f.open("data/" + archivo);
    if (!f) return false;

    string linea;
    int num = 0;
    omitidas = 0;
    while (getline(f, linea)) {
        num++;
        if (!linea.empty() && linea.back() == '\r') linea.pop_back();
        size_t ini = linea.find_first_not_of(" \t");
        if (ini == string::npos || linea[ini] == '[' || linea[ini] == ']') continue;

        Registro r;
        string err;
        if (parseRegistro(linea, r, err)) {
            registros.push_back(r);
            ips.insert(r.ip);
        } else {
            omitidas++;
            cout << "  linea " << num << " omitida: " << err << "\n";
        }
    }
    return true;
}

// lee una linea, false si ya no hay entrada
bool leerLinea(const string& msg, string& s) {
    cout << msg;
    getline(cin, s);
    return (bool)cin;
}

string recortar(const string& s) {
    size_t a = s.find_first_not_of(" \t\r");
    if (a == string::npos) return "";
    size_t b = s.find_last_not_of(" \t\r");
    return s.substr(a, b - a + 1);
}

// pide un numero del uno al max y repite hasta que sea valido
// regresa menos uno si se acabo la entrada
int pedirOpcion(const string& msg, int max) {
    string s;
    while (leerLinea(msg, s)) {
        s = recortar(s);
        if (s.empty()) { cout << "No escribiste nada.\n"; continue; }
        if (soloDigitos(s) && s.size() < 4 && stoi(s) >= 1 && stoi(s) <= max) return stoi(s);
        cout << "Opcion invalida: elige un numero del 1 al " << max << ".\n";
    }
    return -1;
}

// mete los primeros n registros al heap y los saca uno por uno
// deja en altura lo alto que quedo el heap con todos adentro
template <typename Comp>
long long ordenarConHeap(const vector<Registro>& registros, size_t n, vector<Registro>* salida, int& altura) {
    Heap<Registro, Comp> h;
    for (size_t i = 0; i < n; i++) h.push(registros[i]);
    altura = h.height();
    while (!h.empty()) {
        if (salida) salida->push_back(h.top());
        h.pop();
    }
    return h.getComparaciones();
}

const char* PREDICCIONES[4] = {
    "aproximadamente igual",
    "aproximadamente el doble",
    "un poco mas del doble",
    "aproximadamente el cuadruple",
};

// decide en que opcion cae la razon entre las comparaciones con n y con la mitad
int clasificar(double razon) {
    if (razon < 1.5) return 1;
    if (razon < 2.05) return 2;
    if (razon < 3.0) return 3;
    return 4;
}

template <typename Comp>
void ordenar(const vector<Registro>& registros, const string& nombreHeap, const string& sentido, const string& salida) {
    if (registros.size() < 2) { cout << "Se necesitan al menos 2 registros para ordenar.\n"; return; }

    cout << "\nPrediccion: si el archivo tuviera el doble de registros, el numero de comparaciones seria...\n";
    for (int i = 0; i < 4; i++) cout << "  " << i + 1 << ") " << PREDICCIONES[i] << "\n";
    int pred = pedirOpcion("Tu prediccion: ", 4);
    if (pred < 0) return;

    vector<Registro> ordenados;
    ordenados.reserve(registros.size());
    int altura = 0;
    auto t0 = chrono::steady_clock::now();
    long long comps = ordenarConHeap<Comp>(registros, registros.size(), &ordenados, altura);
    double ms = chrono::duration<double, milli>(chrono::steady_clock::now() - t0).count();

    // no hay un archivo del doble, asi que se ordena la mitad y se compara contra todo
    // es la misma proporcion que pasar de n al doble de n
    int alturaMitad = 0;
    size_t mitad = registros.size() / 2;
    long long compsMitad = ordenarConHeap<Comp>(registros, mitad, nullptr, alturaMitad);
    double razon = (double)comps / compsMitad;
    int real = clasificar(razon);

    filesystem::create_directories("out");
    ofstream out("out/" + salida);
    for (const Registro& r : ordenados) out << r << "\n";
    out.close();

    double n = registros.size();
    cout << fixed << setprecision(3)
         << "\n--- Resultado ---\n"
         << "Algoritmo:          Heap Sort con " << nombreHeap << ", " << sentido << "\n"
         << "Registros:          " << registros.size() << "\n"
         << "Tiempo:             " << ms << " ms\n"
         << "Comparaciones:      " << comps << "  (n log2 n = " << (long long)(n * log2(n)) << ")\n"
         << "Altura del heap:    " << altura << " niveles con todos los registros\n"
         << setprecision(2)
         << "Prueba con la mitad: " << mitad << " registros, " << compsMitad << " comparaciones\n"
         << "Al duplicar n las comparaciones crecen x" << razon << ", o sea " << PREDICCIONES[real - 1] << "\n"
         << "Tu prediccion:      " << PREDICCIONES[pred - 1] << " -> "
         << (pred == real ? "COINCIDIO" : "NO coincidio") << "\n"
         << "Archivo generado:   out/" << salida << "\n";
}

int main() {
    vector<Registro> registros;
    BST<IP> ips;
    int omitidas = 0;
    string archivo;

    while (true) {
        if (!leerLinea("Archivo a cargar (Enter para log607-3.json): ", archivo)) return 0;
        archivo = recortar(archivo);
        if (archivo.empty()) archivo = "log607-3.json";
        if (cargar(archivo, registros, ips, omitidas)) break;
        cout << "No se pudo abrir '" << archivo << "'. Intenta de nuevo.\n";
    }
    cout << "Registros validos: " << registros.size() << "\n"
         << "Lineas omitidas:   " << omitidas << "\n"
         << "IPs distintas:     " << ips.size() << "\n";

    while (true) {
        cout << "\n===== MENU =====\n"
                "1) Ordenar de mayor a menor (MaxHeap)\n"
                "2) Ordenar de menor a mayor (MinHeap)\n"
                "3) Top 10 de IPs con mas registros\n"
                "4) Buscar una IP\n"
                "5) Salir\n";
        int op = pedirOpcion("Opcion: ", 5);
        if (op < 0 || op == 5) break;

        // si algo truena se avisa y se regresa al menu en lugar de cerrar el programa
        try {
            if (op == 1) ordenar<greater<Registro>>(registros, "MaxHeap", "de mayor a menor", "output608-1.out");
        } catch (const exception& e) {
            cout << "Ocurrio un error: " << e.what() << ". Intenta de nuevo.\n";
        }
    }
    cout << "Hasta luego.\n";
}
