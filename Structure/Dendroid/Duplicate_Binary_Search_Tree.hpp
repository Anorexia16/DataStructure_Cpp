#ifndef DATASTRUCTURE_DUPLICATE_BINARY_SEARCH_TREE_HPP
#define DATASTRUCTURE_DUPLICATE_BINARY_SEARCH_TREE_HPP

#include <deque>
#include <iostream>
#include "../Assistance/Storage_Unit.hpp"
#include "Binary_Tree.hpp"

template<typename K_Tp, typename V_Tp>
class Duplicate_Binary_Search_Tree
{
public:
    using DBST_Node = Binary_Node<Pair_Unit<K_Tp, V_Tp>>;

    using DBST_Item = Pair_Unit<K_Tp, V_Tp>;

    explicit Duplicate_Binary_Search_Tree(std::vector<DBST_Item> const &);

    std::vector<DBST_Node *> search(K_Tp const &) const;

    std::vector<DBST_Item> ascend() const;

    void insert(DBST_Item const &);

    void insert(DBST_Node &);

    void erase(K_Tp const &);

protected:
    DBST_Node *Head;

private:
    std::pair<DBST_Node *, DBST_Node *> search_between(K_Tp const &) const;

    static void destroy(DBST_Node &);
};

template<typename K_Tp, typename V_Tp>
Duplicate_Binary_Search_Tree<K_Tp, V_Tp>::Duplicate_Binary_Search_Tree(std::vector<DBST_Item> const &vec)
        :Head{nullptr}
{
    for (auto const &_item : vec)
    {
        this->insert(_item);
    }
}

template<typename K_Tp, typename V_Tp>
void Duplicate_Binary_Search_Tree<K_Tp, V_Tp>::insert(const Duplicate_Binary_Search_Tree::DBST_Item &item)
{
    auto *_node = new DBST_Node {item};
    this->insert(*_node);
}

template<typename K_Tp, typename V_Tp>
void Duplicate_Binary_Search_Tree<K_Tp, V_Tp>::insert(Duplicate_Binary_Search_Tree::DBST_Node &node)
{
    node.sink();
    if (this->Head == nullptr)
    {
        this->Head = &node;
        return;
    }
    K_Tp &_key = node.value().Key;
    DBST_Node *_pos;
    int _condition;
    for(DBST_Node *_ptr = this->Head;;)
    {
        if (_key <= _ptr->Element.Key)
        {
            if (_ptr->Left_Child != nullptr) _ptr = _ptr->Left_Child;
            else {
                _pos = _ptr;
                _condition = -1;
                break;
            }
        } else {
            if (_ptr->Right_Child != nullptr) _ptr = _ptr->Right_Child;
            else {
                _pos = _ptr;
                _condition = 1;
                break;
            }
        }
    }

    size_t depth = 2;

    if (_condition == 1) {
        _pos->Right_Child = &node;
        node.Father = _pos;
        for (DBST_Node *broad_cast = _pos;; broad_cast = broad_cast->Father, ++depth)
        {
            broad_cast->Size += 1;
            broad_cast->Depth = std::max(broad_cast->Depth, depth);
            if (broad_cast->Father == nullptr) break;
        }
    } else {
        _pos->Left_Child = &node;
        node.Father = _pos;
        for (DBST_Node *broad_cast = _pos;; broad_cast = broad_cast->Father, ++depth)
        {
            broad_cast->Size += 1;
            broad_cast->Depth = std::max(broad_cast->Depth, depth);
            if (broad_cast->Father == nullptr) break;
        }
    }
}

template<typename K_Tp, typename V_Tp>
void Duplicate_Binary_Search_Tree<K_Tp, V_Tp>::erase(const K_Tp &key)
{
    auto *_ptr = new DBST_Node {this->search(key)};
    bool _dir;
    switch (_ptr->Child_num)
    {
        case 0:
            if (_ptr->Father != nullptr)
            {
                switch (_ptr->locate())
                {
                    case 0:
                        _ptr->Father->Left_Child = nullptr;
                        break;
                    case 1:
                        _ptr->Father->Right_Child = nullptr;
                        break;
                    default:
                        throw;
                }
            } else {
                this->Head = nullptr;
            }
            break;
        case 1:
            _dir = _ptr->Left_Child != nullptr;
            if (_ptr->Father != nullptr) {
                switch (_ptr->locate())
                {
                    case 0:
                        _ptr->Father->Left_Child = _dir ? _ptr->Left_Child : _ptr->Right_Child;
                        _dir? _ptr->Left_Child->Father = _ptr->Father : _ptr->Right_Child->Father = _ptr->Father;
                        ~(*_ptr);
                        break;
                    case 1:
                        _ptr->Father->Right_Child = _dir ? _ptr->Left_Child : _ptr->Right_Child;
                        _dir? _ptr->Left_Child->Father = _ptr->Father : _ptr->Right_Child->Father = _ptr->Father;
                        ~(*_ptr);
                        break;
                    default:
                        throw;
                }
            } else {
                _dir ? this->Head = _ptr->Left_Child: this->Head = _ptr->Right_Child;
            }
            break;
        case 2:
            Duplicate_Binary_Search_Tree::destroy(*_ptr);
            break;
        default:
            throw;
    }
}

