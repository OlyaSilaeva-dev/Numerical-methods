#include "Gaus.h"

int main() {
    std::filesystem::current_path("C:\\src\\GitHub\\Numerical-methods\\lab2-Gaus");
    vector<vector<double>> matrix1;
    vector<vector<double>> matrix2;
    input_all("test1.txt", matrix1);
    input_all("test.txt", matrix2);
//    vector<vector<double>> res = multiply_matrices(matrix1, matrix2);
//    MoveUpMaxElement(matrix2, 1, 1);
    auto res = matrix2;
    vector<double> b = {1, 2, 3};
    Gaus_method(matrix2, b);
    int n = matrix2.size();
    int m = matrix2[0].size();
//

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            std::cout << matrix2[i][j] << " ";
        }
        std::cout << std::endl;
    }



}
