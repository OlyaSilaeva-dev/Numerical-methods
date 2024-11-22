#include "mnk.h"

int main() {
    vector<double> x = {-0.7, -0.4, -0.1, 0.2, 0.5, 0.8};
    vector<double> y = {-1.4754, -0.81152, -0.20017, 0.40136, 1.0236, 1.7273};

    vector<double> x_test = {0.0, 1.7, 3.4, 5.1, 6.8, 8.5};
    vector<double> y_test = {0.4713, 1.0114, 1.5515, 2.0916, 2.6317, 3.1718};

    std::cout << "The result of calculating a polynomial of the first degree: \n";
    vector<double> result1 = polinomial_second_degree(x, y, 2);
    for (int i = 0; i < result1.size(); i++) {
        std::cout << "a["<< i << "]" << " = " << result1[i] << std::endl;
    }
    std::cout << "With an error: " << calculate_Fi(result1, y, x) << "\n\n";

    std::cout << "The result of calculating a polynomial of the second degree: \n";
    vector<double> result2 = polinomial_second_degree(x, y, 3);
    for (int i = 0; i < result2.size(); i++) {
        std::cout << "a["<< i << "]" << " = " << result2[i] << std::endl;
    }
    std::cout << "With an error: " << calculate_Fi(result2, y, x) << endl;

    return 0;
}