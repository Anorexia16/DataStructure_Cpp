#ifndef DATASTRUCTURE_FEASIBLE_PACKING_HPP
#define DATASTRUCTURE_FEASIBLE_PACKING_HPP

#include <map>
#include <vector>
#include <string>
#include "../../Structure/Assistance/Storage_Unit.hpp"
#include "../../Structure/Dendroid/Leftist_Tree.hpp"
#include "../../Structure/Dendroid/Winner_Tree.hpp"

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
    size_t const tasks = cont.size();
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
    size_t const _size = cont.size();
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
    size_t const tasks = cont.size();
    std::vector<std::vector<size_t>> _res {};

    Leftist_Tree<Pair_Unit<size_t, size_t>> _tree {LT_Index::Height, false};
    for(size_t i = 0; i!= tasks; ++i) {
        _tree.insert(Pair_Unit<size_t, size_t> {cont[i], i});
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
    size_t const _size = cont.size();
    std::vector<std::vector<size_t>> _res {};

    Leftist_Tree<Pair_Unit<size_t, size_t>> _tree {LT_Index::Height, false};
    for(size_t i = 0; i!= _size; ++i) {
        _tree.insert(Pair_Unit<size_t, size_t> {cont[i], i});
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
    size_t const _size = cont.size();
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

#endif //DATASTRUCTURE_FEASIBLE_PACKING_HPP
