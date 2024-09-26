#ifndef CM_GAUS_H
#define CM_GAUS_H

#include <iostream>
#include <vector>
#include <filesystem>
#include <string>
#include <fstream>
#include <sstream>
#include "../lab1-Progonka/Progonka.h"
using namespace std;

void ChangeColums() {

}

vector<vector<double>> multiply_matrices(vector<vector<double>> &matrix1, vector<vector<double>> &matrix2) {

    int n1 = matrix1.size();
    int m1 = matrix1[0].size();
    int n2 = matrix2.size();
    int m2 = matrix2[0].size();

    if(m1 != n2) {
        throw logic_error("Matrices are incompatible!!!"); //матрицы несовместны
    }
    vector<vector<double>> result(n1, vector<double> (m2, 0));

    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < m2; j++) {
            result[i][j] = 0;
            for (int p = 0; p < m1; p++) {
                result[i][j] += matrix1[i][p] * matrix2[p][j];
            }
        }
    }

    return result;
}

void MoveUpMaxElement(vector<vector<double>> &matrix, int first_num_i, int first_num_j) {
    int n = matrix.size();
    double max_element = -UINT32_MAX;
    double max_element_id = -UINT32_MAX;
    for (int i = first_num_i; i < n; i++) {
        if (max_element < matrix[i][first_num_j] && matrix[i][first_num_j] != 0) {
            max_element = matrix[i][first_num_j];
            max_element_id = i;
        }
    }

    vector<vector<double>> p(n, vector<double>(n, 0));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if (i == max_element_id) {
                p[i][j] = (j == first_num_j) ? 1: 0;
            } else if (i == first_num_j) {
                p[i][j] = (j == max_element_id) ? 1: 0;
            } else {
                p[i][j] = (j == i) ? 1: 0;
            }
        }
    }

    auto result = multiply_matrices(p, matrix);
    matrix = result;
}

vector<double> Gaus_method(vector<vector<double>> &matrix, vector<double> &result) {

    int n = matrix.size();
    vector<vector<double>> extended_matrix(n, vector<double> (n + 1, 0));

    ///Расширенная матрица
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n + 1; j++) {
            if (j == n) {
                extended_matrix[i][j] = result[i];
            } else {
                extended_matrix[i][j] = matrix[i][j];
            }
        }
    }

    ///Перемещаем строку с максимальным элементом наверх
    MoveUpMaxElement(extended_matrix, 0, 0);

    for (int p = 0; p < n - 1; p++) {
        for (int i = p + 1; i < n; i++) {

            print_matrix(extended_matrix);
            std::cout << "[88]" << p << " " << i << endl;
            double elem = extended_matrix[i][p] / extended_matrix[p][p];
            for (int j = 0; j < n + 1; j++) {
                extended_matrix[i][j] -= extended_matrix[p][j] * elem;
            }
        }

        MoveUpMaxElement(extended_matrix, p+1, p+1);
    }
    matrix = extended_matrix;
}

void input_all(string const & file_name, vector<vector<double>> &input_matrix) {
    ifstream fin(file_name);
    if (!fin.is_open()) {
        throw std::logic_error("Wrong input file: " + file_name + "\n");
    }

    vector<vector<double>> matrix;

    string line;
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
        matrix.push_back(line_vector);
    }

//    print_matrix(matrix);

//    vector<double> result;
//    if(!getline(fin, line))
//        throw logic_error("Wrong input!!!");
//    istringstream line_str(line);
//
//    double a;
//    while (line_str >> a) result.push_back(a);

    input_matrix = matrix;
//    input_result = result;
}


#endif //CM_GAUS_H
