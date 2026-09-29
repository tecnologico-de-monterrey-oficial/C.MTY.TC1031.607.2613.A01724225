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


class Stack {
    // definimos que el head es el ultimo elemento
    public: 
        Stack() {
            m_head = nullptr; 
        }

        void pop() {
            // remove head
            if (m_head == nullptr) return; 

            Node* old = m_head; 
            m_head = m_head->m_next; 
            delete old; 
        }

        void add(int value) {
            m_head = new Node(value, m_head); 
 
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