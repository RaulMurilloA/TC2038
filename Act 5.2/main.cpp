#include <iostream>
#include <vector>
#include <sstream>
#include <cstring>

#define MOD 1000000007

/*Pruebas
 * Prueba 1
    3
    5 100 1
    2
    5 100
    4
    (5, 2, 100)
    (100, 2, 5)
    (1, 2, 100)
    (1, 2, 5)

 * Prueba 2
    6
    52
    63 26 52 74
    52 13 69 41
    5
    98
    46
    9
    (52, 74, 69, 5, 98, 46)
    (52, 63, 69, 5, 98, 46)
    (52, 74, 41, 5, 98, 46)
    (52, 63, 41, 5, 98, 46)
    (52, 26, 69, 5, 98, 46)
    (52, 26, 41, 5, 98, 46)
    (52, 74, 13, 5, 98, 46)
    (52, 63, 13, 5, 98, 46)
    (52, 26, 13, 5, 98, 46)

 * Prueba 3
    2
    1 2 3 4 5 6 7
    1 3 5 7 2 9 10
    44
    (7, 10)
    (7, 9)
    (6, 10)
    (6, 9)
    (6, 7)
    (5, 10)
    (5, 9)
    (5, 7)
    (7, 5)
    (6, 5)
    (4, 10)
    (4, 9)
    (4, 7)
    (4, 5)
    (3, 10)
    (3, 9)
    (3, 7)
    (3, 5)
    (7, 3)
    (6, 3)
    (5, 3)
    (4, 3)
    (2, 10)
    (2, 9)
    (2, 7)
    (2, 5)
    (2, 3)
    (7, 2)
    (6, 2)
    (5, 2)
    (4, 2)
    (3, 2)
    (1, 10)
    (1, 9)
    (1, 7)
    (1, 5)
    (1, 3)
    (1, 2)
    (7, 1)
    (6, 1)
    (5, 1)
    (4, 1)
    (3, 1)
    (2, 1)

 * Prueba 4
    10
    1 2
    2 3
    4 5
    6 7
    8 9
    9 10
    10 11
    11 12
    12 13
    13 14
    84
    (2, 3, 5, 7, 9, 10, 11, 12, 13, 14)
    (2, 3, 5, 7, 8, 10, 11, 12, 13, 14)
    (2, 3, 5, 7, 8, 9, 11, 12, 13, 14)
    (2, 3, 5, 7, 8, 9, 10, 12, 13, 14)
    (2, 3, 5, 7, 8, 9, 10, 11, 13, 14)
    (2, 3, 5, 7, 8, 9, 10, 11, 12, 14)
    (2, 3, 5, 7, 8, 9, 10, 11, 12, 13)
    (2, 3, 5, 6, 9, 10, 11, 12, 13, 14)
    (2, 3, 5, 6, 8, 10, 11, 12, 13, 14)
    (2, 3, 5, 6, 8, 9, 11, 12, 13, 14)
    (2, 3, 5, 6, 8, 9, 10, 12, 13, 14)
    (2, 3, 5, 6, 8, 9, 10, 11, 13, 14)
    (2, 3, 5, 6, 8, 9, 10, 11, 12, 14)
    (2, 3, 5, 6, 8, 9, 10, 11, 12, 13)
    (2, 3, 4, 7, 9, 10, 11, 12, 13, 14)
    (2, 3, 4, 7, 8, 10, 11, 12, 13, 14)
    (2, 3, 4, 7, 8, 9, 11, 12, 13, 14)
    (2, 3, 4, 7, 8, 9, 10, 12, 13, 14)
    (2, 3, 4, 7, 8, 9, 10, 11, 13, 14)
    (2, 3, 4, 7, 8, 9, 10, 11, 12, 14)
    (2, 3, 4, 7, 8, 9, 10, 11, 12, 13)
    (2, 3, 4, 6, 9, 10, 11, 12, 13, 14)
    (2, 3, 4, 6, 8, 10, 11, 12, 13, 14)
    (2, 3, 4, 6, 8, 9, 11, 12, 13, 14)
    (2, 3, 4, 6, 8, 9, 10, 12, 13, 14)
    (2, 3, 4, 6, 8, 9, 10, 11, 13, 14)
    (2, 3, 4, 6, 8, 9, 10, 11, 12, 14)
    (2, 3, 4, 6, 8, 9, 10, 11, 12, 13)
    (1, 3, 5, 7, 9, 10, 11, 12, 13, 14)
    (1, 3, 5, 7, 8, 10, 11, 12, 13, 14)
    (1, 3, 5, 7, 8, 9, 11, 12, 13, 14)
    (1, 3, 5, 7, 8, 9, 10, 12, 13, 14)
    (1, 3, 5, 7, 8, 9, 10, 11, 13, 14)
    (1, 3, 5, 7, 8, 9, 10, 11, 12, 14)
    (1, 3, 5, 7, 8, 9, 10, 11, 12, 13)
    (1, 3, 5, 6, 9, 10, 11, 12, 13, 14)
    (1, 3, 5, 6, 8, 10, 11, 12, 13, 14)
    (1, 3, 5, 6, 8, 9, 11, 12, 13, 14)
    (1, 3, 5, 6, 8, 9, 10, 12, 13, 14)
    (1, 3, 5, 6, 8, 9, 10, 11, 13, 14)
    (1, 3, 5, 6, 8, 9, 10, 11, 12, 14)
    (1, 3, 5, 6, 8, 9, 10, 11, 12, 13)
    (1, 3, 4, 7, 9, 10, 11, 12, 13, 14)
    (1, 3, 4, 7, 8, 10, 11, 12, 13, 14)
    (1, 3, 4, 7, 8, 9, 11, 12, 13, 14)
    (1, 3, 4, 7, 8, 9, 10, 12, 13, 14)
    (1, 3, 4, 7, 8, 9, 10, 11, 13, 14)
    (1, 3, 4, 7, 8, 9, 10, 11, 12, 14)
    (1, 3, 4, 7, 8, 9, 10, 11, 12, 13)
    (1, 3, 4, 6, 9, 10, 11, 12, 13, 14)
    (1, 3, 4, 6, 8, 10, 11, 12, 13, 14)
    (1, 3, 4, 6, 8, 9, 11, 12, 13, 14)
    (1, 3, 4, 6, 8, 9, 10, 12, 13, 14)
    (1, 3, 4, 6, 8, 9, 10, 11, 13, 14)
    (1, 3, 4, 6, 8, 9, 10, 11, 12, 14)
    (1, 3, 4, 6, 8, 9, 10, 11, 12, 13)
    (1, 2, 5, 7, 9, 10, 11, 12, 13, 14)
    (1, 2, 5, 7, 8, 10, 11, 12, 13, 14)
    (1, 2, 5, 7, 8, 9, 11, 12, 13, 14)
    (1, 2, 5, 7, 8, 9, 10, 12, 13, 14)
    (1, 2, 5, 7, 8, 9, 10, 11, 13, 14)
    (1, 2, 5, 7, 8, 9, 10, 11, 12, 14)
    (1, 2, 5, 7, 8, 9, 10, 11, 12, 13)
    (1, 2, 5, 6, 9, 10, 11, 12, 13, 14)
    (1, 2, 5, 6, 8, 10, 11, 12, 13, 14)
    (1, 2, 5, 6, 8, 9, 11, 12, 13, 14)
    (1, 2, 5, 6, 8, 9, 10, 12, 13, 14)
    (1, 2, 5, 6, 8, 9, 10, 11, 13, 14)
    (1, 2, 5, 6, 8, 9, 10, 11, 12, 14)
    (1, 2, 5, 6, 8, 9, 10, 11, 12, 13)
    (1, 2, 4, 7, 9, 10, 11, 12, 13, 14)
    (1, 2, 4, 7, 8, 10, 11, 12, 13, 14)
    (1, 2, 4, 7, 8, 9, 11, 12, 13, 14)
    (1, 2, 4, 7, 8, 9, 10, 12, 13, 14)
    (1, 2, 4, 7, 8, 9, 10, 11, 13, 14)
    (1, 2, 4, 7, 8, 9, 10, 11, 12, 14)
    (1, 2, 4, 7, 8, 9, 10, 11, 12, 13)
    (1, 2, 4, 6, 9, 10, 11, 12, 13, 14)
    (1, 2, 4, 6, 8, 10, 11, 12, 13, 14)
    (1, 2, 4, 6, 8, 9, 11, 12, 13, 14)
    (1, 2, 4, 6, 8, 9, 10, 12, 13, 14)
    (1, 2, 4, 6, 8, 9, 10, 11, 13, 14)
    (1, 2, 4, 6, 8, 9, 10, 11, 12, 14)
    (1, 2, 4, 6, 8, 9, 10, 11, 12, 13)
 * */

