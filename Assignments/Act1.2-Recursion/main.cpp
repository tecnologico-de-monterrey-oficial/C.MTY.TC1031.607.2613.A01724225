#include <iostream>

using namespace std; 

int sumIterative(int n) {
    int sum = 0; 
    for (int i = 0; i <= n; i++) {
        sum += i; 
    }

    return sum; 
}

int sumRecursive(int n) {
    if (n<=0) {
        return 0; 
    }
    return n + sumRecursive(n-1); 

}

int sumFormula(int n) {
    return n * (n + 1)/2; 
}

int fibonacciIterative(int n) {
    if (n == 1 || n == 2) {
        return 1; 
    }

    int n1 = 1; 
    int n2 = 1; 
    int sum = 0; 
    for (int i = 3; i < n; i++){
        sum = n1 + n2; 
        n2 = sum; 
        n1 = n2; 
    }

    return sum; 

}

int fibonacciRecursive(int n) {
    if (n <= 1) {
        return n; 
    }
    
    return fibonacciRecursive(n -1) + fibonacciRecursive(n -2); 
}

int bacteriasIterative(int n) {
    if (n == 0){
        return 1; 
    }
    int bacterias = 1; 
    int muertes = 0;
    int nacimientos = 0;  
    for (int i = 1; i <=n; i++) {
        nacimientos = bacterias * 3.78; 
        muertes = bacterias * 2.34; 
        bacterias += nacimientos - muertes; 
    }

    return bacterias; 

}

int bacteriasRecursive(int n) {
    if (n == 0) {
        return 1; 
    }
    int bacterias = bacteriasRecursive(n-1); 
    int nacimientos = bacterias * 3.78; 
    int muertes = bacterias * 2.34; 
    
    return nacimientos - muertes + bacterias; 
}

double investmentIterative(int months, double q) {
    for (int i = 0; i < months; i++){
        q += q * 0.1875; 
    }

    return q; 
}


double investmentRecursive(int months, double q) {
    if (months <= 0) {
        return q; 
    }
    double initial = investmentRecursive(months - 1, q); 
    return initial * 1.1875; 
}

double powIterative(int n, int pow) {
    int sum = n; 
    for (int i = 1; i < pow; i++){
        sum *= n; 
    }

    return sum; 
}

double powRecursive(int n, int pow) {
    // caso base

    if (pow == 0) {
        return 1; 
    }

    int past = powRecursive(n, pow -1); 
    return past * n; 
}

int main() {

    cout << "sumIterative de 10: " << sumIterative(10) << "\n"; 
    cout << "sumRecursive de 10: " << sumRecursive(10) << "\n"; 
    cout << "sumFormula de 10: " << sumFormula(10) << "\n"; 
    cout << "fibonacciIterative de 6: " << fibonacciIterative(6) << "\n"; 
    cout << "fibonacciRecursive de 6: " << fibonacciRecursive(6) << "\n"; 
    cout << "bacteriasIterative de 100,000: " << bacteriasIterative(100000) << "\n"; 
    cout << "bacteriasRecursive de 100,000: " << bacteriasRecursive(100000) << "\n"; 
    cout << "investmentIterative de 5 meses con 1000: " << investmentIterative(5, 1000) << "\n"; 
    cout << "investmentRecursive de 5 meses con 1000: " << investmentRecursive(5, 1000) << "\n"; 
    cout << "powIterative de 5 a la 2: " << powIterative(5, 2) << "\n"; 
    cout << "powRecursive de 5 a la 2: " << powRecursive(5, 2) << "\n"; 

    return 0; 
}