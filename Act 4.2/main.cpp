#include <iostream>
#include <vector>
#include <string>

using namespace std;

/* Pruebas
 *  Prueba 1
        (0, 2), (1, 2), (2, 3), (4, 5), (1, 0), (2, 2), (3, 2), (3, 4)
        (0, 2)
        (1, 0)
        (3, 2)
        (4, 5)

 *  Prueba 2
        (3, 5), (0, 0), (1, 1)
        (0, 0)
        (1, 1)
        (3, 5)

 *  Prueba 3
        (6, 6), (4, 3)
        Se necesitan tres o mas puntos para el poligono convexo

 *  Prueba 4
        (3, 5), (7, 2), (4, 8), (10, 6), (1, 9), (9, 3), (6, 7), (2, 4), (8, 1), (5, 10)
        (1, 9)
        (2, 4)
        (5, 1)
        (8, 1)
        (9, 3)
        (6, 7)
        (4, 8)
 * */

// Estructura para los puntos
struct Point {
    int x;
    int y;

    Point(int _x, int _y) : x(_x), y(_y) {}

    bool operator<(const Point &other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
};

int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0; // Colinear
    return (val > 0) ? 1 : 2; // A favor de las manecillas del reloj | Contra las manecillas del reloj
}

void graham(int n, vector<Point> &points) {
    // Deben haber almenos tres puntos
    if (n < 3) {
        cout << "Se necesitan tres o mas puntos para el poligono convexo" << endl;
        return;
    }

    // Vectro resultado
    vector<Point> result;

    // Buscamos el punto más a la izquierda
    int l = 0;
    for (int i = 1; i < n; i++) {
        if (points[i].x < points[l].x)
            l = i;
    }

    // Iniciando por el punto más a la izquierda, vamos recorriendo los
    // puntos en dirección a las manecillas del reloj hasta regresar al punto inicial.
    int p = l, q;
    do {
        // Añadimos el punto actual al resultado
        result.push_back(points[p]);

        // Buscamos un punto "q" cuya orientación sea a favor de las
        // manecillas del reloj para todos los puntos "x". Buscando
        // realizar un seguimiento del último punto visitado en el
        // sentido contrario a las agujas del reloj en "q". Si algún
        // punto "i" está más en sentido contrario a las agujas del reloj, se actualzia "q"
        q = (p + 1) % n;
        for (int i = 0; i < n; i++) {
            // Si "i" está más en sentido contrario a las agujas del reloj, actualizamos "q"
            if (orientation(points[p], points[i], points[q]) == 2)
                q = i;
        }

        // Ahora que "q" es el punto más en el sentido contrario
        // a las agujas del reloj con respecto a "p", usaremos "p"
        // para la siguiente iteración y así "q" sea añadido al vector resultado
        p = q;

    } while (p != l);  // Mientras no lleguemos al primer punto

    // Imprimir resultado
    for (int i = 0; i < result.size(); i++)
        cout << "(" << result[i].x << ", "
             << result[i].y << ")\n";
}

int main() {
    vector<Point> points;
    string input;

    getline(cin, input);

    int x, y;
    for (int i = 0; i < input.size(); i++) {
        if (input[i - 1] == '(' && input[i + 1] == ',')
            x = input[i] - '0';
        if (input[i - 1] == ' ' && input[i + 1] == ')')
            y = input[i] - '0';
        if (input[i] == ')')
            points.emplace_back(x, y);
    }

    int n = points.size();

    // Grahams scan
    graham(n, points);

    return 0;
}
