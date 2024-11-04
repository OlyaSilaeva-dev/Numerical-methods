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
        std::cout << std::endl;
    }
    std::cout << std::endl;

}

