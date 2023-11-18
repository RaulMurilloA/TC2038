#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/*Pruebas:
Prueba 1
  Ingrese la cantidad de denominaciones distintas: 2
  Ingrese las distintas denominaciones:
  5
  1
  Precio del producto: 10
  Total de dinero ingresado: 25

  Por método recursivo:
    3 moneda(s) de 5
    0 moneda(s) de 1

  Por método de memorización:
    3 moneda(s) de 5
    0 moneda(s) de 1

  Por método bottom-up:
    3 moneda(s) de 5
    0 moneda(s) de 1

Prueba 2
  Ingrese la cantidad de denominaciones distintas: 3       
  Ingrese las distintas denominaciones: 
  1
  5
  2
  Precio del producto: 70
  Total de dinero ingresado: 100

  Por método recursivo:
    4 moneda(s) de 5
    4 moneda(s) de 2
    2 moneda(s) de 1

  Por método de memorización:
    4 moneda(s) de 5
    4 moneda(s) de 2
    2 moneda(s) de 1

  Por método bottom-up:
    6 moneda(s) de 5
    0 moneda(s) de 2
    0 moneda(s) de 1

Prueba 3
  Ingrese la cantidad de denominaciones distintas: 4
  Ingrese las distintas denominaciones: 
  20
  5
  1
  2
  Precio del producto: 75
  Total de dinero ingresado: 100

  Por método recursivo:
    1 moneda(s) de 20
    1 moneda(s) de 5
    0 moneda(s) de 2
    0 moneda(s) de 1

  Por método de memorización:
    1 moneda(s) de 20
    1 moneda(s) de 5
    0 moneda(s) de 2
    0 moneda(s) de 1

  Por método bottom-up:
    1 moneda(s) de 20
    1 moneda(s) de 5
    0 moneda(s) de 2
    0 moneda(s) de 1

Prueba 4
  Ingrese la cantidad de denominaciones distintas: 2
  Ingrese las distintas denominaciones: 
  1
  2
  Precio del producto: 18
  Total de dinero ingresado: 50

  Por método recursivo:
    11 moneda(s) de 2
    10 moneda(s) de 1

  Por método de memorización:
    11 moneda(s) de 2
    10 moneda(s) de 1

  Por método bottom-up:
    16 moneda(s) de 2
    0 moneda(s) de 1
*/

// Recursividad (Revisado)
vector<int> recursividad(int change, const vector<int> &denominaciones) {
  // Si el cambio es 0
  if (change == 0) {
    vector<int> resultado(denominaciones.size(), 0);
    return resultado;
  }
  // Si el cambio es mayor a cero
  int minMonedas = 10000;
  vector<int> monedas(denominaciones.size(), 0);

  for (int i = 0; i < denominaciones.size(); ++i) {
    // Si la denominación es menor o igual al cambio, se usa esa denominación
    if (denominaciones[i] <= change) {
      // Se llama a la función de recursividad con un valor reducido
      vector<int> subproblemaMonedas =
          recursividad(change - denominaciones[i], denominaciones);
      // Acumulamos la cantidad de monedas
      int subproblema = 1 + subproblemaMonedas[i];
      // Si el subproblema es menor a la cantidad mínima de monedas se actualiza
      // la cantidad mpinima de monedas así como la lista de monedas
      if (subproblema < minMonedas) {
        minMonedas = subproblema;
        monedas = subproblemaMonedas;
        monedas[i]++;
      }
    }
  }
  // Regresamos el vector de ls monedas
  return monedas;
}

