#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

/*Pruebas
 * Prueba 1
    8
       0   59   38   33   30   17    8   63
      37   34   31   60    9   62   29   16
      58    1   36   39   32   27   18    7
      35   48   41   26   61   10   15   28
      42   57    2   49   40   23    6   19
      47   50   45   54   25   20   11   14
      56   43   52    3   22   13   24    5
      51   46   55   44   53    4   21   12

 * Prueba 2
    5
       0    5   14    9   20
      13    8   19    4   15
      18    1    6   21   10
       7   12   23   16    3
      24   17    2   11   22

 * Prueba 3
    2
    No hay solucion para el Knight's Tour con el tamano de tablero especificado.

 * Prueba 4
    6
       0   15    6   25   10   13
      33   24   11   14    5   26
      16    1   32    7   12    9
      31   34   23   20   27    4
      22   17    2   29    8   19
      35   30   21   18    3   28
 * */

// Movimientos válidos del caballo en el tablero
const int movementsRow[8] = {2, 1, -1, -2, -2, -1, 1, 2};
const int movementsColumn[8] = {1, 2, 2, 1, -1, -2, -2, -1};

// Función para validar el movimiento del caballo
bool isMovementValid(int x, int y, int N, vector<vector<int>> &board) {
    return (x >= 0 && x < N && y >= 0 && y < N && board[x][y] == -1);
}

// Función recursiva para mover al caballo
bool moveKnight(int x, int y, int movement, int N, vector<vector<int>> &board) {
    // Caso base
    if (movement == N * N)
        return true;

    // Intentamos realizar todos los movimientos posibles desde la posición actual
    for (int k = 0; k < 8; k++) {
        int nextX = x + movementsRow[k];
