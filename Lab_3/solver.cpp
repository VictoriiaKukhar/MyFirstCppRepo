#include "solver.h"
#include <iostream>
#include <cmath>

EquationSolver::EquationSolver() {}

void EquationSolver::setRange(double l, double r) {
    left  = l;
    right = r;
}

void EquationSolver::setPrecision(double tolerance) {
    precision = tolerance;
}

// f(x) = e^x - e^(-x) - 2  (варіант 8)
double EquationSolver::func(double x) {
    double result = exp(x) - exp(-x) - 2.0;
    return result;
}

// чисельна похідна методом скінченних різниць
double EquationSolver::derivative(double x) {
    double step = 1e-6;
    double result = (func(x + step) - func(x)) / step;
    return result;
}

// метод дихотомії (поділу відрізку навпіл)
void EquationSolver::bisection() {
    if ((func(left) * func(right)) > 0) {
        std::cout << "No solution found on interval: ("
                  << left << " : " << right << ")" << std::endl;
        return;
    }

    double lo = left;
    double hi = right;
    int iter = 0;

    while (std::abs(lo - hi) > precision) {
        double mid = (lo + hi) / 2.0;
        iter++;

        if ((func(lo) * func(mid)) < 0) {
            hi = mid;
        } else {
            lo = mid;
        }
    }

    double answer = (lo + hi) / 2.0;
    std::cout << "[Bisection] x = " << answer << std::endl;
    std::cout << "[Bisection] iterations = " << iter << std::endl;
}

// метод Ньютона (дотичних)
void EquationSolver::newtonMethod() {
    double x = 1.0;        // початкове наближення (всередині [0; 1.5])
    int maxiter = 1000; 
    int iter = 0; 

    while (std::abs(func(x)) > precision && iter < maxiter) {
        if (std::abs(derivative(x)) < 1e-9) {
            std::cout << "Derivative is zero, stopping." << std::endl;
            std::cout << "[Newton] Last x = " << x << std::endl;
            return;
        }
        x = x - func(x) / derivative(x);
        iter++; 
    }

    std::cout << "[Newton] x = " << x << std::endl;
    std::cout << "[Newton] iterations = " << iter << std::endl;
}

EquationSolver::~EquationSolver() {
    std::cout << "Object destroyed." << std::endl;
}

void run() {
    EquationSolver *solver = new EquationSolver();

    double l, r, tol;
    std::cout << "Enter interval (e.g. \"0 1.5\"): ";
    std::cin >> l >> r;
    std::cout << "Enter precision: ";
    std::cin >> tol;

    solver->setRange(l, r);
    solver->setPrecision(tol);
    solver->bisection();
    solver->newtonMethod();

    delete solver;
}