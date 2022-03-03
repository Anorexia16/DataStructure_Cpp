#ifndef DATASTRUCTURE_S02_LINEAR_LIST_CHAIN_HPP
#define DATASTRUCTURE_S02_LINEAR_LIST_CHAIN_HPP

#include "../../Structure/Linear/Chain_Unidirectional_Circle.hpp"
#include "../../Structure/Linear/Chain_Bidirectional_Circle.hpp"
#include <Linear/Chain_Unidirectional.hpp>
#include "chain.hpp"
#include <ostream>
#include <vector>
#include <iterator>

// 01
template<typename cls>
void remove_all(ChainU<cls> &op, cls const &v)
{
    NodeU<cls> *iterator{op.Head};
    for (; iterator->Next != op.Tail;)
    {
        if (iterator->Next->Element == v)
        {
            iterator->Next = iterator->Next->Next;
            --op.Size;
        } else {
            iterator = iterator->Next;
        }
    }
}

// 02
template<typename cls>
void erase_all(ChainU<cls> &op, cls const &v)
{
    NodeU<cls> *iterator{op.Head};
    NodeU<cls> *temp;
    for (; iterator->Next != op.Tail;)
    {
        if (iterator->Next->Element == v)
        {
            temp = iterator->Next;
            iterator->Next = iterator->Next->Next;
            delete (*temp);
            op.resize(op.size() - 1);
        } else {
            iterator = iterator->Next;
        }
    }
}

// 03
template<typename cls>
std::ostream &reverse_output(std::ostream &out, ChainU<cls> const &op)
{
    std::vector<cls> cont;
    NodeU_Iter<cls> ptr{op.head_c()->next_ptr()};
    for (; ptr != op.tail_c(); ++ptr)
    {
        cont.emplace_back(ptr.value_c());
    }
    std::copy(std::rbegin(cont), std::rend(cont), std::ostream_iterator<cls>(out, " "));
    out << std::endl;
    return out;
}

// 04
template<typename cls>
void remove_minimum(ChainU<cls> &op)
{
    if (op.size() == 0) return;
    NodeU<cls> *iter{op.Head};
    NodeU<cls> *record{op.Head};
    cls temp_minimum = op.Head->Next->Element;
    for (; iter->Next != op.Tail; iter = iter->Next)
    {
        if (iter->Element < temp_minimum)
        {
            temp_minimum = iter->Element;
            record = iter;
        }
    }
    record->Next = record->Next->Next;
    --op.Size;
}

// 05
template<typename cls>
void reverse(ChainU<cls> &op)
{
    if (op.Size == 0 || op.size() == 1) return;
    NodeU<cls> *iterator{op.Head->Next};
    NodeU<cls> *front{op.Head};
    NodeU<cls> *after{iterator->Next};
    for (; iterator != op.tail(); ++iterator)
    {
        iterator->Next = front;
        front = iterator;
        iterator = after;
        after = iterator->Next;
    }
}

// 06
template<typename cls>
void sort(ChainU<cls> &op)
{
    if (op.size() == 0 || op.size() == 1) return;
    NodeU<cls> *zone_pointer;
    NodeU<cls> *iterator{op.Head};
    NodeU<cls> *pre_ptr{op.Head};
    cls temp = op.Head->Next->Element;
    for (; iterator->Next != op.Tail; iterator=iterator->Next)
    {
        if (iterator->Next->Element > temp)
        {
            pre_ptr = iterator;
            temp = pre_ptr->Next->Element;
        }
    }

    op.Head->Next = new NodeU<cls>{pre_ptr->Next->Element, op.Head->Next};
    pre_ptr->Next = pre_ptr->Next->Next;
    zone_pointer = op.Head->Next;

    for (; zone_pointer->Next != op.Tail;)
    {
        temp = zone_pointer->Next->Element;
        iterator = zone_pointer;
        pre_ptr = zone_pointer;
        for (; iterator->Next != op.Tail; ++iterator)
        {
            if (iterator->Next->Element > temp)
            {
                pre_ptr = iterator;
                temp = pre_ptr->Next->Element;
            }
        }
        op.Head->Next = new NodeU<cls>{pre_ptr->Next->Element, op.Head->Next};
        pre_ptr->Next = pre_ptr->Next->Next;
    }
}

// 07
template<typename cls>
void remove_during(ChainU<cls> &op, cls const &min, cls const &max)
{
    if (op.size() == 0) return;
    NodeU<cls> *iter{op.Head};
    for (; iter->Next != op.Tail;)
    {
        if (iter->Element < max && iter->Element > min)
        {
            iter->Next = iter->Next->Next;
            --op.Size;
        } else {
            iter = iter->Next;
        }
    }
}

