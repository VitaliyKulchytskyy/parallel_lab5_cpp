#pragma once
#include <cstddef>
#include <ostream>


class Matrix {
public:
    Matrix(size_t rows, size_t columns);
    ~Matrix();

public:
    int* operator[] (const size_t i);
    int** operator& ();
    friend std::ostream& operator<<(std::ostream& out, Matrix &m);

public:
    size_t getRows() const;
    size_t getColumns() const;

private:
    const size_t m_rows;
    const size_t m_columns;
    int** m_matrix;
};
