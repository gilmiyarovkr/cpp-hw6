#include <iostream>
#include <cassert>
#include <map>
#include <tuple>

template <typename T, T DefaultValue = 0> // size_t N = 0
class Matrix
{
private:
    using Index = std::pair<int, int>;
    //    using Index = std::array<int, N>;
    std::map<Index, T> m_matrix;

public:

    class Element
    {
    private:
        Matrix* m_matrix;
        Index m_index;

    public:
        explicit Element(Matrix* m, Index i) :
            m_matrix(m), m_index(i) {}

        operator T() const{
            auto it = m_matrix->m_matrix.find(m_index);
            return (it != m_matrix->m_matrix.end()) ? it->second : T{DefaultValue};
        }

        Element& operator=(const T& value)
        {
            if(value == T{DefaultValue})
            {
                m_matrix->m_matrix.erase(m_index);
            }
            else
            {
                m_matrix->m_matrix[m_index] = value;
            }
            return *this;
        }
    };

    class Row
    {
    private:
        Matrix* m_matrix;
        int m_row;
    public:
        explicit Row(Matrix* m, int r) : m_matrix(m), m_row(r) {}

        Element operator[](int col)
        {
            return Element(m_matrix, {m_row, col});
        }
    };

    size_t size() const
    {
        return m_matrix.size();
    }

    void clear()
    {
        return m_matrix.clear();
    }

    Element operator()(int r, int c)
    {
        return Element(this, {r, c});
    }

    Row operator[](int row)
    {
        return Row(this, row);
    }

    class Iterator
    {
    private:
        using MapIter = typename std::map<Index, T>::iterator;
        MapIter m_cur;
        MapIter m_end;
    public:
        Iterator(MapIter c, MapIter e) : m_cur(c), m_end(e){}

        bool operator != (const Iterator& o) const
        {
            return m_cur != o.m_cur;
        }

        Iterator& operator++()
        {
            ++m_cur; return *this;
        }

        Iterator& operator--()
        {
            --m_cur; return *this;
        }

        std::tuple<int, int, int> operator*() const
        {
            const auto& [x, y] = m_cur->first;
            return {x, y, m_cur->second};
        }
    };

    Iterator begin()
    {
        return Iterator(m_matrix.begin(), m_matrix.end());
    }

    Iterator end()
    {
        return Iterator(m_matrix.end(), m_matrix.end());
    }
};

int main()
{
    // бесконечная матрица int заполнена значениями -1
    Matrix <int, -1> matrix;

    assert(matrix.size() == 0);
    std::cout << (matrix.size() == 0) << std::endl;

    // все ячейки свободны
    auto a = matrix[0][0];
    assert(a == -1);
    std::cout << (a == -1) << std::endl;

    assert(matrix.size() == 0);
    std::cout << (matrix.size() == 0) << std::endl;

    matrix[100][100] = 314;
    assert(matrix[100][100] == 314);
    std::cout << (matrix[100][100] == 314) << std::endl;

    assert(matrix.size() == 1);
    std::cout << (matrix.size() == 1) << std::endl;

    // выведется одна строка
    // 100100314
    for(auto c : matrix)
    {
        int x;
        int y;
        int v;
        std::tie(x, y, v) = c;
        std::cout << x << y << v << std::endl;
    }

    //    Matrix <int, 0> matrix;

    //    // Заполнение матрицы
    //    for(uint8_t i = 0; i <= 9; ++i)
    //    {
    //        matrix[i][i] = i; // главная диагональ
    //        matrix[i][9 - i] = 9 - i; // второстепенная диагональ
    //    }

    //    // Вывод фрагмента матрицы от 1,1 до 8,8
    //    for(uint8_t r = 1; r <= 8; ++r) // row
    //    {
    //        for(uint8_t c = 1; c <= 8; ++c)
    //        {
    //            std::cout << matrix[r][c] << " ";
    //        }
    //        std::cout << std::endl;
    //    }

    //    std::cout << matrix.size() << std::endl;

    //    for(auto c : matrix)
    //    {
    //        int x = 0, y = 0, v = 0;
    //        std::tie(x, y, v) = c;
    //        std::cout << x << y << v << std::endl;
    //    }

    return 0;
}
