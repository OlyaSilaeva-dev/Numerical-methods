#ifndef CM_CAUSY_PROBLEM_H
#define CM_CAUSY_PROBLEM_H
#include <iostream>
#include <cmath>
#include <vector>
#include <functional>
#include <iomanip>
using namespace std;

enum parameter {
    EULER,
    RUNGE_KUTTA,
    ADAMS
};

class values {

private:
    double y;
    double z;
    double x;

public:

    values(double _x, double _y, double _z) {
        this->x = _x;
        this->y = _y;
        this->z = _z;
    }

    [[nodiscard]] double get(char p) const {
        switch (p) {
            case 'x':
                return this->x;
            case 'y':
                return this->y;
            case 'z':
                return this->z;
            default:
                throw logic_error("Wrong value!");
        }
    }

};


void runge_kutta(double x_0, double y_0, double z_0, double h,
                 const function<double(double, double, double)>& f,
                 const function<double(double, double, double)>& g,
                 double& delta_y_0, double& delta_z_0) {
    vector<double> K(4);
    vector<double> L(4);

    K[0] = h * f(x_0, y_0, z_0);
    L[0] = h * g(x_0, y_0, z_0);

    K[1] = h * f(x_0 + (0.5 * h), y_0 + (0.5 * K[0]), z_0 + (0.5 * L[0]));
    L[1] = h * g(x_0 + (0.5 * h), y_0 + (0.5 * K[0]), z_0 + (0.5 * L[0]));

    K[2] = h * f(x_0 + (0.5 * h), y_0 + (0.5 * K[1]), z_0 + (0.5 * L[1]));
    L[2] = h * g(x_0 + (0.5 * h), y_0 + (0.5 * K[1]), z_0 + (0.5 * L[1]));

    K[3] = h * f(x_0 + h, y_0 + K[2], z_0 + L[2]);
    L[3] = h * g(x_0 + h, y_0 + K[2], z_0 + L[2]);

    delta_y_0 = (1.0 / 6.0) * (K[0] + 2.0 * K[1] + 2.0 * K[2] + K[3]);
    delta_z_0 = (1.0 / 6.0) * (L[0] + 2.0 * L[1] + 2.0 * L[2] + L[3]);
}

void adams_bashforth(const vector<values>& prev_values, double h,
                     const function<double(double, double, double)>& f,
                     const function<double(double, double, double)>& g,
                     double& delta_y_0, double& delta_z_0) {
    if (prev_values.size() < 4) {
        throw logic_error("Not enough previous values for Adams-Bashforth method.");
    }

    const double coeffs[4] = { 55.0 / 24.0, -59.0 / 24.0, 37.0 / 24.0, -9.0 / 24.0 };

    double fy[4], fz[4];
    for (int i = 0; i < 4; ++i) {
        const auto& v = prev_values[prev_values.size() - 1 - i];
        fy[i] = f(v.get('x'), v.get('y'), v.get('z'));
        fz[i] = g(v.get('x'), v.get('y'), v.get('z'));
    }

    delta_y_0 = h * (coeffs[0] * fy[0] + coeffs[1] * fy[1] + coeffs[2] * fy[2] + coeffs[3] * fy[3]);
    delta_z_0 = h * (coeffs[0] * fz[0] + coeffs[1] * fz[1] + coeffs[2] * fz[2] + coeffs[3] * fz[3]);
}

// Основная функция вычисления следующего значения
values calculation_next_value(double x_0, double y_0, double z_0, double h,
                              const function<double(double, double, double)>& f,
                              const function<double(double, double, double)>& g,
                              parameter _parameter,
                              const vector<values>& prev_values) {
    double delta_y_0 = 0.0;
    double delta_z_0 = 0.0;
    double y_05, x_05;
    switch (_parameter) {
        case EULER:
            y_05 = y_0 + h / 2 * f(x_0, y_0, z_0);
            x_05 = x_0 + h / 2;
            delta_y_0 = h * f(x_05, y_05, z_0);
            delta_z_0 = h * g(x_05, y_05, z_0);
            break;

        case RUNGE_KUTTA:
            runge_kutta(x_0, y_0, z_0, h, f, g, delta_y_0, delta_z_0);
            break;

        case ADAMS:
            if (prev_values.size() < 4) {
                runge_kutta(x_0, y_0, z_0, h, f, g, delta_y_0, delta_z_0);
            } else {
                adams_bashforth(prev_values, h, f, g, delta_y_0, delta_z_0);
            }
            break;
    }

    double y_1 = y_0 + delta_y_0;
    double z_1 = z_0 + delta_z_0;
    double x_1 = x_0 + h;

    return values(x_1, y_1, z_1);
}
void print_results(const vector<values>& values_table, const function<double(double)>& exact_solution) {
    cout << "+-----------+-----------+-----------+-------------------+--------------+" << endl;
    cout << "|     x     |     y     |     z     |  exact_solution   |    delta     |"  << endl;
    cout << "+-----------+-----------+-----------+-------------------+--------------+" << endl;

    for (const auto& v : values_table) {
        cout << "| " << setw(9) << fixed << setprecision(6) << v.get('x') << " "
             << "| " << setw(9) << fixed << setprecision(6) << v.get('y') << " "
             << "| " << setw(9) << fixed << setprecision(6) << v.get('z') << " "
             << "| " << setw(17) << fixed << setprecision(10) << exact_solution(v.get('x')) << " "
             << "| " << setw(9) << fabs(v.get('y') - exact_solution(v.get('x'))) << " |" << endl;
    }

    cout << "+-----------+-----------+-----------+-------------------+--------------+" << endl;
}

double decision(double y_0, double z_0, double a, double b, double h, const function<double(double, double, double)>& f,
                const function<double(double, double, double)>& g, const function<double(double)>& exact_solution, parameter _parameter) {

    vector<values> values_table;
    values v(a, y_0, z_0);
    values_table.push_back(v);

    double x_cur;
    do {
        values v_tmp = values_table.back();
        values _values = calculation_next_value(v_tmp.get('x'), v_tmp.get('y'), v_tmp.get('z'), h, f, g, _parameter, values_table);
        x_cur = _values.get('x');
        values_table.push_back(_values);
    } while (x_cur < b);

    print_results(values_table, exact_solution);
    return 0.0;
}

#endif //CM_CAUSY_PROBLEM_H
