#include <fstream>
#include "estructuras.h"
#include "registro.h"
using namespace std;

struct Linea { int num; string texto; };
ostream& operator<<(ostream& o, const Linea& l) { return o << l.texto; }

// Lee el archivo, encola cada linea, y un procesador la desencola, valida e inserta al final de la lista.
// Regresa false si el archivo no se pudo abrir.
bool cargar(const string& archivo, DoublyLinkedList<Registro>& lista, int& omitidas) {
    ifstream f(archivo);
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

int main() {
    DoublyLinkedList<Registro> lista;
    string archivo;
    int omitidas = 0;

    while (true) {
        cout << "Archivo a cargar (log608-1.txt / log608-2.txt): ";
        getline(cin, archivo);
        if (!cin) return 0;
        if (archivo.empty()) { cout << "Escribe el nombre del archivo.\n"; continue; }
        if (cargar(archivo, lista, omitidas)) break;
        cout << "No se pudo abrir '" << archivo << "'. Intenta de nuevo.\n";
    }
    cout << "Registros cargados: " << lista.size() << "\nLineas omitidas: " << omitidas << "\n";
}
