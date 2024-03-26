#include <climits>
#include <iostream>
#include <random>
#include "matrix_utils.hpp"
#include <omp.h>


void fillMatrixRnd(Matrix& m) {
    std::random_device rd; 
    std::mt19937 mersenne(rd());

    for (size_t i = 0; i < m.getRows(); i++) {
        for (size_t j = 0; j < m.getColumns(); j++) {
            m[i][j] = static_cast<int>(mersenne());
        }
    } 
    // m[2][1] = -10;
}

long calcMatrixSum(Matrix& m, size_t threadNum) {
    long sum = 0; 

    double t1 = omp_get_wtime();
    #pragma omp parallel for reduction(+:sum) num_threads(threadNum)	
    for (size_t i = 0; i < m.getRows(); i++) {
        for (size_t j = 0; j < m.getColumns(); j++) {
            sum += m[i][j];
        }
    }
    double t2 = omp_get_wtime();
    std::cout << "time_calc_sum: " << t2 - t1 << '\n';

    return sum;
}

size_t getMinMatrixRowIndexSum(Matrix& m, size_t threadNum) {
    size_t minIndex = 0;
    long minSum = LONG_MAX;
    long rowSum;

    double t1 = omp_get_wtime();
    #pragma omp parallel for num_threads(threadNum)
    for (size_t i = 0; i < m.getRows(); i++) {
        rowSum = 0;
        for (size_t j = 0; j < m.getColumns(); j++) {
            rowSum += m[i][j];
        }

        #pragma omp critical
        if (rowSum < minSum) {
            minSum = rowSum;
            minIndex = i;
        }
    }
    double t2 = omp_get_wtime();
    std::cout << "time_min_row_index: " << t2 - t1 << '\n';

    return minIndex;
}
