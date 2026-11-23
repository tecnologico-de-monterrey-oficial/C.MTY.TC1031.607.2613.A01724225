#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "../include/BST.h"
#include "../include/Heap.h"
#include "../include/HeapSort.h"
#include "../include/IP.h"

using namespace std;

int fallas = 0;

void revisar(bool ok, const string& que) {
    cout << (ok ? "[ok]    " : "[falla] ") << que << "\n";
    if (!ok) fallas++;
}

void pruebasHeap() {
    cout << "\nheap\n";
    MaxHeap<int> mx;
    MinHeap<int> mn;
    revisar(mx.empty() && mx.height() == 0, "heap vacio con altura cero");
    revisar(!mx.pop(), "pop en heap vacio regresa false");

    for (int x : {5, 3, 8, 1, 9, 2, 7}) {
        mx.push(x);
        mn.push(x);
    }
    revisar(mx.size() == 7 && mx.height() == 3, "siete elementos, altura tres");
    revisar(mx.top() == 9, "maxheap tiene el 9 arriba");
    revisar(mn.top() == 1, "minheap tiene el 1 arriba");
    mx.pop();
    mn.pop();
    revisar(mx.top() == 8 && mn.top() == 2, "despues de pop quedan 8 y 2");
    revisar(mx.getComparaciones() > 0, "el contador de comparaciones avanza");

    bool lanzo = false;
    try { MinHeap<int>().top(); } catch (const out_of_range&) { lanzo = true; }
    revisar(lanzo, "top en heap vacio lanza excepcion");
}

void pruebasHeapSort() {
    cout << "\nheap sort\n";
    vector<int> v = {9, 4, 7, 1, 8, 2, 2, 6};
    long long c = heapSort(v);
    revisar(v == vector<int>({1, 2, 2, 4, 6, 7, 8, 9}), "ascendente");
    cout << "        comparaciones: " << c << "\n";

    heapSort(v, greater<int>());
    revisar(v == vector<int>({9, 8, 7, 6, 4, 2, 2, 1}), "descendente");

    vector<IP> ips = {IP("10.14.0.10"), IP("10.14.0.9"), IP("9.255.255.255")};
    heapSort(ips);
    revisar(ips[0].texto == "9.255.255.255" && ips[1].texto == "10.14.0.9", "ips ordenadas como numero");
}

void pruebasBST() {
    cout << "\nbst\n";
    BST<IP> t;
    revisar(t.size() == 0 && t.height() == 0, "arbol vacio");

    for (string s : {"10.14.0.10", "10.14.0.9", "192.168.1.1", "10.14.0.9", "172.16.0.1", "10.14.0.9"})
        t.insert(IP(s));
    revisar(t.size() == 4, "repetidas no crean nodo, quedan 4");

    Busqueda b = t.search(IP("10.14.0.9"));
    revisar(b.contador == 3, "10.14.0.9 aparece 3 veces");
    cout << "        comparaciones: " << b.comparaciones << "\n";
    revisar(t.search(IP("1.1.1.1")).contador == 0, "ip que no existe regresa cero");

    vector<unsigned int> orden;
    t.inorden([&orden](const IP& ip, int) { orden.push_back(ip.valor); });
    bool creciente = true;
    for (size_t i = 1; i < orden.size(); i++) if (orden[i - 1] >= orden[i]) creciente = false;
    revisar(creciente, "inorden sale de menor a mayor");
    t.imprimir();
}

// carga las ips del json para probar con datos reales
void pruebaArchivo(const string& ruta) {
    cout << "\narchivo " << ruta << "\n";
    ifstream f(ruta);
    if (!f) { cout << "no se pudo abrir, se omite\n"; return; }

    BST<IP> t;
    string linea, marca = "\"ip\": \"";
    int total = 0;
    while (getline(f, linea)) {
        size_t p = linea.find(marca);
        if (p == string::npos) continue;
        p += marca.size();
        string ip = linea.substr(p, linea.find('"', p) - p), err;
        if (!ipValida(ip, err)) continue;
        t.insert(IP(ip));
        total++;
    }

    int suma = 0;
    t.inorden([&suma](const IP&, int c) { suma += c; });
    cout << "registros: " << total << ", ips distintas: " << t.size() << ", altura: " << t.height() << "\n";
    revisar(suma == total, "la suma de contadores es igual al total de registros");
}

int main() {
    pruebasHeap();
    pruebasHeapSort();
    pruebasBST();
    pruebaArchivo("data/log607-3.json");
    cout << "\n" << (fallas ? to_string(fallas) + " pruebas fallaron" : "todo bien") << "\n";
    return fallas != 0;
}
