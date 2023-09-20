#include <iostream>
#include <thread>
#include "Matrix.h"

int main(int argc, char** argv) {
    int rows = 6;
    int columns = 7;
    int count_threads = 3;

    Matrix matrix(rows, columns);

    matrix.Print_array(rows, columns);
    std::cout << std::endl;
    int sum= matrix.CalculateSum(count_threads);

    std::cout << "Total sum of the matrix elements is equal to " << sum << std::endl;

    return 0;
}
