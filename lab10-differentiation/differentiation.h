#ifndef CM_DIFFERENTIATION_H
#define CM_DIFFERENTIATION_H
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

enum method {
    LEFT,
    RIGHT,
    AVERANGE
};

long double differentiation_first_degree (const vector<long double>& x, const vector<long double>& y, const long double x_star, method _method) {
    int n = (int)y.size();
    long double result = 0;

    for (int i = 1; i < n - 1; i++) {
        if (x_star <= x[i + 1] && x_star >= x[i]) {

            long double left_diff = (y[i] - y[i - 1]) / (x[i] - x[i - 1]);
            long double right_diff = (y[i + 1] - y[i]) / (x[i + 1] - x[i]);
            long double h = x[i + 1] - x[i];

            if (_method == LEFT) {
                result = left_diff;
            } else if (_method == RIGHT) {
                result = right_diff;
            } else {
//                result = (y[i] - y[i - 1]) / h +
//                        (y[i + 1] - 2 * y[i] - y[i - 1]) / (2 * h * h) * (2 * x_star - x[i] - x[i - 1]);
                result = left_diff + (right_diff - left_diff) / (x[i + 1] - x[i - 1]) * (2 * x_star - x[i] - x[i - 1]);
            }
        }
    }

    return result;
}

long double differentiation_second_degree (const vector<long double>& x, const vector<long double>& y, const long double x_star) {
    int n = (int)x.size();
    long double result = 0;

    for (int i = 1; i < n - 1; i++) {
        if (x_star >= x[i] && x_star <= x[i + 1]) {
            long double left_diff = (y[i] - y[i - 1]) / (x[i] - x[i - 1]);
            long double right_diff = (y[i + 1] - y[i]) / (x[i + 1] - x[i]);

            result = 2 * (right_diff - left_diff) / (x[i + 1] - x[i - 1]);
        }
    }
    return result;
}

#endif //CM_DIFFERENTIATION_H
