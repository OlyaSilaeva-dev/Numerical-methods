#include "integration.h"

double func(double x) {
    return x * x / (625.0 - pow(x, 4));
}

double dd_func(double x) {
    return 2 * (3 * pow(x, 8) + 7500 * pow(x, 4) + 390625) /
        pow(x + 5, 3) * (x - 5, 3) * pow((x * x + 25), 3);
}

double func_test(double x) {
    return x / ((3 * x + 4) * (3 * x + 4));
}

int main() {
    double x_0 = 0.0, x_k = 4.0;
    double h_1 = 1.0, h_2 = 0.5;

    double x_0_test = -1.0, x_k_test = 1.0;
    double h_1_test = 0.5, h_2_test = 0.25;

    double result1_test = rectangle_integration_method(func, x_0, x_k, h_1);
    double result_estimation1 = runge_romberg_estimation(func, x_0, x_k, h_1, RECTANGLE);
    std::cout << "rectangle_integration_method for h1: " << result1_test << std::endl;
    std::cout << "Estimation rectangle for h1: " << result_estimation1 << std::endl;

    double result2_test = rectangle_integration_method(func, x_0, x_k, h_2);
    double result_estimation2 = runge_romberg_estimation(func, x_0, x_k, h_2, RECTANGLE);
    std::cout << "rectangle_integration_method_test for h2: " << result2_test << std::endl;
    std::cout << "Estimation rectangle for h2: " << result_estimation2 << std::endl;

    double result3_test = trapezoid_integration_method(func, x_0, x_k, h_1);
    double result_estimation3 = runge_romberg_estimation(func, x_0, x_k, h_1, TRAPEZOID);
    std::cout << "trapezoid_integration_method for h1: " << result3_test << std::endl;
    std::cout << "Estimation trapezoid for h1: " << result_estimation3 << std::endl;

    double result4_test = trapezoid_integration_method(func, x_0, x_k, h_2);
    double result_estimation4 = runge_romberg_estimation(func, x_0, x_k, h_2, TRAPEZOID);
    std::cout << "trapezoid_integration_method for h2: " << result4_test << std::endl;
    std::cout << "Estimation trapezoid for h2: " << result_estimation4 << std::endl;

    double result5_test = Simpson_integration_method(func, x_0, x_k, h_1);
    double result_estimation5 = runge_romberg_estimation(func, x_0, x_k, h_2, SIMPSON);
    std::cout << "Simpson_integration_method for h1: " << result5_test << std::endl;
    std::cout << "Estimation Simpson for h1: " << result_estimation5 << std::endl;

    double result6_test = Simpson_integration_method(func, x_0, x_k, h_2);
    double result_estimation6 = runge_romberg_estimation(func, x_0, x_k, h_2, SIMPSON);
    std::cout << "Simpson_integration_method for h2: " << result6_test << std::endl;
    std::cout << "Estimation Simpson for h2: " << result_estimation6 << std::endl;

    std::cout << "\nEXACT RESULT: " << 0.0423871 << std::endl;
}