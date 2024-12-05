#include "Rotation_method.h"
#include <filesystem>

int main () {
    matrix _matrix;
    filesystem::current_path(R"(C:\src\GitHub\Numerical-methods\lab4-Rotation_method)");
    input_matrix("test.txt", _matrix);

    std::cout << "Matrix: \n"<< _matrix << std::endl;

    vector<double> eigenvalues;
    matrix eigenvectors;
    Rotation_method(_matrix, eigenvalues, eigenvectors);

    for (int i = 0; i < eigenvalues.size(); i++) {
        std::cout << "Value " << i << ": " << eigenvalues[i] << "\t";
        std::cout << "Vector: ";
        for (auto v : eigenvectors.get_matrix()[i]) {
            std::cout << v << " ";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;

    vector<double> y_0 = {1, 1, 1};
    vector<double> power_law_method_res;
    double res = power_law_method(_matrix, y_0, power_law_method_res);

    std::cout << "power_law_method result: " << res << "\n";
    std::cout << "vector_power_law_method result: ";
    for (double k : power_law_method_res) {
        std::cout << k << " ";
    }

}

