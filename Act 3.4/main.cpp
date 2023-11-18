#include <iostream>
#include <vector>

using namespace std;

/*Pruebas
 * Prueba 1
    Ingrese la cantidad de nodos:5
    Ingrese la matriz de adyacencias:
    0 0 1 0 1
    0 0 1 1 1
    1 1 0 1 0
    0 1 1 0 1
    1 1 0 1 0
    Nodo 0, Color asignado: 0
    Nodo 1, Color asignado: 0
    Nodo 2, Color asignado: 1
    Nodo 3, Color asignado: 2
    Nodo 4, Color asignado: 1

 * Prueba 2
    Ingrese la cantidad de nodos:4
    Ingrese la matriz de adyacencias:
    0 1 1 0
    1 0 1 1
    1 1 0 1
    0 1 1 0
    Nodo 0, Color asignado: 0
    Nodo 1, Color asignado: 1
    Nodo 2, Color asignado: 2
    Nodo 3, Color asignado: 0

 * Prueba 3
    Ingrese la cantidad de nodos:6
    Ingrese la matriz de adyacencias:
    0 1 1 0 0 0
    1 0 1 1 0 0
    1 1 0 1 1 0
    0 1 1 0 1 1
    0 0 1 1 0 1
    0 0 0 1 1 0
    Nodo 0, Color asignado: 0
    Nodo 1, Color asignado: 1
    Nodo 2, Color asignado: 2
    Nodo 3, Color asignado: 0
    Nodo 4, Color asignado: 1
    Nodo 5, Color asignado: 2

 * Prueba 4
    Ingrese la cantidad de nodos:10
    Ingrese la matriz de adyacencias:
    0 1 0 0 1 0 0 0 0 1
    1 0 1 0 0 0 0 0 0 0
    0 1 0 1 0 0 0 0 0 0
    0 0 1 0 1 0 0 0 0 0
    1 0 0 1 0 1 0 0 0 0
    0 0 0 0 1 0 1 0 0 0
    0 0 0 0 0 1 0 1 0 0
    0 0 0 0 0 0 1 0 1 0
    0 0 0 0 0 0 0 1 0 1
    1 0 0 0 0 0 0 0 1 0
    Nodo 0, Color asignado: 0
    Nodo 1, Color asignado: 1
    Nodo 2, Color asignado: 0
    Nodo 3, Color asignado: 1
    Nodo 4, Color asignado: 2
    Nodo 5, Color asignado: 0
    Nodo 6, Color asignado: 1
    Nodo 7, Color asignado: 0
    Nodo 8, Color asignado: 1
    Nodo 9, Color asignado: 2
 * */


// Función para verificar si se puede asignar un color a un nodo
bool isColorSafe(int v, vector<vector<int>> &graph, vector<int> &solution, int color, int N) {
    for (int i = 0; i < N; i++) {
        if (graph[v][i] && solution[i] == color)
            return false;
    }
    return true;
}

// Función recursiva para resolver el problema de coloración
bool solveColoring(vector<vector<int>> &graph, int N, vector<int> &solution, int m, int v) {
    if (v == N)
        return true;

    for (int c = 0; c < m; c++) {
        if (isColorSafe(v, graph, solution, c, N)) {
            solution[v] = c;
            if (solveColoring(graph, N, solution, m, v + 1))
                return true;
            solution[v] = -1;
        }
    }

    return false;
}

// Función principal para resolver el problema de coloración de grafos
void graphColoring(vector<vector<int>> &graph, int N, int m) {
    // Vector que almacena la solución de los colores de cada grafo
    vector<int> solution(N, -1);

    // Verifica que s puedan asignar colores y que la solución es válida
    if (solveColoring(graph, N, solution, m, 0)) {
        for (int i = 0; i < N; i++) {
            cout << "Nodo " << i << ", Color asignado: " << solution[i] << endl;
        }
    } else {
        cout << "No es posible asignar colores a los nodos." << endl;
    }
}

int main() {
    // N es la cantidad de nodos
    int N;

    // Ingresamos la matriz de adyacencias
    cout << "Ingrese la cantidad de nodos: ";
    cin >> N;

    vector<vector<int>> graph(N, vector<int>(N));
    // Número máximo de colores
    int m = 3;

    cout << "Ingrese la matriz de adyacencias: " << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> graph[i][j];
        }
    }

    // Función de coloreo del grafo
    graphColoring(graph, N, m);

    return 0;
}
