#ifndef DATASTRUCTURE_HUFFMAN_CODE_HPP
#define DATASTRUCTURE_HUFFMAN_CODE_HPP

#include <algorithm>
#include <utility>
#include <vector>
#include <map>

template<size_t t>
constexpr bool is_multi = t>1;

class Huffman_Tree
{
protected:
    struct Huffman_Node {
        explicit Huffman_Node(size_t const &fre)
                :Frequent{fre}, Father{nullptr}, Left{nullptr}, Right{nullptr} {}

        size_t Frequent;

        Huffman_Node *Father;

        Huffman_Node *Right;

        Huffman_Node *Left;
    };

    mutable std::map<std::string, Huffman_Node *> Map;

    mutable std::map<std::string, size_t> Fre;

    Huffman_Node *Root;

public:
    explicit Huffman_Tree(std::map<std::string, size_t> const &);

    static Huffman_Node &Huffman_merge(Huffman_Node &, Huffman_Node &);

    static std::map<std::string, std::string> Huffman_Chart(std::map<std::string, size_t> const &);

    static size_t WPL(std::map<std::string, size_t> const &);

    size_t WPL() const;

    [[nodiscard]] std::string locate(std::string const &) const;
};

Huffman_Tree::Huffman_Tree(const std::map<std::string, size_t> &frequent)
:Map{}, Root{nullptr}, Fre{frequent}
{
    std::vector<ssize_t> _min_weight {};
    std::multimap<size_t, Huffman_Node *> _node_map;
    std::vector<std::string> _name_sorter {};
    Huffman_Node *_source;

    _name_sorter.reserve(frequent.size());
    _min_weight.reserve(frequent.size());
    for(auto const &iter:frequent) _name_sorter.emplace_back(iter.first);

    for(const auto & _iter : frequent)
    {
        _min_weight.emplace_back(-_iter.second);
        _source = new Huffman_Node{_iter.second};
        _node_map.insert({_iter.second, _source});
        Map.insert({_iter.first, _source});
    }

    ssize_t _right_s;
    ssize_t _left_s;
    Huffman_Node *_node;

    std::make_heap(std::begin(_min_weight), std::end(_min_weight));
    while (true)
    {
        _left_s = _min_weight.front();
        std::pop_heap(std::begin(_min_weight), std::end(_min_weight));
        _min_weight.pop_back();
        _right_s = _min_weight.front();
        std::pop_heap(std::begin(_min_weight), std::end(_min_weight));
        _min_weight.pop_back();
        _node = &Huffman_Tree::Huffman_merge(*_node_map.find(-_left_s)->second, *_node_map.find(-_right_s)->second);
        _min_weight.emplace_back(-_node->Frequent);
        std::make_heap(std::begin(_min_weight), std::end(_min_weight));
        _node_map.erase(_node_map.find(-_left_s));
        _node_map.erase(_node_map.find(-_right_s));
        if(_node_map.empty()) break;
        _node_map.insert({_node->Frequent, _node});
    }
    Root = _node;
}

Huffman_Tree::Huffman_Node &Huffman_Tree::Huffman_merge(Huffman_Node &_a, Huffman_Node &_b)
{
    Huffman_Node &_res = *new Huffman_Node {_a.Frequent + _b.Frequent};
    _res.Left = &_a;
    _res.Right = &_b;
    _a.Father = &_res;
    _b.Father = &_res;
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
    std::reverse(_res.begin(), _res.end());
    return _res;
}

std::map<std::string, std::string> Huffman_Tree::Huffman_Chart(const std::map<std::string, size_t> &map)
{
    std::map<std::string, std::string> _res{};
    Huffman_Tree _solve {map};
    for(auto const &iter: map) _res[iter.first] = _solve.locate(iter.first);
    return _res;
}

size_t Huffman_Tree::WPL(const std::map<std::string, size_t> &map) {
    return Huffman_Tree(map).WPL();
}

size_t Huffman_Tree::WPL() const {
    size_t _res {};
    for(auto const &iter:Map) _res+= locate(iter.first).size() * Fre[iter.first];
    return _res;
}

template<size_t t, typename = typename
std::enable_if<is_multi<t>>::type>
class Multi_Huffman_Tree {
protected:
    struct Multi_Huffman_Node {
        explicit Multi_Huffman_Node(size_t const &fre)
        :Frequent{fre}, Father{nullptr}, Children{} {};

        size_t Frequent;

