#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>
#include <queue>
#include <algorithm>

using namespace std;

/*
    Parte 1
        (C, D)
        (A, B)
        (B, C)
    Parte 2
        A B C D A
    Parte 3
        78
    Parte 4
        Nueva contratacion:
        (400,300)
        Central mas cercana:
        (450,150)
*/

int N;

// Estructura para representar una arista
struct Edge {
    int src, dest, weight;
};

// Estructura para representar un punto en un plano coordenado
struct Location {
    int x;
    int y;

    // Método para calcular la distancia entre dos puntos
    double distance(const Location &other) const {
        return sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
    }
};

// Leemos el archivo con el número de colonias
int readIntTXT(const string &name) {
    int number;
    ifstream file(name);
    // Abre el archivo y lo lee
    if (file.is_open()) {
        if (file >> number) {
            // Se leyó el número correctamente
            file.close();
            return number;
        } else {
            cout << "Error: No se pudo leer un número desde el archivo." << endl;
            file.close();
            return 0;
        }
    } else {
        cout << "Error: No se pudo abrir el archivo." << endl;
        return 0;
    }
}

// Leemos los archivos con matrices
vector<vector<int>> readMatrixTXT(const string &name) {
    vector<vector<int>> matrix;
    ifstream file(name);
    // Abre el archivo y lo va leyendo línea por línea
    if (file.is_open()) {
        int number;
        for (int i = 0; i < N; ++i) {
            vector<int> row;
            for (int j = 0; j < N; ++j) {
                if (file >> number) {
                    row.push_back(number);
                } else {
                    cout << "Error: el archivo no corresponde a una matriz NxN" << endl;
                    return matrix;
                }
            }
            matrix.push_back(row);
        }
        file.close();
    } else {
        // Si el archivo no se pudo leer, regresa un mensaje de error
        // y el matrix vacio
        std::cerr << "No se pudo abrir el archivo: " << name << std::endl;
        return matrix;
    }
    return matrix;
}

// Leemos el archivo con las coordenadas
vector<Location> readLocationTXT(const string &name) {
    vector<Location> coordinates;
    ifstream file(name);
    // Abre el archivo y lo va leyendo línea por línea
    if (file.is_open()) {
        string linea;
        while (getline(file, linea)) {
            Location loc;
            stringstream ss(linea);
            char openPar, coma, closePar;
            ss >> openPar >> loc.x >> coma >> loc.y >> closePar;

            // Verifica que el formato de la línea sea correcto
            if (ss && openPar == '(' && coma == ',' && closePar == ')') {
                coordinates.push_back(loc);
            } else {
                cout << "Error: Formato incorrecto en el archivo." << endl;
                coordinates.clear();
                break;
            }
        }
        file.close();
    } else {
        cout << "Error: No se pudo abrir el archivo." << endl;
    }
    return coordinates;
}

// Función para encontrar el subconjunto al que pertenece un vértice
int find(vector<int> &parent, int i) {
    if (parent[i] == -1)
        return i;
    return find(parent, parent[i]);
}

// Función para unir dos subconjuntos en uno solo
void Union(vector<int> &parent, int x, int y) {
    int xset = find(parent, x);
    int yset = find(parent, y);
    parent[xset] = yset;
}

// Algoritmo de Kurskal's cpn Minimun Spaning Tree (MST)
// O(E log V) donde E es el número de aristas y V el número de vértices del grafo
void kruskalMST(vector<Edge> &edges) {
    // Vector que almacenará el árbol de expansión mínima
    vector<Edge> result(N);
    // Índice de la arista resultante
    int e = 0;
    // Índice de la arista actual ordenada
    int i = 0;

    // Ordenamos las aristas por su peso
    sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) {
        return a.weight < b.weight;
    });

    // Arreglo para almacenar los subconjuntos
    vector<int> parent(N, -1);

    // Iteramos hasta obtener el número de aristas requeridas para el MST
    while (e < N - 1 && i < edges.size()) {
        Edge next_edge = edges[i++];

        // Encontramos los subconjuntos a los que pertenecen los vértices de la arista
        int x = find(parent, next_edge.src);
        int y = find(parent, next_edge.dest);

        // Si agregar la arista no forma un ciclo, aregamos
        // la arista al árbol de expansión mínima resultante
        // y unimos los subconjuntos de x e y en uno solo
        if (x != y) {
            result[e++] = next_edge;
            Union(parent, x, y);
        }
    }

    // Imprimimos el MST
    for (i = 0; i < e; ++i) {
        cout << "(" << char('A' + result[i].src) << ", " << char('A' + result[i].dest) << ")" << endl;
    }
}

