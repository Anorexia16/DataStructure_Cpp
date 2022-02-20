#ifndef DATASTRUCTURE_OI_PROBLEMS_HPP
#define DATASTRUCTURE_OI_PROBLEMS_HPP

#include <Assistance/Storage_Unit.hpp>
#include <Dendroid/Leftist_Tree.hpp>
#include <Dendroid/Winner_Tree.hpp>
#include <Iterations.hpp>
#include <functional>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <string>
#include <random>
#include <array>
#include <map>

typedef unsigned long long size_t;

template<size_t range>
std::array<bool, range+1> &Prime_Sieve() {
    auto &_pool = *new std::array<bool, range+1> {};
    size_t base;

    for (size_t i=2; i<=range; ++i) _pool[i] = true;
    for (size_t i=2; i<=range; ++i) {
        if (_pool[i]) {
            base=2;
            while (base*i<=range)
            {
                _pool[base*i] = false;
                ++base;
            }
        } else {
            continue;
        }
    }
    return _pool;
}

template<typename Tp=int, Iterable_Container Container,
        typename = std::enable_if<std::is_integral_v<Tp>>>
bool is_variable(Container const &vec)
{
    if (vec.index() <= 2) return true;
    Tp max=vec[0]>vec[1]?vec[0]:vec[1],
            min=vec[0]>vec[1]?vec[1]:vec[0];
    for (size_t i=2;i!=vec.index(); ++i)
    {
        if (vec[i]>vec[i-1]&&vec[i]>max||vec[i]<vec[i-1]&&vec[i]<min) {
            return false;
        }
        vec[i]>vec[i-1]?min=vec[i-1]:max=vec[i-1];
    }
    return true;
}

template<typename Tp=int, size_t n,
        typename = std::enable_if<std::is_integral_v<Tp>>>
bool is_variable(Tp const (&arr)[n])
{
    if constexpr (n<=2) return true;
    Tp max = arr[0]>arr[1]?arr[0]:arr[1],
            min = arr[0]>arr[1]?arr[1]:arr[0];
    for (size_t i=2;i!=n;++i)
    {
        if (arr[i]>arr[i-1]&&arr[i]>max||arr[i]<arr[i-1]&&arr[i]<min) {
            return false;
        }
        arr[i]>arr[i-1] ? min = arr[i-1]: max = arr[i-1];
    }
    return true;
}

struct One {
    long long id {};
    long double turns {};
};

template<long long num, long long turns>
std::array<One, num> exp() {
    std::vector<long long> alive, model;
    std::array<One, num> dead{};
    for (long long i=0;i!=num;++i) dead[i].id = i;
    model.reserve(num);
    for(long long i=0;i!=num;++i) model.template emplace_back(i);

    std::random_device rd;
    std::default_random_engine e {rd()};
    std::uniform_int_distribution<long long> ud;
    long long dev, unlucky;
    for (long long i=0;i!=turns;++i) {
        alive = model;
        dev = 0;
        for (long long j=0;j!=num;++j) {
            ud = *new std::uniform_int_distribution<long long> (0, (num-1-dev)/2);
            unlucky = 2*ud(e);
            dead[alive[unlucky]].turns = i==0? j:(dead[alive[unlucky]].turns*i+j)/(i+1);
            alive.erase(alive.begin()+unlucky);
            ++dev;
        }
    }
    return dead;
}

template<size_t n>
std::array<char, n> &solution(std::array<char, n> &arr) {
    size_t tick{}, white{}, blue{};
    for (;tick!=n;++tick) {
        if (arr[tick] == 'r') {
            arr[blue++] = 'w';
            arr[white++] = 'r';
            arr[tick] = 'b';
        } else if (arr[tick] == 'w') {
            arr[blue++] = 'w';
            arr[tick] = 'b';
        }
    }
    return arr;
}

size_t Abs(ssize_t const &num) {
    return num>0 ?num : -num;
}

enum NQ_Optimize {Optimize0, Optimize1, Optimize2};

template<size_t queens, NQ_Optimize=Optimize0>
struct NQ_Func {};

template<size_t queens>
struct NQ_Func
        <queens, Optimize0>
{
    std::array<size_t, queens>
    n_queens()
    {
        std::array<size_t, queens> _platform {};
        constexpr size_t _shape = queens;
        size_t _depth{};
        bool valid;
        while(_depth!=_shape)
        {
            if (_platform[_depth] == _shape)
            {
                _platform[_depth] = 0;
                ++_platform[--_depth];
                continue;
            }
            valid = true;
            for (size_t _i=0;_i!=_depth;++_i)
            {
                if (_platform[_i]==_platform[_depth]||
                    Abs((ssize_t)(_platform[_i])-(ssize_t)(_platform[_depth]))==
                    Abs((ssize_t)(_i)-(ssize_t)(_depth)))
                {
                    valid = false;
                    break;
                }
            }
            valid? ++_depth : ++_platform[_depth];
        }
        return _platform;
    }
};

