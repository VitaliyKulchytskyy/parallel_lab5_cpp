#include <strstream>
#include "matrix.hpp"

Matrix::Matrix(size_t rows, size_t columns)
    : m_rows(rows), m_columns(columns) 
{
    if (rows <= 0 || columns <= 0)
        throw "matrix: incorrect dimension";

    m_matrix = new int*[m_rows];
    for (size_t i = 0; i < m_rows; i++)
        m_matrix[i] = new int[m_columns]{};
}

Matrix::~Matrix() {
    for (size_t i = 0; i < m_rows; i++)
        delete[] m_matrix[i];
    delete[] m_matrix;
}

int* Matrix::operator[] (const size_t i) {
    if (i >= m_rows)
        throw "matrix: index out of range";

    return m_matrix[i];
}

int** Matrix::operator& () {
    return &m_matrix[0];
}

std::ostream& operator<<(std::ostream& out, Matrix &m) {
    for (size_t i = 0; i < m.getRows(); i++) {
        for (size_t j = 0; j < m.getColumns(); j++)
            out << m[i][j] << '\t';
        out << '\n';
    }

    return out; 
}

size_t Matrix::getRows() const {
    return m_rows;
}

size_t Matrix::getColumns() const {
    return m_columns;
}
