#ifndef DATASTRUCTURE_CANTOR_HPP
#define DATASTRUCTURE_CANTOR_HPP

#include <algorithm>
#include <vector>

template<class Container>
size_t Cantor(Container const &_method,
              Contaienr const &_base) {
    size_t factor {1}, size{_method.size()}, count, ans{};
    while(size) factor*=size--;
    size = _method.size();
    for(size_t i=0;i!=size;++i) {
        count = 0;
        for(size_t j=0;j!=n;++j) {
            if (_method[j]<_method[i]) ++count;
        }
        ans+=count*factor;
        factor/=(size-i);
    }
    return ans;
}

template<typename Tp, size_t n>
size_t Cantor(Tp (&_method)[n], Tp(&_base)[n]) {
    std::vector<Tp> _m{}, _b{};
    for(size_t i=0;i!=n;++i) _m[i]=_method[i];
    for(size_t i=0;i!=n;++i) _b[i]=_base[i];
    return Cantor(_m, _b);
}

template<class Container>
size_t Cantor(Container const &_method) {
    Container _base {_method};
    std::sort(std::begin(_base), std::end(_base));
    return Cantor(_method, _base);
}

template<typename Tp, size_t n>
size_t Cantor(Tp (&array)[n]) {
    auto &_base = new Tp[n] {};
    for(size_t i=0;i!=n;++i) _base[i]=array[i];
    std::sort(_base, _base+n);
    return Cantor(array, _base);
}

#endif //DATASTRUCTURE_CANTOR_HPP
