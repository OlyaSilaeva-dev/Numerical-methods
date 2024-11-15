#ifndef CM_MATRIX_H
#define CM_MATRIX_H

#include "vector"
#include "string"
using namespace std;


class matrix {

private:
    vector<vector<double>> _matrix;
    int lines;
    int columns;

public:
    explicit matrix();

    explicit matrix(vector<vector<double>> const &other_matrix);

    explicit matrix(vector<double> &_vector);

    virtual ~matrix() = default;

    matrix(matrix const &other) noexcept = default;

    matrix(matrix &&other) = default;

    matrix &operator=(matrix const &other);

    matrix &operator=(matrix &&other) = default;

    bool operator==(matrix const &other);

public:

    matrix &input_from_file(std::ifstream &fin);

    friend  std::ostream& operator<<(std::ostream& out, const matrix &_matrix1);

    vector<vector<double>> &get_matrix() {
        return this->_matrix;
    }

    int &get_lines_cnt() {
        return lines;
    }

    int &get_columns_cnt() {
        return columns;
    }

    matrix operator*(matrix const &other) const;

    matrix &operator*(std::vector<double> const &_vector);

    matrix &change_lines(int line1, int line2);

    vector<double> &operator[](unsigned index);

    matrix operator+(const matrix &other) const;

    matrix operator+(const vector<double> &other) const;

    matrix &reverse_matrix(matrix& _matrix);
};


#endif //CM_MATRIX_H