// 08
template<typename cls>
NodeU<cls> research_common(ChainU<cls> const &left,ChainU<cls> const &right)
{
    NodeU<cls> res{cls{}, nullptr};
    size_t D_len = left.size() - right.size();
    NodeU<cls> *li{left.Head->Next};
    NodeU<cls> *ri{right.Head->Next};
    if (D_len > 0)
    {
        for (; D_len != 0; --D_len) li=li->Next;
    } else if (D_len < 0) {
        for (; D_len != 0; ++D_len) ri=ri->Next;
    }
    for (; li->Next!= left.Tail;li=li->Next, ri=ri->Next)
    {
        if (li == ri)
        {
            res = *li;
            break;
        }
    }
    return res;
}

// 09
template<typename cls>
std::ostream &crash_output(std::ostream &out, ChainU<cls> &op)
{
    NodeU<cls> *destroy_iterator{op.Head};
    NodeU<cls> *temp;
    for (; destroy_iterator->Next != op.Tail;)
    {
        out << destroy_iterator->Next->Element;
        temp = destroy_iterator->Next;
        destroy_iterator->Next = destroy_iterator->Next->Next;
        delete (*temp);
    }

    op.resize(0);
    out << std::endl;
    return out;
}

// 10
template<typename cls>
std::pair<ChainU<cls>, ChainU<cls>>
split(ChainU<cls>const &op)
{
    ChainU<cls> left{op.size() / 2 + 1};
    ChainU<cls> right{op.size() / 2 + 1};
    NodeU<cls> *main_branch_iterator{op.Head->Next};
    NodeU<cls> *li{left.Head};
    NodeU<cls> *ri{right.Head};
    bool control = false;
    for (; main_branch_iterator != op.tail_c();main_branch_iterator=main_branch_iterator->Next)
    {
        if (!control)
        {
            li->Next = new NodeU<cls>{main_branch_iterator->Element, li->Next};
            li = li->Next;
        } else {
            ri->Next = new NodeU<cls>{main_branch_iterator->Element, ri->Next};
            ri = ri->Next;
        }
        control = !control;
    }
    return std::pair<ChainU<cls>, ChainU<cls>>{left, right};
}

// 11
template<typename cls>
std::pair<ChainU<cls>, ChainU<cls>>
split_r(ChainU<cls> const &op) {
    ChainU<cls> left{op.size() / 2 + 1};
    ChainU<cls> right{op.size() / 2 + 1};
    NodeU<cls> *main_branch_iterator{op.Head->Next};
    NodeU<cls> *li{left.Head};
    NodeU<cls> *ri{right.Head};
    bool control = false;
    for (; main_branch_iterator != op.tail_c();main_branch_iterator=main_branch_iterator->Next)
    {
        if (!control)
        {
            li->Next = new NodeU<cls>{main_branch_iterator->Element, li->Next};
            li = li->Next;
        } else {
            ri->Next = new NodeU<cls>{main_branch_iterator->Element, ri->Next};
            ri = ri->Next;
        }
        control = !control;
    }
    return std::pair<ChainU<cls>, ChainU<cls>>{left, right};
}

// 12
template<typename cls>
ChainU<cls> &unique(ChainU<cls> &op)
{
    if (op.size() <= 1) return op;
    NodeU<cls> *iterator{op.Head->Next};
    NodeU<cls> *pos{op.Head->Next};
    cls temp = op.Head->Next->Element;

    for (; iterator != op.Tail; iterator=iterator->Next)
    {
        if (iterator->Element != temp)
        {
            temp = iterator->Element;
            if (pos->Next != iterator) pos->Next = iterator;
            pos = pos->Next;
        }
    }
    return op;
}

// 13
template<typename cls>
ChainU<cls> merge(ChainU<cls> const &lhv, ChainU<cls> const &rhv)
{
    ChainU<cls> res{lhv.size() + rhv.size()};
    NodeU<cls> *li{lhv.Head};
    NodeU<cls> *ri{rhv.Head};
    NodeU<cls> *build_iterator{res.Head};
    for (; li->Next!= lhv.Tail &&ri->Next!= rhv.Tail;++build_iterator)
    {
        if (li->Next->Element> ri->Next->Element)
        {
            build_iterator->Next = new NodeU<cls>{ri->Element, build_iterator->Next};
            ri = ri->Next;
        } else {
            build_iterator->Next = new NodeU<cls>{li->Element, build_iterator->Next};
            li = li->Next;
        }
    }

    if (li->Next!= lhv.Tail)
    {
        for (; li->Next!= lhv.Tail; build_iterator=build_iterator->Next)
        {
            build_iterator->Next = new NodeU<cls>{li->Element, build_iterator->Next};
            li = li->Next;
        }
    } else if (ri->Next!= rhv.Tail)
    {
        for (; ri->Next!= rhv.Tail;build_iterator=build_iterator->Next)
        {
            build_iterator->Next = new NodeU<cls>{ri->Element, build_iterator->Next};
            ri = ri->Next;
        }
    }
    return res;
}

