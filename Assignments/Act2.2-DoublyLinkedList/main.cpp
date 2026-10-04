#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
using namespace std;

template <class T>
class List {
    struct Node { T v; Node *prev, *next; };
    Node *head = nullptr, *tail = nullptr;
    int n = 0;

    Node* at(int i) const {
        if (i < 0 || i >= n) throw out_of_range("indice invalido");
        Node* p = head;
        while (i--) p = p->next;
        return p;
    }
    void unlink(Node* p) {
        if (p->prev) p->prev->next = p->next; else head = p->next;
        if (p->next) p->next->prev = p->prev; else tail = p->prev;
        delete p;
        n--;
    }

public:
    List() {}
    List(const List& o) { *this = o; }
    ~List() { clear(); }

    void clear() {
        while (head) { Node* t = head; head = head->next; delete t; }
        tail = nullptr;
        n = 0;
    }
    List& operator=(const List& o) {
        if (this != &o) {
            clear();
            for (Node* p = o.head; p; p = p->next) addLast(p->v);
        }
        return *this;
    }
    void addFirst(T v) {
        Node* x = new Node{v, nullptr, head};
        if (head) head->prev = x; else tail = x;
        head = x;
        n++;
    }
    void addLast(T v) {
        Node* x = new Node{v, tail, nullptr};
        if (tail) tail->next = x; else head = x;
        tail = x;
        n++;
    }
    void insertAfter(int i, T v) {
        Node* p = at(i);
        Node* x = new Node{v, p, p->next};
        if (p->next) p->next->prev = x; else tail = x;
        p->next = x;
        n++;
    }
    int find(T v) const {
        int i = 0;
        for (Node* p = head; p; p = p->next, i++)
            if (p->v == v) return i;
        return -1;
    }
    bool removeValue(T v) {
        int i = find(v);
        if (i < 0) return false;
        unlink(at(i));
        return true;
    }
    void removeAt(int i) { unlink(at(i)); }
    T get(int i) const { return at(i)->v; }
    bool update(T old, T nuevo) {
        int i = find(old);
        if (i < 0) return false;
        at(i)->v = nuevo;
        return true;
    }
    void updateAt(int i, T nuevo) { at(i)->v = nuevo; }
    T& operator[](int i) { return at(i)->v; }
    void print() const {
        cout << "[";
        for (Node* p = head; p; p = p->next) cout << p->v << (p->next ? ", " : "");
        cout << "] (" << n << " elementos)" << endl;
    }
};

void aleatorio(int& x) { x = rand() % 100; }
void aleatorio(string& x) {
    const char* palabras[] = {"manzana", "pera", "uva", "kiwi", "mango", "fresa"};
    x = palabras[rand() % 6];
}

template <class T>
T leer(const string& msg) {
    T x;
    cout << msg;
    cin >> x;
    return x;
}

template <class T>
void run() {
    List<T> l;
    int modo = leer<int>("Crear lista: 1) aleatoria  2) capturada: ");
    int cant = leer<int>("Cantidad de elementos: ");
    for (int i = 0; i < cant; i++) {
        T x;
        if (modo == 1) aleatorio(x); else x = leer<T>("Elemento: ");
        l.addLast(x);
    }
    int op;
    do {
        cout << "\nLista: ";
        l.print();
        cout << "1) Agregar al principio\n2) Agregar al final\n3) Insertar despues del indice\n"
                "4) Borrar elemento dado\n5) Borrar por posicion\n6) Obtener por posicion\n"
                "7) Actualizar elemento dado\n8) Actualizar por posicion\n9) Buscar elemento\n"
                "10) Obtener con operador []\n11) Actualizar con operador []\n12) Copiar lista (operador =)\n"
                "0) Salir\n";
        op = leer<int>("Opcion: ");
        try {
            if (op == 1) l.addFirst(leer<T>("Elemento: "));
            else if (op == 2) l.addLast(leer<T>("Elemento: "));
            else if (op == 3) { int i = leer<int>("Indice: "); l.insertAfter(i, leer<T>("Elemento: ")); }
            else if (op == 4) cout << (l.removeValue(leer<T>("Elemento: ")) ? "Borrado" : "No encontrado") << endl;
            else if (op == 5) l.removeAt(leer<int>("Posicion: "));
            else if (op == 6) cout << "Elemento: " << l.get(leer<int>("Posicion: ")) << endl;
            else if (op == 7) { T a = leer<T>("Elemento a cambiar: "); cout << (l.update(a, leer<T>("Nuevo valor: ")) ? "Actualizado" : "No encontrado") << endl; }
            else if (op == 8) { int i = leer<int>("Posicion: "); l.updateAt(i, leer<T>("Nuevo valor: ")); }
            else if (op == 9) { int i = l.find(leer<T>("Elemento: ")); if (i < 0) cout << "No encontrado" << endl; else cout << "Encontrado en posicion " << i << endl; }
            else if (op == 10) cout << "l[i] = " << l[leer<int>("Posicion: ")] << endl;
            else if (op == 11) { int i = leer<int>("Posicion: "); l[i] = leer<T>("Nuevo valor: "); }
            else if (op == 12) { List<T> copia; copia = l; cout << "Copia: "; copia.print(); }
        } catch (out_of_range& e) {
            cout << "Error: " << e.what() << endl;
        }
    } while (op != 0);
}

int main() {
    srand(time(nullptr));
    int tipo = leer<int>("Tipo de lista: 1) int  2) string: ");
    if (tipo == 1) run<int>(); else run<string>();
    return 0;
}
