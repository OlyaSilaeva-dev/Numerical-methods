#include "methods.h"
#include "filesystem"


ld func (ld x) {
    return pow(x,4.0) - 2.0 * x - 1.0;
}

ld dfunc (ld x) {
    return 4.0 * pow(x, 3.0) - 2.0;
}

ld ddfunc (ld x) {
    return 12.0 * x * x;
}

ld phi_x_p (ld x) {
    return (pow(x, 4) - 1.0) / 2.0;
}

ld dphi_x_p (ld x) {
    return 2.0 * pow(x, 3);
}

int main () {
//    std::cout << "Enter the epsilon: " << std::endl;
    ld eps = 0.0000001;
//    std::cin >> eps;

    ld result_simple_iteration_method = simple_iteration_method(phi_x_p, dphi_x_p, 0.0, 1.4, eps);
    std::cout << "Result of simple iteration method: " << result_simple_iteration_method << std::endl;

    ld result_dichotomy_method1 = dichotomy_method(func, 0.0, 2.0, eps);
    ld result_dichotomy_method = dichotomy_method(func, -1.0, 1.0, eps);
    std::cout << "Result of dichotomy method: " << result_dichotomy_method << ", " << result_dichotomy_method1 << std::endl;

    ld result_newton_method1 = newton_method(func, dfunc, ddfunc, 0.0, 2.0, eps);
    ld result_newton_method = newton_method(func, dfunc, ddfunc, -0.5, 0.0, eps);
    std::cout << "Result of newton method: " << result_newton_method << ", " << result_newton_method1 << std::endl;

    ld result_secant_method1 = secant_method(func, ddfunc, eps, 0.89, 1.5);
    ld result_secant_method = secant_method(func, ddfunc, eps, -0.89, 0.99);
    std::cout << "Result of secant method: " << result_secant_method << ", " << result_newton_method1 << std::endl;
}