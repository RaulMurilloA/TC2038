#include <iostream>
#import <vector>
#import <math.h>
#import <algorithm>

using namespace std;

/*Pruebas
 * Prueba 1
    6
    2, 3
    12, 30
    40, 50
    5, 1
    12, 10
    3, 4
    La distancia mas corta es: 1.41421

 * Prueba 2
    5
    2, 5
    3, 7
    8, 4
    6, 9
    1, 3
    La distancia mas corta es: 2.23607

 * Prueba 3
    1
    51, 2
    La distancia mas corta es: inf

 * Prueba 4
    3
    52, 55
    50, 80
    152, 215
    La distancia mas corta es: 25.0799
 * */

struct Point {
    int x;
    int y;
};

// Función de comparación para ordenar los puntos por coordenada x
bool compareX(const Point &p1, const Point &p2) {
    return p1.x < p2.x;
}

// Función de comparación para ordenar los puntos por coordenada y
bool compareY(const Point &p1, const Point &p2) {
    return p1.y < p2.y;
}

// Función de cálculo de la distnaica entre dos puntos
float calculateDist(Point p1, Point p2) {
    return float(sqrt((p1.x - p2.x) * (p1.x - p2.x) +
                      (p1.y - p2.y) * (p1.y - p2.y))
    );
}


// Función para encontrar la distanica entre los
// puntos más cercanos del strip. Todos los puntos
// son ordenados acorde a su coordenada en y. Todos
// tienen un límite supeior de distanica mínima minDist.
float stripClosest(vector<Point> strip, float minDist) {
    sort(strip.begin(), strip.end(), [](const Point &a, const Point &b) {
        return a.y < b.y;
    });

    // Recorremos los puntos uno por uno hsta que la diferencia entre
    // la distancia en la coordenada y sea menos que minDist
    for (size_t i = 0; i < strip.size(); ++i) {
        for (size_t j = i + 1; j < strip.size() && float(strip[j].y - strip[i].y) < minDist; ++j) {
            float dist = calculateDist(strip[i], strip[j]);
            minDist = min(minDist, dist);
        }
    }
    return minDist;
}

// Función recursiva para encontrar la distancia más corta.
float minDist(vector<Point> P) {
    // Si hay menos de dos puntos, la distanica es infinita
    if (P.size() < 2) {
        return numeric_limits<float>::infinity();
    }

    // Si hay dos puntos, regresamos la distancia entre estos
    if (P.size() == 2) {
        return calculateDist(P[0], P[1]);
    }

    // Ordenamos los puntos
    sort(P.begin(), P.end(), compareX);

    // Dividimos los puntos en dos conjuntos
    size_t mid = P.size() / 2;
    vector<Point> left(P.begin(), P.begin() + mid);
    vector<Point> right(P.begin() + mid, P.end());

    // Consiederanod la línea vertical que corta por el punto medio
    // calculamos la distancia más corta dl a la izquierda del
    // punto medio y de dr a la derecha
    float dl = minDist(left);
    float dr = minDist(right);

    // Buscamos la menor de dos distancias
    float d = min(dl, dr);

    // Creamos un vector que contenga puntos cercanos
    // a la línea que corta el punto medio
    vector<Point> strip;
    for (const auto &punto: P) {
        if (abs(float(punto.x - P[mid].x)) < d) {
            strip.push_back(punto);
        }
    }

    return stripClosest(strip, d);
}

int main() {
    int n;
    cin >> n;

    vector<Point> points;
    // Ingresamos los puntos linea por linea
    for (int i = 0; i < n; ++i) {
        Point tempPoint;
        char coma;

        // Leemos las coordenadas x, y
        cin >> tempPoint.x >> coma >> tempPoint.y;

        // Agregamos el tempPoint al vector
        points.push_back(tempPoint);
    }

    cout << "La distancia mas corta es: " << minDist(points) << endl;

    return 0;
}
