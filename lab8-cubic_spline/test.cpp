#include <iostream>
#include "spline.h"

int main () {

    vector<double> x = {-0.4, -0.1, 0.2, 0.5, 0.8};
    vector<double> f = {-0.81152, -0.20017, 0.40136, 1.0236, 1.7273};
    double X_star = 0.1;

    vector<double> x_test = {0.0, 1.0, 2.0, 3.0, 4.0};
    vector<double> f_test = {0.0, 1.8415, 2.9093, 3.1411, 3.2432};
    double X_star_test = 1.5;

    double result = splain(f, x, X_star);
    std::cout << "result: " << result << std::endl;
}