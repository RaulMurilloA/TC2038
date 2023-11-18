#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

/*Pruebas
 * Prueba 1
    N =4
     m[][] =
    1 0 0 0
    1 1 0 1
    1 1 0 0
    0 1 1 1
    DRDDRR

 * Prueba 2
    N =5
     m[][] =
    1 1 1 1 0
    1 0 0 1 1
    1 1 1 1 1
    1 0 0 0 1
    1 1 1 1 1
    RRRDRDDD

 * Prueba 3
    N =3
     m[][] =
    1 0 0
    0 1 0
    0 0 1
    No hay solucion para este laberinto

 * Prueba 4
    N =5
     m[][] =
    1 1 1 1 1
    1 1 1 1 1
    1 1 1 1 1
    1 1 1 1 1
    1 1 1 1 1
    RRRRDDDD
 * */

// Estructura para almacenar un nodo del laberinto
struct Node {
    int x, y; // Coordenadas x, y
    int g; // Costo desde el inicio hasta este nodo
    int h; // Heurística estimada hasta el final
    Node(int x, int y, int g, int h) : x(x), y(y), g(g), h(h) {}

    // Sobrecarga del operador < para ordenar la cola de prioridad
    bool operator<(const Node &other) const {
        return g + h > other.g + other.h;
    }
};

// Movimientos permitidos en el laberinto
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

// función para validar que la posición dada está dentro del laberint
bool isValid(int x, int y, int N, vector<vector<int>> &maze) {
    return x >= 0 && x < N && y >= 0 && y < N && maze[x][y];
}

// Imprimimos el camino encontrado
void printPathMoves(vector<pair<int, int>> path) {
    int x = 0, y = 0;

    for (int i = 1; i < path.size(); i++) {
        int newX = path[i].first;
        int newY = path[i].second;

        if (newX > x) {
            cout << "D"; // Abajo
        } else if (newX < x) {
            cout << "U"; // Arriba
        } else if (newY > y) {
            cout << "R"; // Derecha
        } else if (newY < y) {
            cout << "L"; // Izquierda
        }

        x = newX;
        y = newY;
    }
    cout << endl;
}

// Función que omplementa A*
vector<pair<int, int>> aStar(vector<vector<int>> &maze, int N) {
    // Cola de prioridad para almacenar nodos por visitar
    priority_queue<Node> pq;

    // Vector para almacenar el camino final
    vector<pair<int, int>> path;

    // Variable para saber si tiene solución o no
    bool solution = false;

    // Creamos nodo inicial y lo agregamos a la cola
    pq.emplace(0, 0, 0, 0);

    // Matriz para marcar nodos visitados
    vector<vector<bool>> visited(N, vector<bool>(N, false));

    while (!pq.empty()) {
        // Obtenemos el nodo con menor costo de la cola
        Node curr = pq.top();
        pq.pop();

        int x = curr.x;
        int y = curr.y;

        // Lo marcamos como visitado
        visited[x][y] = true;

        // Si llegamos al destino, construimos el camino y salimos
        if (x == N - 1 && y == N - 1) {
            path.emplace_back(x, y);

            while (x != 0 || y != 0) {
                if (isValid(x - 1, y, N, maze)) {
                    path.emplace_back(x - 1, y);
                    x--;
                } else if (isValid(x, y - 1, N, maze)) {
                    path.emplace_back(x, y - 1);
                    y--;
                } else if (isValid(x + 1, y, N, maze)) {
                    path.emplace_back(x + 1, y);
                    x++;
                } else if (isValid(x, y + 1, N, maze)) {
                    path.emplace_back(x, y + 1);
                    y++;
                }
            }
            reverse(path.begin(), path.end());

            // Encontramos una solución
            solution = true;
            return path;
        }



        // En caso contrario, exploramos los vecinos
        // Arriba
        if (isValid(x - 1, y, N, maze) && !visited[x - 1][y]) {
            pq.emplace(x - 1, y, curr.g + 1, abs(x - 1 - (N - 1)) + abs(y - (N - 1)));
        }

        // Abajo
        if (isValid(x + 1, y, N, maze) && !visited[x + 1][y]) {
            pq.emplace(x + 1, y, curr.g + 1, abs(x + 1 - (N - 1)) + abs(y - (N - 1)));
        }

        // Izquierda
        if (isValid(x, y - 1, N, maze) && !visited[x][y - 1]) {
            pq.emplace(x, y - 1, curr.g + 1, abs(x - (N - 1)) + abs(y - 1 - (N - 1)));
        }

        // Derecha
        if (isValid(x, y + 1, N, maze) && !visited[x][y + 1]) {
            pq.emplace(x, y + 1, curr.g + 1, abs(x - (N - 1)) + abs(y + 1 - (N - 1)));
        }
    }

    if (!solution) {
        cout << "No hay solucion para este laberinto" << endl;
    }

    return path;
}

int main() {
    int N;
    cout << "N = ";
    cin >> N;

    vector<vector<int>> maze(N, vector<int>(N));
    cout << "m[][] = " << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> maze[i][j];
        }
    }

    // Llamamos ala función que emplea el algoritmo
    // A* y guardamos el resultado en path
    auto path = aStar(maze, N);

    // Imprimimos los movimientos
    printPathMoves(path);
    return 0;
}
