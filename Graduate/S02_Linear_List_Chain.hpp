#ifndef DATASTRUCTURE_S02_LINEAR_LIST_CHAIN_HPP
#define DATASTRUCTURE_S02_LINEAR_LIST_CHAIN_HPP

#include "../Structure/Chain_Unidirectional_Circle.hpp"
#include "../Structure/Chain_Bidirectional_Circle.hpp"
#include "../Structure/Chain_Unidirectional.hpp"
#include "../Structure/Chain_Bidirectional.hpp"
#include <ostream>
#include <vector>
#include <iterator>

// 01
template<typename cls>
void remove_all(ChainU<cls> &op, cls const &v) {
    NodeU_Iter<cls> iterator{op.head()};
    for (; iterator.next_ptr() != op.tail();) {
        if (iterator.next().value_c() == v) {
            iterator.link(iterator.next().next());
            op.resize(op.size() - 1);
        } else {
            ++iterator;
        }
    }
}

// 02
template<typename cls>
void erase_all(ChainU<cls> &op, cls const &v) {
    NodeU_Iter<cls> iterator{op.head()};
    NodeU_Iter<cls> temp{};
    for (; iterator.next_ptr() != op.tail();) {
        if (iterator.next().value_c() == v) {
            temp = NodeU_Iter<cls>{iterator.next_ptr()};
            iterator.link(iterator.next().next());
            delete (*temp);
            op.resize(op.size() - 1);
        } else {
            ++iterator;
        }
    }
}

// 03
template<typename cls>
std::ostream &reverse_output(std::ostream &out, ChainU<cls> const &op) {
    std::vector<cls> cont;
    NodeU_Iter<cls> ptr{op.head_c()->next_ptr()};
    for (; ptr != op.tail_c(); ++ptr) {
        cont.emplace_back(ptr.value_c());
    }
    std::copy(std::rbegin(cont), std::rend(cont), std::ostream_iterator<cls>(out, " "));
    out << std::endl;
    return out;
}

// 04
template<typename cls>
void remove_minimum(ChainU<cls> &op) {
    if (op.size() == 0) return;
    NodeU_Iter<cls> iter{op.head()};
    NodeU_Iter<cls> record{op.head()};
    cls temp_minimum = op.head()->next().value_c();
    for (; iter.next_ptr != op.tail(); ++iter) {
        if (iter.value_c() < temp_minimum) {
            temp_minimum = iter.value_c();
            record = iter;
        }
    }
    record.link(record.next().next());
    op.resize(op.size() - 1);
}

// 05
template<typename cls>
void reverse(ChainU<cls> &op) {
    if (op.Size == 0 || op.size() == 1) return;
    NodeU_Iter<cls> iterator{op.head()->next_ptr()};
    NodeU_Iter<cls> front{op.head()};
    NodeU_Iter<cls> after{iterator.next_ptr()};
    for (; iterator != op.tail(); ++iterator) {
        iterator.link(*front);
        front = iterator;
        iterator = after;
        after = iterator.next_ptr();
    }
}

// 06
template<typename cls>
void sort(ChainU<cls> &op) {
    if (op.size() == 0 || op.size() == 1) return;
    NodeU_Iter<cls> zone_pointer{};
    NodeU_Iter<cls> iterator{op.head()};
    NodeU_Iter<cls> pre_ptr{op.head()};
    cls temp = op.head()->next().value_c();
    for (; iterator->next_ptr() != op.tail(); ++iterator) {
        if (iterator->next().value_c() > temp) {
            pre_ptr = iterator;
            temp = pre_ptr->next().value_c();
        }
    }

    op.head()->link(*new NodeU<cls>{pre_ptr->next().value_c(), op.head()->next_ptr()});
    pre_ptr->link(pre_ptr->next().next());
    zone_pointer = NodeU_Iter<cls>{op.head()->next_ptr()};

    for (; zone_pointer->next_ptr() != op.tail();) {
        temp = zone_pointer->next().value_c();
        iterator = zone_pointer;
        pre_ptr = zone_pointer;
        for (; iterator->next_ptr() != op.tail(); ++iterator) {
            if (iterator->next().value_c() > temp) {
                pre_ptr = iterator;
                temp = pre_ptr->next().value_c();
            }
        }
        op.head()->link(*new NodeU<cls>{pre_ptr->next().value_c(), op.head()->next_ptr()});
        pre_ptr->link(pre_ptr->next_ptr()->next());
    }
}

// 07
template<typename cls>
void remove_during(ChainU<cls> &op, cls const &min, cls const &max) {
    if (op.size() == 0) return;
    NodeU_Iter<cls> iter{op.head()};
    for (; iter.next_ptr != op.tail();) {
        if (iter.value_c() < max && iter.value_c() > min) {
            iter.link(iter.next().next());
            op.resize(op.size() - 1);
        } else {
            ++iter;
        }
    }
}

