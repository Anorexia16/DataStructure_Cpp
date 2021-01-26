#ifndef DATASTRUCTURE_SHARE_CHAIN_HPP
#define DATASTRUCTURE_SHARE_CHAIN_HPP

#include <map>

template<typename Tp, template<typename >class Cont>
concept has_head = requires (Cont<Tp> const &cont) {cont.Head;};

template<typename Tp, template<typename >class Cont>
concept has_head_elem = requires (Cont<Tp> const &cont) {cont.Container.Head;};

template<typename Tp, typename Tp_Iter, template<typename >class cls>
requires (has_head<Tp, cls>)
class Linear_Groups: virtual public cls<Tp> {
public:
    explicit Linear_Groups(size_t const & = 1);

protected:
    std::map<size_t, Tp_Iter> Container;
};

template<typename Tp, typename Tp_Iter, template<typename >class cls>
requires (has_head<Tp, cls>)
Linear_Groups<Tp, Tp_Iter, cls>::Linear_Groups(const size_t &size)
    :Container{} {
    auto iter=0;
    decltype(auto) ptr = (*new cls{}).head();
    for(; iter != size; ++iter) {

    }
}


#endif //DATASTRUCTURE_SHARE_CHAIN_HPP
