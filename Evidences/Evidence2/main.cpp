#include <cassert>
#include "estructuras.h"
using namespace std;

void titulo(const char* t) { cout << "\n=== " << t << " ===\n"; }

void pruebaLista() {
    titulo("Lista ligada simple");
    LinkedList<int> l;
    cout << "Vacia: "; l.print();
    cout << "removeFirst en vacia -> " << (l.removeFirst() ? "borro" : "vacia, nada que borrar") << "\n";
    l.addFirst(1);
    cout << "Un elemento: "; l.print();
    assert(l.size() == 1);
    l.addFirst(0); l.addLast(2); l.addLast(3);
    cout << "Extremos (0 al inicio, 2 y 3 al final): "; l.print();
    l.removeFirst();
    cout << "Tras removeFirst: "; l.print();
    l.removeFirst(); l.removeFirst(); l.removeFirst();
    cout << "Vaciada: "; l.print();
    l.addLast(9); // head y tail deben haberse reiniciado bien
    cout << "addLast tras vaciar: "; l.print();
    assert(l.size() == 1);
}

void pruebaPila() {
    titulo("Pila");
    Stack<int> s;
    cout << "isEmpty: " << s.isEmpty() << ", size: " << s.size() << "\n";
    s.pop();
    s.peek();
    s.push(10);
    cout << "Un elemento, peek = " << *s.peek() << ", size = " << s.size() << "\n";
    s.push(20); s.push(30);
    cout << "Pila: "; s.print();
    cout << "peek = " << *s.peek() << "\n";
    s.pop(); s.pop();
    cout << "Tras 2 pops, peek = " << *s.peek() << "\n";
    s.pop();
    cout << "isEmpty: " << s.isEmpty() << "\n";
    s.pop();
    assert(s.isEmpty());
}

void pruebaFila() {
    titulo("Fila");
    Queue<string> q;
    cout << "isEmpty: " << q.isEmpty() << ", size: " << q.size() << "\n";
    q.dequeue();
    q.front();
    q.enqueue("Ana");
    cout << "Un elemento, front = " << *q.front() << ", size = " << q.size() << "\n";
    q.enqueue("Beto"); q.enqueue("Carla");
    cout << "Fila: "; q.print();
    cout << "front = " << *q.front() << "\n";
    q.dequeue();
    cout << "Tras dequeue, front = " << *q.front() << "\n";
    q.dequeue(); q.dequeue();
    cout << "isEmpty: " << q.isEmpty() << "\n";
    q.dequeue();
    q.enqueue("Dani"); // reutilizable tras vaciarse
    cout << "enqueue tras vaciar: "; q.print();
    assert(q.size() == 1);
}

void pruebaDoble() {
    titulo("Lista doblemente ligada");
    DoublyLinkedList<int> d;
    d.printForward(); d.printBackward();
    d.remove(nullptr);
    d.insertAfter(nullptr, 1);

    auto* a = d.addFirst(5);
    cout << "Un elemento:\n"; d.printForward(); d.printBackward();
    d.remove(a);
    cout << "Borrado el unico:\n"; d.printForward(); d.printBackward();
    assert(d.size() == 0 && !d.getHead() && !d.getTail());

    auto* x = d.addLast(2);
    d.addFirst(1);
    auto* z = d.addLast(4);
    cout << "Extremos:\n"; d.printForward(); d.printBackward();
    d.insertAfter(x, 3);   // en medio
    d.insertAfter(z, 5);   // despues del ultimo: actualiza tail
    cout << "insertAfter en medio y en la cola:\n"; d.printForward(); d.printBackward();
    assert(d.getTail()->v == 5);
    d.remove(d.getHead());
    d.remove(d.getTail());
    d.remove(x);           // nodo intermedio
    cout << "Borrados cabeza, cola y un intermedio:\n"; d.printForward(); d.printBackward();
    assert(d.size() == 2);
}

int main() {
    pruebaLista();
    pruebaPila();
    pruebaFila();
    pruebaDoble();
    cout << "\nTodas las pruebas pasaron\n";
}
