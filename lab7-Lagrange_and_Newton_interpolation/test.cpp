#include <iostream>
#include "interpolations.h"

double f(double x) {
    return asin(x) + x;
}

int main () {
    double a = -0.4;
    double b = 0.5;
    vector<double> vector1 = {-0.4, -0.1, 0.2, 0.5};
    vector<double> vector2 = {-0.4, 0, 0.2, 0.5};
    double x_star = 0.1;

    double result1 = Lagrange_polynomial(f, vector1, x_star);
    std::cout << "Lagrange_result1: " << result1 << std::endl;

    double result2 = Lagrange_polynomial(f, vector2, x_star);
    std::cout << "Lagrange_result2: " << result2 << std::endl;

    double Newton_result1 = Newton_method(f, vector1, x_star);
    double Newton_result2 = Newton_method(f, vector2, x_star);

    std::cout << "Newton_result1: " << Newton_result1 << std::endl;
    std::cout << "Newton_result2: " << Newton_result2 << std::endl;

    return 0;
}