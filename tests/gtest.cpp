#include <gtest/gtest.h>
#include <tuple>
#include "matrix.hpp"

TEST(MatrixTest, BasicOperations2D) {
    Matrix<int, -1> matrix;

    EXPECT_EQ(matrix.size(), 0U);

    auto a = matrix[0][0];
    EXPECT_EQ(a, -1);
    EXPECT_EQ(matrix.size(), 0U);

    matrix[100][100] = 314;
    EXPECT_EQ(matrix[100][100], 314);
    EXPECT_EQ(matrix.size(), 1U);

    bool element_found = false;
    for (auto c : matrix) {
        int x, y, v;
        std::tie(x, y, v) = c;

        EXPECT_EQ(x, 100);
        EXPECT_EQ(y, 100);
        EXPECT_EQ(v, 314);
        element_found = true;
    }
    EXPECT_TRUE(element_found);
}

TEST(MatrixTest, MultiDimensionalOperations5D) {
    Matrix<int, 0, 5> matrix5D;

    EXPECT_EQ(matrix5D.size(), 0U);

    int default_val = matrix5D[1][2][3][4][5];
    EXPECT_EQ(default_val, 0);
    EXPECT_EQ(matrix5D.size(), 0U);

    matrix5D[10][20][30][40][50] = 42;
    EXPECT_EQ(matrix5D[10][20][30][40][50], 42);
    EXPECT_EQ(matrix5D.size(), 1U);

    bool element_found = false;
    for (auto cell : matrix5D) {
        auto [i1, i2, i3, i4, i5, val] = cell;

        EXPECT_EQ(i1, 10);
        EXPECT_EQ(i2, 20);
        EXPECT_EQ(i3, 30);
        EXPECT_EQ(i4, 40);
        EXPECT_EQ(i5, 50);
        EXPECT_EQ(val, 42);
        element_found = true;
    }
    EXPECT_TRUE(element_found);

    matrix5D[10][20][30][40][50] = 0;
    EXPECT_EQ(matrix5D.size(), 0U); // Память успешно освобождена
    EXPECT_EQ(matrix5D[10][20][30][40][50], 0); // Возвращается дефолт
}

TEST(MatrixTest, ChainedAssignments) {
    Matrix<int, 0, 2> matrix;

    ASSERT_EQ(matrix.size(), 0U);

    ((matrix[100][100] = 314) = 0) = 217;

    EXPECT_EQ(matrix[100][100], 217);
    EXPECT_EQ(matrix.size(), 1U);

    ((matrix[200][200] = 555) = 888) = 0;

    EXPECT_EQ(matrix[200][200], 0);
    EXPECT_EQ(matrix.size(), 1U);
}

