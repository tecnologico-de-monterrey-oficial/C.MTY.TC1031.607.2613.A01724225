#include <iostream> 
#include <vector> 

using namespace std; 

template <typename T> 

void mergeSort(vector<T> &list, int left, int right) {
    if (left < right) {
        // calculamos mid 
        int mid = (left + right) /2; 

        // separamos de left a mid
        mergeSort(list, left, mid); 

        // separamos mid + 1 a right
        mergeSort(list, mid+1, right); 

        merge(list, left, mid, right); 
    }
}

template <typename T> 
void merge(vector<T>& list, int left, int mid, int right) {
    // generamos la lista de left a mid
    // creamos una list para los valores del lado izquierdo
    vector<T> leftList; 
    // iteramos la lista 
    for (int i=left; i <=mid; i++) {
        leftList.push_back(list[i]); 
    }

    // generamos rightList
    vector<T> rightList; 
    for (int j = mid + 1; j<= right; j++) {
        rightList.push_back(list[j]); 
    }

    int index = left; 
    // inicializamos el indice del lado izquierdo
    int i =0; 
    //lado derecho
    int j = 0; 

    while (i<=leftList.size() && j<rightLIst.size()) {
        if (listLeft[i]) {
            list[index] = leftList[i]; 

            i++; 
        } else {
            list[index] = rightList; 
        }
    }
}

int main() { 
    return 0; 
}