template<typename K_Tp, typename V_Tp>
std::vector<typename Duplicate_Binary_Search_Tree<K_Tp, V_Tp>::DBST_Node *> Duplicate_Binary_Search_Tree<K_Tp, V_Tp>::search(K_Tp const &key) const
{
    if (this->Head == nullptr) return std::vector<DBST_Node *> {};
    size_t const _size = this->Head->Size;
    std::deque<DBST_Node *> _cache {};
    std::vector<DBST_Node *> _res {};
    DBST_Node *_node {this->Head};
    size_t in_range = 0;


    for(size_t _idx = 0; _idx != _size; ++_idx)
    {
        switch (_node->Child_num)
        {
            case 2:
                _cache.template emplace_back(_node->Right_Child);
                if (_node->Element.Key == key)
                {
                    _res.template emplace_back(_node);
                    in_range = 1;
                } else if (in_range == 1) {
                    in_range = 2;
                }
                _node = _node->Left_Child;
                break;
            case 1:
                if (_node->Element.Key == key)
                {
                    _res.template emplace_back(_node);
                    in_range = 1;
                } else if (in_range == 1) {
                    in_range = 2;
                }
                _node = _node->Left_Child;
                break;
            default:
                if (_node->Element.Key == key)
                {
                    _res.template emplace_back(_node);
                    in_range = 1;
                } else if (in_range == 1) {
                    in_range = 2;
                }
                _node = &_cache.back();
                _cache.pop_back();
                break;
        }
        if (in_range == 2) break;
    }
    return _res;
}

template<typename K_Tp, typename V_Tp>
std::pair<typename Duplicate_Binary_Search_Tree<K_Tp, V_Tp>::DBST_Node *, typename Duplicate_Binary_Search_Tree<K_Tp, V_Tp>::DBST_Node *> Duplicate_Binary_Search_Tree<K_Tp, V_Tp>::search_between(const K_Tp &key) const
{
    if (this->Head == nullptr) return std::pair<DBST_Node*, DBST_Node*>{nullptr, nullptr};
    std::pair<DBST_Node *, DBST_Node *> _res {};
    K_Tp _temp = this->Head->Element.Key;
    for(DBST_Node *_ptr_iterator {this->Head};;)
    {
        if (_ptr_iterator->Right_Child != nullptr && key > _temp)
        {
            if (key < _ptr_iterator->Right_Child->Element.Key)
            {
                return std::pair<DBST_Node *, DBST_Node *>{_ptr_iterator, _ptr_iterator->Right_Child};
            } else {
                _ptr_iterator = _ptr_iterator->Right_Child;
            }
        } else if (_ptr_iterator->Left_Child != nullptr && key < _temp)
        {
            if (key > _ptr_iterator->Left_Child->Element.Key)
            {
                return std::pair<DBST_Node *, DBST_Node *>{_ptr_iterator->Left_Child, _ptr_iterator};
            } else {
                _ptr_iterator = _ptr_iterator->Left_Child;
            }
        }  else {
            return std::pair<DBST_Node*, DBST_Node*> {_ptr_iterator, nullptr};
        }
    }
}

template<typename K_Tp, typename V_Tp>
std::vector<typename Duplicate_Binary_Search_Tree<K_Tp, V_Tp>::DBST_Item> Duplicate_Binary_Search_Tree<K_Tp, V_Tp>::ascend() const
{
    size_t const _size = this->Head->Size;
    std::deque<DBST_Node *> _cache {};
    std::vector<DBST_Item> _res {};
    DBST_Node *_node {this->Head};

    for(size_t _idx = 0; _idx != _size; ++_idx)
    {
        switch (_node->Child_num)
        {
            case 2:
                _cache.template emplace_back(_node->Right_Child);
                _res.template emplace_back(_node->Element);
                _node = _node->Left_Child;
                break;
            case 1:
                _res.template emplace_back(_node->Element);
                _node = _node->Left_Child;
                break;
            default:
                _res.template emplace_back(_node->Element);
                _node = &_cache.back();
                _cache.pop_back();
                break;
        }
    }
    return _res;
}

template<typename K_Tp, typename V_Tp>
void Duplicate_Binary_Search_Tree<K_Tp, V_Tp>::destroy(Duplicate_Binary_Search_Tree::DBST_Node &node)
{
    if (node.Right_Child != nullptr)
    {
        node.Element = node.Right_Child->Element;
        destroy(node.Right_Child);
    } else if (node.Left_Child != nullptr) {
        node.Element = node.Left_Child->Element;
        destroy(node.Left_Child);
    } else {
        node.sink();
        ~node();
    }
}

template<typename kt, typename vt>
Duplicate_Binary_Search_Tree<kt, vt> make_DBST(std::vector<Pair_Unit<kt ,vt>> const &vec)
{
    return Duplicate_Binary_Search_Tree<kt, vt> {vec};
}

#endif //DATASTRUCTURE_DUPLICATE_BINARY_SEARCH_TREE_HPP
