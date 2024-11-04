#ifndef CM_ROTATION_METHOD_H
#define CM_ROTATION_METHOD_H

#include "matrix.h"
#include <iostream>
#include <fstream>
#include <cmath>

const double EPS = 1e-9;

matrix transpose (matrix &other) {
    int n = other.get_lines_cnt();
    int m = other.get_columns_cnt();
    vector<vector<double>> transposed_matrix(m, vector<double> (n, 0.0));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            transposed_matrix[i][j] = other[j][i];
        }
    }

    matrix result(transposed_matrix);
    return result;
}

void input_matrix(const string &file_name, matrix &input_matrix) {
    ifstream fin(file_name);
    if (!fin.is_open()) {
        throw std::runtime_error("Wrong input file: " + file_name + "\n");
    }

    matrix _matrix;
    _matrix.input_from_file(fin);
    input_matrix = _matrix;
}

double sum_non_diagonal_elements (matrix &_matrix) {
    int n = _matrix.get_lines_cnt();
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                sum += abs(_matrix[i][j]);
            }
        }
    }
    return sum;
}

void Rotation_method(const matrix &_matrix, vector<double> &eigenvalues, matrix &eigenvectors) {
    matrix A = _matrix;
    matrix A_next;

    if (A.get_lines_cnt() != A.get_columns_cnt()) {
        throw runtime_error("The matrix is not a square!");
    }

    vector<matrix> U;
    int n = A.get_lines_cnt();

    do {
        double max_element = 0.0;
        int max_i, max_j;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j && abs(A[i][j]) > max_element) {
                    max_element = A[i][j];
                    max_i = i;
                    max_j = j;
                }
            }
        }

        double delta = A[max_i][max_i] - A[max_j][max_j];
        if (abs(delta) < EPS) {
            throw runtime_error("division by zero!!!");
        }
        auto fi = 0.5 * atan2(2 * max_element, delta);

        vector<vector<double>> u_vec(n, vector<double>(n, 0.0));
        matrix Uk(u_vec);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if ((i == max_i && j == max_i) || (i == max_j && j == max_j)) {
                    Uk[i][j] = cos(fi);
                } else if (i == max_i && j == max_j) {
                    Uk[i][j] = -sin(fi);
                } else if (i == max_j && j == max_i) {
                    Uk[i][j] = sin(fi);
                } else if (i == j) {
                    Uk[i][j] = 1.0;
                } else {
                    Uk[i][j] = 0.0;
                }
            }
        }

        U.push_back(Uk);

        matrix TU = transpose(Uk);

        A_next = TU * A * Uk;
        if (A_next == A) {
            break;
        }

        A = A_next;
    } while (abs(sum_non_diagonal_elements(A)) > EPS);

    vector<double> lambda(n); //собственные значения
    for (int i = 0; i < n; i++) {
        lambda[i] = A[i][i];
    }

    eigenvalues = lambda;

    matrix compos = U[0];
    for (int i = 1; i < U.size(); i++) {
        compos = compos * U[i];
    }
    eigenvectors = transpose(compos);
}

#endif //CM_ROTATION_METHOD_H
