#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>

using namespace std;

/*
 * Prueba 1
    set[] ={45, 34, 4, 12, 5, 2}
     S =42
     41
 * Prueba 2
    set[] ={3, 34, 4, 12, 5, 2}
     S =10
     10

 * Prueba 3
    set[] ={500, 1000, 1500, 2000, 2500}
     S =3501
     3500

 * Prueba 4
    set[] ={7, 14, 21, 28, 35, 42, 49}
     S =100
     98
 * */

// Función recursiva para generar todas las sumas posibles de un subconjunto de un vector.
void generateSubsetSums(vector<long long> &arr, int start, int end, long long sum, vector<long long> &subsetSums) {
    if (start > end) {
        subsetSums.push_back(sum);
        return;
    }

    generateSubsetSums(arr, start + 1, end, sum + arr[start], subsetSums);
    generateSubsetSums(arr, start + 1, end, sum, subsetSums);
}

// Función para el algoritmo meet in the middle
long long meetInTheMiddle(vector<long long> &arr, long long S) {
    int n = arr.size();
    int mid = n / 2;

    // Calculamos las sumas de las mitades izquierda y derecha del conjunto
    vector<long long> leftHalf, rightHalf;
    generateSubsetSums(arr, 0, mid - 1, 0, leftHalf);
    generateSubsetSums(arr, mid, n - 1, 0, rightHalf);

    // Ordenamos las sumas de la mitad derecha
    sort(rightHalf.begin(), rightHalf.end());

    long long maxSum = 0;

    // Iteramos sobre las sumas de la mitad izquierda, verificando que cada suma sea menor o igual a S
    for (long long sum: leftHalf) {
        if (sum > S) continue;
        
        // Usamos búsqueda binaria para encontrar la suma más grande menor o igual a S - sum
        auto it = upper_bound(rightHalf.begin(), rightHalf.end(), S - sum);
        // Si encontramos tal suma, buscamos la mayor entre esa suma y la actual, para tomar la mayor
        if (it != rightHalf.begin()) {
            --it;
            maxSum = max(maxSum, sum + (*it));
        }
    }

    return maxSum;
}

int main() {
    long long int S;
    vector<long long int> set;

    string input;
    cout << "set[] = ";
    getline(cin, input);

    // Eliminamos las llaves de la entrada
    input.erase(std::remove(input.begin(), input.end(), '{'), input.end());
    input.erase(std::remove(input.begin(), input.end(), '}'), input.end());

    // Guardamos los números del conjunto en el vector set
    stringstream ss(input);
    string token;
    while (getline(ss, token, ',')) {
        long long int num;
        stringstream(token) >> num;
        set.push_back(num);
    }

    cout << "S = ";
    cin >> S;

    cout << meetInTheMiddle(set, S) << endl;
    return 0;
}
