#ifndef CM_INTEGRATION_H
#define CM_INTEGRATION_H
#include <iostream>
#include <functional>
#include <cmath>
#include <vector>
using namespace std;

double rectangle_integration_method(const function<double(double)>& f,const double x_0,
                                    const double x_k, const double h) {
    double result = 0;
    double x_prev = x_0;
    double x = x_0 + h;

    if (x_k >= x_0) {
        while (x <= x_k) {
            result += f((x_prev + x) / 2.0);
            x_prev = x;
            x += h;
        }
    } else {
        while (x >= x_k) {
            result += f((x_prev + x) / 2.0);
            x_prev = x;
            x -= h;
        }
    }

    result *= h;
    return result;
}

double trapezoid_integration_method(const function<double(double)>& f,const double x_0,
                                    const double x_k, const double h) {
    double result = 0;
    result += f(x_0) / 2;
    double x = x_0 + h;

    if (x_k >= x_0) {
        while (x <= x_k - h) {
            result += f(x);
            x += h;
        }
    } else {
        while (x >= x_k + h) {
            result += f(x);
            x -= h;
        }
    }

    result += f(x_k) / 2;
    result *= h;
    return result;
}

double Simpson_integration_method(const function<double(double)>& f,const double x_0,
                                  const double x_k, const double h) {
    double result = 0;
    result += f(x_0);
    double x = x_0 + h;
    int iter = 0;

    if (x_k >= x_0) {
        while (x <= x_k - h) {
            double coef = (iter % 2 == 0) ? 4: 2;
            result += coef * f(x);
            x += h;
            iter++;
        }
    } else {
        while (x >= x_k + h) {
            double coef = (iter % 2 == 0) ? 4: 2;
            result += coef * f(x);
            x -= h;
            iter++;
        }
    }

    result += f(x_k);
    result *= h / 3;
    return result;
}

double calculate_M(const function<double(double)>& ddf, const double x_0, const double x_k, const double h) {
    double M = 0;
    double x = x_0;
    while (x <= x_k) {
        M = max(M, abs(ddf(x)));
        x += h;
    }
    return M;
}

enum Parametr {
    RECTANGLE,
    TRAPEZOID,
    SIMPSON
};

double runge_romberg_estimation(const function<double(double)>& f,const double x_0,
                                const double x_k, const double h1, const double h2, Parametr parametr) {
    double I_h;
    double I_h2;
    int p;

    switch (parametr) {
        case RECTANGLE:
            I_h = rectangle_integration_method(f, x_0, x_k, h1);
            I_h2 = rectangle_integration_method(f, x_0, x_k, h2);
            p = 1;
            break;
        case TRAPEZOID:
            I_h = trapezoid_integration_method(f, x_0, x_k, h1);
            I_h2 = trapezoid_integration_method(f, x_0, x_k, h2);
            p = 2;
            break;
        case SIMPSON:
            I_h = Simpson_integration_method(f, x_0, x_k, h1);
            I_h2 = Simpson_integration_method(f, x_0, x_k, h2);
            p = 4;
            break;
        default:
            return 0;
    }

    // h1 * k = h2 => k = h2 / h1
    double error_estimation = I_h2 + fabs((I_h2 - I_h) / (pow(h1 / h2, p) - 1.0));
    return error_estimation;
}


#endif //CM_INTEGRATION_H
