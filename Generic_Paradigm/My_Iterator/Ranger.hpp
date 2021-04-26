#ifndef DATASTRUCTURE_RANGER_HPP
#define DATASTRUCTURE_RANGER_HPP

#include "Range.hpp"

Range::Range(const long long &end)
        : Start{0}, End{end}, Count{1} {if (end < 0) Count = -1;}

Range::Range(const long long &start, const long long &end)
        : Start{start}, End{end}, Count{} {if (end < start) Count=-1;}

Range::Range(const long long &start, const long long &end, const long long &count)
        : Start{start}, End{end}, Count{count} {if ((end - start) * count < 0) throw;}

Range_iterator Range::begin()
{
    return Range_iterator(*this);
}

Range_iterator Range::end()
{
    Range_iterator end_iter {*this};
    long long value {this->Start};
    for (;(value<this->End&&this->Count>0||value>this->End&&this->Count<0);) value += this->Count;
    end_iter.Value = value;
    return end_iter;
}

Range_iterator::Range_iterator(class Range const &range)
        : Range{const_cast<class Range *>(&range)}, Value{range.Start} {}

Range_iterator &Range_iterator::operator=(const class Range_iterator &iter)
        = default;

long long &Range_iterator::operator*()
{
    return this->Value;
}

Range_iterator &Range_iterator::operator++()
{
    this->Value += this->Range->Count;
    return *this;
}

const Range_iterator Range_iterator::operator++(int) const
{
    Range_iterator res {*this->Range};
    this->Value += this->Range->Count;
    return res;
}

bool Range_iterator::operator<(const Range_iterator &op) const
{
    if (static_cast<void*>(this->Range) != static_cast<void *>(op.Range)) throw;
    return this->Value<op.Value;
}

bool Range_iterator::operator>(const Range_iterator &op) const
{
    if (static_cast<void*>(this->Range) != static_cast<void *>(op.Range)) throw;
    return this->Value>op.Value;
}

bool Range_iterator::operator<=(const Range_iterator &op) const
{
    if (static_cast<void*>(this->Range) != static_cast<void *>(op.Range)) throw;
    return this->Value<=op.Value;
}

bool Range_iterator::operator>=(const Range_iterator &op) const
{
    if (static_cast<void*>(this->Range) != static_cast<void *>(op.Range)) throw;
    return this->Value>=op.Value;
}

bool Range_iterator::operator==(const Range_iterator &op) const
{
    if (static_cast<void*>(this->Range) != static_cast<void *>(op.Range)) throw;
    return this->Value==op.Value;
}

bool Range_iterator::operator!=(const Range_iterator &op) const
{
    if (static_cast<void*>(this->Range) != static_cast<void *>(op.Range)) throw;
    return this->Value!=op.Value;
}


#endif //DATASTRUCTURE_RANGER_HPP
