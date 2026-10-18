#include <chrono>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <map>
#include "../include/Queue.h"
#include "../include/Stack.h"
#include "../include/DoublyLinkedList.h"
#include "../include/Registro.h"
using namespace std;

struct Linea { int num; string texto; };
ostream& operator<<(ostream& o, const Linea& l) { return o << l.texto; }

// Lee el archivo, encola cada linea, y un procesador la desencola, valida e inserta al final de la lista.
// Regresa false si el archivo no se pudo abrir.
bool cargar(const string& archivo, DoublyLinkedList<Registro>& lista, int& omitidas) {
    ifstream f(archivo);
    if (!f) f.open("data/" + archivo);  // tambien busca en la carpeta data/
    if (!f) return false;

    Queue<Linea> fila;
    string texto;
    int num = 0;
    while (getline(f, texto)) {
        if (!texto.empty() && texto.back() == '\r') texto.pop_back();  // archivos de Windows
        fila.enqueue({++num, texto});
    }

    omitidas = 0;
    while (!fila.isEmpty()) {
        Linea l = *fila.front();
        fila.dequeue();
        Registro r;
        string err;
        if (parseRegistro(l.texto, r, err)) lista.addLast(r);
        else { omitidas++; cout << "  Linea " << l.num << " omitida: " << err << "\n"; }
    }
    return true;
}

using Lista = DoublyLinkedList<Registro>;
auto menorFecha = [](const Registro& a, const Registro& b) { return a.clave < b.clave; };

// Lee una linea. false si se acabo la entrada
bool leerLinea(const string& msg, string& s) {
    cout << msg;
    getline(cin, s);
    return (bool)cin;
}

// Pide un entero del 1 al max. repite hasta que sea valido. -1 si se acabo la entrada
int pedirOpcion(const string& msg, int max) {
    string s;
    while (leerLinea(msg, s)) {
        if (s.empty()) { cout << "No escribiste nada.\n"; continue; }
        if (soloDigitos(s) && s.size() < 4 && stoi(s) >= 1 && stoi(s) <= max) return stoi(s);
        cout << "Opcion invalida: elige un numero del 1 al " << max << ".\n";
    }
    return -1;
}

// Pide un dia tipo "Sep 14 2024" y lo valida
long long pedirDia() {
    string s;
    while (leerLinea("Dia a buscar (ej. Sep 14 2024): ", s)) {
        istringstream in(s);
        string m, d, a, extra;
        in >> m >> d >> a;
        if (s.find_first_not_of(" \t") == string::npos) { cout << "No escribiste nada.\n"; continue; }
        string err;
        long long dia = 0;
        if (in.fail()) err = "usa el formato Mes dd yyyy";
        else if (in >> extra) err = "sobran datos, usa el formato Mes dd yyyy";
        else dia = parseDia(m, d, a, err);
        if (dia) return dia;
        cout << "Formato de dia invalido: " << err << ".\n";
    }
    return 0;
}

void escribirSalida(const Lista& lista, const string& nombre) {
    filesystem::create_directories(filesystem::path(nombre).parent_path());
    ofstream out(nombre);
    for (auto* p = lista.getHead(); p; p = p->next) out << p->v.original << "\n";
}

void ordenar(Lista& lista, const string& archivo, bool& ordenada) {
    if (lista.size() == 0) { cout << "No hay registros que ordenar.\n"; return; }
    if (ordenada || lista.isSorted(menorFecha)) {
        ordenada = true;
        cout << "La lista ya esta ordenada por fecha y hora; no hace falta ordenar de nuevo.\n";
        return;
    }
    cout << "Prediccion del crecimiento de comparaciones:\n  1) ~ n log n\n  2) ~ n^2\n";
    int pred = pedirOpcion("Tu prediccion: ", 2);
    if (pred < 0) return;

    long long comps;
    int prof;
    auto t0 = chrono::steady_clock::now();
    lista.mergeSort(menorFecha, comps, prof);
    double ms = chrono::duration<double, milli>(chrono::steady_clock::now() - t0).count();
    ordenada = true;
    escribirSalida(lista, "out/output607.out");

    double n = lista.size();
    double nlogn = n * log2(n);
   

    int real = comps <= 2 * nlogn ? 1 : 2;
    cout << fixed << setprecision(3)
         << "\n--- Resultado ---\n"
         << "Algoritmo:            Merge Sort (sobre la lista doblemente ligada)\n"
         << "Archivo:              " << archivo << "\n"
         << "Tamano de los datos:  " << lista.size() << " registros\n"
         << "Tiempo:               " << ms << " ms\n"
         << "Comparaciones:        " << comps << "  (n log2 n = " << (long long)nlogn << ", n^2 = " << (long long)(n * n) << ")\n"
         << "Profundidad maxima:   " << prof << "\n"
         << "Crecimiento real:     ~ " << (real == 1 ? "n log n" : "n^2") << "\n"
         << "Tu prediccion:        " << (pred == real ? "COINCIDIO" : "NO coincidio") << "\n"
         << "Datos ordenados guardados en out/output607.out\n";
}