// 08
template<typename cls>
NodeU<cls> research_common(ChainU<cls>
                           const &left,
                           ChainU<cls> const &right
) {
    NodeU<cls> res{cls{}, nullptr};
    size_t D_len = left.size() - right.size();
    NodeU_Iter<cls> li{left.head_c()->next_ptr()};
    NodeU_Iter<cls> ri{right.head_c()->next_ptr()};
    if (D_len > 0) {
        for (; D_len != 0; --D_len) ++li;
    } else if (D_len < 0) {
        for (; D_len != 0; ++D_len) ++ri;
    }
    for (; li.next_ptr()!= left.tail_c();++li, ++ri) {
        if (li == ri) {
            res = *li;
            break;
        }
    }
    return res;
}

// 09
template<typename cls>
std::ostream &crash_output(std::ostream &out, ChainU<cls> &op) {
    NodeU_Iter<cls> destroy_iterator{op.head()};
    NodeU<cls> *temp;
    for (; destroy_iterator.next_ptr() != op.tail();) {
        out << destroy_iterator.next().value_c();
        temp = destroy_iterator.next_ptr();
        destroy_iterator.link(destroy_iterator.next().next());
        delete (*temp);
    }

    op.resize(0);
    out << std::endl;
    return out;
}

// 10
template<typename cls>
std::pair<ChainU<cls>, ChainU<cls>>
split(ChainU<cls>
      const &op) {
    ChainU<cls> left{op.size() / 2 + 1};
    ChainU<cls> right{op.size() / 2 + 1};
    NodeU_Iter<cls> main_branch_iterator{op.head_c()->next_ptr()};
    NodeU_Iter<cls> li{left.head()};
    NodeU_Iter<cls> ri{right.head()};
    bool control = false;
    for (; main_branch_iterator != op.tail_c();++main_branch_iterator) {
        if (!control) {
            li.link(*new NodeU<cls>{main_branch_iterator.value_c(), li.next_ptr()});
            ++li;
        } else {
            ri.link(*new NodeU<cls>{main_branch_iterator.value_c(), ri.next_ptr()});
            ++ri;
        }
        control = !control;
    }
    return std::pair<ChainU<cls>, ChainU<cls>>{left, right};
}

// 11
template<typename cls>
std::pair<ChainU<cls>, ChainU<cls>>
split_r(ChainU<cls>
        const &op) {
    ChainU<cls> left{op.size() / 2 + 1};
    ChainU<cls> right{op.size() / 2 + 1};
    NodeU_Iter<cls> main_branch_iterator{op.head_c()->next_ptr()};
    NodeU_Iter<cls> li{left.head()};
    NodeU_Iter<cls> ri{right.head()};
    bool control = false;
    for (; main_branch_iterator != op.tail_c();++main_branch_iterator) {
        if (!control) {
            li.link(*new NodeU<cls>{main_branch_iterator.value_c(), li.next_ptr()});
            ++li;
        } else {
            ri.link(*new NodeU<cls>{main_branch_iterator.value_c(), ri.next_ptr()});
        }
        control = !control;
    }
    return std::pair<ChainU<cls>, ChainU<cls>>{left, right};
}

// 12
template<typename cls>
ChainU<cls> &unique(ChainU<cls> &op) {
    if (op.size() <= 1) return op;
    NodeU_Iter<cls> iterator{op.head()->next_ptr()};
    NodeU_Iter<cls> pos{op.head()->next_ptr()};
    cls temp = op.head()->next_ptr()->value_c();

    for (; iterator != op.tail(); ++iterator) {
        if (iterator.value_c() != temp) {
            temp = iterator.value_c();
            if (pos.next_ptr() != iterator) pos.link(*iterator);
            ++pos;
        }
    }
    return op;
}

// 13
template<typename cls>
ChainU<cls> merge(ChainU<cls>
                  const &lhv,
                  ChainU<cls> const &rhv
) {
    ChainU<cls> res{lhv.size() + rhv.size()};
    NodeU_Iter<cls> li{lhv.head_c()};
    NodeU_Iter<cls> ri{rhv.head_c()};
    NodeU_Iter<cls> build_iterator{res.head()};
    for (; li.next_ptr()!= lhv.tail_c() &&ri.next_ptr()!= rhv.tail_c();++build_iterator) {
        if (li.next().value_c()> ri.next().value_c()) {
            build_iterator.link(*NodeU<cls>{ri.value_c(), build_iterator.next_ptr()});
            ++ri;
        } else {
            build_iterator.link(*NodeU<cls>{li.value_c(), build_iterator.next_ptr()});
            ++li;
        }
    }

    if (li.next_ptr()!= lhv.tail_c()) {
        for (; li.next_ptr()!= lhv.tail_c(); ++build_iterator) {
            build_iterator.link(*NodeU<cls>{li.value_c(), build_iterator.next_ptr()});
            ++li;
        }
    } else if (ri.next_ptr()!= rhv.tail_c()) {
        for (; ri.next_ptr()!= rhv.tail_c();++build_iterator) {
            build_iterator.link(*NodeU<cls>{ri.value_c(), build_iterator.next_ptr()}
            );
            ++ri;
        }
    }
    return res;
}

