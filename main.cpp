#include <iostream>
#include <vector>
#include <filesystem>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;


void print_matrix(vector<vector<double>> &matrix) {
    size_t n = matrix.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

vector<double> Method_Progonki(vector<vector<double>> &matrix, vector<double> &result){
    //прямой ход
    int  n = matrix.size();
    vector<double> Q(n, 0);
    vector<double> P(n, 0);

    double b1 = matrix[0][0];
    double c1 = matrix[0][1];
    double d1 = result[0];

    P[0] = -c1 / b1;
    Q[0] = d1 / b1;

    for (int i = 1; i < n-1; i++) {
        double ai = matrix[i][i - 1];
        double bi = matrix[i][i];
        double ci = matrix[i][i + 1];
        double di = result[i];

        P[i] = -ci / (bi + ai * P[i-1]);
        Q[i] = (di - ai * Q[i-1]) / (bi + ai * P[i-1]);
    }

    double dn = result[n-1];
    double an = matrix[n-1][n-2];
    double bn = matrix[n-1][n-1];

    P[n-1] = 0;
    Q[n-1] = (dn - an * Q[n-2]) / (bn + an * P[n-2]);

    //обратный ход
    vector<double> x(n, 0);
    x[n-1] = Q[n-1];

    for (int i = n-2; i >= 0; i--) {
        x[i] = P[i] * x[i+1] + Q[i];
    }

    return x;
}

double determinant(vector<vector<double>> matrix, uint32_t n) {

//    uint32_t n = matrix.size();
    vector<vector<double>> tmp(n,vector<double>(n, 0));
    double det;

    if (n == 1) {
        return matrix[0][0];
    } else if  (n == 2) {
        return (matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1]);
    } else {
        for (int k = 0; k < n; k++) {
            int x = 0;
            int y = 0;

            for (int i = 1; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (j == k) continue;

                    tmp[x][y] = matrix[i][j];
                    y++;
                    if(y == n-1) {
                        x++;
                        y = 0;
                    }
                }
            }

            int sign = (k % 2 == 0) ? 1: -1;
            det = det + matrix[0][k] * sign * determinant(tmp, n-1);
        }
        return det;
    }
}

void input_all(string const & file_name, vector<vector<double>> &input_matrix, vector<double> &input_result) {
    ifstream fin(file_name);
    if (!fin.is_open()) {
        throw std::logic_error("Wrong input file: " + file_name + "\n");
    }

    vector<vector<double>> matrix;

    string line;
    while (true) {
        if (!getline(fin, line)) break;

        char c = line[line.length() - 1];
        if ( c == '\n' || c == '\r')
            line.erase(line.length() - 1);
        if (line.empty()) break;

        istringstream line_str(line);

        vector<double> line_vector;
        double a;
        while (line_str >> a) line_vector.push_back(a);
        matrix.push_back(line_vector);
    }

    print_matrix(matrix);

    vector<double> result;
    if(!getline(fin, line))
        throw logic_error("Wrong input!!!");
    istringstream line_str(line);

    double a;
    while (line_str >> a) result.push_back(a);

    input_matrix = matrix;
    input_result = result;
}

int main(int argc, char * argv[]) {

//    filesystem::current_path("/mnt/c/src/GitHub/CM");
    filesystem::current_path("C:/src/GitHub/CM");
//    std::string file_name(argv[1]);
    std::string file_name("test.txt");

    vector<vector<double>> matrix;
    vector<double> result;
    input_all(file_name, matrix, result);

    vector<double> result_operation;
    result_operation = Method_Progonki(matrix, result);

    size_t n = result_operation.size();

    std::cout << "\nResult: " << std::endl;
    for (int i = 0; i < n; i++) {
        cout.precision(6);
        cout << fixed << result_operation[i] << " ";
    }

    double det = determinant(matrix, matrix.size());
    std::cout << "\n\nDeterminant: " << std::endl;

    cout.precision(6);
    cout << det << endl;

    return 0;
}