// 14
template<typename cls>
ChainU<cls> intersect(ChainU<cls>const &lhv, ChainU<cls> const &rhv)
{
    ChainU<cls> res{lhv.size() + rhv.size()};
    NodeU<cls> *li{lhv.Head->Next};
    NodeU<cls> *ri{rhv.Head->Next};
    NodeU<cls> *build_iterator{res.Head};

    for (; li != lhv.Tail &&ri != rhv.Tail;build_iterator=build_iterator->Next)
    {
        if (li->Element<ri->Element)
        {
            li = li->Next;
        } else if (li->Element > ri->Element) {
            ri = ri->Next;
        } else {
            build_iterator->Next = new NodeU<cls>{ri->Element, build_iterator->Element};
            li = li->Next;
            ri = ri->Next;
        }
    }
    return res;
}

// 15
template<typename cls>
ChainU<cls> intersect_r(ChainU<cls> &&lhv, ChainU<cls> const &rhv)
{
    NodeU<cls> *li{lhv.Head};
    NodeU<cls> *ri{rhv.Head};
    NodeU<cls> *temp;

    for (; li->Next!= lhv.Tail &&ri->Next!= rhv.Tail;)
    {
        if (li->Next->Element< ri->Next->Element)
        {
            temp = li->Next;
            li->Next = li->Next->Next;
            delete (*temp);
            li = li->Next;
        } else if (li->Element > ri->Element) {
            temp = li->Next;
            li->Next = li->Next->Next;
            delete (*temp);
            ri =ri->Next;
        } else {
            li = li->Next;
            ri = ri->Next;
        }
    }
}

// 16
template<typename cls>
bool is_subsequence(ChainU<cls> const &large, ChainU<cls> const &sub)
{
    NodeU<cls> *li{large.Head->Next};
    NodeU<cls> *si{sub.Head->Next};

    for (; li != large.Tail;li = li->Next)
    {
        if (si->Element == li->Element)
        {
            si = si->Next;
            if (si == sub.Tail) return true;
        } else {
            si = NodeU_Iter<cls>{sub.Head->Next};
        }
    }
    return false;
}

// 17
template<typename cls>
bool symmetrical(ChainBC<cls> const &op)
{
    if (op.size()<= 1)
        return true;
    NodeB<cls> *pi{op.Head->Next};
    NodeB<cls> *ni{op.Head->Prev};
    for (;; pi=pi->Next, ni=ni->Prev)
    {
        if (pi->Element != ni->Element)return false;
        if (pi->Next == ni->Prev|| ni == pi->Next)
            break;
    }
    return true;
}

// 18
template<typename cls>
void link(ChainUC<cls> &&lhv, ChainUC<cls> &&rhv)
{
    NodeU<cls> *li{lhv.Head};
    NodeU<cls> *ri{rhv.Head};

    for (; li->Next != lhv.Head; li=li->Next);
    for (; ri->Next != rhv.Head; ri=ri->Next);

    li->Next = rhv.Head->Next;
    ri->Next = lhv.Head;
    lhv.Size = lhv.Size + rhv.Size;
}

// 19
template<typename cls>
void pop_min_circle(ChainUC<cls> &&op)
{
    NodeU<cls> *oi;
    NodeU<cls> *di;
    cls v{};
    NodeU<cls> *ptr;

    for (; op.Head->Next != op.Head;)
    {
        oi = op.Head;
        di = op.Head;
        v = {op.Head->Next->Element};

        for (; oi->Next != op.Head; oi=oi->Next)
        {
            if (v > oi->Next->Element)
            {
                di = oi;
                v = oi->Next->Element;
            }
        }
        ptr = di->Next;
        di->Next = di->Next->Next;
        delete (*ptr);
    }
}

