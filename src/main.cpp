#include <chrono>
#include <iostream>

#include "matrix.hpp"

int main() {
    const std::size_t n = 256;

    parabench::Matrix a = parabench::Matrix::random(n, n, 1);
    parabench::Matrix b = parabench::Matrix::random(n, n, 2);

    auto start = std::chrono::steady_clock::now();
    parabench::Matrix c = parabench::multiply_serial(a, b);
    auto end = std::chrono::steady_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Multiplied " << n << "x" << n << " matrices serially in "
              << elapsed.count() << "s\n";
    std::cout << "c(0,0) = " << c(0, 0) << " (sanity check)\n";

    return 0;
}
