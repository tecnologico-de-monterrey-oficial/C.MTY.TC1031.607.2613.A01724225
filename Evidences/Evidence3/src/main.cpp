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
    }
    cout << "Hasta luego.\n";
}
