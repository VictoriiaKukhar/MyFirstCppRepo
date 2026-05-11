#include "triangle.h"
#include <iostream>
#include <cmath>
#include <vector>

double distance(const Point &A, const Point &B) {
    return std::hypot(A.x - B.x, A.y - B.y);
}

bool Point::operator==(const Point &other) const {
    return distance(*this, other) < 1e-9;
}

double Triangle::perimeter() const {
    return distance(A, B) + distance(B, C) + distance(C, A);
}

double Triangle::area() const {
    return 0.5 * std::fabs((B.x - A.x) * (C.y - A.y) -
                            (C.x - A.x) * (B.y - A.y));
}

bool Triangle::hasArea() const {
    return area() > 1e-9;
}

bool Triangle::containsByArea(const Point &P) const {
    double S  = area();
    double S1 = Triangle{A, B, P}.area();
    double S2 = Triangle{B, C, P}.area();
    double S3 = Triangle{C, A, P}.area();
    return std::fabs(S - (S1 + S2 + S3)) < 1e-9;
}

bool Triangle::containsByVector(const Point &P) const {
    auto cross = [](const Point &O, const Point &X, const Point &Y) {
        return (X.x - O.x) * (Y.y - O.y) -
               (X.y - O.y) * (Y.x - O.x);
    };
    double d1 = cross(A, B, P);
    double d2 = cross(B, C, P);
    double d3 = cross(C, A, P);

    bool has_neg = (d1 < -1e-9) || (d2 < -1e-9) || (d3 < -1e-9);
    bool has_pos = (d1 >  1e-9) || (d2 >  1e-9) || (d3 >  1e-9);

    return !(has_neg && has_pos);
}

bool Triangle::isPointOnEdge(const Point &P,
                              const Point &p1, const Point &p2) const {
    double cross = (P.x - p1.x) * (p2.y - p1.y) -
                   (P.y - p1.y) * (p2.x - p1.x);
    if (std::fabs(cross) > 1e-9) return false;

    double dot  = (P.x - p1.x) * (p2.x - p1.x) +
                  (P.y - p1.y) * (p2.y - p1.y);
    double len2 = (p2.x - p1.x) * (p2.x - p1.x) +
                  (p2.y - p1.y) * (p2.y - p1.y);

    return dot >= -1e-9 && dot <= len2 + 1e-9;
}

std::string Triangle::whichEdge(const Point &P) const {
    if (isPointOnEdge(P, A, B)) return "AB";
    if (isPointOnEdge(P, B, C)) return "BC";
    if (isPointOnEdge(P, C, A)) return "CA";
    return "";
}

void Triangle::checkPointDegenerate(const Point &P) const {
    if (P == A) { std::cout << "  Tochka zbigayetsya z vershynoyu A\n"; return; }
    if (P == B) { std::cout << "  Tochka zbigayetsya z vershynoyu B\n"; return; }
    if (P == C) { std::cout << "  Tochka zbigayetsya z vershynoyu C\n"; return; }

    std::string edge = whichEdge(P);

    std::cout << "  Metod 1 (rozkladannya ploshchi): ";
    if (!edge.empty()) std::cout << "na rebri " << edge << "\n";
    else               std::cout << "zovni\n";

    std::cout << "  Metod 2 (vektornyi dobutok): ";
    if (!edge.empty()) std::cout << "na rebri " << edge << "\n";
    else               std::cout << "zovni\n";

    std::cout << "  Obydva metody uzhodzhuyutsya.\n";
}

void Triangle::checkPoint(const Point &P) const {
    if (P == A) { std::cout << "  Tochka zbigayetsya z vershynoyu A\n"; return; }
    if (P == B) { std::cout << "  Tochka zbigayetsya z vershynoyu B\n"; return; }
    if (P == C) { std::cout << "  Tochka zbigayetsya z vershynoyu C\n"; return; }

    bool byArea = containsByArea(P);
    bool byVec  = containsByVector(P);
    std::string edge = whichEdge(P);

    std::cout << "  Metod 1 (rozkladannya ploshchi): ";
    if (byArea) {
        if (!edge.empty()) std::cout << "na rebri " << edge << "\n";
        else               std::cout << "stroho vseredyni\n";
    } else {
        std::cout << "zovni\n";
    }

    std::cout << "  Metod 2 (vektornyi dobutok): ";
    if (byVec) {
        if (!edge.empty()) std::cout << "na rebri " << edge << "\n";
        else               std::cout << "stroho vseredyni\n";
    } else {
        std::cout << "zovni\n";
    }

    if (byArea == byVec)
        std::cout << "  Obydva metody uzhodzhuyutsya.\n";
    else
        std::cout << "  UVAGA: metody ne uzhodzhuyutsya!\n";
}

static Triangle readTriangle(bool &degenerate) {
    Triangle t;
    std::cout << "\nVvedit vershyny trykutnyka:\n";
    std::cout << "  A (x y): "; std::cin >> t.A.x >> t.A.y;
    std::cout << "  B (x y): "; std::cin >> t.B.x >> t.B.y;
    std::cout << "  C (x y): "; std::cin >> t.C.x >> t.C.y;

    degenerate = !t.hasArea();
    return t;
}

void run() {
    bool degenerate = false;
    Triangle ABC = readTriangle(degenerate);

    if (!degenerate) {
        std::cout << "\nInformatsiya pro trykutnyk:\n";
        std::cout << "  Ploshcha   : " << ABC.area()      << "\n";
        std::cout << "  Perymetr   : " << ABC.perimeter() << "\n";
    } else {
        std::cout << "\n  Vyrodzhenyi trykutnyk: tochky kolinearni.\n";
        std::cout << "  Perymetr (suma dovzhyn vidrizkiv): " << ABC.perimeter() << "\n";
    }

    int n;
    std::cout << "\nSkilky tochok pereviryty? ";
    std::cin >> n;

    std::vector<Point> points(n);
    
    for (int i = 0; i < n; i++) {
        std::cout << "Tochka #" << (i + 1) << " (x y): ";
        std::cin >> points[i].x >> points[i].y;
    }

    std::cout << "\n=== Rezultaty ===\n";
    for (int i = 0; i < n; i++) {
        std::cout << "\nTochka #" << (i + 1) << " (" 
                  << points[i].x << ", " << points[i].y << "):\n";
        
        if (degenerate)
            ABC.checkPointDegenerate(points[i]);
        else
            ABC.checkPoint(points[i]);
    }
}