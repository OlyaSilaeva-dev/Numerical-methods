#ifndef CM_GAUS_H
#define CM_GAUS_H

#include <iostream>
#include <vector>
#include <filesystem>
#include <string>
#include <fstream>
#include <sstream>
#include "matrix.h"
using namespace std;

const double EPS = 1e-9;

void move_up_max_element(matrix &_matrix, int line, int column) {
    auto &_matrix1 = _matrix.get_matrix();
    double max_element = std::abs(_matrix1[line][column]);
    int max_line = line;
    for (int p = line; p < _matrix.get_lines_cnt(); p++) {
        if (std::abs(_matrix1[p][column]) > max_element) {
            max_element = std::abs(_matrix1[p][column]);
            max_line = p;
        }
    }
    _matrix.change_lines(line, max_line);
}

vector<double>  Gaus_method(matrix &_matrix, vector<double> &result) {
    int n = _matrix.get_lines_cnt();
    int m = _matrix.get_columns_cnt() + 1;
    vector<vector<double>> extended_matrix(n, vector<double> (m, 0));

    matrix _extended_matrix(extended_matrix);
    ///Расширенная матрица
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (j == m - 1) {
                _extended_matrix.get_matrix()[i][j] = result[i];
            } else {
                _extended_matrix.get_matrix()[i][j] = _matrix.get_matrix()[i][j];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        int j;
        for (j = 0; j < m; j++) {
            if(abs(_extended_matrix.get_matrix()[i][j]) < EPS) {
                continue;
            }
            move_up_max_element(_extended_matrix, i, j);
            break;
        }
        for(int k = i + 1; k < n; k++) {

            double koef = _extended_matrix.get_matrix()[k][j] / _extended_matrix.get_matrix()[i][j];
            for(int p = j; p < m; p++) {
                _extended_matrix.get_matrix()[k][p] -= koef * _extended_matrix.get_matrix()[i][p];
            }
        }
    }

    std::vector<double> X(n, 0);

    for (int i = n-1; i >= 0; i--) {
        X[i] = _extended_matrix.get_matrix()[i][m-1] / _extended_matrix.get_matrix()[i][i];
        for (int j = i + 1; j < n; j++) {
            X[i] -= _extended_matrix.get_matrix()[i][j] * X[j] / _extended_matrix.get_matrix()[i][i];
        }
    }

    std::reverse(X.begin(), X.end());
    return X;
}

void input_all(string const & file_name, matrix &input_matrix, std::vector<double> &result) {
    ifstream fin(file_name);
    if (!fin.is_open()) {
        throw std::logic_error("Wrong input file: " + file_name + "\n");
    }

    matrix _matrix;
    _matrix.input_from_file(fin);
    input_matrix = _matrix;


}


#endif //CM_GAUS_H
