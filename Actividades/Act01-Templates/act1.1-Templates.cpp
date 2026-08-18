#include <iostream>
#include <string>
#include "Lista.h"

using namespace std;

int main() {
    // ==========================================
    // 1. PRUEBAS CON TIPO: int
    // ==========================================
    cout << "========================================\n";
    cout << "         PRUEBAS CON LISTA DE INT       \n";
    cout << "========================================\n";
    
    Lista<int> listaInt;

    listaInt.insert(10);
    listaInt.insert(20);
    listaInt.insert(40);
    cout << "--- Contenido inicial ---\n";
    listaInt.print();

    cout << "\n[Accion] Insertar 30 en la posicion 2:\n";
    listaInt.insertAt(2, 30);
    listaInt.print();

    cout << "\nTamano actual: " << listaInt.getSize() << "\n";
    cout << "Elemento maximo: " << listaInt.getMax() << "\n";

    if (auto dato = listaInt.getData(2); dato.has_value()) {
        cout << "Dato en posicion 2: " << *dato << "\n";
    }

    cout << "\n[Accion] Eliminar elemento en posicion 1:\n";
    listaInt.removeAt(1);
    listaInt.print();

    cout << "\n[Accion] removeLast:\n";
    listaInt.removeLast();
    listaInt.print();


    // ==========================================
    // 2. PRUEBAS CON TIPO: std::string
    // ==========================================
    cout << "\n========================================\n";
    cout << "       PRUEBAS CON LISTA DE STRING      \n";
    cout << "========================================\n";

    Lista<string> listaStr;

    listaStr.insert("Alfa");
    listaStr.insert("Charlie");
    listaStr.insert("Delta");
    cout << "--- Contenido inicial ---\n";
    listaStr.print();

    cout << "\n[Accion] Insertar 'Bravo' en posicion 1:\n";
    listaStr.insertAt(1, "Bravo");
    listaStr.print();

    cout << "\nElemento maximo (lexicografico): " << listaStr.getMax() << "\n";

    if (auto datoStr = listaStr.getData(0); datoStr.has_value()) {
        cout << "Primer elemento: " << *datoStr << "\n";
    }

    cout << "\n[Accion] Eliminar primer elemento (pos 0):\n";
    listaStr.removeAt(0);
    listaStr.print();


    // ==========================================
    // 3. PRUEBAS CON TIPO: double Y CASOS BORDE
    // ==========================================
    cout << "\n========================================\n";
    cout << "       PRUEBAS CON DOUBLE Y BORDES      \n";
    cout << "========================================\n";

    Lista<double> listaDouble;

    cout << "[Borde] removeLast en lista vacia:\n";
    listaDouble.removeLast();

    cout << "\n[Borde] getData en lista vacia:\n";
    listaDouble.getData(0);

    // Insertar decimales
    listaDouble.insert(3.1416);
    listaDouble.insert(2.7182);
    listaDouble.insert(1.4142);
    cout << "\n--- Lista de doubles ---\n";
    listaDouble.print();

    cout << "\nValor maximo: " << listaDouble.getMax() << "\n";

    cout << "\n[Borde] Acceder a posicion fuera de rango (pos 5):\n";
    listaDouble.getData(5);

    return 0;
}