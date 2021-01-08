#ifndef DATASTRUCTURE_ABSTRACT_MATRIX_HPP
#define DATASTRUCTURE_ABSTRACT_MATRIX_HPP

#include <cstddef>
#include <utility>

template<typename cls>
class Matrix {
public:
    virtual cls &get(size_t const &, size_t const &) = 0;

    virtual cls get_c(size_t const &, size_t const &) const = 0;

    [[nodiscard]] virtual std::pair<size_t, size_t> shape() const = 0;

    [[nodiscard]] virtual size_t size() const = 0;
};

#endif //DATASTRUCTURE_ABSTRACT_MATRIX_HPP
