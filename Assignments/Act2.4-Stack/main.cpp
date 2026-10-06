#include <iostream>
#include <string>

template <typename T>
class Node {
    public:
        Node(T value, Node<T>* next) {
            m_next = next;
            m_value = value;
        }

        T m_value;
        Node<T>* m_next;
};

template <typename T>
class Stack {
    public:
        Stack() {
            m_head = nullptr;
            m_size = 0;
        }

        ~Stack() {
            while (!isEmpty()) pop();
        }

        void push(T value) {
            m_head = new Node<T>(value, m_head);
            m_size++;
        }

        void pop() {
            if (m_head == nullptr) return;

            Node<T>* old = m_head;
            m_head = m_head->m_next;
            delete old;
            m_size--;
        }

        T& top() {
            return m_head->m_value;
        }

        bool isEmpty() {
            return m_head == nullptr;
        }

        int size() {
            return m_size;
        }

    private:
        Node<T>* m_head;
        int m_size;
};

struct PaginaWeb {
    std::string titulo;
    std::string url;
};

int main() {
    Stack<PaginaWeb> historial;
    int opcion = 0;

    while (opcion != 5) {
        std::cout << "\n1. Visitar una nueva pagina\n"
                  << "2. Retroceder a la pagina anterior\n"
                  << "3. Ver la pagina actual\n"
                  << "4. Mostrar cuantas paginas hay en el historial\n"
                  << "5. Salir\n"
                  << "Opcion: ";
        std::cin >> opcion;
        std::cin.ignore(10000, '\n');

        if (opcion == 1) {
            PaginaWeb pagina;
            std::cout << "Titulo: ";
            std::getline(std::cin, pagina.titulo);
            std::cout << "URL: ";
            std::getline(std::cin, pagina.url);
            historial.push(pagina);
        } else if (opcion == 2) {
            if (historial.isEmpty()) {
                std::cout << "El historial esta vacio\n";
            } else {
                std::cout << "Se cerro: " << historial.top().titulo << " (" << historial.top().url << ")\n";
                historial.pop();
            }
        } else if (opcion == 3) {
            if (historial.isEmpty()) {
                std::cout << "El historial esta vacio\n";
            } else {
                std::cout << "Pagina actual: " << historial.top().titulo << " - " << historial.top().url << "\n";
            }
        } else if (opcion == 4) {
            std::cout << "Paginas en el historial: " << historial.size() << "\n";
        }
    }

    return 0;
}
