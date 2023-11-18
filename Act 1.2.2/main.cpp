#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
/* Pruebas:
Prueba 1
  Ingrese la cantidad de denominaciones distintas: 3
  Ingrese las distintas denominaciones:
  5
  10
  20
  Precio del producto: 25
  Total de dinero ingresado: 50
    1 moneda(s) de 20
    0 moneda(s) de 10
    1 moneda(s) de 5

Prueba 2
  Ingrese la cantidad de denominaciones distintas: 3
  Ingrese las distintas denominaciones:
  1
  5
  2
  Precio del producto: 70
  Total de dinero ingresado: 100
    6 moneda(s) de 5
    0 moneda(s) de 2
    0 moneda(s) de 1

Prueba 3
  Ingrese la cantidad de denominaciones distintas: 2
  Ingrese las distintas denominaciones:
  1
  2
  Precio del producto: 18
  Total de dinero ingresado: 50
    16 moneda(s) de 2
    0 moneda(s) de 1

Prueba 4
  Ingrese la cantidad de denominaciones distintas: 5
  Ingrese las distintas denominaciones:
  7
  4
  2
  1
  10
  Precio del producto: 11
  Total de dinero ingresado: 200
    18 moneda(s) de 10
    1 moneda(s) de 7
    0 moneda(s) de 4
    1 moneda(s) de 2
    0 moneda(s) de 1
*/

// Función para imprirmir los datos
void print(vector<int> denominaciones, vector<int> monedas) {
  for (int i = 0; i < denominaciones.size(); ++i) {
    cout << "\t" << monedas[i] << " moneda(s) de " << denominaciones[i] << endl;
  }
}

// Algortimo avaro
vector<int> avaro(vector<int> denominaciones, int P, int Q) {
  // Inicializamos el cambio que regresará
  int change = Q - P;
  // Iniciamos el veactor que almacenará la cantidad de monedas
  vector<int> monedas(denominaciones.size(), 0);

  // Recorremos el arreglo de denominaciones
  for (int i = 0; i < denominaciones.size(); i++) {
    // Si el cambio a regresa es mayor o igual a la denominación actual,
    // calculamos la mayor cantidad de monedas de esa denominación necesarias y
    // el cambio cambia según las monedas usadas
    if (change >= denominaciones[i]) {
      monedas[i] = change / denominaciones[i];
      change = change % denominaciones[i];
    } else { // Si no se cumple la condición anterior, no utilizamos esa moneda
      monedas[i] = 0;
    }
  }

  return monedas;
}

int main() {
  // Iniciar la cantidad de denominaciones, el precio del producto, el dinero
  // ingresado y una variable de uso temporal
  int numDenominaciones, P, Q;

  // Ingresar la cantidad de denominaciones
  cout << "Ingrese la cantidad de denominaciones distintas: ";
  cin >> numDenominaciones;

  // Iniciar el arreglo de las denominaciones disponibles
  vector<int> arrDenominaciones(numDenominaciones, 0);

  // Ingresar las denominaciones
  cout << "Ingrese las distintas denominaciones: " << endl;
  for (int i = 0; i < numDenominaciones; i++) {
    cin >> arrDenominaciones[i];
  }

  // Ordenamos las denominaciones
  sort(arrDenominaciones.begin(), arrDenominaciones.end(), greater<int>());

  // Ingresar el precio y el total de dinero ingresado
  cout << "Precio del producto: ";
  cin >> P;
  cout << "Total de dinero ingresado: ";
  cin >> Q;

  // Algoritmo avaro
  print(arrDenominaciones, (avaro(arrDenominaciones, P, Q)));
}
