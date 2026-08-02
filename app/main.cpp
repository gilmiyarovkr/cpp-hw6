#include <iostream>
#include <cassert>
#include "matrix.hpp"

int main()
{
    // бесконечная матрица int заполнена значениями -1
    // Matrix <int, 2, -1> matrix;

    // assert(matrix.size() == 0);
    // std::cout << (matrix.size() == 0) << std::endl;

    // // все ячейки свободны
    // auto a = matrix[0][0];
    // assert(a == -1);
    // std::cout << (a == -1) << std::endl;

    // assert(matrix.size() == 0);
    // std::cout << (matrix.size() == 0) << std::endl;

    // matrix[100][100] = 314;
    // assert(matrix[100][100] == 314);
    // std::cout << (matrix[100][100] == 314) << std::endl;

    // assert(matrix.size() == 1);
    // std::cout << (matrix.size() == 1) << std::endl;

    // // выведется одна строка
    // // 100100314
    // for(auto c : matrix)
    // {
    //     int x;
    //     int y;
    //     int v;
    //     std::tie(x, y, v) = c;
    //     std::cout << x << y << v << std::endl;
    // }

    Matrix <int, 2, 0> matrix;

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
