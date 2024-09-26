#include <fstream>
#include <sstream>
#include "matrix.h"


matrix::matrix(const vector<vector<double>> &other_matrix) {
    this->_matrix = other_matrix;
    this->lines = (int)other_matrix.size();
    this->columns = (int)other_matrix[0].size();
}

void matrix::input_from_file(ifstream &fin, matrix &matrix1) {
    std::string line;
    while (true) {
        if (!getline(fin, line)) break;

        char c = line[line.length() - 1];
        if ( c == '\n' || c == '\r')
            line.erase(line.length() - 1);
        if (line.empty()) break;

        istringstream line_str(line);

        vector<double> line_vector;
        double a;
        while (line_str >> a) line_vector.push_back(a);
        matrix1._matrix.push_back(line_vector);
    }
    matrix1.lines = (int)matrix1._matrix.size();
    matrix1.columns = (int)matrix1._matrix[0].size();
}

matrix &matrix::operator*(const matrix &other) {
    int n1 = this->lines;
    int m1 = this->columns;
    int n2 = other.lines;
    int m2 = other.columns;

    if(m1 != n2) {
        throw logic_error("Matrices are incompatible!!!"); //матрицы несовместны
    }
    vector<vector<double>> result(n1, vector<double> (m2, 0));

    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < m2; j++) {
            result[i][j] = 0;
            for (int p = 0; p < m1; p++) {
                result[i][j] += this->_matrix[i][p] * other._matrix[p][j];
            }
        }
    }

    matrix matrix_result(result);
    *this = matrix_result;
    return *this;
}

matrix &matrix::change_lines(int line1, int line2) {
    int n = this->lines;
    vector<vector<double>> p(n, vector<double>(n, 0));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if (i == line2) {
                p[i][j] = (j == line1) ? 1: 0;
            } else if (i == line1) {
                p[i][j] = (j == line2) ? 1: 0;
            } else {
                p[i][j] = (j == i) ? 1: 0;
            }
        }
    }
    matrix p1(p);

    auto result = p1 * (*this);
    *this = result;
    return *this;
}






