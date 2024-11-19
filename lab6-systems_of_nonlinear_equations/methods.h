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

        norm = 0;
        for (int j = 0; j < cnt; j++) {
            norm = max(norm, abs(prev[j] - Xk[j]));
        }

        prev = Xk;
        iteration++;
    } while (q / (1 - q) * norm >= epsilon);

    std::cout << "Final result after " << iteration << " iterations: ";
    //1.2758 2.0596

    std::cout << std::endl;
    return Xk;
}

ld det2(ld a11, ld a12, ld a21, ld a22) {
    return a11 * a22 - a21 * a12;
}

vector<ld> NewtonMethod(int cnt, const vector<function<ld(vector<ld>)>>& phi_f,
                        const vector<vector<function<ld(vector<ld>)>>>& J,
                        const vector<ld>& x_0, ld epsilon) {
    std::cout << "Newton method start" << std::endl;
    vector<ld> Xk = x_0;
    vector<ld> prev = Xk;

    ld _max;

    if (phi_f.size() != 2 || J.size() != 2 || J[0].size() != 2 || x_0.size() != 2) {
        std::cout << "Wrong number arguments" << std::endl;
        return {};
    }

    int iteration = 0;
    do {
        ld detA1k = det2(phi_f[0](prev), J[0][1](prev),
                         phi_f[1](prev), J[1][1](prev));
        ld detA2k = det2(J[0][0](prev), phi_f[0](prev),
                         J[1][0](prev), phi_f[1](prev));

//        std::cout << "[94] A1: " << detA1k << " A2: " << detA2k << std::endl;

        ld detJ = det2(J[0][0](prev), J[0][1](prev),
                       J[1][0](prev), J[1][1](prev));

        Xk[0] = prev[0] - detA1k / detJ;
        Xk[1] = prev[1] - detA2k / detJ;

        _max = 0;
        for (int i = 0; i < 2; i++) {
            _max = max(_max, abs(Xk[i] - prev[i]));
        }

        iteration++;
        prev = Xk;
    } while (_max >= epsilon);


    std::cout << "Final result after " << iteration << " iterations: " << std::endl;

    return Xk;
}



#endif //CM_METHODS_H
