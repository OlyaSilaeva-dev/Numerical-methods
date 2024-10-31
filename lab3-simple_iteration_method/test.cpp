#include "filesystem"
#include "simple_iteration_method.h"

int main() {
    matrix a;
    vector<double> b;

    filesystem::current_path("C:/src/GitHub/Numerical-methods/lab3-simple_iteration_method");
    input_all("test.txt", a, b);

    std::cout << "matrix: \n" << a << "\nvector b: " << std::endl;
    for (double d : b) {
        std::cout << d << " ";
    }
    std::cout << "\n\n";

    vector<double> result;
    result = simple_iteration_method(a, b);

    for (auto elem : result) {
        std::cout << elem << " ";
    }

    vector<double> result1 = Zeidal_method(a, b);
    for (auto elem : result1) {
        std::cout << elem << " ";
    }

    return 0;
}