// 14
template<typename cls>
ChainU<cls> intersect(ChainU<cls>
                      const &lhv,
                      ChainU<cls> const &rhv
) {
    ChainU<cls> res{lhv.size() + rhv.size()};
    NodeU_Iter<cls> li{lhv.head_c()->next_ptr()};
    NodeU_Iter<cls> ri{rhv.head_c()->next_ptr()};
    NodeU_Iter<cls> build_iterator{res.head()};

    for (; li != lhv.tail_c() &&ri != rhv.tail_c();++build_iterator) {
        if (li.value_c()< ri.value_c()) {
            ++li;
        } else if (li.value_c()> ri.value_c()) {
            ++ri;
        } else {
            build_iterator.link(*NodeU<cls>{ri.value_c(), build_iterator.next_ptr()}
            );
            ++li;
            ++ri;
        }
    }
    return res;
}

// 15
template<typename cls>
ChainU<cls> intersect_r(ChainU<cls> &&lhv, ChainU<cls>
const &rhv) {
    NodeU_Iter<cls> li{lhv.head()};
    NodeU_Iter<cls> ri{rhv.head_c()};
    NodeU<cls> *temp;

    for (; li.next_ptr()!= lhv.tail() &&ri.next_ptr()!= rhv.tail_c();) {
        if (li.next().value_c()< ri.next().value_c()) {
            temp = li.next_ptr();
            li.link(li.next_ptr()->next());
            delete (*temp);
            ++li;
        } else if (li.value_c()> ri.value_c()) {
            temp = li.next_ptr();
            li.link(li.next_ptr()->next());
            delete (*temp);
            ++ri;
        } else {
            ++li;
            ++ri;
        }
    }
}

// 16
template<typename cls>
bool is_subsequence(ChainU<cls>
                    const &large,
                    ChainU<cls> const &sub
) {
    NodeU_Iter<cls> li{large.head_c()->next_ptr()};
    NodeU_Iter<cls> si{sub.head_c()->next_ptr()};

    for (; li != large.tail_c();++li) {
        if (si.value_c()== li.value_c()) {++si;
            if (si == sub.tail_c()) return true;
        } else {
            si = NodeU_Iter<cls>{sub.head_c()->next_ptr()};
        }
    }
    return false;
}

// 17
template<typename cls>
bool symmetrical(ChainBC<cls>
                 const &op) {
    if (op.size()<= 1)
        return true;
    NodeB_Iter<cls> pi{op.head_c()->next_ptr()};
    NodeB_Iter<cls> ni{op.head_c()->prev_ptr()};
    for (;; ++pi, --ni) {
        if (pi.value_c()!= ni.value_c())return false;
        if (pi.next_ptr()== ni.prev_ptr()|| (ni == pi.next_ptr()))
            break;
    }
    return true;
}

// 18
template<typename cls>
void link(ChainUC<cls> &&lhv, ChainUC<cls> &&rhv) {
    NodeU_Iter<cls> li{lhv.head()};
    NodeU_Iter<cls> ri{rhv.head()};

    for (; li.next_ptr() != lhv.head(); ++li);
    for (; ri.next_ptr() != rhv.head(); ++ri);

    li.link(rhv.head()->next());
    ri.link(lhv.head());
    lhv.resize(lhv.size() + rhv.size());
}

// 19
template<typename cls>
void pop_min_circle(ChainUC<cls> &&op) {
    NodeU_Iter<cls> oi{};
    NodeU_Iter<cls> di{};
    cls v{};
    NodeU<cls> *ptr;

    for (; op.head()->next_ptr() != op.head();) {
        oi = NodeU_Iter<cls>{op.head()};
        di = NodeU_Iter<cls>{op.head()};
        v = {op.head()->next().value_c()};

        for (; oi.next_ptr() != op.head(); ++oi) {
            if (v > oi.next_ptr()->value_c()) {
                di = oi;
                v = oi.next_ptr()->value_c();
            }
        }
        ptr = di.next_ptr();
        di.link(di.next_ptr()->next());
        delete (*ptr);
    }
}

