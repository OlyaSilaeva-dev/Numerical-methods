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
        double fi;
        if (abs(delta) < EPS) {
//            throw runtime_error("division by zero!!!");
            fi = M_PI / 4;
        }
        fi = 0.5 * atan2(2 * max_element, delta);

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

double power_law_method(matrix& _matrix, const vector<double>& y_0) {
    const double epsilon = 0.1;
    int n = _matrix.get_lines_cnt();
    vector<double> lambda;
    vector<matrix> y;
    vector<vector<double>> y_v(n, vector<double>(1, 0));
    for (int i = 0; i < n; i++) {
        y_v[i][0] = y_0[i];
    }
    y.emplace_back(y_v);
    lambda.push_back(0);
    int k = 1;
    do {
        matrix y_k = _matrix * y[k - 1];
        y.push_back(y_k);

        double lambda_k = (y[k][0][0]) / (y[k-1][0][0]);
        lambda.push_back(lambda_k);
        k++;
    } while (abs(lambda[k - 1] - lambda[k - 2]) > epsilon);

    return lambda[k - 1];
}

#endif //CM_ROTATION_METHOD_H
