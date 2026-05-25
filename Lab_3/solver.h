#ifndef SOLVER_H
#define SOLVER_H

class EquationSolver {
    public:
        EquationSolver(void);
        ~EquationSolver(void);
        
        void setRange(double left, double right);
        void setPrecision(double tolerance);
        
        void bisection();
        void newtonMethod();
        
        double func(double x);
        double derivative(double x);
        
    private:
        double left;
        double right;
        double precision;
};

void run();

#endif