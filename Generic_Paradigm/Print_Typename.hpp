#ifndef DATASTRUCTURE_PRINT_TYPENAME_HPP
#define DATASTRUCTURE_PRINT_TYPENAME_HPP

#include <iostream>

template<typename Tp>
std::ostream &print_typename(std::ostream &out = std::cout) {
    out << typeid(Tp{}).name() << std::endl;
    return out;
}

#endif //DATASTRUCTURE_PRINT_TYPENAME_HPP
