#ifndef CM_SPLINE_H
#define CM_SPLINE_H

#include <cmath>
#include <iostream>
#include <vector>
#include "../lab1-Progonka/Progonka.h"
using namespace std;

void print_table(vector<double> x, vector<double> a, vector<double> b, vector<double> c, vector<double> d, vector<double> result) {
    cout << "+-----------+-----------+-----------+-----------+-----------+-----------+" << endl;
    cout << "|     x     |     a     |     b     |     c     |     d     |   result  |" << endl;
    cout << "+-----------+-----------+-----------+-----------+-----------+-----------+" << endl;

    for (int i = 0; i < a.size(); i++) {
        cout << "| " << setw(9) << fixed << setprecision(6) << x[i] << " "
             << "| " << setw(9) << fixed << setprecision(6) << a[i] << " "
             << "| " << setw(9) << fixed << setprecision(6) << b[i] << " "
             << "| " << setw(9) << fixed << setprecision(6) << c[i] << " "
             << "| " << setw(9) << fixed << setprecision(6) << d[i] << " "
             << "| " << setw(9) << fixed << setprecision(6) << d[i] << " |" << endl;

    }
    cout << "+-----------+-----------+-----------+-----------+-----------+-----------+" << endl;
}
vector<double> calculate_c(const vector<double>& x,const vector<double>& f,const vector<double>& h) {
    int n = (int)x.size();

    vector<vector<double>> system_c(n - 2, vector<double> (n - 2, 0));
    vector<double> b(n - 2);

    for (int i = 0; i < n - 2; i++) {
        if (i == 0) {
            system_c[i][i] = 2 * (h[0] + h[1]);
            system_c[i][i + 1] = h[1];
        } else if (i == n - 3) {
            system_c[i][i - 1] = h[i];
            system_c[i][i] = 2 * (h[i] + h[i + 1]);
        } else {
            system_c[i][i - 1] = h[i];
            system_c[i][i] = 2 * (h[i] + h[i + 1]);
            system_c[i][i + 1] = h[i + 1];
        }
        b[i] = 3.0 * ((f[i + 2] - f[i + 1]) / h[i + 1] - (f[i + 1] - f[i]) / h[i]);
    }

    vector<double> c_end = Method_Progonki(system_c, b);

    vector<double> c;
    c.push_back(0.0);
    for (double elem : c_end) {
        c.push_back(elem);
    }

    return c;
}

vector<double> calculate_b(int n, const vector<double>& c, const vector<double>& f, const vector<double>& h) {

    vector<double> b(n - 1);
    for (int i = 0; i < n - 2; i++) {
        b[i] = (f[i + 1] - f[i]) / h[i] - (1.0 / 3) * h[i] * (c[i + 1] + 2 * c[i]);
    }
    b[n - 2] = (f[n - 1] - f[n - 2]) / h[n - 2] - (2.0 / 3) * h[n - 2] * c[n - 2];

    return b;
}

void print_vector(const string& s,const vector<double>& v) {
    std::cout << s << " ";
    for (double elem : v) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

vector<double> calculate_d(int n, const vector<double>& c, const vector<double>& h) {

    vector<double> d(n - 1);
    for (int i = 0; i < n - 2; i++) {
        d[i] = (c[i + 1] - c[i]) / (3 * h[i]);
    }
    d[n - 2] = - c[n - 2] / (3 * h[n - 2]);

    return d;
}

double splain(const vector<double>& f,const vector<double>& x, double x_star) {
    int n = (int)x.size();

    vector<double> h(n - 1);
    for (int i = 0; i < n - 1; i++) {
        h[i] = x[i + 1] - x[i];
    }

    vector<double> c = calculate_c(x, f, h);
    vector<double> a;
    for (int i = 0; i < n - 1; i++) {
        a.push_back(f[i]);
    }
    vector<double> b = calculate_b(n, c, f, h);
    vector<double> d = calculate_d(n, c, h);

    int index = 0;
    while (x[index] < x_star) {
        index++;
    }
    index--;

    vector<double> result(n);
    for (int i = 0; i < n; i++) {
        double delta = (x_star - x[i]);
        result[i] = a[i] + b[i] * delta + c[i] * pow(delta, 2) + d[i] * pow(delta, 3);
    }
    print_table(x, a, b, c, d, result);

    return result.back();
}


#endif //CM_SPLINE_H
