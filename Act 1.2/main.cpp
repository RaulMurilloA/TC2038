#include <algorithm>
#include <iostream>

// Insertion sort O(n^2) Mayor a menor
void insertionSortMAX(int arr[], int n) {
  int i, key, j;
  for (i = 1; i < n; i++) {
    key = arr[i];
    j = i - 1;
    // Move elements of arr[0..i-1],
    // that are greater than key, to one
    // position ahead of their
    // current position
    while (j >= 0 && arr[j] < key) {
      arr[j + 1] = arr[j];
      j = j - 1;
    }
    arr[j + 1] = key;
  }
}

// Insertion sort O(n^2) Menor a mayor
void insertionSortMin(int arr[], int n) {
  int i, key, j;
  for (i = 1; i < n; i++) {
    key = arr[i];
    j = i - 1;
    // Move elements of arr[0..i-1],
    // that are greater than key, to one
    // position ahead of their
    // current position
    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      j = j - 1;
    }
    arr[j + 1] = key;
  }
}

/*Se busca generar una matriz con los datos para ir calculando el gasto segun
 * los calculos anteriores*/
// Programacion dinamica O(n^2)
void dinamico(int arr[], int n, int f) {
  // Inicializamos infinito
  int INF = 1000001;
  // Inizializamos la matriz
  int matriz[n + 1][f + 1];
  // Inicializamos el arreglo con el cambio
  int M[n];

  // Caso inicial
  for (int i = 0; i <= n; i++)
    matriz[i][0] = 0;
  for (int j = 1; j <= f; j++)
    matriz[0][j] = INF;

  // Llenamos la matriz
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= f; j++) {
      if (arr[i - 1] > j)
        matriz[i][j] = matriz[i - 1][j];
      else {
        matriz[i][j] =
            std::min(matriz[i - 1][j], matriz[i][j - arr[i - 1]] + 1);
      }
    }
  }

  // Inizilizamos el arreglo como vacio
  for (int i = 0; i < n; i++)
    M[i] = 0;

  // Llenamos el arreglo con las cantidades de monedas
  int i = n;
  int j = f;
  while (j != 0) {
    if ((i > 1) && (matriz[i][j] == matriz[i - 1][j]))
      i = i - 1;
    else {
      M[i - 1] = M[i - 1] + 1;
      j = j - arr[i - 1];
    }
  }

  // Imprimir la cantidad minima de monedas si es mayor a cero, y su respectiva
  // denominacion
  for (int i = n; i > 0; i--) {
    if (M[i] >= 1)
      std::cout << M[i] << " " << arr[i] << std::endl;
  }
}

/*Algoritmo de fuerza ruta que busca solucionar el problema simplemente
 * dividiendo para asi ir calculando la cantidad de monedas de cata tipo*/
// Algoritmo codiciso O(n)
void codicioso(int arr[], int n, int f) {
  // inicializamos un arreglo que ira almacenando la cantidad de cada tipo de
  // moneda en ceros
  int arr2[n];
  for (int i = 0; i < n; i++)
    arr2[i] = 0;

  // Recorremos el arreglo que contiene las monedas disponibles
  for (int j = 0; j < n; j++) {
    // Si el cambio aun no es cero
    if (f >= 0) {
      if ((f / arr[j]) > 0) {
        arr2[j] = (f / arr[j]);
        f = f - (arr[j] * arr2[j]);
      }
    }
  }

  // Imprimir la cantidad minima de monedas si es mayor a cero, y su respectiva
  // denominacion
  for (int i = 0; i < n; i++) {
    if (arr2[i] >= 1)
      std::cout << arr2[i] << " " << arr[i] << std::endl;
  }
}

// Complegidad general O(n^2)
int main() {
  int N, P, Q;
  std::cin >> N;
  int arrMonedas[N];
  for (int i = 0; i < N; i++)
    std::cin >> arrMonedas[i];
  std::cin >> P;
  std::cin >> Q;
  int cambio = Q - P;
  // Para la programacion dinamica es mas efectivo tener las denominaciones de
  // menor a mayor
  insertionSortMin(arrMonedas, N);
  // Programacion dinamica
  dinamico(arrMonedas, N, cambio);

  std::cout << std::endl;

  // Para el algoritmo avaro, ordenamos las denominaciones de las monedas de
  // mayor a menor
  insertionSortMAX(arrMonedas, N);
  // Programacion avariciosa
  codicioso(arrMonedas, N, cambio);
}
