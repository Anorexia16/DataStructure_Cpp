#ifndef DATASTRUCTURE_HUFFMAN_CODE_HPP
#define DATASTRUCTURE_HUFFMAN_CODE_HPP

#include "../Assistance/Storage_Unit.hpp"
#include "Leftist_Tree.hpp"
#include <utility>
#include <vector>
#include <map>

class Huffman_Tree
{
protected:
    struct Huffman_Node {
        Huffman_Node(size_t const &fre, std::string name)
                :Frequent{fre}, Word{std::move(name)}, Father{}, Left{nullptr}, Right{nullptr} {}

        size_t Frequent;

        std::string Word{};

        Huffman_Node *Father;

        Huffman_Node *Right;

        Huffman_Node *Left;
    };

    mutable std::map<std::string, Huffman_Node *> Map;

    Huffman_Node *Root;

public:
    explicit Huffman_Tree(std::map<std::string, size_t> const &);

    static Huffman_Node &Huffman_merge(Huffman_Node &, Huffman_Node &, std::vector<std::string> const &);

    static std::map<std::string, std::string> Huffman_Chart(std::map<std::string, size_t> const &);

    [[nodiscard]] std::string locate(std::string const &) const;
};

Huffman_Tree::Huffman_Tree(const std::map<std::string, size_t> &frequent)
: Map{}, Root{nullptr}
{
    Leftist_Tree<size_t> _storage_tree {true};
    std::multimap<size_t, Huffman_Node *> _node_map;
    std::vector<std::string> _vec {};
    Huffman_Node *_source;

    _vec.reserve(frequent.size());
    for(auto const &iter:frequent) _vec.emplace_back(iter.first);

    for(auto _iter = frequent.begin(); _iter != frequent.end(); ++_iter)
    {
        _storage_tree.insert(_iter->second);
        _source = new Huffman_Node{_iter->second, _iter->first};
        _node_map.insert(std::make_pair(_iter->second, _source));
        Map.insert(std::make_pair(_iter->first, _source));
    }

    size_t _right_s;
    size_t _left_s;
    Huffman_Node *_node;

    while (_node_map.size() != 1)
    {
        _left_s = _storage_tree.top();
        _storage_tree.pop();
        _right_s = _storage_tree.top();
        _storage_tree.pop();
        _node = &Huffman_Tree::Huffman_merge(*_node_map.find(_left_s)->second, *_node_map.find(_right_s)->second, _vec);
        _storage_tree.insert(_node->Frequent);
        _node_map.erase(_node_map.find(_left_s));
        _node_map.erase(_node_map.find(_right_s));
        _node_map.insert(std::make_pair(_node->Frequent, _node));
    }
    Root = _node_map.begin()->second;
}

Huffman_Tree::Huffman_Node &Huffman_Tree::Huffman_merge(Huffman_Node &_a, Huffman_Node &_b, std::vector<std::string> const &vec)
{
    Huffman_Node &_res = *new Huffman_Node {_a.Frequent + _b.Frequent, _b.Word + _a.Word};
    Huffman_Node *_ap = &_a, *_bp = &_b;
    for (;;_ap = _ap->Left) if (_ap->Left == nullptr) break;
    for (;;_bp = _bp->Left) if (_bp->Left == nullptr) break;
    auto _ap_pos = std::find(vec.begin(), vec.end(), _ap->Word) - std::begin(vec);
    auto _bp_pos = std::find(vec.begin(), vec.end(), _bp->Word) - std::begin(vec);
    if (_ap_pos < _bp_pos)
    {
        _res.Left = &_a;
        _res.Right = &_b;
        _a.Father = &_res;
        _b.Father = &_res;
    } else {
        _res.Left = &_b;
        _res.Right = &_a;
        _a.Father = &_res;
        _b.Father = &_res;
    }
    return _res;
}

std::string Huffman_Tree::locate(const std::string &s) const
{
    std::string _res {};
    std::vector<size_t> _path {};
    for (const Huffman_Node* node = this->Map[s];node->Father != nullptr ; node = node->Father) {
        _path.template emplace_back(node->Father->Left == node? 0 : 1);
    }
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
