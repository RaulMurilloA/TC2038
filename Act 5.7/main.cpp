#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

/*Pruebas
 * Prueba 1
    8
     0 0 0 1 0 0 0 0
     1 0 0 0 0 0 0 0
     0 0 0 0 1 0 0 0
     0 0 0 0 0 0 0 1
     0 0 0 0 0 1 0 0
     0 0 1 0 0 0 0 0
     0 0 0 0 0 0 1 0
     0 1 0 0 0 0 0 0

 * Prueba 2
    4
     0 1 0 0
     0 0 0 1
     1 0 0 0
     0 0 1 0

 * Prueba 3
    8
     0 0 0 0 0 1 0 0
     1 0 0 0 0 0 0 0
     0 0 0 0 1 0 0 0
     0 1 0 0 0 0 0 0
     0 0 0 0 0 0 0 1
     0 0 1 0 0 0 0 0
     0 0 0 0 0 0 1 0
     0 0 0 1 0 0 0 0

 * Prueba 4
    N debe ser 4 u 8
 * */

int N;

// Función para configurar el vector "board" y "state" de manera
// aleatoria para proveer un punto de inicio para el algoritmo
void configureRandomly(vector<vector<int>> &board, vector<int> &state) {
    // Semilla para la función random
    srand(time(0));

    // Iteramos atraves de los íncdices de la columna
    for (int i = 0; i < N; i++) {
        // Obtenemos un índice random para las filas
        state[i] = rand() % N;

        // Colocamos una reina en el lugar obtenido
        board[state[i]][i] = 1;
    }
}

// Función para imprimir el tablero
void printBoard(vector<vector<int>> &board) {
    for (int i = 0; i < N; i++) {
        cout << " ";
        for (int j = 0; j < N; j++) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}

// Función para comparar dos vectores, y regresar true si son iguales
bool compareStates(vector<int> &state1, vector<int> &state2) {
    for (int i = 0; i < N; i++) {
        if (state1[i] != state2[i]) {
            return false;
        }
    }
    return true;
}

// Función para rellenar el vector "board" con un valor "value"
void fill(vector<vector<int>> &board, int value) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = value;
        }
    }
}

// Función para calcular el valor objetivo del estado usando el tablero
int calculateObjective(vector<vector<int>> &board, vector<int> &state) {
    // Para cada reina en una columa, revisamos por otras reinas
    //  en la línea de nuestra reina actual y si hay alguna,
    //  incrementamos el recuento de ataques de la variable

    // Número de reinas atacándose, inicializado en 0
    int attacking = 0;

    // Variables para indexar una fila y columa en particulas del tablero
    int row, col;

    for (int i = 0; i < N; i++) {
        // En cada columna "i", la reina es colocada en la
        // fila "state[i]", por definición de nuestro estado

        // A la izquierda de la misma fila (la fila
        // permanece constante y la columna disminuye)
        row = state[i], col = i - 1;
        while (col >= 0 && board[row][col] != 1) {
            col--;
        }
        if (col >= 0 && board[row][col] == 1) {
            attacking++;
        }

        // A la derecha de la misma fila (la fila
        // permanece constante y la columna aumenta)
        row = state[i], col = i + 1;
        while (col < N && board[row][col] != 1) {
            col++;
        }
        if (col < N && board[row][col] == 1) {
            attacking++;
        }

        // En diagonal a la izquierda y arriba (la
        // fila y columna disminuyen simultáneamente)
        row = state[i] - 1, col = i - 1;
        while (col >= 0 && row >= 0 && board[row][col] != 1) {
            col--;
            row--;
        }
        if (col >= 0 && row >= 0 && board[row][col] == 1) {
            attacking++;
        }

        // En diagonal a la derecha y abajo (la
        // fila y columna aumentan simultáneamente)
        row = state[i] + 1, col = i + 1;
        while (col < N && row < N && board[row][col] != 1) {
            col++;
            row++;
        }
        if (col < N && row < N && board[row][col] == 1) {
            attacking++;
        }

        // En diagonal a la izquierda y abajo (la
        // columna disminuye y la fila aumenta)
        row = state[i] + 1, col = i - 1;
        while (col >= 0 && row < N && board[row][col] != 1) {
            col--;
            row++;
        }
        if (col >= 0 && row < N && board[row][col] == 1) {
            attacking++;
        }

        // En diagonal a la derecha y arriba (la
        // columna incrementa y la fila disminuye)
        row = state[i] - 1, col = i + 1;
        while (col < N && row >= 0 && board[row][col] != 1) {
            col++;
            row--;
        }
        if (col < N && row >= 0 && board[row][col] == 1) {
            attacking++;
        }
    }

    // Regresamos pares
    return (int) (attacking / 2);
}

