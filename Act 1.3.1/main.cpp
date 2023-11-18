#include <iostream>
#include <vector>

using namespace std;
/*Pruebas
Prueba 1
  Ingrese la cantidad de filas: 4
  Ingrese la cantidad de columnas: 4
  Ingrese la matriz:
  1 0 0 0
  1 1 0 1
  0 1 0 0
  1 1 1 1
  La solución es:
  1 0 0 0
  1 1 0 0
  0 1 0 0
  0 1 1 1

Prueba 2
  Ingrese la cantidad de filas: 5
  Ingrese la cantidad de columnas: 5
  Ingrese la matriz:
  1 1 1 1 0
  1 0 0 1 1
  1 1 1 1 1
  1 0 0 0 1
  1 1 1 1 1
  La solución es:
  1 0 0 0 0
  1 0 0 0 0
  1 0 0 0 0
  1 0 0 0 0
  1 1 1 1 1

Prueba 3
  Ingrese la cantidad de filas: 4
  Ingrese la cantidad de columnas: 3
  Ingrese la matriz: 
  1 0 0 0
  0 0 0 0
  0 0 0 1
  La matriz no tiene solución

Prueba 4
  Ingrese la cantidad de filas: 5
  Ingrese la cantidad de columnas: 4
  Ingrese la matriz: 
  1 0 1 1
  1 1 1 1
  0 1 1 1
  0 0 1 1
  1 1 1 1
  La solución es:
  1 0 0 0 
  1 1 0 0 
  0 1 1 0 
  0 0 1 0 
  0 0 1 1 
*/

// Función para imprimir la matriz solución
void print(int m, int n, bool **matriz) {
  cout << "La solución es:" << endl;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      cout << matriz[i][j] << " ";
    }
    cout << endl;
  }
}

// Función para saber si la casilla es válida
bool esSegura(int m, int n, bool **matriz, int x, int y) {
  if (x >= 0 && x < m && y >= 0 && y < n && matriz[x][y] == 1)
    return true;
  return false;
}

// Función auxiliar de backtracking para encontrar la solución (recursiva)
bool backtrackingAux(int m, int n, bool **matriz, int x, int y,
                     bool **matrizSol) {
  // Si ya estamos en la meta, regresa un true
  if (x == m - 1 && y == n - 1 && matriz[x][y] == 1) {
    matrizSol[x][y] = 1;
    return true;
  }

  // Verifica que la matriz sea válida
  if (esSegura(m, n, matriz, x, y)) {
    // Verifica si la ubicación actual ya es parte de la solución
    if (matrizSol[x][y] == 1)
      return false;

    // Consideramos la casilla actual como parte de la solución
    matrizSol[x][y] = 1;

    // Avanzamos hacia la derecha
    if (backtrackingAux(m, n, matriz, x + 1, y, matrizSol))
      return true;

    // Si no funciona movernos hacia la derecha vamos por la izquierda
    if (backtrackingAux(m, n, matriz, x - 1, y, matrizSol))
      return true;

    // Si no hubo solución al movernos por la derecha o izquierda
    // Avanzamos hacia abajo
    if (backtrackingAux(m, n, matriz, x, y + 1, matrizSol))
      return true;

    // Si no funciona movernos hacia abajo vamos por arriba
    if (backtrackingAux(m, n, matriz, x, y - 1, matrizSol))
      return true;

    // Si ninguno de los anteriores movimientos funcionó, dejamos de usar la
    // casilla actual
    matrizSol[x][y] = 0;
    return false;
  }
  return false;
}

// Función de backtracking
bool backtracking(int m, int n, bool **matriz) {
  // Inicamos la matris solución
  bool **matrizSolucion = new bool *[n];

  // Declaramos la matriz dinámica para la solución
  for (int i = 0; i < m; i++) {
    matrizSolucion[i] = new bool[n];
  }
  // Llenamos la matriz con ceros
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      matrizSolucion[i][j] = 0;
    }
  }

  // Si no existe ninguna solución para la matriz, lo notificamos
  if (backtrackingAux(m, n, matriz, 0, 0, matrizSolucion) == false) {
    cout << "La matriz no tiene solución" << endl;
    return false;
  }

  //Imprimimos la matriz
  print(m, n, matrizSolucion);

  // Liberamos la memoria de la matriz
  for (int i = 0; i < n; ++i) {
    delete[] matrizSolucion[i];
  }
  delete[] matrizSolucion;
  return true;
}

int main() {
  // M es la cantidad de filas(?)) y N la cantidad de columnas(?)
  int M, N;

  // Ingresamos los datos de filas y columnas
  cout << "Ingrese la cantidad de filas: ";
  cin >> M;
  cout << "Ingrese la cantidad de columnas: ";
  cin >> N;

  // Inicializamos la matriz
  bool **matrizInicial = new bool *[N];

  // Solicitamos los datos que irán dentro de la matriz
  cout << "Ingrese la matriz: " << endl;

  // Declaramos la matriz dinámica
  for (int i = 0; i < M; i++) {
    matrizInicial[i] = new bool[N];
  }
  // Llenamos la matriz
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      cin >> matrizInicial[i][j];
    }
  }

  // Función que realiza la backtracking
  backtracking(M, N, matrizInicial);

  // Liberamos la memoria de la matriz
  for (int i = 0; i < N; ++i) {
    delete[] matrizInicial[i];
  }
  delete[] matrizInicial;

  return 0;
}
