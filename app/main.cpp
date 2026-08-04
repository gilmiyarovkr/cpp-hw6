#include <iostream>
#include "matrix.hpp"

int main()
{
    Matrix <int, 0> matrix;

    // Заполнение матрицы
    for(size_t i = 0; i <= 9; ++i)
    {
       matrix[i][i] = i; // главная диагональ
       matrix[i][9 - i] = 9 - i; // второстепенная диагональ
    }

    // Вывод фрагмента матрицы от 1,1 до 8,8
    for(size_t r = 1; r <= 8; ++r) // row
    {
       for(size_t c = 1; c <= 8; ++c)
       {
           std::cout << matrix[r][c] << " ";
       }
       std::cout << std::endl;
    }

    std::cout << matrix.size() << std::endl;

    for(auto c : matrix)
    {
       int x = 0, y = 0, v = 0;
       std::tie(x, y, v) = c;
       std::cout << x << y << v << std::endl;
    }

    return 0;
}