template<size_t queens>
struct NQ_Func
        <queens, Optimize1>
{
    std::array<size_t, queens>
    n_queens()
    {
        std::array<size_t, queens> _platform {};
        constexpr size_t _shape = queens;
        size_t _depth{};
        bool valid;
        while(_depth!=_shape)
        {
            if (_platform[_depth] == _shape)
            {
                _platform[_depth] = 0;
                ++_platform[--_depth];
                continue;
            }
            valid = true;
            for (size_t _i=0;_i!=_depth;++_i)
            {
                if (_platform[_i]==_platform[_depth]||
                    Abs((ssize_t)(_platform[_i])-(ssize_t)(_platform[_depth]))==
                    Abs((ssize_t)(_i)-(ssize_t)(_depth)))
                {
                    valid = false;
                    break;
                }
            }
            valid? ++_depth : ++_platform[_depth];
        }
        return _platform;
    }
};

template<size_t queens>
struct NQ_Func
        <queens, Optimize2>
{
    std::array<size_t, queens>
    n_queens()
    {
        std::array<size_t, queens> _platform {};
        std::array<bool, queens> _filled {};
        constexpr size_t _shape = queens;
        size_t _depth{};
        bool valid;
        while(_depth!=_shape) {
            if (_platform[_depth] == _shape)
            {
                _platform[_depth] = 0;
                --_depth;
                _filled[_platform[_depth]] = false;
                ++_platform[_depth];
                continue;
            }
            if (_filled[_platform[_depth]])
            {
                ++_platform[_depth];
                continue;
            }
            valid = true;
            for (size_t _i=0;_i!=_depth;++_i)
            {
                if (_platform[_i]==_platform[_depth]||
                    Abs((ssize_t)(_platform[_i])-(ssize_t)(_platform[_depth]))==
                    Abs((ssize_t)(_i)-(ssize_t)(_depth)))
                {
                    valid = false;
                    break;
                }
            }
            if (valid) _filled[_platform[_depth++]]=true;
            else ++_platform[_depth];
        }
        return _platform;
    }
};

using Machine_Info = KW_Pair<double, size_t>;

std::vector<std::vector<size_t>> solve_lpt(std::vector<double> const &time_chart, size_t const &machine_num)
{
    Leftist_Tree<Machine_Info> _machine_time = make_LT<Machine_Info>();
    Machine_Info machine_instance;
    for (size_t machine = 0; machine != machine_num; ++machine)
    {
        machine_instance = Machine_Info {0, machine};
        _machine_time.insert(machine_instance);
    }
    std::vector<KW_Pair<double, size_t>> _task_info {};

    _task_info.reserve(time_chart.size());
    for (size_t i = 0; i < time_chart.size(); ++i) _task_info.emplace_back(KW_Pair<double, size_t> {time_chart[i], i});
    Leftist_Tree<KW_Pair<double, size_t>> _longest_task = make_LT<KW_Pair<double, size_t>>(_task_info, false);
    std::vector<std::vector<size_t>> res {};

    for (size_t _index = 0; _index != machine_num; ++_index) res.template emplace_back(std::vector<size_t>{});

    for(size_t _index = 0; _index!=time_chart.size() ; ++_index)
    {
        res[_machine_time.top().Value].emplace_back(_longest_task.top().Value);
        _machine_time.insert(Machine_Info {_machine_time.top().Key + _longest_task.top().Key, _machine_time.top().Value});
        _machine_time.pop();
        _longest_task.pop();
    }
    return res;
}

template <typename Tp>
bool standard_close_to(Tp const &lhv, Tp const &rhv)
{
    Tp temp = rhv;
    return lhv==++temp;
}

template<typename cls, template<typename elem, typename = std::allocator<elem>> class Cont>
bool Legal_4Stack(Cont<cls> const &container)
{
    cls min {};
    cls var = *std::begin(container);
    cls max = *std::begin(container);
    ++min;

    decltype(auto) func = std::function<bool(cls const &, cls const &)>{standard_close_to<cls>};
    for(auto iterator=std::begin(container);iterator!=std::end(container);++iterator)
    {
        if (var == min)
        {
            var = *(iterator++);
            min = ++max;
        }
        if (func(var, *iterator))
        {
            --var;
        } else if (*iterator > var) {
            max = std::max(*iterator, max);
        } else if (*iterator < var) {
            return false;
        }
    }
    return true;
}

class FP_Algorithm {

    template<class Container>
    static std::vector<std::vector<size_t>> FF(Container &&, size_t const &, size_t const &);

    template<class Container>
    static std::vector<std::vector<size_t>> BF(Container &&, size_t const &, size_t const &);

    template<class Container>
    static std::vector<std::vector<size_t>> FFD(Container &&, size_t const &, size_t const &);

    template<class Container>
    static std::vector<std::vector<size_t>> BFD(Container &&, size_t const &, size_t const &);