// Memoria
vector<int> memorizacion(int change, const vector<int> &denominaciones,
                         vector<vector<int>> memo) {
  // Si el cambio es 0
  if (change == 0) {
    vector<int> resultado(denominaciones.size(), 0);
    return resultado;
  }
  // Si ya hemos calculado y almacenado el resultado, devuelve ese valor
  if (memo[change][0] != -1) {
    return memo[change];
  }

  // Si el cambio es mayor a cero
  int minMonedas = 10000;
  vector<int> monedas(denominaciones.size(), 0);

  for (int i = 0; i < denominaciones.size(); ++i) {
    // Si la denominación es menor o igual al cambio, se usa esa denominación
    if (denominaciones[i] <= change) {
      // Se llama a la función de recursividad con un valor reducido
      vector<int> subproblemaMonedas =
          memorizacion(change - denominaciones[i], denominaciones, memo);
      // Acumulamos la cantidad de monedas
      int subproblema = 1 + subproblemaMonedas[i];
      if (subproblema < minMonedas) {
        // Si el subproblema es menor a la cantidad mínima de monedas se
        // actualiza
        // la cantidad mpinima de monedas así como la lista de monedas
        minMonedas = subproblema;
        monedas = subproblemaMonedas;
        monedas[i]++;
      }
    }
  }
  // Se almacena el resultado en memo para el valor change
  memo[change] = monedas;
  return monedas;
}

vector<int> memo(int change, const vector<int> &denominaciones) {
  vector<vector<int>> memo(change + 1, vector<int>(denominaciones.size(), -1));

  return memorizacion(change, denominaciones, memo);
}

// Bottom-up
vector<int> bottomUp(int change, const vector<int> &denominaciones) {
  // Generamos el vector para la cantidad mínima de monedas
  vector<int> monedasMin(change + 1, 0);
  // Vector para "rastrear la demoninación de las monedas usadas"
  vector<int> monedasUsadas(change + 1, 0);

  // Iniciamos un blucle en el que vamos recorriendo el cambio e instaciamos el
  // mínimo de monedas con un valor alto
  for (int i = 1; i <= change; ++i) {
    monedasMin[i] = 10000;
    // Iteramos entre las denominaciones de las monedas
    for (int j = 0; j < denominaciones.size(); ++j) {
      // Si la denominación es menor o igual a la cantidad de cambio se usa esa
      // moneda
      if (denominaciones[j] <= i &&
          monedasMin[i - denominaciones[j]] + 1 < monedasMin[i]) {
        // Se registran las monedas necesarias de esa denominación
        monedasMin[i] = monedasMin[i - denominaciones[j]] + 1;
        // Se almacena la denominación de la moneda usada
        monedasUsadas[i] = denominaciones[j];
      }
    }
  }
  // Obtenemos la cantidad de monedas de cada tipo que se utilizaron
  vector<int> monedas(denominaciones.size(), 0);
  int faltante = change;
  while (faltante > 0) {
    int moneda = monedasUsadas[faltante];
    ++monedas[moneda];
    faltante -= moneda;
  }
  // Regresamos el vector con las monedas empleadas
  return monedas;
}

// Función para imprirmir los datos del método recursivo y por memorización
void print(vector<int> denominaciones, vector<int> monedas) {
  for (int i = 0; i < denominaciones.size(); ++i) {
    cout << "\t" << monedas[i] << " moneda(s) de " << denominaciones[i] << endl;
  }
}

// Función para imprimir los datos del método bottom-up
void printBU(vector<int> denominaciones, vector<int> monedas) {
  for (int i = 0; i < denominaciones.size(); i++) {
    cout << "\t" << monedas[denominaciones[i]] << " moneda(s) de "
         << denominaciones[i] << endl;
  }
}

void dynamicP(vector<int> denominaciones, int price, int money) {
  // Variable del cambio total a entregar
  int change = money - price;
  // Si este cambio es negativo o cero no da cambio
  if (change < 0) {
    cout << "No se le puede dar cambio" << endl;
  } else {
    // Método recursividad
    cout << "\nPor método recursivo:" << endl;
    print(denominaciones, recursividad(change, denominaciones));
    // Método memorización
    cout << "\nPor método de memorización:" << endl;
    print(denominaciones, memo(change, denominaciones));
    // Método bottom-up
    cout << "\nPor método bottom-up:" << endl;
    printBU(denominaciones, bottomUp(change, denominaciones));
  }
}

int main() { /*Usar recursiva, memoria y bottom up*/
  // Iniciar la cantidad de denominaciones, el precio del producto, el dinero
  // ingresado y una variable de uso temporal
  int numDenominaciones, P, Q, temp;

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

  // Algoritmos
  dynamicP(arrDenominaciones, P, Q);
}
