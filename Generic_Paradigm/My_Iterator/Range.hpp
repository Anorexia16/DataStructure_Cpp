#ifndef DATASTRUCTURE_RANGE_HPP
#define DATASTRUCTURE_RANGE_HPP
#include "Range_Iterator.hpp"

class Range {
private:
    long long Count;
    long long Start;
    long long End;

public:
    friend class Range_iterator;

    explicit Range(long long const & = 0);

    explicit Range(long long const &, long long const &);

    explicit Range(long long const &, long long const &, long long const &);

    Range_iterator begin();

    Range_iterator end();
};

#endif //DATASTRUCTURE_RANGE_HPP
