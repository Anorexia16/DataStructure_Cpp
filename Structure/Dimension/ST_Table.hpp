#ifndef DATASTRUCTURE_ST_TABLE_HPP
#define DATASTRUCTURE_ST_TABLE_HPP

#include <array>

template<size_t x, size_t l>
constexpr size_t log_iter() {
    if constexpr (x<(1<<l)) {
        return l-1;
    } else {
        return log_iter<x, l + 1>();
    }
}

template<size_t x>
constexpr size_t static_log2() {
    return log_iter<x, 0>();
}

template<size_t x>
constexpr bool ST_size = x>2;

enum class ST_OP {Max, Min, And , Or, Xor, Gcd, Null};

template<typename tp>
tp func_and(tp const &a, tp const &b) {
    return a and b;
}

template<typename tp>
tp func_or(tp const &a, tp const &b) {
    return a or b;
}

template<typename tp>
tp func_max(tp const &a, tp const &b) {
    return a>b?a:b;
}

template<typename tp>
tp func_min(tp const &a, tp const &b) {
    return a>b?b:a;
}

template<typename tp>
tp func_xor(tp const &a, tp const &b) {
    return a xor b;
}

template<typename tp>
tp func_gcd(tp const &a, tp const &b) {
    for(tp i=a;i<=a*b;++i) if (i%a==0&&i%b==0) return i;
}

template<typename tp>
tp func_null(tp const &a, tp const &b) {
    return tp{};
}

template<class I, size_t N, typename = typename std::enable_if_t<ST_size<N>>>
class ST_Table {
public:
    explicit ST_Table(I (&)[N], I (*) (I const &, I const &));

    explicit ST_Table(std::array<I, N> const &, I (*) (I const &, I const &));

    I get(size_t const &, size_t const &) const;

private:
    size_t max_depth;

    size_t lgs[N+1];

    I Container[N+1][static_log2<N>() + 1];

    I (*Func) (I const &, I const &);
};

template<class I, size_t N, typename valid>
ST_Table<I, N, valid>::ST_Table(I (&arr)[N], I (*fc) (I const &, I const &))
:Container{}, lgs{}, Func{fc}, max_depth{static_log2<N>()} {
    for(size_t i=0; i != N+1; ++i) Container[i][0] = arr[i];
    for(size_t i=0;i!=max_depth;++i) {
        for(size_t j=0; j != N+1; ++j) {
            Container[j][i] = Func(Container[j][i-1], Container[j+(1<<(i-1))][i-1]);
        }
    }
    if (N > 1)lgs[1] = 0; lgs[2] = 1;
    for(size_t i=3; i < N+1; ++i) {
        lgs[i] = lgs[i/2] + 1;
    }
}

template<class I, size_t N, typename valid>
ST_Table<I, N, valid>::ST_Table(const std::array<I, N> &arr, I (*fc) (I const &, I const &))
:Container{}, lgs{}, Func{fc}, max_depth{static_log2<N>()} {
    for(size_t i=1; i != N+1; ++i) Container[i][0] = arr[i];
    for(size_t i=1;i!=max_depth;++i) {
        for(size_t j=1; j != N+1; ++j) {
            Container[j][i] = Func(Container[j][i-1], Container[j+(1<<(i-1))][i-1]);
        }
    }
    if (N > 1)lgs[1] = 0; lgs[2] = 1;
    for(size_t i=3; i < N+1; ++i) {
        lgs[i] = lgs[i/2] + 1;
    }
}

template<class I, size_t N, typename valid>
I ST_Table<I, N, valid>::get(size_t const &left, size_t const &right) const {
    auto lg=lgs[right - left + 1];
    return Func(Container[left][lg], Container[right - (1 << lg) + 1][lg]);
}

template<typename tp, size_t n, ST_OP op>
decltype(auto) make_st_table(tp (&arr)[n]) {
    switch (op) {
        case ST_OP::Max:
            return ST_Table<tp, n>(arr, func_max<tp>);
        case ST_OP::Min:
            return ST_Table<tp, n>(arr, func_min<tp>);
        case ST_OP::And:
            return ST_Table<tp, n>(arr, func_and<tp>);
        case ST_OP::Or:
            return ST_Table<tp, n>(arr, func_or<tp>);
        case ST_OP::Xor:
            return ST_Table<tp, n>(arr, func_xor<tp>);
        case ST_OP::Gcd:
            return ST_Table<tp, n>(arr, func_gcd<tp>);
        default:
            return ST_Table<tp, n>(arr, func_null<tp>);
    }
}

template<typename tp, size_t n, ST_OP op>
ST_Table<tp, n> make_st_table(std::array<tp, n> const &arr) {
    switch (op) {
        case ST_OP::Max:
            return ST_Table<tp, n>(arr, func_max<tp>);
        case ST_OP::Min:
            return ST_Table<tp, n>(arr, func_min<tp>);
        case ST_OP::And:
            return ST_Table<tp, n>(arr, func_and<tp>);
        case ST_OP::Or:
            return ST_Table<tp, n>(arr, func_or<tp>);
        case ST_OP::Xor:
            return ST_Table<tp, n>(arr, func_xor<tp>);
        case ST_OP::Gcd:
            return ST_Table<tp, n>(arr, func_gcd<tp>);
        default:
            return ST_Table<tp, n>(arr, func_null<tp>);
    }
}

#endif //DATASTRUCTURE_ST_TABLE_HPP
