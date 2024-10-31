//
// Created by olya- on 17.10.2024.
//

#ifndef CM_SIMPLE_ITERATION_METHOD_H
#define CM_SIMPLE_ITERATION_METHOD_H
#include <string>
#include "matrix.h"
#include <iostream>
#include <sstream>
#include <fstream>

double const EPS = 1e-8;

void input_all(string const & file_name, matrix &input_matrix, std::vector<double> &result) {
    ifstream fin(file_name);
    if (!fin.is_open()) {
        throw std::logic_error("Wrong input file: " + file_name + "\n");
    }

    matrix _matrix;
    _matrix.input_from_file(fin);
    input_matrix = _matrix;

    std::string line;

    if (!getline(fin, line)) {
        std::cout << "wrong input! " << std::endl;
        throw std::logic_error("Wrong input format");
    }

    istringstream line_str(line);
    vector<double> line_vector;
    double a;
    while (line_str >> a) line_vector.push_back(a);
    result = line_vector;
    std::cout << std::endl;
}

void conversion_to_an_equivalent_form(matrix &_matrix, vector<double> &b, matrix &alpha, matrix &beta_v) {
    int n = _matrix.get_lines_cnt();
    vector<vector<double>> _alpha(n, vector<double>(n, 0));
    matrix alpha_tmp(_alpha);
    vector<double> beta_tmp(n, 0);

    double norm = 0;

    for (int i = 0; i < n; i++) {
        double sum = 0;
        double koef = _matrix[i][i];

        for (int j = 0; j < n; j++) {
            if (j == i) {
                alpha_tmp[i][j] = 0;
            } else {
                alpha_tmp[i][j] = - _matrix[i][j] / koef;
                sum += abs(alpha_tmp[i][j]);
            }
        }

        beta_tmp[i] = b[i] / koef;

        if (sum > norm) {
            norm = sum;
        }
    }

    std::cout << alpha_tmp << std::endl;

    std::cout << "Norm: "<< norm << std::endl;

    if (norm > 1.0 + EPS) {
        throw runtime_error("the convergence condition is violated"); //нарушается условие сходимости
    }

    vector<vector<double>> _beta_v(beta_tmp.size(), vector<double> (1, 0));
    for (int i = 0; i < beta_tmp.size(); i++) { //транспонируем
        _beta_v[i][0] = beta_tmp[i];
    }

    alpha = alpha_tmp;
    matrix beta_v_tmp(_beta_v);
    beta_v = beta_v_tmp;
}

vector<double> simple_iteration_method(matrix &_matrix, vector<double> &b) {
    std::cout << "Simple_iteration_method" << std::endl;
    int n = _matrix.get_lines_cnt();

    matrix alpha;
    matrix _beta;
    conversion_to_an_equivalent_form(_matrix, b, alpha, _beta);

    matrix x(_beta);
    std::vector<double> tmp;

    double error;
    do {
        matrix x_new = alpha * x + _beta;
        error = 0.0;
        for (int i = 0; i < n; i++) {
            error += abs(x_new[i][0] - x[i][0]);
        }
        x = x_new;
    } while (error > EPS);


    std::vector<double> x_v;
    for (int i = 0; i < x.get_lines_cnt(); i++) {
        x_v.push_back(x[i][0]);
    }
    return x_v;
}

vector<double> Zeidal_method(matrix &_matrix, vector<double> &b) {
    std::cout << "\n\nThe_Zeidal_method" << std::endl;
    int n = _matrix.get_lines_cnt();

    matrix alpha;
    matrix _beta;
    conversion_to_an_equivalent_form(_matrix, b, alpha, _beta);

    matrix x(_beta); // начальное приближение x = beta
    double error;
    int max_iterations = 1000; // Ограничение по числу итераций
    int iterations = 0;

    do {
        error = 0.0;

        for (int i = 0; i < n; i++) {
            double sum = _beta[i][0];

            for (int j = 0; j < n; j++) {
                if (j != i) {
                    sum += alpha[i][j] * x[j][0];
                }
            }

            double new_x_i = sum;
            error += abs(new_x_i - x[i][0]);
            x[i][0] = new_x_i;
        }

        iterations++;
    } while (error > EPS && iterations < max_iterations);

    if (iterations == max_iterations) {
        throw std::runtime_error("Exceeded maximum number of iterations, method did not converge");
    }

    std::vector<double> x_v;
    for (int i = 0; i < x.get_lines_cnt(); i++) {
        x_v.push_back(x[i][0]);
    }
    return x_v;
}

#endif //CM_SIMPLE_ITERATION_METHOD_H
