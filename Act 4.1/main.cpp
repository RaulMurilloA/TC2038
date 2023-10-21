#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

/*Pruebas
 * Prueba 1
    3
    1 5 7 1 1 4 10 9
    10 2 1 12 3 3 0 15
    -6 -6 3 4 2 2 1 1
    True (1.81818, 4.45455)
    False
    False

 * Prueba 2
    4
    0 0 3 3 1 0 4 4
    2 2 3 3 5 5 6 6
    7 7 8 8 9 9 10 10
    -8 -4 -2 -2 4 2 6 -6
    True (4, 4)
    False
    False
    True (4.46154, 0.153846)

 * Prueba 3
    2
    -5 5 -5 -5 5 5 5 -5
    -10 5 -5 0 0 5 15 -10
    False
    False

 * Prueba 4
    5
    0 0 10 15 0 5 25 0
    14 28 24 6 10 2 26 28
    16 22 16 6 16 28 16 2
    4 6 28 12 18 4 32 8
    15 25 60 -10 5 5 75 5
    True (2.94118, 4.41176)
    True (19.098, 16.7843)
    False
    True (172, 48)
    True (40.7143, 5)
 * */

class Point {
public:
    double x;
    double y;

    Point() : x(0), y(0) {};

    Point(double _x, double _y) : x(_x), y(_y) {};

    bool operator==(Point point) {
        return x == point.x && y == point.y;
    }

    string pointToString() {
        stringstream sstream;
        sstream << '(' << x << ", " << y << ')';
        return sstream.str();
    }
};

class Line {
public:
    Point p1;
    Point p2;

    Line(const Point &point1, const Point &point2) : p1(point1), p2(point2) {};

    Line(double x1, double y1, double x2, double y2) : p1(x1, y1), p2(x2, y2) {};

    bool operator==(Line line) {
        return p1 == line.p1 && p2 == line.p2;
    }

    // Método para verificar si dos líneas son paralelas
    bool isParallel(const Line &other) const {
        double slope1 = (p2.y - p1.y) / (p2.x - p1.x);
        double slope2 = (other.p2.y - other.p1.y) / (other.p2.x - other.p1.x);
        return slope1 == slope2;
    }

    // Método para verificar si dos líneas son la misma
    bool isSame(const Line &other) const {
        return (p1.x == other.p1.x && p1.y == other.p1.y && p2.x == other.p2.x && p2.y == other.p2.y) ||
               (p1.x == other.p2.x && p1.y == other.p2.y && p2.x == other.p1.x && p2.y == other.p1.y);
    }

    // Método para identificar si exite una intersección entre dos líneas
    pair<bool, Point> intersect(Line &other, Point &intersection) const {
        // Si las líneas son paralelas o son la misma, regresa un "false"
        if (isParallel(other) || isSame(other)) {
            return make_pair(false, Point(0, 0));
        }

        double x1 = p1.x, y1 = p1.y;
        double x2 = p2.x, y2 = p2.y;
        double x3 = other.p1.x, y3 = other.p1.y;
        double x4 = other.p2.x, y4 = other.p2.y;

        // Cálculo del determinante por medio de la fórmula del determinante de la matriz foramda por los coeficientes de las ecuaciones de las dos líneas
        double det = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

        // No se intersecan
        if (det == 0) {
            return make_pair(false, Point(0, 0));
        }

        // Valor para determinar el punto de intersección
        double t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / det;

        // Se calcula el punto de intersección
        intersection.x = x1 + t * (x2 - x1);
        intersection.y = y1 + t * (y2 - y1);
        return make_pair(true, intersection);
    }
};

int main() {
    int n;
    cin >> n;
    vector<pair<bool, Point>> results(n);

    for (int i = 0; i < n; i++) {
        Point p1, q1, p2, q2;
        cin >> p1.x >> p1.y >> q1.x >> q1.y >> p2.x >> p2.y >> q2.x >> q2.y;

        Line line1(p1, q1);
        Line line2(p2, q2);
        Point intersection;

        results[i] = line1.intersect(line2, intersection);
    }

    for (int i = 0; i < n; i++) {
        if (results[i].first)
            cout << "True " << results[i].second.pointToString() << endl;
        else
            cout << "False" << endl;
    }

    return 0;
}
