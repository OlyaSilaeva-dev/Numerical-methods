#include "matrix.h"
#include "iostream"

int main () {

    vector<vector<double>> v1 = {{1,2,3},
                                {4,5,6},
                                {7,8,9}};

    vector<vector<double>> v2 = {{1,0,0},
                                {0,0,1},
                                {0,1,0}};
    matrix _matrix1(v1);
    matrix _matrix2(v2);
    std::cout << _matrix1 << std::endl;
    std::cout << _matrix2 << std::endl;

    matrix result = _matrix2 * _matrix1;
    std::cout << result << std::endl;

    result.change_lines(2,3);
    std::cout << result;
}