// 20
template<typename Freq_Node_Iter, typename Freq_Chain, typename Freq_Node>
void Locate(Freq_Chain &&op, size_t const &pos) {
    if (pos > op.size()) throw;
    Freq_Node_Iter scan_iterator{op.head()};
    for (auto iter = 0; iter != pos; ++iter) ++scan_iterator;

    ++(scan_iterator.next_ptr()->Freq);
    int Freq = scan_iterator.next_ptr()->Freq();
    Freq_Node_Iter sort_iterator{op.head()};

    for (; sort_iterator.next_ptr() != op.head(); ++sort_iterator) {
        if (sort_iterator->next_ptr().Freq < Freq) {
            sort_iterator.link(*new Freq_Node{scan_iterator.next().value_c(), sort_iterator.next_ptr()});
            scan_iterator.link(scan_iterator.next().next());
            break;
        }
    }
    if (sort_iterator.next_ptr() == op.head()) {
        sort_iterator.link(*new Freq_Node{scan_iterator.next().value_c(), op.head()});
        scan_iterator.link(scan_iterator.next().next());
    }
}

// 21
template<typename cls>
void getR(ChainUC<cls>const &op,size_t const &index) {
    NodeU_Iter<cls> pre_iter{op.head_c()};
    NodeU_Iter<cls> aft_iter{op.head_c()};
    size_t count = index;

    for (; count != 0; --count, ++pre_iter);
    for (; pre_iter != op.head_c();++pre_iter, ++aft_iter);
    return aft_iter.value_c();
}

// 22
template<typename cls>
NodeU<cls> &common_begin(ChainUC<cls>const &lhv, ChainUC<cls> const &rhv) {
    NodeU_Iter<cls> lli{lhv.head_c()};
    NodeU_Iter<cls> rli{rhv.head_c()};
    size_t ll = 0, rl = 0;
    for (; lli.next_ptr()!= lhv.head_c();++lli, ++ll);
    for (; rli.next_ptr()!= rhv.head_c();++rli, ++rl);
    NodeU_Iter<cls> li{lhv.head_c()};
    NodeU_Iter<cls> ri{rhv.head_c()};
    if (ll > rl) {
        for (auto n = ll - rl;n != 0; --n)
            ++li;
    } else if (ll < rl) {
        for (auto n = rl - ll;n != 0; --n)++ri;
    }
    for (; li != lhv.head_c();++li, ++ri) {
        if (li == ri) return *li;
    }
    throw;
}

// 23
template<typename cls>
ChainUC<cls> &Unique_abs(ChainUC<cls> &&op, size_t const &n) {
    bool *sets = new bool[n];
    for (auto i = 0; i != n; ++i) sets[i] = false;
    NodeU<cls> *temp;

    for (NodeU_Iter<cls> oi{op.head()}; oi.next_ptr() != op.head(); ++oi) {
        if (sets[static_cast<size_t>(abs(oi.value_c()))]) {
            temp = oi.next_ptr();
            oi.link(oi.next().next());
            delete (*temp);
        } else { sets[static_cast<size_t>(abs(oi.value_c()))] = true; }
    }
}

// 24
template<typename cls>
NodeU<cls> *bad_circle(ChainU<cls>
                       const &op) {
    NodeU_Iter<cls> slow{op.head_c()};
    NodeU_Iter<cls> fast{op.head_c()};
    size_t count = 0;
    for (; fast.next_ptr()!= op.tail_c();++slow, ++fast, ++fast, ++count) {
        if (slow == fast)
            return &*fast;
    }
    return nullptr;
}

// 25
template<typename cls>
ChainUC<cls> &Cross_Merge(ChainUC<cls> &&op) {
    if (op.size() <= 2) return op;
    NodeU_Iter<cls> ti{op.head()};
    NodeU_Iter<cls> mi{op.head()};
    size_t size = 0;

    for (; ti.next_ptr() != op.head() && ti.next().next_ptr() != op.head(); ++mi, ++ti, ++ti, size += 2);
    if (ti.next().next_ptr() == op.head()) {
        ++ti;
        ++size;
    }
    NodeU<cls> *temp;
    for (; mi.next_ptr() != &*ti; ++ti) {
        temp = mi.next_ptr();
        ti.link(*new NodeU<cls>{mi.next().value_c(), ti.next_ptr()});
        mi.link(mi.next().next());
        delete (*temp);
    }
    temp = mi.next_ptr();
    ti.link(*new NodeU<cls>{mi.next().value_c(), ti.next_ptr()});
    mi.link(mi.next().next());
    delete (*temp);

    NodeU_Iter<cls> bi{op.head()->next_ptr()};
    for (; mi.next_ptr() != op.head(); ++bi) {
        temp = mi.next_ptr();
        bi.link(*new NodeU<cls>{mi.next().value_c(), ti.next_ptr()});
        mi.link(mi.next().next());
        delete (*temp);
    }
    return op;
}

#endif //DATASTRUCTURE_S02_LINEAR_LIST_CHAIN_HPP
