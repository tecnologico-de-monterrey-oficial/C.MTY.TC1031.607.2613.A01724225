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


class Queue {
    public: 
        Queue() {
            m_head = nullptr; 
        }

        void pop() {
            // remove the head
            if (m_head == nullptr) {
                return; 
            }
            Node* old_head = m_head; 
            m_head = old_head->m_next; 
            delete old_head; 
        }

        void add(int value) {
            // add to tail 
            if (m_head == nullptr) {
                m_head = new Node(value, nullptr); 
                return; 

            }

            Node* aux = m_head; 
            while (aux->m_next != nullptr) {
                aux = aux->m_next; 
            }

            aux->m_next = new Node(value, nullptr); 

        }

        Node* front() {
            return m_head; 
        }

        void print() {
            Node* cur = m_head; 

            while (cur != nullptr) {
                std::cout << cur->m_value << ", "; 
                cur = cur->m_next; 
                
            }
        }



    private: 
        Node* m_head; 



}; 

int main(){



    return 0; 
}