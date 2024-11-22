#ifndef CM_MNK_H
#define CM_MNK_H
#include <iostream>
#include <vector>
#include <functional>
#include <cmath>
#include "matrix.h"
#include "../lab2-Gaus/Gaus.h"
using namespace std;

double sum_vector_indegree (int n, const vector<double>& v, int degree) {
    double sum = 0;
    for (int j = 0; j < n; j++) {
        sum += pow(v[j], degree);
    }
    return sum;
}

vector<double> polinomial_second_degree(const vector<double>& x, const vector<double>& f, int degree) {
    int n = (int)x.size();
    vector<vector<double>> coef_a(degree, vector<double> (degree, 0));

    for (int i = 0; i < degree; i++) {
        for (int j = 0; j < degree; j++) {
            if ((i == 0) && (j == 0)) {
                coef_a[i][j] = n;
            } else {
                coef_a[i][j] = sum_vector_indegree(n, x, i + j);
            }
        }
    }

    vector<double> b(degree, 0);
    for (int i = 0; i < degree; i++) {
        double sum = 0.0;
        for (int j = 0; j < n; j++) {
            sum += f[j] * pow(x[j], i);
        }
        b[i] = sum;
    }

    double det;
    matrix system = matrix(coef_a);
    vector<double> a = Gaus_method(system, b, det);

    return a;
}

double calculate_Fi(const vector<double>& a, const vector<double>& f, const vector<double>& x) {
    int n = (int)f.size();
    double degree = (int)a.size();
    vector<double> F(n, 0);
    for(int i = 0; i < n; i++) {
        F[i] = 0;
        for (int j = 0; j < degree; j++) {
            F[i] += a[j] * pow(x[i], j);
        }
    }

    double Fi = 0.0;
    for (int i = 0; i < n; i++) {
        Fi += (F[i] - f[i]) * (F[i] - f[i]);
    }
    return Fi;
}

#endif //CM_MNK_H
