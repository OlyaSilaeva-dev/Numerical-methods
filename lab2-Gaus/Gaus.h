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

void move_up_max_element(matrix &_matrix, int line, int column, int &cnt) {
    auto &_matrix1 = _matrix.get_matrix();
    double max_element = std::abs(_matrix1[line][column]);
    int max_line = line;
    for (int p = line; p < _matrix.get_lines_cnt(); p++) {
        if (std::abs(_matrix1[p][column]) > max_element) {
            max_element = std::abs(_matrix1[p][column]);
            max_line = p;
        }
    }
    if (line != max_line) {
        _matrix.change_lines(line, max_line);
        cnt++;
    }
}

void to_the_upper_triangular(matrix &_matrix, int &cnt) {
    ///Приведение матрицы к верхне треугольному виду
    int n = _matrix.get_lines_cnt();
    int m = _matrix.get_columns_cnt();
    for (int i = 0; i < n; i++) {
        int j;
        for (j = 0; j < m; j++) {
            if(abs(_matrix.get_matrix()[i][j]) < EPS) {
                continue;
            }
            move_up_max_element(_matrix, i, j, cnt);
            break;
        }
        for(int k = i + 1; k < n; k++) {

            double koef = _matrix.get_matrix()[k][j] / _matrix.get_matrix()[i][j];
            for(int p = j; p < m; p++) {
                _matrix.get_matrix()[k][p] -= koef * _matrix.get_matrix()[i][p];
            }
        }
    }
}

void to_the_lower_triangular(matrix &_matrix, int &cnt) {
    ///Приведение матрицы к нижне треугольному виду
    int n = _matrix.get_lines_cnt();
    int m = _matrix.get_columns_cnt();
    for (int i = 0; i < m; i++) {
        int j;
        for (j = 0; j < n; j++) {
            if(abs(_matrix.get_matrix()[j][i]) < EPS) {
                continue;
            }
            break;
        }
        for(int k = j + 1; k < n; k++) {

            double koef = _matrix.get_matrix()[k][i] / _matrix.get_matrix()[j][i];
            for(int p = j; p < m; p++) {
                _matrix.get_matrix()[k][p] -= koef * _matrix.get_matrix()[j][p];
            }
        }
    }
}


vector<double>  Gaus_method(matrix &_matrix, vector<double> &result, double &_det) {
    double det = 1;
    int cnt = 0;

    if (_matrix.get_lines_cnt() != result.size() || _matrix.get_lines_cnt() != result.size()) {
        throw logic_error("it is imposible to find solution!");
    }
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

    to_the_upper_triangular(_extended_matrix, cnt);
    ///Вычисление результата - обратный ход
    std::vector<double> X(n, 0);

    for (int i = n-1; i >= 0; i--) {
        X[i] = _extended_matrix.get_matrix()[i][m-1] / _extended_matrix.get_matrix()[i][i];
        det *= _extended_matrix.get_matrix()[i][i];
        for (int j = i + 1; j < n; j++) {
            X[i] -= _extended_matrix.get_matrix()[i][j] * X[j] / _extended_matrix.get_matrix()[i][i];
        }
    }

    _det = det * (cnt % 2 == 0 ? 1 : -1);
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

    std::string line;
    getline(fin, line);
    istringstream line_str(line);
    vector<double> line_vector;
    double a;
    while (line_str >> a) line_vector.push_back(a);
    result = line_vector;
    std::cout << std::endl;
}

matrix reverse_matrix(matrix& _matrix) {
    int n = _matrix.get_lines_cnt();
    if (_matrix.get_columns_cnt() != n) {
        throw std::invalid_argument("The matrix must be square.");
    }

    // Создаем расширенную матрицу [A | E]
    std::vector<std::vector<double>> augmented(n, std::vector<double>(2 * n, 0.0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 2 * n; ++j) {
            if (j < n) {
                augmented[i][j] = _matrix.get_matrix()[i][j];
            } else {
                augmented[i][j] = (i == (j - n)) ? 1.0 : 0.0;
            }
        }
    }

    // Приведение расширенной матрицы к приведенному виду
    for (int i = 0; i < n; ++i) {
        // Поиск максимального элемента в столбце для выбора опорного элемента
        double maxEl = abs(augmented[i][i]);
        int maxRow = i;
        for (int k = i + 1; k < n; ++k) {
            if (abs(augmented[k][i]) > maxEl) {
                maxEl = abs(augmented[k][i]);
                maxRow = k;
            }
        }

        // Проверка на вырожденность матрицы
        if (maxEl < EPS) {
            throw std::runtime_error("The matrix is degenerate and has no inverse matrix.");
        }
        // Перестановка строк
        std::swap(augmented[i], augmented[maxRow]);

        // Приведение опорного элемента к 1
        double pivot = augmented[i][i];
        for (int j = 0; j < 2 * n; ++j) {
            augmented[i][j] /= pivot;
        }

        // Обнуление остальных элементов в текущем столбце
        for (int k = 0; k < n; ++k) {
            if (k != i) {
                double factor = augmented[k][i];
                for (int j = 0; j < 2 * n; ++j) {
                    augmented[k][j] -= factor * augmented[i][j];
                }
            }
        }
    }

    // Извлечение обратной матрицы из расширенной матрицы
    std::vector<std::vector<double>> inverse(n, std::vector<double>(n, 0.0));
    for (int i = 0; i < n; ++i) {
        for (int j = n; j < 2 * n; ++j) {
            inverse[i][j - n] = augmented[i][j];
        }
    }
    matrix result(inverse);
    std::cout << result;
    return result;
}

bool CheckCorrectAnswer(matrix &matrix, vector<double> b, vector<double> result) {
    int n = matrix.get_lines_cnt();
    for(int i = 0; i < n; i++) {
        double b_i = 0;
        for(int j = 0; j < n; j++) {
            b_i += result[j] * matrix.get_matrix()[i][j];
        }
        if (abs(b_i - b[i]) > EPS) {
            return false;
        }
    }
    return true;
}

bool CheckReverseMatrix(matrix &A, matrix &A_reverse) {
    int n = A.get_lines_cnt();
    vector<vector<double>> vE(n, vector<double> (n, 0));
    for (int i = 0; i < n; i++) {
        vE[i][i] = 1;
    }
    matrix E(vE);

    std::cout << A * A_reverse << std::endl;

    return A * A_reverse == E;
}
#endif //CM_GAUS_H
