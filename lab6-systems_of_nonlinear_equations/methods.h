#ifndef CM_METHODS_H
#define CM_METHODS_H
#include <vector>
#include <functional>
#include <cmath>
#include <iostream>
#include "../lab2-Gaus/Gaus.h"

using namespace std;
using ld = long double;

vector<ld> simple_iteration_method(int cnt, const vector<function<ld(vector<ld>)>>& phi_f,
                                   const vector<vector<function<ld(vector<ld>)>>>& d_phi_f,const vector<ld>& x_0, ld epsilon) {
    std::cout << "simple_iteration_method start!" << std::endl;

    vector<ld> Xk = x_0;
    vector<ld> prev = Xk;
    ld q = 0;

    for (int i = 0; i < d_phi_f.size(); i++) {
        ld sum = 0;
        for (int j = 0; j < d_phi_f[0].size(); j++) {
            if (d_phi_f[i][j] != nullptr) {
                sum += abs(d_phi_f[i][j](prev));
            }
        }
        q = max(q, sum);
    }

    std::cout << "q: " << q << std::endl;
    if (q >= 1) {
        std::cerr << "The method will not converge, because q >= 1." << std::endl;
        return Xk;
    }

    ld norm;
    int iteration = 0;
    do {
        for (int j = 0; j < cnt; j++) {
            Xk[j] = phi_f[j](prev);
        }
        std::cout << std::endl;

        norm = 0;
        for (int j = 0; j < cnt; j++) {
            norm = max(norm, abs(prev[j] - Xk[j]));
        }

        prev = Xk;
        iteration++;
    } while (q / (1 - q) * norm >= epsilon);

    std::cout << "Final result after " << iteration << " iterations: ";
    for (ld x : Xk) {
        std::cout << x << " ";
    }
    //1.2758 2.0596

    std::cout << std::endl;
    return Xk;
}

vector<ld> NewtonMethod(int cnt, const vector<function<ld(vector<ld>)>>& phi_f,
                        const vector<vector<function<ld(vector<ld>)>>>& d_phi_f,
                        const vector<ld>& x_0, ld epsilon) {
    std::cout << "Newton method start" << std::endl;
    vector<ld> Xk = x_0;
    vector<ld> prev = x_0;

    // Печать начального приближения
    std::cout << "Initial approximation: ";
    for (ld i : Xk) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    ld _max;
    do {
        vector<double> delta_x;

        // Матрица Якоби
        vector<vector<double>> matrix_phi_v(cnt, vector<double>(cnt, 0));
        for (int i = 0; i < cnt; i++) {
            for (int j = 0; j < cnt; j++) {
                if (d_phi_f[i][j] != nullptr) {
                    try {
                        matrix_phi_v[i][j] = (double)d_phi_f[i][j](Xk);
                    } catch (const std::exception& e) {
                        std::cerr << "Error in Jacobian computation at [" << i << "," << j << "]: " << e.what() << std::endl;
                        throw;
                    }
                } else {
                    matrix_phi_v[i][j] = 0;
                }
            }
        }
        matrix matrix_phi(matrix_phi_v);

        // Печать матрицы Якоби
        std::cout << "Jacobian matrix:\n" << matrix_phi << std::endl;

        // Вектор b
        std::cout << "vector b: ";
        vector<double> b_v(cnt, 0);
        for (int i = 0; i < cnt; i++) {
            b_v[i] = -(double)phi_f[i](Xk);
            std::cout << b_v[i] << " ";
        }
        std::cout << std::endl;

        // Решение системы уравнений
        double not_use;
        delta_x = Gaus_method(matrix_phi, b_v, not_use);

        if (delta_x.empty()) {
            throw std::runtime_error("Gaussian method returned empty result.");
        }

        // Обновление приближения
        for (int i = 0; i < cnt; i++) {
            Xk[i] = Xk[i] - (ld)delta_x[i];
            std::cout << delta_x[i] << " ";
        }

        // Вычисление максимального изменения
        _max = 0;
        for (int i = 0; i < cnt; i++) {
            _max = max(abs(Xk[i] - prev[i]) / max(abs(prev[i]), (ld)1.0), _max);
        }

        // Печать текущего приближения
        std::cout << "Current approximation: ";
        for (ld x : Xk) {
            std::cout << x << " ";
        }
        std::cout << "\nMax difference in this iteration: " << _max << std::endl;

        // Обновляем prev
        prev = Xk;

    } while (_max >= epsilon);

    return Xk;
}



#endif //CM_METHODS_H
