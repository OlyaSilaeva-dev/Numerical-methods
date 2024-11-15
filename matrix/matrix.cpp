#include <fstream>
#include <sstream>
#include "matrix.h"
#include "iostream"
double EXP = 1e-9;

matrix::matrix(const vector<vector<double>> &other_matrix) { //конструктор
    this->_matrix = other_matrix;
    this->lines = (int)other_matrix.size();
    this->columns = (int)other_matrix[0].size();
}

matrix &matrix::input_from_file(std::ifstream &fin) { //считывает матрицу из файла
    matrix result;
    std::string line;
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
        result._matrix.push_back(line_vector);
    }
    result.lines = (int)result._matrix.size();
    result.columns = (int)result._matrix[0].size();
    (*this) = result;
    return *this;
}

matrix matrix::operator*(const matrix &other) const{ //оператор *
    int n1 = this->lines;
    int m1 = this->columns;
    int n2 = other.lines;
    int m2 = other.columns;

    if(m1 != n2) {
        throw logic_error("Matrices are incompatible!!!"); //матрицы несовместны
    }
    vector<vector<double>> result(n1, vector<double> (m2, 0));

    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < m2; j++) {
            for (int p = 0; p < m1; p++) {
                result[i][j] += this->_matrix[i][p] * other._matrix[p][j];
            }
        }
    }

    matrix matrix_result(result);
    return matrix_result;
}

matrix &matrix::change_lines(int line1, int line2) { //меняет местами две линии
    int n = this->lines;
    vector<vector<double>> p(n, vector<double>(n, 0));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if (i == (line1)) {
                p[i][j] = (j == (line2)) ? 1: 0;
            } else if (i == line2) {
                p[i][j] = (j == line1) ? 1: 0;
            } else {
                p[i][j] = (j == i) ? 1: 0;
            }
        }
    }
    matrix p1(p);
//    std::cout << p1 << std::endl;

    auto result = p1 * (*this);
    *this = result;
    return *this;
}

std::ostream &operator<<(ostream &out, const matrix &_matrix1) {

    for (int i = 0; i < _matrix1.lines; i++) {
        for (int j = 0; j < _matrix1.columns; j++) {
            out << _matrix1._matrix[i][j] << " ";
        }
        out << "\n";
    }
    return out;
}

matrix::matrix() {
    this->_matrix = vector<vector<double>> ();
    this->lines = 0;
    this->columns = 0;
}

bool matrix::operator==(const matrix &other) {
    if(lines != other.lines || columns != other.columns) return false;
    for(int i = 0; i < this->lines; i++) {
        for(int j = 0; j < this->columns; j++) {
            if(abs(_matrix[i][j] - other._matrix[i][j]) > EXP) return false;
        }
    }
    return true;
}

matrix::matrix(vector<double> &_vector) {
    _matrix.push_back(_vector);
    this->lines = 1;
    this->columns = _vector.size();
}

matrix &matrix::operator*(const std::vector<double> &_vector) {
    matrix matrix_vector(this->_matrix);
    matrix result;
    result = *this * matrix_vector;
    *this = result;
    std::cout << fixed << result;
    return *this;
}

std::vector<double> &matrix::operator[](unsigned index) {
    return this->_matrix[index];
}

matrix matrix::operator+(const matrix &other) const{
    vector<vector<double>> result_v(this->lines, vector<double>(this->columns, 0));
    matrix result(result_v);

    for (int i = 0; i < this->lines; i++) {
        for (int j = 0; j < this->columns; j++) {
            result[i][j] = this->_matrix[i][j] + other._matrix[i][j];
        }
    }

    return result;
}

matrix matrix::operator+(const vector<double> &other) const {
    if (this->columns != 1 && other.size() != this->lines) {
        throw runtime_error("not equal size! Can`t add up!");
    }

    vector<vector<double>> result_v(this->lines, vector<double>(this->columns, 0));
    matrix result(result_v);

    for (int i = 0; i < this->lines; i++) {
       result[i][0] = this->_matrix[i][0] + (other)[i];
    }

    return matrix();
}

matrix &matrix::operator=(const matrix &other) {
    if(*this == other) {
        return *this;
    }

    this->_matrix.clear();
    for (int i = 0; i < other.lines; i++) {
        vector<double> tmp;
        for (int j = 0; j < other.columns; j++) {
            tmp.push_back(other._matrix[i][j]);
        }
        this->_matrix.push_back(tmp);
    }
    this->lines = other.lines;
    this->columns = other.columns;
    return *this;
}

matrix &matrix::reverse_matrix(matrix& _matrix) {
    int n = _matrix.get_lines_cnt();
    if (_matrix.get_columns_cnt() != n) {
        throw std::invalid_argument("The matrix must be square.");
    }

    // Создаем расширенную матрицу [A | E]
    std::vector<std::vector<double>> augmented(n, std::vector<double>(2 * n, 0.0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 2 * n; ++j) {
            if (j < n) {
                augmented[i][j] = _matrix.get_matrix()[i][j];
            } else {
                augmented[i][j] = (i == (j - n)) ? 1.0 : 0.0;
            }
        }
    }

    // Приведение расширенной матрицы к приведенному виду
    for (int i = 0; i < n; ++i) {
        // Поиск максимального элемента в столбце для выбора опорного элемента
        double maxEl = abs(augmented[i][i]);
        int maxRow = i;
        for (int k = i + 1; k < n; ++k) {
            if (abs(augmented[k][i]) > maxEl) {
                maxEl = abs(augmented[k][i]);
                maxRow = k;
            }
        }

        // Проверка на вырожденность матрицы
        if (maxEl < EXP) {
            throw std::runtime_error("The matrix is degenerate and has no inverse matrix.");
        }
        // Перестановка строк
        std::swap(augmented[i], augmented[maxRow]);

        // Приведение опорного элемента к 1
        double pivot = augmented[i][i];
        for (int j = 0; j < 2 * n; ++j) {
            augmented[i][j] /= pivot;
        }

        // Обнуление остальных элементов в текущем столбце
        for (int k = 0; k < n; ++k) {
            if (k != i) {
                double factor = augmented[k][i];
                for (int j = 0; j < 2 * n; ++j) {
                    augmented[k][j] -= factor * augmented[i][j];
                }
            }
        }
    }

    // Извлечение обратной матрицы из расширенной матрицы
    std::vector<std::vector<double>> inverse(n, std::vector<double>(n, 0.0));
    for (int i = 0; i < n; ++i) {
        for (int j = n; j < 2 * n; ++j) {
            inverse[i][j - n] = augmented[i][j];
        }
    }
    matrix result(inverse);
    std::cout << result;
    (*this) = result;
    return *this;
}



