#include "Progonka.h"

int main(int argc, char * argv[]) {

//    filesystem::current_path("/mnt/c/src/GitHub/Numerical-methods/lab1-Progonka");
    filesystem::current_path("C:/src/GitHub/Numerical-methods/lab1-Progonka");
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


    bool check = CheckCorrectAnswer(matrix, result, result_operation);
    if (check) {
        cout << "\nCORRECT" << endl;
    } else {
        cout << "\nWRONG" << endl;
    }
    return 0;
}