#ifndef DATASTRUCTURE_RANGE_ITERATOR_HPP
#define DATASTRUCTURE_RANGE_ITERATOR_HPP

class Range;

class Range_iterator: std::iterator<std::forward_iterator_tag, long long> {
private:
    friend class Range;

    Range* Range;

    long long Value;
public:
    explicit Range_iterator(class Range const &);

    Range_iterator &operator=(const class Range_iterator&);

    long long &operator *();

    Range_iterator &operator++();

    const Range_iterator operator++(int) const;

    bool operator<(Range_iterator const &) const;

    bool operator>(Range_iterator const &) const;

    bool operator<=(Range_iterator const &) const;

    bool operator>=(Range_iterator const &) const;

    bool operator==(Range_iterator const &) const;

    bool operator!=(Range_iterator const &) const;
};


#endif //DATASTRUCTURE_RANGE_ITERATOR_HPP
