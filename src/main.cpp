#include "matrix.hpp"
#include <iostream>

int main()
{

    OtusMatrix::Matrix<int, -1> matrix;

    const std::size_t SIZE = 10;

    for (std::size_t i = 0; i < SIZE; ++i)
    {
        matrix[i][i] = i;
        matrix[i][SIZE - i - 1] = SIZE - i - 1;
    }

    for (std::size_t i = 1; i < SIZE - 1; ++i)
    {
        for (std::size_t j = 1; j < SIZE - 1; ++j)
        {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    for (auto c : matrix)
    {
        int x;
        int y;
        int v;
        std::tie(x, y, v) = c;
        std::cout << x << y << v << std::endl;
    }

    return 0;
}