using namespace std;

const int N = 100;
vector<int> capList[N + 1];
int dp[1025][101];
int allmask;
int n;

long long int countWaysUtil(int mask, int i) {
    // Si todas las persones tienen una gorra significa
    // que la posibilidad es posible y regresamos 1
    if (mask == allmask) return 1;

    // Si no todos llevan una gorra y tampoco hay más gorras
    // para procesar, significa que no hay solución y regresamos 0
    if (i > 100) return 0;

    // Si ya tenemos solución para este subproblema, regresamos la respuesta
    if (dp[mask][i] != -1) return dp[mask][i];

    // ways, cuando no incluimos esta gorra en nuestro arreglo o solución
    long long int ways = countWaysUtil(mask, i + 1);

    // size es el número total de personas teniendo una gorra con el id 1
    int size = capList[i].size();

    // Asignamos uno por uno el límite máximo a todas las
    // personas posibles y repetimos para los límites restantes
    for (int j = 0; j < size; j++) {
        // Si la personas capList[i][j] ya lleva una gorra,
        // continuamos hasta que no podamos asignarle esta gorra
        if (mask & (1 << capList[i][j])) continue;

            // Si no, le asignamos esta gorra y regresamos para las gorras
            // restantes con un nuevo vector de máscara actualziado
        else ways += countWaysUtil(mask | (1 << capList[i][j]), i + 1);
        ways %= MOD;
    }

    // Guardamos el resultado y lo regresamos
    return dp[mask][i] = ways;
}

