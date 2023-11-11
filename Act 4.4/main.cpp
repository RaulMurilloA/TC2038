#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

/*Pruebas
 * Prueba 1
    10
    2, 3, 4, 10, 40
    El elemento esta presente en el indice: 3

 * Prueba 2
    11
    2, 3, 4, 10, 40
    El elemento no esta presente en el arreglo

 * Prueba 3
    15
    5, 10, 15, 20, 25, 30
    El elemento esta presente en el indice: 2

 * Prueba 4
    23
    2, 5, 6, 8, 9, 11, 14, 17, 19, 23
    El elemento esta presente en el indice: 9
 * */

// Función para generar un número aleatorio entre dos valores
int random(int x, int y) {
    return (x + rand() % (y - x + 1));
}

// Función para realziar la búsqeuda aleatoria binaria
int randomizedBinarySearch(vector<int> &set, int target) {
    int l = 0;
    int r = int(set.size()) - 1;

    while (l <= r) {
        // Generamos un índice aleatorio para que sea nuestro punto "central"
        int mid = random(l, r);

        // Si el valor del índice generado al azar es el
        // mismo valor que el buscado, regresamos el indice.
        // Si el valor del índice generado al azar es más chico que el buscado,
        // tomamos el valor del índice como la nueva izquierda.
        // Pero si el valor del índice generado al azar es mayor que el buscado,
        // tomamos el valor del índice como la nueva derecha.
        if (set[mid] == target) {
            return mid;
        } else if (set[mid] < target) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    return -1;
}

int main() {
    int toFind;
    cin >> toFind;
    cin.ignore();

    vector<int> numberSet;
    string input;
    getline(cin, input);
    stringstream ss(input);
    int num;
    while (ss >> num) {
        numberSet.push_back(num);
        if (ss.peek() == ',') {
            ss.ignore();
        }
    }

    // Almacenámos el resultado de la búsqueda binaria aleatoria
    int result = randomizedBinarySearch(numberSet, toFind);

    // Si el resultado es -1, significa que no se encuentra en el conjunto
    if (result != -1) {
        cout << "El elemento esta presente en el indice: " << result << endl;
    } else {
        cout << "El elemento no esta presente en el arreglo" << endl;
    }

    return 0;
}