// Algoritmo de Traveling salesman por fuerza bruta O(n!)
void travelingSalesmanBF(vector<vector<int>> &graph) {
    int start = 0;
    int num_cities = graph.size();

    // Almacenamos todos los vértices a aparte del vértice fuente
    vector<int> cities;
    for (int i = 0; i < num_cities; ++i) {
        if (i != start) {
            cities.push_back(i);
        }
    }

    // Almacenamos el peso mínimo
    int min_path = INT_MAX;
    vector<int> min_path_order;

    do {
        // Almacenamos el peso del camino actual
        int current_pathweight = 0;
        int k = start;
        for (int i = 0; i < cities.size(); ++i) {
            current_pathweight += graph[k][cities[i]];
            k = cities[i];
        }
        current_pathweight += graph[k][start];

        // Actualizamos el mínimo
        if (current_pathweight < min_path) {
            min_path = current_pathweight;
            min_path_order = {start};
            min_path_order.insert(min_path_order.end(), cities.begin(), cities.end());
            min_path_order.push_back(start);
        }
    } while (next_permutation(cities.begin(), cities.end()));

    // Imprimimos la ruta más corta encontrada
    for (int i = 0; i < min_path_order.size(); ++i) {
        cout << char('A' + min_path_order[i]) << " ";
    }
    cout << endl;
}


// Algoritmo de búsqueda en amplitud. Regresa true si encuentra
// un camino del nodo fuente "s" al nodo sumidero "t" en el grafo
// residual. Además, rellena el vector "parent" para almacenar el camino
bool bfs(vector<vector<int>> &rGraph, int s, int t, vector<int> &parent) {
    // Creamos un vector visitado y marcamos sus vértices como no visitados.
    vector<bool> visited(N, false);

    // Creamos una queue, ponemos en esta el vértice origen y lo marcamos como visitado
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < N; v++) {
            if (visited[v] == false && rGraph[u][v] > 0) {
                // Si encintrmos una conección al nodo sumidero,
                // significa que el algoritmo BFS no tiene sentido
                // y solo necesitamos configurar su padre y devolder true
                if (v == t) {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    // Si no alcanzamos el nodo sumidero en BFS a partir del nodo fuente, regresamos false
    return false;
}

// Algoritmo de Ford Fulkerson
// O(|V| * E^2) donde E es el número de aristas y V el número de vértices del grafo
int fordFulkerson(vector<vector<int>> &graph) {
    int s = 0, t = N - 1;
    // Creamos un grafo residual y lo llenamos con las capacidades
    // dadas en el grafo original como capacidades residuales en el grafico residual
    vector<vector<int>> rGraph = graph;

    // Vector para almacenar el camino
    vector<int> parent(N);

    // Establecemos el flujo inicial en 0
    int max_flow = 0;

    // Aumentamos el flujo mientras haya un camino desde el nodo fuente al nodo sumidero
    while (bfs(rGraph, s, t, parent)) {
        // Buscamos la capacidad residual mínima de los bordes a
        // lo largo del camino lleno por el BFS. O podemos encontrar
        // el flujo máximo através del camino encontrado
        int path_flow = INT_MAX;
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }
        // Actualizamos las capacidades residuales de los
        // bordes y los bordes invrtidos a lo largo del camino
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
        // Agregamos el flujo de ruta al flujo general
        max_flow += path_flow;
    }
    // Regresamos el flujo general
    return max_flow;
}

// Algoritmo de búsqueda linear O(N)
int linearSearch(vector<Location> &plants, Location &newHiring) {
    int index = -1;
    // Generamos un valor grande para la distancia mínima
    double minDist = numeric_limits<double>::max();
    // Recorremos todos los elementos calculando la distancia
    // entre los puntos del vector y el punto a buscar
    for (int i = 0; i < N; i++) {
        double newDist = newHiring.distance(plants[i]);
        // Si la distancia es la mínima, guardamos su valor
        // y el índice en dónde se encontró
        if (newDist < minDist) {
            minDist = newDist;
            index = i;
        }
    }
    return index;
}

int main() {
    // Leemos los archivos y almacenamos su contenido
    N = readIntTXT("coloniesnum.txt");
    vector<vector<int>> dbtwcolonies = readMatrixTXT("dbtwcolonies.txt");
    vector<vector<int>> maxdataflow = readMatrixTXT("maxdataflow.txt");
    vector<Location> plantslocation = readLocationTXT("plantslocation.txt");

    cout << "Parte 1" << endl;
    // Vector para almacenar las aristas
    vector<Edge> edges;

    // Agregamos las aristas al vector
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (dbtwcolonies[i][j] != 0) {
                Edge edge;
                edge.src = i;
                edge.dest = j;
                edge.weight = dbtwcolonies[i][j];
                edges.push_back(edge);
            }
        }
    }

    // Kruskal's
    kruskalMST(edges);

    cout << "Parte 2" << endl;
    // Traveling salesman
    travelingSalesmanBF(dbtwcolonies);

    cout << "Parte 3" << endl;
    //Ford Fulkenson
    cout << fordFulkerson(maxdataflow) << endl;

    cout << "Parte 4" << endl;
    // Búsqueda linear
    cout << "Nueva contratacion:" << endl;
    Location newHiring;
    char openPar, coma, closePar;
    cin >> openPar >> newHiring.x >> coma >> newHiring.y >> closePar;
    int nearestPlant = linearSearch(plantslocation, newHiring);
    cout << "Central mas cercana:" << endl;
    cout << "(" << plantslocation[nearestPlant].x << "," << plantslocation[nearestPlant].y << ")" << endl;

    return 0;
}