// Función que genera la configuración del tablero dado el estado
void generateBoard(vector<vector<int>> &board, vector<int> &state) {
    fill(board, 0);
    for (int i = 0; i < N; i++) {
        board[state[i]][i] = 1;
    }
}

// Función que copia el contenido de "state2" a "state1"
void copyState(vector<int> &state1, vector<int> &state2) {
    for (int i = 0; i < N; i++) {
        state1[i] = state2[i];
    }
}

// Función para obtener el vecino del estado actual que tiene el menor
// valor objetivo entre todos los vecinos, así como el estado actual.
void getNeighbour(vector<vector<int>> &board, vector<int> &state) {
    // Declaramos e inicializamos el tablero y estado óptimo como el punto de inicio

    vector<vector<int>> opBoard(N, vector<int>(N));
    vector<int> opState(N);

    copyState(opState, state);
    generateBoard(opBoard, opState);

    // Inicializamos el valor objetivo óptimo
    int opObjective = calculateObjective(opBoard, opState);

    // Declaramos e inizializamos el tablero y estado temporal para computarizarlo
    vector<vector<int>> NeighbourBoard(N, vector<int>(N));
    vector<int> NeighbourState(N);

    copyState(NeighbourState, state);
    generateBoard(NeighbourBoard, NeighbourState);

    // Iteramos a traves de todos los vecinos posibles del tablero
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {

            // Condición para saltarnos el estado actual
            if (j != state[i]) {

                // Inizializamos vecinos temporales con el vecino actual
                NeighbourState[i] = j;
                NeighbourBoard[NeighbourState[i]][i] = 1;
                NeighbourBoard[state[i]][i] = 0;

                // Calculamos el valor objetivo de los vecinos
                int temp = calculateObjective(NeighbourBoard, NeighbourState);

                // Comparamos los vecinos temporales y óptimos y si
                // el temporal tiene menos valor que el óptimo, actualizamos
                if (temp <= opObjective) {
                    opObjective = temp;
                    copyState(opState, NeighbourState);
                    generateBoard(opBoard, opState);
                }

                // Regresamos a la ocnfiguración original para la siguiente iteración
                NeighbourBoard[NeighbourState[i]][i] = 0;
                NeighbourState[i] = state[i];
                NeighbourBoard[state[i]][i] = 1;
            }
        }
    }

    // Copiamos el tablero y estado óptimo encontrados en el tablero actual
    copyState(state, opState);
    fill(board, 0);
    generateBoard(board, state);
}

void hillClimbing(vector<vector<int>> &board, vector<int> &state) {
    // Declaramos e inicializamos el tablero y estado vecinos con
    // el tableroy el estado actual como punto de inicio
    vector<vector<int>> neighbourBoard(N, vector<int>(N));
    vector<int> neighbourState(N);

    copyState(neighbourState, state);
    generateBoard(neighbourBoard, neighbourState);

    do {

        // Declaramos el tablero y estado vecino al tablero y estado actual
        copyState(state, neighbourState);
        generateBoard(board, state);

        // Obtenemos el vecino óptimo
        getNeighbour(neighbourBoard, neighbourState);

        if (compareStates(state, neighbourState)) {

            // Si el vecino y el actual son iguales entonces no existe
            // un vecino óptimo, por lo tanto generamos el resultado y rompemos el loop
            printBoard(board);
            break;
        } else if (calculateObjective(board, state) ==
                   calculateObjective(neighbourBoard, neighbourState)) {
            // Si el vecino y el actual no son iguales pero sus objetivos
            // son iguales entonces nos estamos acercando a un óptimo local,
            // en cualquier caso, saltamos a un vecino aleatorio para librarnso de él

            // Vecino aleatorio
            neighbourState[rand() % N] = rand() % N;
            generateBoard(neighbourBoard, neighbourState);
        }

    } while (true);
}

int main() {
    cin >> N;

    if (N != 4 && N != 8) {
        cout << "N debe ser 4 u 8" << endl;
        return 1;
    }

    vector<int> state(N);
    vector<vector<int>> board(N, vector<int>(N));

    // Obtenemos un punto de inicio por medio de configurar aleatoriamente el tablero
    configureRandomly(board, state);

    // Llamamos al algoritmo de Hill Climbing con el tablero obtenido
    hillClimbing(board, state);

    return 0;
}
