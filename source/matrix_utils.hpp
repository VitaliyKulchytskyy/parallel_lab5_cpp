#pragma once
#include "matrix.hpp"


extern void fillMatrixRnd(Matrix& m);

extern long calcMatrixSum(Matrix&, size_t = 1);

extern size_t getMinMatrixRowIndexSum(Matrix&, size_t = 1);
