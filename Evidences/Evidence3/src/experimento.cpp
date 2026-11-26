#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include "../include/BST.h"
#include "../include/IP.h"
#include "../include/Registro.h"

using namespace std;

// mete las ips al arbol en el orden dado y mide altura y comparaciones de busqueda
void medir(const string& nombre, const vector<IP>& orden, const vector<IP>& distintas) {
    BST<IP> t;
    for (const IP& ip : orden) t.insert(ip);

    long long suma = 0;
    int peor = 0;
    for (const IP& ip : distintas) {
        int c = t.search(ip).comparaciones;
        suma += c;
        if (c > peor) peor = c;
    }
    cout << left << setw(26) << nombre << right << setw(8) << t.size() << setw(9) << t.height()
         << setw(14) << fixed << setprecision(1) << (double)suma / distintas.size() << setw(12) << peor << "\n";
}

int main() {
    ifstream f("data/log607-3.json");
    if (!f) { cout << "No se pudo abrir data/log607-3.json\n"; return 1; }

    // las ips de los registros validos en el orden en que vienen en el archivo
    vector<IP> archivo;
    string linea, err;
    while (getline(f, linea)) {
        Registro r;
        if (parseRegistro(linea, r, err)) archivo.push_back(r.ip);
    }

    // el inorden del arbol da las ips distintas ya ordenadas de menor a mayor
    BST<IP> base;
    for (const IP& ip : archivo) base.insert(ip);
    vector<IP> ascendente, descendente;
    base.inorden([&ascendente](const IP& ip, int) { ascendente.push_back(ip); });
    for (int i = ascendente.size() - 1; i >= 0; i--) descendente.push_back(ascendente[i]);

    int n = ascendente.size();
    cout << "Experimento del BST con " << archivo.size() << " registros y " << n << " IPs distintas\n"
         << "Altura ideal: ceil(log2 " << n << ") = " << (int)ceil(log2(n)) << "\n\n"
         << left << setw(26) << "Orden de insercion" << right << setw(8) << "Nodos" << setw(9) << "Altura"
         << setw(14) << "Comp. prom." << setw(12) << "Comp. max." << "\n"
         << string(69, '-') << "\n";
    medir("Orden del archivo", archivo, ascendente);
    medir("IPs ordenadas ascendente", ascendente, ascendente);
    medir("IPs ordenadas descendente", descendente, ascendente);
}
