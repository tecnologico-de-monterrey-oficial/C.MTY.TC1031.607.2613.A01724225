#include <iostream> 

class Node {
    public: 
        Node (int value, Node* next) {
            m_next = next; 
            m_value = value; 
        }

        int m_value; 
        Node* m_next; 
}; 

class LinkedList {
    public: 
        LinkedList() {
            m_head = nullptr; 
        
        }

        void addToFront(int value) {
            Node* tempNode = new Node(value, m_head); 
            m_head = tempNode; 
        }

        void addToBack(int value) {
            // null ptr porque este ahora sera el ultimo
            Node* lastNode = new Node(value, nullptr);  

            if (m_head == nullptr) {
                // si no hay elementos, simplemente agregamos ese como head
                m_head = lastNode; 
                return; 
            }

            // si ya hay elementos, movemos hasta el ultimo 
            // primer elemento
            Node *prevLastNode = m_head; 
            while (prevLastNode -> m_next != nullptr) {
                // recorremos
                prevLastNode = prevLastNode -> m_next; 
            }
             
            // cambiamos para que el next del ultimo elemento sea nuestro nuevo pointer
            prevLastNode -> m_next = lastNode; 
        }

        void insert(int value, int index) {

            // primero agarramos el del index actual
            Node* tempNode = m_head; 
            for (int i =0; i < index - 1; i ++) {
                // si llegamos al final antes
                if (tempNode == nullptr) {
                    return; 
                }
                // recorremos 
                tempNode = tempNode -> m_next; 
            }

            // creamos nuevo nodo, con el valor y el next siendo el next de nuestro temporal             
            Node* newNode = new Node(value, tempNode ->m_next); 
            // ahora el temporal apunta su next hacia el nuevo nodo
            tempNode -> m_next  = newNode; 

            
            
        }

       

    private: 

        Node* m_head; 
}; 