#include <fstream>
#include <sstream>
#include "matrix.h"
#include "iostream"

matrix::matrix(const vector<vector<double>> &other_matrix) { //конструктор
    this->_matrix = other_matrix;
    this->lines = (int)other_matrix.size();
    this->columns = (int)other_matrix[0].size();
}

matrix &matrix::input_from_file(std::ifstream &fin) { //считывает матрицу из файла
    matrix result;
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
        result._matrix.push_back(line_vector);
    }
    result.lines = (int)result._matrix.size();
    result.columns = (int)result._matrix[0].size();
    (*this) = result;
    return *this;
}

matrix &matrix::operator*(const matrix &other) { //оператор *
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

matrix &matrix::change_lines(int line1, int line2) { //меняет местами две линии
    int n = this->lines;
    vector<vector<double>> p(n, vector<double>(n, 0));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if (i == (line1)) {
                p[i][j] = (j == (line2)) ? 1: 0;
            } else if (i == line2) {
                p[i][j] = (j == line1) ? 1: 0;
            } else {
                p[i][j] = (j == i) ? 1: 0;
            }
        }
    }
    matrix p1(p);
//    std::cout << p1 << std::endl;

    auto result = p1 * (*this);
    *this = result;
    return *this;
}

std::ostream &operator<<(ostream &out, const matrix &_matrix1) {

    for (int i = 0; i < _matrix1.lines; i++) {
        for (int j = 0; j < _matrix1.columns; j++) {
            out << _matrix1._matrix[i][j] << " ";
        }
        out << "\n";
    }
    return out;
}

matrix::matrix() {
    this->_matrix = vector<vector<double>> ();
    this->lines = 0;
    this->columns = 0;
}







