#include <iostream>
#include <string>

template <typename T>
class Node {
    public:
        Node(T value, Node* next) {
            m_next = next;
            m_value = value;
        }

        T m_value;
        Node* m_next;
};

template <typename T>
class Queue {
    public:
        Queue() {
            m_head = nullptr;
            m_tail = nullptr;
            m_size = 0;
        }

        ~Queue() {
            while (!empty()) {
                pop();
            }
        }

        void pop() {
            if (m_head == nullptr) {
                return;
            }
            Node<T>* old_head = m_head;
            m_head = old_head->m_next;
            if (m_head == nullptr) {
                m_tail = nullptr;
            }
            delete old_head;
            m_size--;
        }

        void add(T value) {
            Node<T>* node = new Node<T>(value, nullptr);
            if (m_head == nullptr) {
                m_head = node;
            } else {
                m_tail->m_next = node;
            }
            m_tail = node;
            m_size++;
        }

        T& front() {
            return m_head->m_value;
        }

        bool empty() {
            return m_head == nullptr;
        }

        int size() {
            return m_size;
        }

    private:
        Node<T>* m_head;
        Node<T>* m_tail;
        int m_size;
};

struct Cliente {
    std::string nombre;
    int boletos;
};

int main() {
    Queue<Cliente> fila;
    int opcion = 0;

    while (opcion != 5) {
        std::cout << "\n1. Llegada de un nuevo cliente\n"
                  << "2. Atender al siguiente cliente\n"
                  << "3. Ver al siguiente cliente\n"
                  << "4. Personas en la fila\n"
                  << "5. Salir\n"
                  << "Opcion: ";
        std::cin >> opcion;

        if (opcion == 1) {
            Cliente c;
            std::cout << "Nombre: ";
            std::cin >> c.nombre;
            std::cout << "Boletos: ";
            std::cin >> c.boletos;
            fila.add(c);
        } else if (opcion == 2 || opcion == 3) {
            if (fila.empty()) {
                std::cout << "La fila esta vacia\n";
                continue;
            }
            Cliente c = fila.front();
            std::cout << c.nombre << " pidio " << c.boletos << " boletos\n";
            if (opcion == 2) {
                fila.pop();
            }
        } else if (opcion == 4) {
            std::cout << "Hay " << fila.size() << " personas en la fila\n";
        }
    }

    return 0;
}