    template<class Container>
    std::vector<std::vector<size_t>> AA(Container &&, size_t const &);
};

template<class Container>
std::vector<std::vector<size_t>> FP_Algorithm::FF(Container &&cont, const size_t &nums, const size_t &capacity)
{
    std::vector<size_t> _capacity(nums, capacity);
    size_t const tasks = cont.index();
    std::vector<std::vector<size_t>> _res {};

    for(size_t _item = 0; _item != tasks; ++_item) {
        for(size_t _cont_idx = 0; _cont_idx != nums; ++_cont_idx) {
            if (cont[_item] < _capacity[_cont_idx]) {
                _capacity[_cont_idx] -= cont[_item];
                _res[_cont_idx].template emplace_back(_item);
            }
        }
    }
    return _res;
}

template<class Container>
std::vector<std::vector<size_t>> FP_Algorithm::BF(Container &&cont, const size_t &nums, const size_t &capacity)
{
    std::map<std::string , size_t> _winner_tree_map {};
    size_t const _size = cont.index();
    std::vector<std::vector<size_t>> _res {};

    for(size_t i = 0; i!= nums; ++i) {
        _winner_tree_map[std::to_string(i)] = capacity;
    }

    Winner_Tree _winner {_winner_tree_map};
    size_t _idx;

    for(size_t _item = 0; _item !=_size; ++_item) {
        _idx = _winner.player_find(_winner.winner());
        _winner.change(_idx, -cont[_item]);
        _res[_idx].template emplace_back(_item);
    }
    return _res;
}

template<class Container>
std::vector<std::vector<size_t>> FP_Algorithm::FFD(Container &&cont, const size_t &nums, const size_t &capacity)
{
    std::vector<size_t> _capacity(nums, capacity);
    size_t const tasks = cont.index();
    std::vector<std::vector<size_t>> _res {};

    Leftist_Tree<KW_Pair<size_t, size_t>> _tree {LT_Index::Height, false};
    for(size_t i = 0; i!= tasks; ++i) {
        _tree.insert(KW_Pair<size_t, size_t> {cont[i], i});
    }

    for(size_t _item = _tree.top().Key; !_tree.empty(); _tree.pop()) {
        for(size_t _cont_idx = 0; _cont_idx != nums; ++_cont_idx) {
            if (_item < _capacity[_cont_idx]) {
                _capacity[_cont_idx] -= _item;
                _res[_cont_idx].template emplace_back(_tree.top().Value);
            }
        }
    }
    return _res;

}

template<class Container>
std::vector<std::vector<size_t>> FP_Algorithm::BFD(Container &&cont, const size_t &nums, const size_t &capacity)
{
    std::map<std::string , size_t> _winner_tree_map {};
    size_t const _size = cont.index();
    std::vector<std::vector<size_t>> _res {};

    Leftist_Tree<KW_Pair<size_t, size_t>> _tree {false};
    for(size_t i = 0; i!= _size; ++i) {
        _tree.insert(KW_Pair<size_t, size_t> {cont[i], i});
    }

    for(size_t i = 0; i!= nums; ++i) {
        _winner_tree_map[std::to_string(i)] = capacity;
    }

    Winner_Tree _winner {_winner_tree_map};
    size_t _idx;

    for(size_t _item = _tree.top().Key; !_tree.empty(); _tree.pop()) {
        _idx = _winner.player_find(_winner.winner());
        _winner.change(_idx, _item);
        _res[_idx].template emplace_back(_tree.top().Value);
    }
    return _res;

}

template<class Container>
std::vector<std::vector<size_t>> FP_Algorithm::AA(Container &&cont, size_t const &capacity)
{
    size_t const _size = cont.index();
    std::vector<size_t> _capacities {};
    std::vector<std::vector<size_t>> _res {};
    size_t _i = 0;
    bool _found;

    for(size_t _idx = 0; _idx != _size; ++_idx) {
        size_t &_temp = cont[_idx];
        _found = false;

        for(size_t _ci = _i; _ci!= _capacities.size(); ++_ci, ++_i) {
            _i = _capacities.empty() ? 0 : _i % _capacities.size();
            if (_temp < _capacities[_ci]) {
                _capacities[_ci] -= _temp;
                _res[_ci].template emplace_back(_idx);
                _found = true;
                break;
            }
        }

        if (!_found) {
            _res.template emplace_back(std::vector<size_t>{_idx});
            _temp > capacity ? throw : _capacities.template emplace_back(capacity-_temp);
            ++_i;
        }
    }
    return _res;
}


template<class Container>
size_t Cantor(Container const &_method,
              Container const &_base) {
    size_t factor {1}, size{_method.size()}, count, ans{};
    while(size) factor*=size--;
    size = _method.size();
    for(size_t i=0;i!=size;++i) {
        count = 0;
        for(size_t j=0;j!=i;++j) {
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

#endif //DATASTRUCTURE_OI_PROBLEMS_HPP
