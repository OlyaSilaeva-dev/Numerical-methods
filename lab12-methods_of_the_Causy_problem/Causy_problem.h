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

values calculation_next_value(double x_0, double y_0, double z_0, double h,
                              const function<double(double, double, double)>& f,
                              const function<double(double, double, double)>& g,
                              parameter _parameter) {
    int n = 4;
    vector<double> K(n);
    vector<double> L(n);

    double delta_y_0 = 0.0;
    double delta_z_0 = 0.0;

    switch (_parameter) {
        case EULER:
            delta_y_0 = h * f(x_0, y_0, z_0);
            delta_z_0 = h * g(x_0, y_0, z_0);
            break;

        case RUNGE_KUTTA:
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
            break;

        case ADAMS:
            double delta_y_1 = h * f(x_0, y_0, z_0);
            double delta_z_1 = h * g(x_0, y_0, z_0);

            double delta_y_2 = h * f(x_0 + h, y_0 + delta_y_1, z_0 + delta_z_1);
            double delta_z_2 = h * g(x_0 + h, y_0 + delta_y_1, z_0 + delta_z_1);

            delta_y_0 = delta_y_2;
            delta_z_0 = delta_z_2;
            break;
    }

    double y_1 = y_0 + delta_y_0;
    double z_1 = z_0 + delta_z_0;
    double x_1 = x_0 + h;

    values val(x_1, y_1, z_1);
    return val;
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
        values _values = calculation_next_value(v_tmp.get('x'), v_tmp.get('y'), v_tmp.get('z'), h, f, g, _parameter);
        x_cur = _values.get('x');
        values_table.push_back(_values);
    } while (x_cur < b);

    print_results(values_table, exact_solution);
    return 0.0;
}

#endif //CM_CAUSY_PROBLEM_H
