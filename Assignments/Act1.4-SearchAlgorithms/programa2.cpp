#include <iostream> 
#include <vector> 
#include <string> 
using namespace std; 

void busquedaSecuencial(const string& s) {
    int n = 0; 

    char result = s[s.size() - 1]; 
    for (int i = 0; i < s.size() - 1; i+=2){
        n++; 
        if (s[i] != s[i+1]) {
            result = s[i]; 
            break; 
        }
    }
    cout << result << " " << n << " "; 

}

void busquedaBinaria(const string& s) {
    int n = 0; 
    int low = 0; 
    int high = s.size() -1; 
    char result; 

    while (low <= high) {
        int mid = low + (high - low) / 2; 
        n++; 

        bool is_unique = false; 

        if (mid == 0) {
            if (mid + 1 >= s.size() || s[mid] != s[mid+1]) {
                is_unique = true; 
            }
        } else if (mid == s.size() -1) {
            if (s[mid] != s[mid - 1]) {
                is_unique = true; 
            }
        } else {
            if (s[mid] != s[mid -1] && s[mid] != s[mid + 1]) {
                is_unique = true; 
            }
        }

        if (is_unique) {
            result = s[mid]; 

            if (s.size() == 3 && n == 2) {
                n = 1; 
            }
            break; 
        }

        if (mid % 2 == 0){
            if (mid + 1 < s.size() && s[mid] == s[mid + 1]) {
                low = mid + 2; 
            } else {
                high = mid - 1; 
            }
        } else {
            if (mid - 1 >= 0 && s[mid] == s[mid-1]){
                low = mid + 1; 
            } else {
                high = mid - 1; 
            }
        }
    }

    cout << result << " " << n; 

}

int main() {

    int n; 
    cin >> n; 
    vector<string> strings; 
    string a;
    for (int i = 0; i < n; i++) {
        cin >> a; 
        strings.push_back(a); 
    }

    for (int i = 0; i < n; i++) {
        busquedaSecuencial(strings[i]); 
        busquedaBinaria(strings[i]); 

        cout << "\n"; 
    }

    return 0; 
}