// Recorre la lista ordenada y llama accion(registro) por cada registro del dia.
// Se detiene en cuanto pasas del dia buscado. Regresa cuantos encontro.
template <typename F>
int recorrerDia(const Lista& lista, long long dia, F accion) {
    int total = 0;
    for (auto* p = lista.getHead(); p; p = p->next) {
        if (p->v.dia() < dia) continue;
        if (p->v.dia() > dia) break;
        accion(p->v);
        total++;
    }
    return total;
}

void buscarDia(const Lista& lista, bool ordenada, long long& ultimoDia) {
    if (!ordenada) { cout << "La lista aun no esta ordenada. Primero usa la opcion 1.\n"; return; }
    long long dia = pedirDia();
    if (!dia) return;
    ultimoDia = dia;
    cout << "\n";
    int total = recorrerDia(lista, dia, [](const Registro& r) { cout << r << "\n"; });
    if (total == 0) cout << "No hay registros para ese dia.\n";
    else cout << "\nTotal encontrado: " << total << "\n";
}

// yyyymmdd -> "Sep 08 2024"
string formatoDia(long long d) {
    ostringstream o;
    o << MESES[(d / 100 % 100) - 1] << " " << setfill('0') << setw(2) << d % 100 << " " << d / 10000;
    return o.str();
}

// Usa una Pila para invertir: push al recorrer (ascendente), pop al mostrar (descendente)
void mostrarDescendente(const Lista& lista, bool ordenada, long long& ultimoDia) {
    if (!ordenada) { cout << "La lista aun no esta ordenada. Primero usa la opcion 1.\n"; return; }
    if (!ultimoDia) {
        cout << "Aun no has buscado ningun dia, indica cual quieres ver.\n";
        ultimoDia = pedirDia();
        if (!ultimoDia) return;
    } else {
        cout << "Dia de la ultima busqueda: " << formatoDia(ultimoDia) << "\n";
    }
    Stack<Registro> pila;
    recorrerDia(lista, ultimoDia, [&](const Registro& r) { pila.push(r); });
    if (pila.isEmpty()) { cout << "No hay registros para ese dia.\n"; return; }
    int total = pila.size();
    cout << "\n";
    while (!pila.isEmpty()) { cout << *pila.peek() << "\n"; pila.pop(); }
    cout << "\nTotal mostrado: " << total << " (orden descendente)\n";
}

// Imprime la(s) llave(s) con mas apariciones; si hay empate, todas
template <typename K, typename Fmt>
void maximos(const string& titulo, const map<K, int>& cuenta, Fmt fmt) {
    int max = 0;
    for (auto& kv : cuenta) max = std::max(max, kv.second);
    cout << titulo << (max ? "" : ": -") << "\n";
    for (auto& kv : cuenta)
        if (kv.second == max) cout << "    " << fmt(kv.first) << "  (" << max << " apariciones)\n";
}

void estadisticas(const Lista& lista) {
    if (lista.size() == 0) { cout << "No hay registros para calcular estadisticas.\n"; return; }
    map<long long, int> dias;
    map<string, int> eventos, ips;
    for (auto* p = lista.getHead(); p; p = p->next) {
        dias[p->v.dia()]++;
        eventos[p->v.desc]++;
        ips[p->v.ip]++;
    }
    cout << "\n--- Estadisticas ---\nTotal de registros: " << lista.size() << "\n";
    maximos("Dia(s) con mas incidentes:", dias, formatoDia);
    maximos("Tipo(s) de evento mas frecuente(s):", eventos, [](const string& s) { return s; });
    maximos("Direccion(es) IP que mas aparece(n):", ips, [](const string& s) { return s; });
}

int main() {
    Lista lista;
    string archivo;
    int omitidas = 0;

    while (true) {
        if (!leerLinea("Archivo a cargar (log607-1.txt / log607-2.txt): ", archivo)) return 0;
        if (archivo.empty()) { cout << "Escribe el nombre del archivo.\n"; continue; }
        if (cargar(archivo, lista, omitidas)) break;
        cout << "No se pudo abrir '" << archivo << "'. Intenta de nuevo.\n";
    }
    cout << "Registros cargados: " << lista.size() << "\nLineas omitidas: " << omitidas << "\n";

    bool ordenada = false;
    long long ultimoDia = 0;  // dia de la ultima busqueda, lo reutiliza la opcion 3
    while (true) {
        cout << "\n===== MENU =====\n"
                "1) Ordenar por fecha y hora\n"
                "2) Buscar logs por dia\n"
                "3) Mostrar logs por dia en orden descendente\n"
                "4) Estadisticas del archivo\n"
                "5) Salir\n";
        int op = pedirOpcion("Opcion: ", 5);
        if (op < 0 || op == 5) break;
        if (op == 1) ordenar(lista, archivo, ordenada);
        else if (op == 2) buscarDia(lista, ordenada, ultimoDia);
        else if (op == 3) mostrarDescendente(lista, ordenada, ultimoDia);
        else estadisticas(lista);
    }
    cout << "Hasta luego.\n";
}
