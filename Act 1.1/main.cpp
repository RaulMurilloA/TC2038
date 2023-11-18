#include <iostream>

/***
Casos de prueba:
10 elementos >> Entrada: 1, 4.8, 6, 6, 8, 2, 3, 2.3, 10, 5
  Resultado: 10 8 6 6 5 4.8 3 2.3 2 1

18 elementos >> Entrada: 2, 2.2, 4, 9, 20, 22, 1, 1, 1, 1, 10, 11, 12, 14,
6, 2.7, 7, 100
  Resultado: 100 22 20 14 12 11 10 9 7 6 4 2.7 2.2 2 1 1 1 1

12 elementos >> Entrada: 17, 16, 61, 51.5, 17.7, 6, 10, 8.5, 10.4, 10.41,
12, 12.9
  Resultado: 61 51.5 17.7 17 16 12.9 12 10.41 10.4 10 8.5 6

5 elementos >> Entrada:5.2, 7.1, 9.85, 9.84, 5
  Resultado: 9.85 9.84 7.1 5.2 5

8 elementos >> 84, 51, 83, 80, 50, 9, 10, 79
  Resultado: 84 83 80 79 51 50 10 9
***/

// Función Merge
void merge(double lista[], int const left, int const mid, int const right) {
  int const subListaUno = mid - left + 1;
  int const subListaDos = right - mid;

  // Arreglos temporales
  auto *leftLista = new double[subListaUno],
       *rightLista = new double[subListaDos];

  // Copia los datos en los arreglos temporales
  for (auto i = 0; i < subListaUno; i++)
    leftLista[i] = lista[left + i];
  for (auto j = 0; j < subListaDos; j++)
    rightLista[j] = lista[mid + 1 + j];

  auto indiceSubListaUno = 0, indiceSubListaDos = 0;
  int indiceListaCombinada = left;

  // Combina los arreglos temporales en el principal
  while (indiceSubListaUno < subListaUno && indiceSubListaDos < subListaDos) {
    if (leftLista[indiceSubListaUno] >= rightLista[indiceSubListaDos]) {
      lista[indiceListaCombinada] = leftLista[indiceSubListaUno];
      indiceSubListaUno++;
    } else {
      lista[indiceListaCombinada] = rightLista[indiceSubListaDos];
      indiceSubListaDos++;
    }
    indiceListaCombinada++;
  }

  // Copia los elmentos restantes del lado izquierdo
  while (indiceSubListaUno < subListaUno) {
    lista[indiceListaCombinada] = leftLista[indiceSubListaUno];
    indiceSubListaUno++;
    indiceListaCombinada++;
  }

  // Copia los elmentos restantes del lado izquierdo
  while (indiceSubListaDos < subListaDos) {
    lista[indiceListaCombinada] = rightLista[indiceSubListaDos];
    indiceSubListaDos++;
    indiceListaCombinada++;
  }

  delete[] leftLista;
  delete[] rightLista;
}

// Función Merge Sort
void mergeSort(double lista[], int low, int high) {
  if (low >= high) {
    return;
  } else {
    int mid = low + (high - low) / 2;
    mergeSort(lista, low, mid);
    mergeSort(lista, mid + 1, high);
    merge(lista, low, mid, high);
  }
}

int main() {
  int n;    // Número de datos
  double j; // Número ingresado en el arreglo

  // Entrada de datos
  std::cout << "Ingrese la cantidad de valores: ";
  std::cin >> n;

  std::cout << "Ingrese los valores: " << std::endl;
  double arreglo[n]; // Arreglo de números
  // Ciclo para ingresar los datos en el arreglo
  for (int i = 0; i < n; i++) {
    std::cin >> j;
    arreglo[i] = j;
  }

  // mergeSort
  mergeSort(arreglo, 0, n - 1);

  // Salida de datos
  for (int i = 0; i < n; i++) {
    std::cout << arreglo[i] << " ";
    if (i == n - 1) {
      std::cout << std::endl;
    }
  }
}
