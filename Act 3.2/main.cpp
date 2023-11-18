#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const int INF = INT_MAX;

/*Pruebas
 * Prueba 1
    Ingrese la cantidad de nodos:4
    Ingrese la matriz de costos:
    0 2 -1 3
    -1 0 1 5
    2 3 0 -1
    3 -1 4 0
    Dijkstra:
    node 1 to node 2 : 2
    node 1 to node 3 : 3
    node 1 to node 4 : 3
    node 2 to node 1 : 3
    node 2 to node 3 : 1
    node 2 to node 4 : 5
    node 3 to node 1 : 2
    node 3 to node 2 : 3
    node 3 to node 4 : 5
    node 4 to node 1 : 3
    node 4 to node 2 : 5
    node 4 to node 3 : 4
    Floyd:
    0 2 3 3
    3 0 1 5
    2 3 0 5
    3 5 4 0

 * Prueba 2
    Ingrese la cantidad de nodos:3
    Ingrese la matriz de costos:
    0 2 -1
    -1 0 5
    1 -1 0
    Dijkstra:
    node 1 to node 2 : 2
    node 1 to node 3 : 7
    node 2 to node 1 : 6
    node 2 to node 3 : 5
    node 3 to node 1 : 1
    node 3 to node 2 : 3
    Floyd:
    0 2 7
    6 0 5
    1 3 0

 * Prueba 3
    Ingrese la cantidad de nodos:3
    Ingrese la matriz de costos:
    0 -1 3
    2 0 -1
    -1 4 0
    Dijkstra:
    node 1 to node 2 : 7
    node 1 to node 3 : 3
    node 2 to node 1 : 2
    node 2 to node 3 : 5
    node 3 to node 1 : 6
    node 3 to node 2 : 4
    Floyd:
    0 7 3
    2 0 5
    6 4 0

 * Prueba 4
    Ingrese la cantidad de nodos:4
    Ingrese la matriz de costos:
    0 3 -1 7
    -1 0 2 -1
    -1 -1 0 1
    5 -1 -1 0
    Dijkstra:
    node 1 to node 2 : 3
    node 1 to node 3 : 5
    node 1 to node 4 : 6
    node 2 to node 1 : 8
    node 2 to node 3 : 2
    node 2 to node 4 : 3
    node 3 to node 1 : 6
    node 3 to node 2 : 9
    node 3 to node 4 : 1
    node 4 to node 1 : 5
    node 4 to node 2 : 8
    node 4 to node 3 : 10
    Floyd:
    0 3 5 6
    8 0 2 3
    6 9 0 1
    5 8 10 0

 * */


// Algortimo de Dijkstra
void dijkstra(vector<vector<int>> &graph, int source) {
    // Número de nodos
    int numNodes = graph.size();
    // Vector de distancias mínimas
    vector<int> distance(numNodes, INF);
    // Vector que registra si el nodo ha sido visitado o no
    vector<bool> visited(numNodes, false);

    // Distancia inicializada en 0 para el nodo de inicio
    distance[source] = 0;

    for (int i = 0; i < numNodes - 1; ++i) {
        int minDistance = INF, minIndex = -1;

        // Encontramos el nodo no visitado con la distancia mínima actual
        for (int j = 0; j < numNodes; ++j) {
            if (!visited[j] && distance[j] < minDistance) {
                minDistance = distance[j];
                minIndex = j;
            }
        }

        visited[minIndex] = true;

        // Actualizamos las distancias de los nodos adyacentes al nodo actual
        for (int j = 0; j < numNodes; ++j) {
            if (!visited[j] && graph[minIndex][j] != -1 &&
                distance[minIndex] + graph[minIndex][j] < distance[j]) {
                distance[j] = distance[minIndex] + graph[minIndex][j];
            }
        }
    }

    // Imprimimos las distancias mínimas
    for (int i = 0; i < numNodes; ++i) {
        if (i != source) {
            cout << "node " << source + 1 << " to node " << i + 1 << " : ";
            if (distance[i] == INF) {
                cout << "No hay camino" << endl;
            } else {
                cout << distance[i] << endl;
            }
        }
    }
}

// Algoritmo de Floyd
vector<vector<int>> floyd(vector<vector<int>> &graph) {
    int numNodes = graph.size();

    // Matriz de distancias mínimas entre todos los nodos
    vector<vector<int>> dist(numNodes, vector<int>(numNodes, INF));

    // Diagonal de la matriz de distancias con ceros
    for (int i = 0; i < numNodes; ++i) {
        dist[i][i] = 0;
    }

    // Llenamos la matriz de distancias con los valores iniciales del grafo
    for (int i = 0; i < numNodes; ++i) {
        for (int j = 0; j < numNodes; ++j) {
            if (graph[i][j] != -1) {
                dist[i][j] = graph[i][j];
            }
        }
    }

    // Algoritmo de Floyd-Warshall.
    for (int k = 0; k < numNodes; ++k) {
        for (int i = 0; i < numNodes; ++i) {
            for (int j = 0; j < numNodes; ++j) {
                if (dist[i][k] != INF && dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    return dist;
}

int main() {
    // N es la cantidad de nodos
    int N;

    // Ingresamos la matriz de costos del grafo dirigido
    cout << "Ingrese la cantidad de nodos: ";
    cin >> N;

    cout << "Ingrese la matriz de costos:" << endl;
    // Inicializamos la matriz (un vector de vectores)
    vector<vector<int>> graph(N, vector<int>(N));

    //Llenamos la matriz de costos
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> graph[i][j];
        }
    }

    // Algoritmo de Dijktra
    cout << "Dijkstra:" << endl;
    for (int i = 0; i < N; i++) {
        dijkstra(graph, i);
    }

    // Algoritmo de Floyd
    cout << "Floyd:" << endl;
    vector<vector<int>> result = floyd(graph);

    // Imprimimos la matriz de distancias mínimas
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (j > 0) {
                cout << " ";
            }
            if (result[i][j] == INF) {
                cout << "-1";
            } else {
                cout << result[i][j];
            }
        }
        cout << endl;
    }

    return 0;
}
