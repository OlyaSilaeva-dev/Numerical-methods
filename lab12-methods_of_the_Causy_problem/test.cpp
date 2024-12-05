#include "Causy_problem.h"

double d_y(double x, double y, double z) {
    return z;
}

double d_z (double x, double y, double z) {
    return - z / x - 2.0 * y / x;
}

double exact_solution (double x) {
    return (cos(2.0) - sin(2.0)) * cos(2.0 * sqrt(x)) +
           (cos(2.0) + sin(2.0)) * sin(2.0 * sqrt(x));
}

int main () {
    double y_0 = 1.0;
    double z_0 = 1.0;
    double a = 1.0, b = 2.0;
    double h = 0.1;

    decision(y_0, z_0, a, b, h, d_y, d_z, exact_solution,ADAMS);

    decision(y_0, z_0, a, b, h, d_y, d_z, exact_solution,RUNGE_KUTTA);
}