// 20
template<typename Freq_Node_Iter, typename Freq_Chain, typename Freq_Node>
void Locate(Freq_Chain &&op, size_t const &pos)
{
    if (pos > op.index()) throw;
    Freq_Node_Iter scan_iterator{op.front()};
    for (auto iter = 0; iter != pos; ++iter) ++scan_iterator;

    ++(scan_iterator.next_ptr()->Freq);
    int Freq = scan_iterator.next_ptr()->Freq();
    Freq_Node_Iter sort_iterator{op.front()};

    for (; sort_iterator.next_ptr() != op.front(); ++sort_iterator)
    {
        if (sort_iterator->next_ptr().Freq < Freq)
        {
            sort_iterator.link(*new Freq_Node{scan_iterator.next().value_c(), sort_iterator.next_ptr()});
            scan_iterator.link(scan_iterator.next().next());
            break;
        }
    }
    if (sort_iterator.next_ptr() == op.front())
    {
        sort_iterator.link(*new Freq_Node{scan_iterator.next().value_c(), op.front()});
        scan_iterator.link(scan_iterator.next().next());
    }
}

// 21
template<typename cls>
void getR(ChainUC<cls>const &op,size_t const &index)
{
    NodeU<cls> *pre_iter{op.Head};
    NodeU<cls> *aft_iter{op.Head};
    size_t count = index;

    for (; count != 0; --count, pre_iter = pre_iter->Next);
    for (; pre_iter != op.Head;pre_iter=pre_iter->Next, aft_iter=aft_iter->Next);
    return aft_iter->Element;
}

// 22
template<typename cls>
NodeU<cls> &common_begin(ChainUC<cls>const &lhv, ChainUC<cls> const &rhv)
{
    NodeU<cls> *lli{lhv.Head};
    NodeU<cls> *rli{rhv.Head};
    size_t ll = 0, rl = 0;
    for (; lli->Next!= lhv.Head;lli=lli->Next, ++ll);
    for (; rli->Next!= rhv.Head;rli=rli->Next, ++rl);
    NodeU<cls> *li{lhv.Head};
    NodeU<cls> *ri{rhv.Head};
    if (ll > rl) {
        for (auto n = ll - rl;n != 0; --n)
            li = li->Next;
    } else if (ll < rl) {
        for (auto n = rl - ll;n != 0; --n)
            ri = ri->Next;
    }
    for (; li != lhv.head_c();li = li->Next, ri =ri->Next) {
        if (li == ri) return *li;
    }
    throw;
}

// 23
template<typename cls>
ChainUC<cls> &Unique_abs(ChainUC<cls> &&op, size_t const &n)
{
    bool *sets = new bool[n];
    for (auto i = 0; i != n; ++i) sets[i] = false;
    NodeU<cls> *temp;

    for (NodeU<cls> *oi{op.Head}; oi->Next != op.Head; oi=oi->Next)
    {
        if (sets[static_cast<size_t>(abs(oi->Element))])
        {
            temp = oi->Next;
            oi->Next = oi->Next->Next;
            delete (*temp);
        } else { sets[static_cast<size_t>(abs(oi->Element))] = true; }
    }
}

// 24
template<typename cls>
NodeU<cls> *bad_circle(ChainU<cls> const &op)
{
    NodeU<cls> *slow{op.Head};
    NodeU<cls> *fast{op.Head};
    size_t count = 0;
    for (; fast->Next!= op.Tail;slow=slow->Next, fast= fast->Next->Next, ++count)
    {
        if (slow == fast)
            return fast;
    }
    return nullptr;
}

// 25
template<typename cls>
ChainUC<cls> &Cross_Merge(ChainUC<cls> &&op)
{
    if (op.size() <= 2) return op;
    NodeU<cls> *ti{op.Head};
    NodeU<cls> *mi{op.Head};
    size_t size = 0;

    for (; ti->Next != op.Head && ti->Next->Next != op.Head; mi=mi->Next, ti=ti->Next->Next, size += 2);
    if (ti->Next->Next == op.Head)
    {
        ti=ti->Next;
        ++size;
    }
    NodeU<cls> *temp;
    for (; mi->Next != ti; ti=ti->Next)
    {
        temp = mi->Next;
        ti->Next = new NodeU<cls>{mi->Next->Element, ti->Next};
        mi->Next = mi->Next->Next;
        delete (*temp);
    }
    temp = mi->Next;
    ti->Next = new NodeU<cls>{mi->Next->Element, ti->Next};
    mi->Next = mi->Next->Next;
    delete (*temp);

    NodeU<cls> *bi{op.Head->Next};
    for (; mi->Next != op.Head; ++bi)
    {
        temp = mi->Next;
        bi->Next = new NodeU<cls>{mi->Next->Element, ti->Next};
        mi->Next = mi->Next->Next;
        delete (*temp);
    }
    return op;
}

#endif //DATASTRUCTURE_S02_LINEAR_LIST_CHAIN_HPP
