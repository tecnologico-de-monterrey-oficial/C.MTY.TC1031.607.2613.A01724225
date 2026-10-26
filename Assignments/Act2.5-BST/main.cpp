#include <iostream>
#include <string>
#include <queue>
#include <algorithm>

template <typename T>
class Node {
    public:
        Node(T value) {
            m_value = value;
            m_left = nullptr;
            m_right = nullptr;
        }

        T m_value;
        Node<T>* m_left;
        Node<T>* m_right;
};

template <typename T>
class BST {
    public:
        BST() {
            m_root = nullptr;
        }

        ~BST() {
            clear(m_root);
        }

        // Los duplicados se ignoran
        void insert(T value) {
            m_root = insert(m_root, value);
        }

        // "delete" es palabra reservada en C++, por eso se llama remove
        void remove(T value) {
            m_root = remove(m_root, value);
        }

        void print() {
            visit(2);
        }

        bool find(T value) {
            Node<T>* current = m_root;
            while (current != nullptr) {
                if (value == current->m_value) return true;
                current = value < current->m_value ? current->m_left : current->m_right;
            }
            return false;
        }

        // 1 = preorder, 2 = inorder, 3 = postorder, 4 = level by level
        void visit(int order) {
            if (order == 1) preorder(m_root);
            else if (order == 2) inorder(m_root);
            else if (order == 3) postorder(m_root);
            else if (order == 4) levelByLevel();
            std::cout << "\n";
        }

        // Arbol vacio = 0, solo raiz = 1
        int height() {
            return height(m_root);
        }

        void ancestors(T value) {
            if (!find(value)) {
                std::cout << "El dato no esta en el arbol\n";
                return;
            }
            Node<T>* current = m_root;
            while (current->m_value != value) {
                std::cout << current->m_value << " ";
                current = value < current->m_value ? current->m_left : current->m_right;
            }
            if (current == m_root) std::cout << "La raiz no tiene ancestros";
            std::cout << "\n";
        }

        // La raiz esta en el nivel 0. regresa -1 si no se encuentra
        int whatLevelAmI(T value) {
            Node<T>* current = m_root;
            int level = 0;
            while (current != nullptr) {
                if (value == current->m_value) return level;
                current = value < current->m_value ? current->m_left : current->m_right;
                level++;
            }
            return -1;
        }

    private:
        Node<T>* m_root;

        Node<T>* insert(Node<T>* node, T value) {
            if (node == nullptr) return new Node<T>(value);
            if (value < node->m_value) node->m_left = insert(node->m_left, value);
            else if (node->m_value < value) node->m_right = insert(node->m_right, value);
            return node;
        }

        Node<T>* remove(Node<T>* node, T value) {
            if (node == nullptr) return nullptr;

            if (value < node->m_value) {
                node->m_left = remove(node->m_left, value);
            } else if (node->m_value < value) {
                node->m_right = remove(node->m_right, value);
            } else if (node->m_left == nullptr || node->m_right == nullptr) {
                Node<T>* child = node->m_left != nullptr ? node->m_left : node->m_right;
                delete node;
                return child;
            } else {
                Node<T>* successor = node->m_right;
                while (successor->m_left != nullptr) successor = successor->m_left;
                node->m_value = successor->m_value;
                node->m_right = remove(node->m_right, successor->m_value);
            }
            return node;
        }

        void preorder(Node<T>* node) {
            if (node == nullptr) return;
            std::cout << node->m_value << " ";
            preorder(node->m_left);
            preorder(node->m_right);
        }

        void inorder(Node<T>* node) {
            if (node == nullptr) return;
            inorder(node->m_left);
            std::cout << node->m_value << " ";
            inorder(node->m_right);
        }

        void postorder(Node<T>* node) {
            if (node == nullptr) return;
            postorder(node->m_left);
            postorder(node->m_right);
            std::cout << node->m_value << " ";
        }

        void levelByLevel() {
            if (m_root == nullptr) return;
            std::queue<Node<T>*> pending;
            pending.push(m_root);
            while (!pending.empty()) {
                Node<T>* node = pending.front();
                pending.pop();
                std::cout << node->m_value << " ";
                if (node->m_left != nullptr) pending.push(node->m_left);
                if (node->m_right != nullptr) pending.push(node->m_right);
            }
        }

        int height(Node<T>* node) {
            if (node == nullptr) return 0;
            return 1 + std::max(height(node->m_left), height(node->m_right));
        }

        void clear(Node<T>* node) {
            if (node == nullptr) return;
            clear(node->m_left);
            clear(node->m_right);
            delete node;
        }
};

template <typename T>
T read(const std::string& message) {
    T value;
    std::cout << message;
    std::cin >> value;
    return value;
}

template <typename T>
void run() {
    BST<T> tree;
    int option = 0;

    while (option != 8) {
        std::cout << "\n1. Insertar valor\n"
                  << "2. Eliminar valor\n"
                  << "3. Mostrar recorridos (preorder, inorder, postorder, por niveles)\n"
                  << "4. Buscar un valor\n"
                  << "5. Mostrar la altura del arbol\n"
                  << "6. Mostrar los ancestros de un nodo\n"
                  << "7. Consultar el nivel de un nodo\n"
                  << "8. Salir\n";
        option = read<int>("Opcion: ");

        if (option == 1) {
            tree.insert(read<T>("Valor: "));
        } else if (option == 2) {
            tree.remove(read<T>("Valor: "));
        } else if (option == 3) {
            std::cout << "Preorder:    "; tree.visit(1);
            std::cout << "Inorder:     "; tree.visit(2);
            std::cout << "Postorder:   "; tree.visit(3);
            std::cout << "Por niveles: "; tree.visit(4);
        } else if (option == 4) {
            std::cout << (tree.find(read<T>("Valor: ")) ? "Encontrado\n" : "No encontrado\n");
        } else if (option == 5) {
            std::cout << "Altura: " << tree.height() << "\n";
        } else if (option == 6) {
            tree.ancestors(read<T>("Valor: "));
        } else if (option == 7) {
            int level = tree.whatLevelAmI(read<T>("Valor: "));
            if (level == -1) std::cout << "No se encuentra en el arbol\n";
            else std::cout << "Nivel: " << level << "\n";
        }
    }
}

int main() {
    int type = read<int>("Tipo de dato: 1) int  2) string: ");
    if (type == 1) run<int>();
    else run<std::string>();
    return 0;
}
