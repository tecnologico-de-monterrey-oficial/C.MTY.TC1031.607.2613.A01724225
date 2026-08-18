#pragma once 
#include <vector>
#include <iostream>
#include <optional> 
#include <algorithm> 
#include <functional> 
using namespace std; 

template <typename T> 
class Lista {
    private: 
        vector<T> data; 
        int size; 
    
    public: 

        Lista() : size(0) {}

        void insert(T t) {
            data.push_back(t); 
            size++; 
        }

        void removeLast() {
            if (data.size() == 0) {
                cout << "La lista ya esta vacia\n"; 
            } else {
                data.pop_back(); 
                size--; 
            }
        }

        optional<T> getData(int pos) { 
            if (data.size() == 0) { 
                cout << "No hay datos\n"; 
                return nullopt; 
            } else if (pos >= data.size()) {
                cout << "El indice está fuera de rango\n"; 
                return nullopt; 
            } else {
                return data[pos]; 
            }
        }

        int getSize() {
            return size; 
        }

        T getMax() {
            return *max_element(data.begin(), data.end()); 
        }

        void print() {
            for (int i = 0; i < size; i++) {
                cout << "\n"; 
                cout << "[" << i << "] - " << data[i] << "\n"; 

            }
        }

        void insertAt(int pos, T t) {
            if (0 <= pos && pos <= size) {
                size++; 
                // agarramos el dato en la posicion
                T current = data[pos]; 
                data[pos] = t; 
                T last = current; 
               
                for (int i = pos + 1; i < size; i++) {
                    // agarramos valor actual
                    T current = data[i]; 
                    // en esta posicion ponemos el pasado
                    data[i] = last; 
                    // ahora el valor "pasado" es el que se va a poner
                    last = current; 
                }
                

            } else {
                cout << "El valor es menor a 0 o fuera del rango"; 

            }

        }

        void removeAt(int pos) {
            if (pos < 0) {
                cout << "La posicion no puede ser menor a 0"; 
            } else if (pos >= size) {
                cout << "ListaLa posicion es inexistente"; 
            }else {
                for (int i = pos; i < size - 1; i++) {
                data[i] = data[i+1]; 

                }   
                data.pop_back(); 
                size--; 
            }
            
        }



        
}; 