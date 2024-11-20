#ifndef CM_INTERPOLATIONS_H
#define CM_INTERPOLATIONS_H

#include <functional>
using namespace std;

const double EPS = 1e-9;

int factorial(int n) {
    int f = 1;
    for (int i = 1; i < n; i++) {
        f += i;
    }
    return f;
}

double the_Lagrange_polynomial(const function<double(double)>& f,const vector<double>& x, double x_star) {
    int n = (int)x.size();
    vector<double> F(n);
    vector<double> w_dx(n);
    double M = -1e9;

    double L = 0;

    for (int i = 0; i < n; i++) {
        F[i] = f(x[i]);
        w_dx[i] = 1;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                w_dx[i] *= x[i] - x[j];
            }
        }

        if (abs(w_dx[i]) < EPS) {
            throw runtime_error("division by zero!");
        }

        double koef = F[i] / w_dx[i];
//        double delta_x = x_star - x[i];

        double result_i = 1;
        for (int j = 0; (j < n) && (j != i); j++) {
            result_i *= (x_star - x[j]);
        }
        result_i *= koef;
        L += result_i;

        M = max(M, f(x[i]));
    }

    double f_x = f(x_star);
    double delta = abs(L - f_x);



}

#endif //CM_INTERPOLATIONS_H
