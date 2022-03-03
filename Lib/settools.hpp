#ifndef DATASTRUCTURE_SETTOOLS_HPP
#define DATASTRUCTURE_SETTOOLS_HPP

#ifndef ax_size
#define ax_size
typedef unsigned long long size_t;
typedef long long ssize_t;
#endif

#include"vector.hpp"
#include "iterator.hpp"

namespace ax
{
    template<typename I, typename II>
    struct pair
    {
        pair(I const &, II const &);
        pair() = default;
        I first;
        II second;
    };

    template<typename K_Tp, typename V_Tp>
    struct orderly_pair
    {
        orderly_pair();

        explicit orderly_pair(K_Tp const & , V_Tp const &);

        inline bool operator==(orderly_pair const &) const;

        inline bool operator!=(orderly_pair const &) const;

        bool operator<(orderly_pair const &) const;

        bool operator>(orderly_pair const &) const;

        bool operator<=(orderly_pair const &) const;

        bool operator>=(orderly_pair const &) const;

        inline bool operator==(K_Tp const &) const;

        inline bool operator!=(K_Tp const &) const;

        inline bool operator<(K_Tp const &) const;

        inline bool operator>(K_Tp const &) const;

        inline bool operator<=(K_Tp const &) const;

        inline bool operator>=(K_Tp const &) const;

        K_Tp Key;

        V_Tp Value;
    };

    template <typename Tp>
    struct Triple_Node
    {
        Triple_Node
                (Tp const &value, size_t const &row, size_t const &column)
                :Value{value}, Column_Num{column}, Row_Num{row} {}

        size_t Row_Num;

        size_t Column_Num;

        Tp Value;
    };

    struct sparse_matrix_triple_tuple
    {
        template<class Iterable_2Dim_Container>
        explicit sparse_matrix_triple_tuple(Iterable_2Dim_Container const &cont);

        std::vector<int[3]> Container;

        int &operator[](std::pair<int, int> const &);

        sparse_matrix_triple_tuple &T();
    };

    template<class Iterable_2Dim_Container>
    sparse_matrix_triple_tuple::sparse_matrix_triple_tuple
            (const Iterable_2Dim_Container &cont)
            : Container{}
    {
        int i=0, j=0;
        for(auto const &iter1:cont)
        {
            for(auto const &iter2:iter1) {
                if (iter2 != 0) Container.template emplace_back(int {i, j, iter2});
                ++j;
            }
            ++i;
        }
    }

    int &sparse_matrix_triple_tuple::operator[](const std::pair<int, int> &pair)
    {
        int row = pair.first, column = pair.second;
        for(auto & iter: this->Container)
        {
            if (row == iter[0] && column == iter[1])
                return iter[2];
        }
        return *new int{};
    }

    sparse_matrix_triple_tuple &sparse_matrix_triple_tuple::T()
    {
        int temp;
        for(auto & iter: this->Container)
        {
            temp = iter[0];
            iter[0] = iter[1];
            iter[1] = temp;
        }
        return *this;
    }


    template<typename Tp>
    struct Triple_Tuple
    {
        template<class Iterable_2Dim_Container>
        explicit Triple_Tuple
                (Iterable_2Dim_Container const &cont);

        Tp &operator[](pair<size_t, size_t> const &);

        vector<Tp> Container;

        vector<size_t[2]> Pos;
    };

    template<typename Tp>
    template<class Iterable_2Dim_Container>
    Triple_Tuple<Tp>::Triple_Tuple(const Iterable_2Dim_Container &cont)
            : Container{}, Pos{}
    {
        size_t i=0, j=0;
        Tp const empty {};
        for(auto const &row_iter: cont)
        {
            for(auto const &column_iter: row_iter)
            {
                if (column_iter != empty)
                {
                    Container.template emplace_back(column_iter);
                    Pos.template emplace_back(new size_t[2]{i, j});
                }
                ++j;
            }
            ++i;
        }
    }

    template<typename Tp>
    Tp &Triple_Tuple<Tp>::operator[](const pair<size_t, size_t> &pair) {
        size_t idx = 0;
        for(auto const &row_iter: Pos)
        {
            if (row_iter[0] != pair.first || row_iter[1] != pair.second) ++idx;
            else return Container.operator[](idx);
        }
        return *new Tp{};
    }

    template<typename K_Tp, typename V_Tp>
    orderly_pair<K_Tp, V_Tp>::orderly_pair()
            :Key{K_Tp{}}, Value{V_Tp{}} {}

    template<typename K_Tp, typename V_Tp>
    orderly_pair<K_Tp, V_Tp>::orderly_pair(const K_Tp &key, const V_Tp &value)
            :Key{key}, Value{value} {}

    template<typename K_Tp, typename V_Tp>
    bool orderly_pair<K_Tp, V_Tp>::operator==(const orderly_pair &op) const
    {
        return this->Key == op.Key && this->Value == op.Value;
    }

    template<typename K_Tp, typename V_Tp>
    bool orderly_pair<K_Tp, V_Tp>::operator!=(const orderly_pair &op) const
    {
        return this->Key != op.Key || this->Value != op.Value;
    }

    template<typename K_Tp, typename V_Tp>
    bool orderly_pair<K_Tp, V_Tp>::operator<(const orderly_pair &op) const
    {
        return this->Key<op.Key;
    }

    template<typename K_Tp, typename V_Tp>
    bool orderly_pair<K_Tp, V_Tp>::operator>(const orderly_pair &op) const
    {
        return this->Key>op.Key;
    }

    template<typename K_Tp, typename V_Tp>
    bool orderly_pair<K_Tp, V_Tp>::operator<=(const orderly_pair &op) const
    {
        return this->Key<=op.Key;
    }

    template<typename K_Tp, typename V_Tp>
    bool orderly_pair<K_Tp, V_Tp>::operator>=(const orderly_pair &op) const
    {
        return this->Key>=op.Key;
    }

    template<typename K_Tp, typename V_Tp>
    bool orderly_pair<K_Tp, V_Tp>::operator==(const K_Tp &word) const
    {
        return this->Key == word;
    }

    template<typename K_Tp, typename V_Tp>
    bool orderly_pair<K_Tp, V_Tp>::operator!=(const K_Tp &word) const
    {
        return this->Key != word;
    }

    template<typename K_Tp, typename V_Tp>
    bool orderly_pair<K_Tp, V_Tp>::operator<(const K_Tp &word) const
    {
        return this->Key < word;
    }

    template<typename K_Tp, typename V_Tp>
    bool orderly_pair<K_Tp, V_Tp>::operator>(const K_Tp &word) const
    {
        return this->Key > word;
    }

    template<typename K_Tp, typename V_Tp>
    bool orderly_pair<K_Tp, V_Tp>::operator<=(const K_Tp &word) const
    {
        return this->Key <= word;
    }

    template<typename K_Tp, typename V_Tp>
    bool orderly_pair<K_Tp, V_Tp>::operator>=(const K_Tp &word) const
    {
        return this->Key >= word;
    }

    template<typename I, typename II>
    pair<I, II>::pair(const I &first_input, const II &second_input)
    :first{first_input}, second{second_input} {}

    
}

#endif //DATASTRUCTURE_SETTOOLS_HPP
