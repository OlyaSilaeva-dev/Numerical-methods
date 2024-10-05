#include "Gaus.h"

int main() {
    std::filesystem::current_path("C:\\src\\GitHub\\Numerical-methods\\lab2-Gaus");
    matrix matrix1;
    matrix matrix2;
    input_all("test1.txt", matrix1);
    input_all("test.txt", matrix2);
//    MoveUpMaxElement(matrix2, 1, 1);
    auto res = matrix2;
    std::cout << matrix2 << std::endl;
    vector<double> b = {-144, 25, -21, 103};
    vector<double> result = Gaus_method(matrix2, b);

    for(auto elem : result) {
        std::cout << elem << " ";
    }
    int n = matrix2.get_lines_cnt();
    int m = matrix2.get_columns_cnt();
//
}
