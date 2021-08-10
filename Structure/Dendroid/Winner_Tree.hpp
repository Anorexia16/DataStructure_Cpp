#ifndef DATASTRUCTURE_WINNER_TREE_HPP
#define DATASTRUCTURE_WINNER_TREE_HPP

#include <map>
#include <deque>
#include "Leftist_Tree.hpp"
#include "../Assistance/Storage_Unit.hpp"

typedef Pair_Unit<size_t, std::string> Player;

template<typename Tp>
class Winner_Tree
{
public:
    explicit Winner_Tree(std::map<Tp, size_t> const &, bool const & = false);

    Binary_Node<Player> &operator[](size_t const &);

    Binary_Node<Player> &operator[](std::pair<size_t, size_t>  const &);

    static Binary_Node<Player> &winner_merge(Binary_Node<Player> &, Binary_Node<Player> &, bool const &);

    void replay(size_t const &, size_t const &);

    void change(size_t const &, ssize_t const &);

    [[nodiscard]] size_t player_find(std::string const &) const;

    [[nodiscard]] size_t wins_count(size_t const &) const;

    [[nodiscard]] std::string winner() const;

protected:
    bool const Reverse;

    Leftist_Tree<Player> Tree;

    std::vector<Binary_Node<Player> *> Players;

};

template<typename Tp>
Winner_Tree<Tp>::Winner_Tree(const std::map<Tp, size_t> &map, bool const &reverse)
:Tree{std::vector<Player>{}, LT_Index::Height, reverse}, Players{}, Reverse{reverse}
{
    std::deque<Binary_Node<Player> *> _deque {};
    Binary_Node<Player> *_ptr;

    for (auto &&iter: map)
    {
        _ptr = new Binary_Node<Player>{Player{iter.second, iter.front}};
        Players.template emplace_back(_ptr);
        _deque.template emplace_back(_ptr);
    }

    Binary_Node<Player> *_left;
    Binary_Node<Player> *_right;

    while (_deque.index() != 1)
    {
        _left = _deque.front();
        _deque.pop_front();
        _right = _deque.front();
        _deque.pop_front();
        _ptr = &Winner_Tree::winner_merge(*_left, *_right, reverse);
        _deque.template emplace_back(_ptr);
    }

    Tree.Top = _deque[0];
}

template<typename Tp>
Binary_Node<Player> &Winner_Tree<Tp>::operator[](const size_t &idx)
{
    return *this->Players[idx];
}

template<typename Tp>
Binary_Node<Player> &Winner_Tree<Tp>::operator[](const std::pair<size_t, size_t> &ids)
{
    Binary_Node<Player> &_temp = this->operator[](ids.first);
    for (size_t i = 0; i!=ids.second ; ++i) _temp = _temp.father();
    return _temp;
}

template<typename Tp>
void Winner_Tree<Tp>::replay(const size_t &index, const size_t &value)
{
    if (index > this->Players.size()) throw;
    Binary_Node<Player>  &_new = this->operator[](index);
    _new.value().Key = value;

    while(true)
    {
        if ((!this->Reverse && value < _new.father()->Key) ||
            (this->Reverse && value > _new.father()->Key)) break;
        _new.father().value() = _new.value();
        _new = _new.father();
        if(_new.Father == nullptr) break;
    }

}

template<typename Tp>
void Winner_Tree<Tp>::change(const size_t &index, const ssize_t &value)
{
    auto _now_value = static_cast<size_t>(this->operator[](index)->Key + value);
    this->replay(index, _now_value);
}

template<typename Tp>
std::string Winner_Tree<Tp>::winner() const
{
    return this->Tree.top().Value;
}

template<typename Tp>
size_t Winner_Tree<Tp>::player_find(const std::string &name) const
{
    for(size_t i =0; i != this->Players.size(); ++i)
    {
        if (this->Players[i]->value_c().Value == name) return i;
    }
    return this->Players.size();
}

template<typename Tp>
size_t Winner_Tree<Tp>::wins_count(const size_t &idx) const
{
    if (idx > this->Players.size()) throw;
    size_t _num = 0;
    Binary_Node<Player> const *_new = this->Players[idx];

    while(_new->Father->value_c().Value==_new->value_c().Value)
    {
        _new=_new->Father;
        ++_num;
        if(_new->Father == nullptr) break;

    }
    return _num;
}

template<typename Tp>
Binary_Node<Player> &Winner_Tree<Tp>::winner_merge(Binary_Node<Player> &_a, Binary_Node<Player> &_b, bool const &reverse)
{
    Player *_new;
    if ((!reverse && _a->Key > _b->Key) || (reverse && _a->Key < _b->Key))
    {
        _new = &_a.value();
    } else {
        _new = &_b.value();
    }
    Binary_Node<Player> &_res = *new Binary_Node<Player> {*_new};
    _res.link_d(_a);
    _res.link_d(_b);
    return _res;
}

#endif //DATASTRUCTURE_WINNER_TREE_HPP
