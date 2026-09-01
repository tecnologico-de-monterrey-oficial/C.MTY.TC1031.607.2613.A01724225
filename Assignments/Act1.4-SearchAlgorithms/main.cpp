#include <iostream> 
#include <vector> 
#include <random> 
#include <algorithm> 
#include <chrono> 

using namespace std; 

bool seqSearch(const vector<int>& nums, int s) {

    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] == s) {
            cout << "Found\n"; 
            return true; 
        }
    }
    cout << "Not found\n"; 
    return false; 
}

bool binarySearch(const vector<int>& nums, int s) {
    int start = 0; 
    int end = nums.size(); 
    int mid = (start + end) / 2; 

    while (start != end) {
    if (s > nums[mid]) {
        start = mid + 1; 
        mid = (start + end) / 2; 
    } else if (s < nums[mid]) {
        end = mid - 1; 
        mid = (start + end) / 2; 
    } else {
        cout << "Found\n"; 
        return true; 

    }
}

    cout << "Not found\n"; 
    return false; 
}
int main() {
    std::random_device rd; 

    std::mt19937 gen(rd()); 

    std::uniform_int_distribution<> dist(1, 1000000); 

    std::vector<int> numbers (10000); 
    for (int& num : numbers) {
        num = dist(gen);
    }

    // poner 100 para testear
    numbers[3] = 100; 

    // ordenar el vector 

    std::sort(numbers.begin(), numbers.end()); 
    
    // seqSearch(numbers, 100); 
    // binarySearch(numbers, 100); 


    int answer = -1; 

    while (answer != 0) {
        cout << "\nNumero a buscar (0 para salir): "; 
        cin >> answer; 

        if (answer == 0) break; 

        auto start_seq = chrono::high_resolution_clock::now();
        
        seqSearch(numbers, answer); 
        
        auto end_seq = chrono::high_resolution_clock::now();
        chrono::duration<double, std::micro> elapsed_seq = end_seq - start_seq;
        cout << "Tiempo Secuencial: " << elapsed_seq.count() << " microsegundos\n\n";

        auto start_bin = chrono::high_resolution_clock::now();
        
        binarySearch(numbers, answer); 
        
        auto end_bin = chrono::high_resolution_clock::now();
        chrono::duration<double, std::micro> elapsed_bin = end_bin - start_bin;
        cout << "Tiempo Binaria: " << elapsed_bin.count() << " microsegundos\n";
    }
    
   return 0; 
    

}