#include <iostream> 
#include <vector> 


using namespace std; 


int sumaImpares(vector<int> positivos) {
    int sum = 0; 
    for (int i = 0; i < positivos.size(); i++) {
        if (positivos[i] % 2 != 0) {
            sum += positivos[i]; 
        }
    }
    
    return sum; 
}

int sumaRecursivaAux(const vector<int>& v, int index) {
    if (index < 0) {
        return 0; 
    }

    int valor = (v[index] %2 != 0) ? v[index] : 0; 
    return valor + sumaRecursivaAux(v, index -1 );
}
int sumaRecursiva(vector<int> positivos) {
    return sumaRecursivaAux(positivos, (int)positivos.size() -1);  
    

}

int main() {

    vector<int> nums = {1, 3, 4, 7, 9, 11, 5, 6}; 
    cout << "Suma Impares Iterativo: " << sumaImpares(nums) << "\n"; 
    cout << "Suma Impares Recursivo: " << sumaRecursiva(nums) << "\n"; 

    
    return 0; 
}