#include "methods.h"
#include "filesystem"

int main () {
    std::filesystem::current_path(R"(C:\src\GitHub\Numerical-methods\lab5-4methods_for_nonlinear_equations)");

    std::string expression;
    double epsilon;
    input_data("test.txt", expression, epsilon);

    std::cout << expression << "\n" << epsilon << std::endl;
    double init_guess = 1.0;
    std::vector<double> result = simple_iteration_method(expression, init_guess, epsilon);
    std::cout << "Iterations:\n";
    for (double x : result) {
        std::cout << x << std::endl;
    }
}