#ifndef CM_METHODS_H
#define CM_METHODS_H
#include <vector>
#include <functional>
#include <cmath>
#include <iostream>

using namespace std;
using ld = long double;
const double EPS = 1e-9;

//d_phi_f = d phi_x1x2 / dx1; d
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
        for (int x : Xk) {
            std::cout << x << " ";
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



#endif //CM_METHODS_H
