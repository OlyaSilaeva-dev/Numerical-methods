#include "Gaus.h"

int main() {
    std::filesystem::current_path("C:\\src\\GitHub\\Numerical-methods\\lab2-Gaus");
    matrix _matrix;
    vector<double> b;

    input_all("test.txt", _matrix, b);
    double det;
    vector<double> result = Gaus_method(_matrix, b, det);

    std::cout << "matrix: \n" << _matrix << std::endl;
    std::cout << "vector b: " << std::endl;
    for (auto i : b) {
        std::cout << i << " ";
    }
    std::cout << "\n\n";

    std::cout << "result: ";
    for(auto elem : result) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    if (CheckCorrectAnswer(_matrix, b, result)) {
        std::cout << "CORRECT ANSWER" << std::endl;
    } else {
        std::cout << "WRONG ANSWER" << std::endl;
    }
    std::cout << "\n";
    std::cout << "determinant: ";
    std::cout << det << "\n\n";

    std::cout << "reverse matrix: \n";
    matrix reverse = reverse_matrix(_matrix);
    if (CheckReverseMatrix(_matrix, reverse)) {
        std::cout << "Correct reverse matrix" << std::endl;
    } else {
        std::cout << "Wrong reverse matrix" << std::endl;
    }
}
