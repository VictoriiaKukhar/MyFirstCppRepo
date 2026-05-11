#pragma once
#include <string>

struct Point {
    double x, y;
    bool operator==(const Point &other) const;
};

struct Triangle {
    Point A, B, C;

    double perimeter() const;
    double area() const;
    bool hasArea() const;

    bool containsByArea(const Point &P) const;
    bool containsByVector(const Point &P) const;
    bool isPointOnEdge(const Point &P, const Point &p1, const Point &p2) const;
    std::string whichEdge(const Point &P) const;

    void checkPoint(const Point &P) const;
    void checkPointDegenerate(const Point &P) const;
};

double distance(const Point &A, const Point &B);
void run();