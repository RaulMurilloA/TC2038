#include <iostream>
#include <bits/stdc++.h>

using namespace std;

/*Pruebas
 * Prueba 1
    3
    1
    2
    3
    4
    5
    1
    4

    3

 * Prueba 2
    7
    3
    6
    2
    8
    5
    4
    7
    12
    24
    8
    32
    20
    16
    28
    13

    3

 * Prueba 3
    3
    60
    100
    120
    10
    20
    30
    50

    220

 * Prueba 4
    10
    5
    2
    8
    1
    10
    3
    6
    4
    7
    9
    20
    10
    30
    5
    40
    15
    25
    18
    35
    45
    217

    49
 * */

// Función para encontrar la ganancia máxima
int knapSack(int W, int *valores, int *pesos, int n) {
    // Creamos e inicializamos el arreglo dp
    int dp[W + 1];
    memset(dp, 0, sizeof(dp));

    //  Bucle anidado para recorrer los arreglos en busca del valor máximo
    for (int i = 1; i <= n; i++) {
        for (int w = W; w >= 0; w--) {
            if (pesos[i - 1] <= w)
                // Buscamos el valor máximo
                dp[w] = max(dp[w], dp[w - pesos[i - 1]] + valores[i - 1]);
        }
    }

    // Regresamos el valor máximo
    return dp[W];
}

int main() {
    int N, W;

    //  Número de elementos
    cin >> N;

    // Arreglo de valores
    int valores[N];
    for (int i = 0; i < N; i++) {
        cin >> valores[i];
    }

    // Arreglo de pesos
    int pesos[N];
    for (int i = 0; i < N; i++) {
        cin >> pesos[i];
    }

    // Peso máximo
    cin >> W;

    cout << endl;
    // Función para calcular la ganancia máxima
    cout << knapSack(W, valores, pesos, N);

    return 0;
}
