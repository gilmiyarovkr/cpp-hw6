#pragma once

#include <map>
#include <tuple>
#include <array>

template <typename T, size_t N, T DefaultValue = 0>
class Matrix
{
public:
    using Index = std::array<int, N>;

private:
    std::map<Index, T> m_matrix;

public:

    class Element
    {
    private:
        Matrix* m_matrix;
        Index m_index;

    public:
        explicit Element(Matrix* m, const Index& i) :
            m_matrix(m), m_index(i) {}

        operator T() const
        {
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

    template <size_t Size>
    class Node
    {
    private:
        Matrix* m_matrix;
        Index m_index;

    public:
        explicit Node(Matrix* m, const Index& i) : m_matrix(m), m_index(i) {}

        auto operator[](int idx) -> std::conditional_t<Size == N - 1, Element, Node<Size + 1>>
        {
            Index next_index = m_index;
            next_index[Size] = idx;

            if constexpr (Size == N - 1)
            {
                return Element(m_matrix, next_index);
            }
            else
            {
                return Node<Size + 1>(m_matrix, next_index);
            }
        }
    };

    size_t size() const
    {
        return m_matrix.size();
    }

    void clear()
    {
        m_matrix.clear();
    }

    auto operator[](int idx)
    {
        Index init_index{};
        init_index[0] = idx;
        if constexpr (N == 1)
        {
            return Element(this, init_index);
        }
        else
        {
            return Node<1>(this, init_index);
        }
    }

    class Iterator
    {
    private:
        using MapIter = typename std::map<Index, T>::iterator;
        MapIter m_cur;

    public:
        Iterator(MapIter c) : m_cur(c) {}

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

        auto operator*() const
        {
            auto indices_tuple = std::apply([](auto... elems) {
                return std::make_tuple(elems...);
            }, m_cur->first);

            return std::tuple_cat(indices_tuple, std::tie(m_cur->second));
        }
    };

    Iterator begin()
    {
        return Iterator(m_matrix.begin());
    }

    Iterator end()
    {
        return Iterator(m_matrix.end());
    }
};