        Multi_Huffman_Tree::Multi_Huffman_Node *Father;

        std::array<Multi_Huffman_Tree::Multi_Huffman_Node*, t> Children;
    };

    mutable std::map<std::string, Multi_Huffman_Tree::Multi_Huffman_Node *> Map;

    Multi_Huffman_Tree::Multi_Huffman_Node *Root;

public:
    explicit Multi_Huffman_Tree(std::map<std::string, size_t> const &);

    static Multi_Huffman_Tree::Multi_Huffman_Node &Huffman_merge(std::vector<Multi_Huffman_Node*> const &);


    static std::map<std::string, std::string> Huffman_Chart(std::map<std::string, size_t> const &);

    [[nodiscard]] std::string locate(std::string const &) const;
};

template<size_t t, typename valid>
Multi_Huffman_Tree<t, valid>::Multi_Huffman_Tree(const std::map<std::string, size_t> &frequent)
:Map{}, Root{nullptr} {
    std::vector<ssize_t> _min_weight {};
    std::multimap<size_t, Multi_Huffman_Node*> _node_map {};
    std::vector<std::string> _name {};
    Multi_Huffman_Node *_source;

    _name.reserve(frequent.size());

    for(const auto & _iter : frequent)
    {
        _min_weight.emplace_back(-_iter.second);
        _source = new Multi_Huffman_Node{_iter.second};
        _node_map.insert({_iter.second, _source});
        Map.insert({_iter.first, _source});
    }

    std::array<ssize_t, t> _sum {};
    std::vector<Multi_Huffman_Node*> _nodes {};
    Multi_Huffman_Node *_node;
    size_t _si {}, _counter = 1 + (frequent.size()-1) % (t-1);

    std::make_heap(std::begin(_min_weight), std::end(_min_weight));
    while(true)
    {
        for (;_si!=_counter;)
        {
            _sum[_si++] = _min_weight.front();
            std::pop_heap(std::begin(_min_weight), std::end(_min_weight));
            _min_weight.pop_back();
        }
        _nodes.reserve(_si);
        for (size_t i=0;i!=_si;++i)
        {
            _nodes.template emplace_back(_node_map.template find(-_sum[i])->second);
            _node_map.erase(_node_map.template find(-_sum[i]));
        }
        _node = &Multi_Huffman_Tree::Huffman_merge(_nodes);
        _min_weight.template emplace_back(-_node->Frequent);
        if (_node_map.empty()) break;
        _si = 0;
        _counter = t;
        _nodes.clear();
        _node_map.template insert({_node->Frequent, _node});
    }
    Root = _node;
}

template<size_t t, typename valid>
typename Multi_Huffman_Tree<t, valid>::Multi_Huffman_Node &
Multi_Huffman_Tree<t, valid>::Huffman_merge(const std::vector<Multi_Huffman_Node *> &sorting) {
    if (sorting.size()==1) {
        return *sorting.front();
    }
    auto &_res =  *new Multi_Huffman_Node {0};
    size_t const size = sorting.size();
    for (size_t i=0;i!=size;++i) {
        _res.Children[i] = sorting[i];
        sorting[i]->Father = &_res;
    }
    for (size_t i=0;i!=size&&_res.Children[i]!= nullptr;++i) {
        _res.Frequent += _res.Children[i]->Frequent;
    }
    return _res;
}

template<size_t t, typename valid>
std::map<std::string, std::string>
Multi_Huffman_Tree<t, valid>::Huffman_Chart(const std::map<std::string, size_t> &frequent_map) {
    std::map<std::string, std::string> _res {};
    Multi_Huffman_Tree<t, valid> _tree {frequent_map};
    for (auto const &iter: frequent_map)
        _res[iter.first] = _tree.locate(iter.first);
    return _res;
}

template<size_t t, typename valid>
std::string Multi_Huffman_Tree<t, valid>::locate(const std::string &c) const {
    std::string _res {}, _path;
    size_t _at;
    for (const Multi_Huffman_Node* node = Map[c]; node->Father!= nullptr;node=node->Father) {
        _at = std::find(node->Father->Children.begin(), node->Father->Children.end(), node) -
                node->Father->Children.begin();
        _path = _at<10? static_cast<char>(_at+'0'): static_cast<char>(_at+'a'-10);
        _res.append(_path);
    }
    std::reverse(_res.begin(), _res.end());
    return _res;
}


#endif //DATASTRUCTURE_HUFFMAN_CODE_HPP
