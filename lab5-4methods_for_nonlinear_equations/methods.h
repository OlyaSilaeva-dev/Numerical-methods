#ifndef CM_METHODS_H
#define CM_METHODS_H
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>

void input_data(const std::string & file_name, std::string & expression, double & epsilon) {
    std::ifstream fin(file_name);
    if (!fin.is_open()) {
        throw std::runtime_error("Wrong input file: " + file_name + "\n");
    }

    getline(fin, expression);
    fin >> epsilon;
}

double evaluate_expression(const std::string& expr, double x) {
    // Здесь мы разберем только конкретные типы выражений для примера.
    // Например, поддержка pow(), sqrt(), +, -, *, /
    if (expr.find("pow(") == 0) {
        auto start = expr.find('(') + 1;
        auto comma = expr.find(',');
        auto end = expr.find(')');

        double base = std::stod(expr.substr(start, comma - start));
        double exponent = std::stod(expr.substr(comma + 1, end - comma - 1));
        return std::pow(base, exponent);
    }
    else if (expr.find("sqrt(") == 0) {
        auto start = expr.find('(') + 1;
        auto end = expr.find(')');

        std::string inner_expr = expr.substr(start, end - start);
        double inner_value = evaluate_expression(inner_expr, x);
        return std::sqrt(inner_value);
    }
    else if (expr.find("x") != std::string::npos) {
        std::string modified_expr = expr;
        size_t pos = modified_expr.find("x");
        while (pos != std::string::npos) {
            modified_expr.replace(pos, 1, std::to_string(x));
            pos = modified_expr.find("x", pos + 1);
        }
        return std::stod(modified_expr);
    }
    else {
        return std::stod(expr);
    }
}

std::vector<double> simple_iteration_method (std::string &expression, double initial_guess, double epsilon, int max_iter = 1000) {
    std::vector<double> iterations;
    double x = initial_guess;
    iterations.push_back(x);

    for (int i = 0; i < max_iter; ++i) {
        double next_x = evaluate_expression(expression, x);
        iterations.push_back(next_x);

        if (std::abs(next_x - x) < epsilon) {
            break;
        }

        x = next_x;
    }

    return iterations;
}




#endif //CM_METHODS_H