// Función para imprimir las combinaciones posibles
void printCombinations(int mask, int i, vector<int> &combinations) {
    // Verificamos si ya se asignaron gorras a todas las personas
    if (i > N) {
        // Recorremos el vector combinations para verificar que no haya combinaciones inválidas
        bool valid = true;
        for (int j = 0; j < n; j++) {
            if (combinations[j] == -1) {
                valid = false;
                break;
            }
        }

        // Si la combinación es válida, la imprimimos
        if (valid) {
            cout << "(";
            for (int j = 0; j < n; j++) {
                if (j < (n - 1))
                    cout << combinations[j] << ", ";
                else
                    cout << combinations[j];
            }
            cout << ")" << endl;
        }

        return;
    }

    // Llamada recursiva para explorar asignando la siguiente gorra
    printCombinations(mask, i + 1, combinations);

    // Iteramos por las personas que tienen la gorra i
    for (auto person: capList[i]) {
        if (mask & (1 << person))
            continue;

        // Les asignamos la gorra en combinations
        combinations[person] = i;
        // Llamada recursiva para seguir explorando
        printCombinations(mask | (1 << person), i + 1, combinations);
        // Les retiramos la asignación
        combinations[person] = -1;
    }
}


void countWays() {
    // Recibimos la cantidad de gorras de cada persona
    string temp, str;
    int x;
    getline(cin, str);
    for (int i = 0; i < n; i++) {
        getline(cin, str);
        stringstream ss(str);
        while (ss >> temp) {
            stringstream s;
            s << temp;
            s >> x;

            capList[x].push_back(i);
        }
    }

    // allmask se usa para comprobar si todas las personas
    // están incluidas o no, estableciento los bits en 1
    allmask = (1 << n) - 1;

    // Inicializamos todas las entradas en dp como -1
    memset(dp, -1, sizeof dp);

    // Llamamos a la función recursiva countWaysUtil
    cout << countWaysUtil(0, 1) << endl;

    // Imprimimos las combinaciones posibles
    vector<int> comb(n, -1);
    printCombinations(0, 1, comb);
}

int main() {
    cin >> n;
    countWays();
    return 0;
}
