#ifndef DATASTRUCTURE_HUFFMAN_CODE_HPP
#define DATASTRUCTURE_HUFFMAN_CODE_HPP

#include "Storage_Unit.hpp"
#include "Leftist_Tree.hpp"
#include <vector>
#include <map>

class Huffman_Tree
{
public:
    typedef Binary_Node<Pair_Unit<size_t, std::string>> Huffman_Node;

    explicit Huffman_Tree(std::map<std::string, size_t> const &);

    static Huffman_Node &Huffman_merge(Huffman_Node &, Huffman_Node &, std::vector<std::string> const &);

    static std::map<std::string, std::string> Huffman_Chart(std::map<std::string, size_t> const &);

    [[nodiscard]] std::string locate(std::string const &) const;


protected:
    mutable std::map<std::string, Huffman_Node *> Map;

    Leftist_Tree<Pair_Unit<size_t, std::string>> Tree;
};

Huffman_Tree::Huffman_Tree(const std::map<std::string, size_t> &frequent)
: Map{}, Tree{std::vector<Pair_Unit<size_t, std::string>>{}, LT_Index::Weight, false}
{
    Leftist_Tree<size_t> _storage_tree {std::vector<size_t>{}, LT_Index::Height,true};
    std::multimap<size_t, Huffman_Node *> _node_map;
    std::vector<std::string> _vec {};
    Huffman_Node *_source;

    _vec.reserve(frequent.size());
    for(auto const &iter:frequent) _vec.emplace_back(iter.first);

    for(auto _iter = frequent.begin(); _iter != frequent.end(); ++_iter)
    {
        _storage_tree.insert(_iter->second);
        _source = new Huffman_Node{Pair_Unit<size_t, std::string>{_iter->second, _iter->first}};
        _node_map.insert(std::make_pair(_iter->second, _source));
        Map.insert(std::make_pair(_iter->first, _source));
        _source->resize(_source->value_c().Key);
    }

    size_t _right_s;
    size_t _left_s;
    Huffman_Node *_node;

    while (_storage_tree.Top->size() != 1)
    {
        _left_s = _storage_tree.top();
        _storage_tree.pop();
        _right_s = _storage_tree.top();
        _storage_tree.pop();
        _node = &Huffman_Tree::Huffman_merge(*_node_map.find(_left_s)->second, *_node_map.find(_right_s)->second, _vec);
        _storage_tree.insert(_node->value_c().Key);
        _node_map.erase(_node_map.find(_left_s));
        _node_map.erase(_node_map.find(_right_s));
        _node_map.insert(std::make_pair(_node->value_c().Key, _node));
    }
    Tree.Top = _node_map.begin()->second;
}

Huffman_Tree::Huffman_Node &Huffman_Tree::Huffman_merge(Huffman_Node &_a, Huffman_Node &_b, std::vector<std::string> const &vec)
{
    Pair_Unit<size_t, std::string> _new {_a.value_c().Key + _b.value_c().Key,
                                         _b.value_c().Value + _a.value_c().Value};
    Huffman_Node &_res = *new Huffman_Node {_new};
    Huffman_Node *_ap = &_a, *_bp = &_b;
    for (;;_ap = _ap->Left_Child) if (_ap->leaves_count() == 0) break;
    for (;;_bp = _bp->Left_Child) if (_bp->leaves_count() == 0) break;
    auto _ap_pos = std::find(vec.cbegin(), vec.cend(), _ap->value_c().Value) - std::begin(vec);
    auto _bp_pos = std::find(vec.cbegin(), vec.cend(), _bp->value_c().Value) - std::begin(vec);
    if (_ap_pos < _bp_pos)
    {
        _res.link_d(_a);
        _res.link_d(_b);
    } else {
        _res.link_d(_b);
        _res.link_d(_a);
    }
    _res.resize(_a.size() + _b.size());
    return _res;
}

std::string Huffman_Tree::locate(const std::string &s) const
{
    std::string _res {};
    std::vector<size_t> _path = this->Map[s]->path();
    _res.reserve(_path.size());
    for(auto const &iter: _path) _res += std::to_string(iter);
    return _res;
}

std::map<std::string, std::string> Huffman_Tree::Huffman_Chart(const std::map<std::string, size_t> &map)
{
    std::map<std::string, std::string> _res{};
    Huffman_Tree _solve {map};
    for(auto const &iter: map) _res[iter.first] = _solve.locate(iter.first);
    return _res;
}


#endif //DATASTRUCTURE_HUFFMAN_CODE_HPP
