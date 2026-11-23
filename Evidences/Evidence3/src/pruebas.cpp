#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "../include/BST.h"
#include "../include/Heap.h"
#include "../include/HeapSort.h"
#include "../include/IP.h"

using namespace std;

int fallas = 0, total = 0;

// imprime el caso con lo que se esperaba y lo que salio
void caso(const string& nombre, const string& esperado, const string& obtenido) {
    bool ok = esperado == obtenido;
    total++;
    if (!ok) fallas++;
    cout << (ok ? "[ok]    " : "[falla] ") << nombre << "\n"
         << "        esperado: " << esperado << "\n"
         << "        obtenido: " << obtenido << "\n";
}

string txt(bool b) { return b ? "true" : "false"; }

template <typename T>
string lista(const vector<T>& v) {
    string s = "[";
    for (size_t i = 0; i < v.size(); i++) {
        if (i) s += ", ";
        if constexpr (is_same<T, IP>::value) s += v[i].texto;
        else s += to_string(v[i]);
    }
    return s + "]";
}

// saca todo el heap en el orden en que sale la raiz
template <typename H>
vector<int> vaciar(H& h) {
    vector<int> v;
    while (!h.empty()) {
        v.push_back(h.top());
        h.pop();
    }
    return v;
}

void pruebasHeap() {
    cout << "\n=== Heap ===\n";
    MaxHeap<int> vacio;
    caso("heap vacio: size, empty, height", "0, true, 0",
         to_string(vacio.size()) + ", " + txt(vacio.empty()) + ", " + to_string(vacio.height()));
    caso("pop en heap vacio", "false", txt(vacio.pop()));

    string msg = "no lanzo";
    try { vacio.top(); } catch (const out_of_range& e) { msg = e.what(); }
    caso("top en heap vacio lanza excepcion", "heap vacio, no hay top", msg);

    MinHeap<int> uno;
    uno.push(42);
    caso("un elemento: top y height", "42, 1", to_string(uno.top()) + ", " + to_string(uno.height()));
    uno.pop();
    caso("pop del unico elemento lo deja vacio", "true", txt(uno.empty()));

    MaxHeap<int> mx;
    MinHeap<int> mn;
    for (int x : {5, 3, 8, 1, 9, 2, 7}) {
        mx.push(x);
        mn.push(x);
    }
    caso("siete elementos: size y height", "7, 3", to_string(mx.size()) + ", " + to_string(mx.height()));
    caso("maxheap: top", "9", to_string(mx.top()));
    caso("minheap: top", "1", to_string(mn.top()));
    caso("maxheap: sacar todo", "[9, 8, 7, 5, 3, 2, 1]", lista(vaciar(mx)));
    caso("minheap: sacar todo", "[1, 2, 3, 5, 7, 8, 9]", lista(vaciar(mn)));

    MaxHeap<int> dup;
    for (int i = 0; i < 4; i++) dup.push(4);
    caso("todos iguales", "[4, 4, 4, 4]", lista(vaciar(dup)));

    MaxHeap<int> c;
    for (int x : {1, 2, 3}) c.push(x);
    caso("contador de comparaciones avanza", "true", txt(c.getComparaciones() > 0));
    c.reiniciarComparaciones();
    caso("reiniciar contador", "0", to_string(c.getComparaciones()));
}

void pruebasHeapSort() {
    cout << "\n=== Heap Sort ===\n";
    vector<int> v;
    long long comps = heapSort(v);
    caso("arreglo vacio", "[], 0 comparaciones", lista(v) + ", " + to_string(comps) + " comparaciones");

    v = {7};
    comps = heapSort(v);
    caso("un elemento", "[7], 0 comparaciones", lista(v) + ", " + to_string(comps) + " comparaciones");

    v = {1, 2, 3, 4, 5};
    heapSort(v);
    caso("ya ordenado", "[1, 2, 3, 4, 5]", lista(v));

    v = {5, 4, 3, 2, 1};
    heapSort(v);
    caso("orden inverso", "[1, 2, 3, 4, 5]", lista(v));

    v = {9, 4, 7, 1, 8, 2, 2, 6};
    heapSort(v);
    caso("con repetidos, ascendente", "[1, 2, 2, 4, 6, 7, 8, 9]", lista(v));
    heapSort(v, greater<int>());
    caso("con repetidos, descendente", "[9, 8, 7, 6, 4, 2, 2, 1]", lista(v));

    vector<IP> ips = {IP("10.14.0.10"), IP("10.14.0.9"), IP("9.255.255.255")};
    heapSort(ips);
    caso("ips comparadas como numero", "[9.255.255.255, 10.14.0.9, 10.14.0.10]", lista(ips));
}

