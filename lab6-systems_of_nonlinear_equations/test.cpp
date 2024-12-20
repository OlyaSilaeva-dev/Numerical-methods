#include "methods.h"

ld phi_f_1 (vector<ld> x) {
    return sqrt(2 * log10(x[1]) + 1);
}

ld phi_f_2 (vector<ld> x) {
    return (x[0] * x[0] + 1) / x[0];
}

ld d_phi_f_1_x2 (vector<ld> x) {
    return 1 / (x[1] * sqrt(2 * log(x[1]) / log(10) + 1) * log(10));
}

ld d_phi_f_2_x1 (vector<ld> x) {
    return  (x[0] * x[0] - 1) / (x[0] * x[0]);
}

//для метода Ньютона
ld f1 (vector<ld> x) {
    return x[0] * x[0] - 2 * log10(x[1]) - 1;
}

ld f2 (vector<ld> x) {
    return x[0] * x[0] - x[0] * x[1] + 1;
}

ld d_f1_x1 (vector<ld> x) {
    return 2 * x[0];
}

ld d_f1_x2 (vector<ld> x) {
    return -2 / (x[1] * log(10));
}

ld d_f2_x1 (vector<ld> x) {
    return 2 * x[0] - x[1];
}

ld d_f2_x2 (vector<ld> x) {
    return -x[0];
}

ld null_func(vector<ld> x) {
    return 0.0;
}

int main () {
    vector<int> k = {1, 2};
    vector<function<ld(vector<ld>)>> phi_f = {phi_f_1, phi_f_2};

    vector<vector<function<ld(vector<ld>)>>> d_phi_f;
    vector<function<ld(vector<ld>)>> d_phi_f_1 = {null_func, d_phi_f_1_x2};
    vector<function<ld(vector<ld>)>> d_phi_f_2 = {d_phi_f_2_x1, null_func};
    d_phi_f.push_back(d_phi_f_1);
    d_phi_f.push_back(d_phi_f_2);

    vector<ld> x_0 = {1.25, 2.0};

    vector<ld> result = simple_iteration_method(2, phi_f, d_phi_f, x_0, 1e-9);
    for (auto i : result) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    vector<function<ld(vector<ld>)>> f = {f1, f2};
    vector<vector<function<ld(vector<ld>)>>> J = {
            {d_f1_x1, d_f1_x2},
            {d_f2_x1, d_f2_x2}
    };

    vector<ld> result1 = NewtonMethod(2, f, J, x_0, 1e-9);
    for (auto i : result1) {
        std::cout << i << " ";
    }

}