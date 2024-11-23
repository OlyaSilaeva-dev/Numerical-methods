#include "differentiation.h"

int main () {
    double x_star = 1.0;
    vector<long double> x = {-1.0, 0.0, 1.0, 2.0, 3.0};
    vector<long double> y = {-1.7854, 0.0, 1.7854, 3.1071, 4.249};

    long double result1 = differentiation_first_degree(x, y, x_star, LEFT);
    cout << "differentiation_first_degree_left: " << result1 << endl;

    long double result2 = differentiation_first_degree(x, y, x_star, RIGHT);
    cout << "differentiation_first_degree_right: " << result2 << endl;

    long double result3 = differentiation_first_degree(x, y, x_star, AVERANGE);
    cout << "differentiation_first_degree_averange: " << result3 << endl;

    long double result4 = differentiation_second_degree(x, y, x_star);
    cout << "differentiation_second_degree: " << result4 << endl;
}