void pruebasIP() {
    cout << "\n=== Validacion de IP ===\n";
    string err;
    caso("10.14.0.9", "true", txt(ipValida("10.14.0.9", err)));
    caso("0.0.0.0 y 255.255.255.255", "true, true",
         txt(ipValida("0.0.0.0", err)) + ", " + txt(ipValida("255.255.255.255", err)));
    caso("10.14.12, faltan numeros", "false", txt(ipValida("10.14.12", err)));
    caso("10.14.256.7, numero mayor a 255", "false", txt(ipValida("10.14.256.7", err)));
    caso("1.2.3.4., punto al final", "false", txt(ipValida("1.2.3.4.", err)));
    caso("1..2.3, parte vacia", "false", txt(ipValida("1..2.3", err)));
    caso("a.b.c.d, letras", "false", txt(ipValida("a.b.c.d", err)));
    caso("texto vacio", "false", txt(ipValida("", err)));
}

void pruebasBST() {
    cout << "\n=== BST ===\n";
    BST<IP> vacio;
    Busqueda b = vacio.search(IP("1.1.1.1"));
    caso("arbol vacio: size, height", "0, 0", to_string(vacio.size()) + ", " + to_string(vacio.height()));
    caso("buscar en arbol vacio: contador, comparaciones", "0, 0",
         to_string(b.contador) + ", " + to_string(b.comparaciones));

    BST<IP> uno;
    uno.insert(IP("10.0.0.1"));
    b = uno.search(IP("10.0.0.1"));
    caso("un nodo: size, height, contador", "1, 1, 1",
         to_string(uno.size()) + ", " + to_string(uno.height()) + ", " + to_string(b.contador));

    BST<IP> t;
    for (string s : {"10.14.0.10", "10.14.0.9", "192.168.1.1", "10.14.0.9", "172.16.0.1", "10.14.0.9"})
        t.insert(IP(s));
    caso("seis inserciones, una ip repetida 3 veces: size", "4", to_string(t.size()));
    b = t.search(IP("10.14.0.9"));
    caso("buscar 10.14.0.9: contador, comparaciones", "3, 2",
         to_string(b.contador) + ", " + to_string(b.comparaciones));
    b = t.search(IP("1.2.3.4"));
    caso("buscar ip que no existe: contador", "0", to_string(b.contador));

    vector<IP> orden;
    t.inorden([&orden](const IP& ip, int) { orden.push_back(ip); });
    caso("inorden de menor a mayor como numero", "[10.14.0.9, 10.14.0.10, 172.16.0.1, 192.168.1.1]", lista(orden));

    BST<IP> lineal;
    for (string s : {"1.0.0.1", "1.0.0.2", "1.0.0.3", "1.0.0.4", "1.0.0.5"}) lineal.insert(IP(s));
    caso("insertar en orden degenera el arbol: height", "5", to_string(lineal.height()));
}

// carga las ips validas del json para probar con datos reales
void pruebaArchivo(const string& ruta) {
    cout << "\n=== Archivo " << ruta << " ===\n";
    ifstream f(ruta);
    if (!f) { cout << "no se pudo abrir, se omite\n"; return; }

    BST<IP> t;
    string linea, marca = "\"ip\": \"";
    int registros = 0;
    while (getline(f, linea)) {
        size_t p = linea.find(marca);
        if (p == string::npos) continue;
        p += marca.size();
        string ip = linea.substr(p, linea.find('"', p) - p), err;
        if (!ipValida(ip, err)) continue;
        t.insert(IP(ip));
        registros++;
    }

    int suma = 0;
    t.inorden([&suma](const IP&, int c) { suma += c; });
    cout << "registros con ip valida: " << registros << ", ips distintas: " << t.size()
         << ", altura: " << t.height() << "\n";
    caso("suma de contadores igual a registros", to_string(registros), to_string(suma));
}

int main() {
    pruebasHeap();
    pruebasHeapSort();
    pruebasIP();
    pruebasBST();
    pruebaArchivo("data/log607-3.json");
    cout << "\n" << total - fallas << " de " << total << " pruebas pasaron\n";
    return fallas != 0;
}
