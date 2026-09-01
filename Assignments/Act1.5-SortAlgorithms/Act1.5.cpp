#include <iostream> 
#include <vector> 

using namespace std; 

template <typename T> 
vector<T> sSort(vector<T> v) {
    for (int i = 0; i < v.size() -1; i++) {

        for (int j = i + 1; j < v.size(); j++) {
            if (v[j] < v[i]) {
                T temp = v[j]; 
                v[j] = v[i]; 
                v[i] = temp; 
            }
        }
    }

    return v; 

}

template <typename T> 
vector<T> selectionSort(vector<T> v) {
    // iteramos por cada numero de la lista
    for (int i = 0; i < v.size() - 1; i++) {
        // vamos desde i + 1 para ver cual es el menor
        int index = i; 
        for (int j = i + 1; j < v.size(); j++) {
            if (v[index] > v[j]) {
                index = j; 
            }

        }

        // swapeamos el actual por el menor
        if (index != -1) {
            int temp = v[i]; 
            v[i] = v[index]; 
            v[index] = temp; 
        }
       
    }

    return v; 
}

template <typename T> 
vector<T> bubbleSort(vector<T> v) {
    for (int i = 1; i <= v.size(); i++) {
        for (int j = 0; j < v.size() - i; j++) {
            if (v[j] > v[j+1]) {
                int temp = v[j]; 
                v[j] = v[j+1]; 
                v[j+1] = temp; 

            }
        }
    }

    return v; 
}

template <typename T> 
vector<T> insertionSort(vector<T> v) {
    
    for (int i = 0; i < v.size(); i++) {
        for (int j = i -1; j >=0; j--) {
            if (v[j] > v[j+1]) {
                T temp = v[j + 1]; 
                v[j+1] = v[j]; 
                v[j] = temp; 
            }
        }
    }
    return v; 
}

template <typename T> 
void printVect(const vector<T>& v) {
    cout << "\n"; 
    for (int i =0; i < v.size(); i++) {
        if (i == v.size() - 1) {
            cout << v[i]; 
        } else {
            cout << v[i] << ", "; 
            
        }

    }

    cout << "\n\n"; 
}




int main() {
    vector<int> nums = {1, 4, 23, 99, 2, 15, 3, 54, 101}; 
    
    cout << "Selection Sort: "; 
    printVect(sSort(nums)); 

    // printVect(nums); 
    cout << "Bubble Sort: "; 
    printVect(bubbleSort(nums)); 


    cout << "Selection Sort: "; 
    printVect(selectionSort(nums)); 

    cout << "Insertion Sort: "; 
    printVect(insertionSort(nums)); 


    return 0; 
}