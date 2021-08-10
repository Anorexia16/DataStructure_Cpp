#ifndef DATASTRUCTURE_QUICK_FIND_ALGORITHM_HPP
#define DATASTRUCTURE_QUICK_FIND_ALGORITHM_HPP

#include <cstdlib>

template<class cls>
concept Iterable_Container = requires (cls instance)
{
    instance.operator[](0);
    instance.size();
};

template<class cls>
concept Iterable_Iterator = requires (cls iterator)
{
    cls(iterator);
    iterator.operator=(iterator);
    iterator.operator-(-1);
    ++iterator;
    --iterator;
};

template<typename Tp, Iterable_Container Container>
Tp quick_find(Container &container, size_t pos) {
    if (pos >= container.size()) return Tp {};
    Tp extra {container[0]};
    size_t bi{}, ei{container.size()-1}, b{}, e{container.size()-1};
    bool dir {true};
    while(true) {
        if (dir) {
            if (container[e] < extra) {
                container[b++] = container[e];
                dir = false;
            } else {
                --e;
            }
        } else {
            if (container[b] > extra) {
                container[e--] = container[b];
                dir = true;
            } else {
                ++b;
            }
        }
        if (b==e) {
            if (b > pos) {
                ei = b - 1;
                b = bi;
                e = ei;
            } else if (b < pos) {
                bi = b + 1;
                b = bi;
                e = ei;
            } else return extra;
        }
    }
}

template<typename Tp, Iterable_Iterator iterator>
Tp quick_find(iterator begin, iterator end, size_t pos) {
    if (pos >= end-begin) return Tp {};
    Tp extra {*(begin)};
    size_t bi{}, ei{end-begin-1}, b{}, e{end-begin-1};
    bool dir {true};
    while(true) {
        if (dir) {
            if (*(begin+e) < extra) {
                *(begin+b++) = *(begin+e);
                dir = false;
            } else {
                --e;
            }
        } else {
            if (*(begin+b) > extra) {
                *(begin+e--) = *(begin+b);
                dir = true;
            } else {
                ++b;
            }
        }
        if (b==e) {
            if (b > pos) {
                ei = b - 1;
                b = bi;
                e = ei;
            } else if (b < pos) {
                bi = b + 1;
                b = bi;
                e = ei;
            } else return extra;
        }
    }
}

#endif //DATASTRUCTURE_QUICK_FIND_ALGORITHM_HPP
