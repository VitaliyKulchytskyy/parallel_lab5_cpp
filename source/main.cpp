#include <cstring>
#include <exception>
#include <iostream>
#include <vector>
#include "omp.h"
#include "matrix.hpp"
#include "matrix_utils.hpp"


void getMatrixArgs(int argc, 
                   char** argv, 
                   size_t& rows, 
                   size_t& columns,
                   size_t& threads) 
{
    if (argc > 5) 
        throw "[!] There is only 3 args: <rows> <columns> <threads> (<v> for verbose)";

    rows = std::stoi(argv[1]);        
    columns = std::stoi(argv[2]);
    threads = std::stoi(argv[3]);

    if (rows <= 0 || columns <= 0 || threads <= 0)
        throw "[!] Arg range: 1 - SIZE_T_MAX";
}

int main(int argc, char** argv) {
    size_t rows, columns, threads;

    try {
        (void) getMatrixArgs(argc, argv, rows, columns, threads);
        if (argc == 5 && strcmp(argv[4], "v") == 0) {
            std::cout << "rows:    " << rows    << "\n";
            std::cout << "columns: " << columns << "\n";
            std::cout << "threads: " << threads << "\n\n";
        }

        Matrix m{rows, columns};
        (void) fillMatrixRnd(m);
        // std::cout << m << '\n';

        omp_set_nested(1);
        long matrixSum = 0;
        size_t minRow = 0;
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                matrixSum = calcMatrixSum(m, threads);
            }

            #pragma omp section
            {
                minRow = getMinMatrixRowIndexSum(m, threads);
            }
        }

        std::cout << "\nsum = " << matrixSum << '\n';
        std::cout << "minRow = " << minRow << '\n';
    } catch (std::exception& e) {
        std::cout << "[!] Wrong arg value. Values range: 1 - SIZE_T_MAX" << '\n'; 
    } catch (const char* e) {
        std::cout << e << '\n';
    } 
}
