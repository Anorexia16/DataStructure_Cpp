#ifndef DATASTRUCTURE_INDEXED_BINARY_SEARCH_TREE_HPP
#define DATASTRUCTURE_INDEXED_BINARY_SEARCH_TREE_HPP

#include <deque>
#include <iostream>
#include "../Assistance/Storage_Unit.hpp"
#include "Binary_Tree.hpp"


template<typename K_Tp, typename V_Tp>
class Indexed_Binary_Search_Tree
{
public:
    using IBST_Node = Binary_Node<KW_Pair<K_Tp, V_Tp>>;

    using IBST_Item = KW_Pair<K_Tp, V_Tp>;

    explicit Indexed_Binary_Search_Tree(std::vector<IBST_Item> const &);

    IBST_Node *search(K_Tp const &) const;

    IBST_Item &operator[](size_t const &);

    std::vector<IBST_Item> ascend() const;

    void insert(IBST_Item const &);

    void insert(IBST_Node &);

    void erase(K_Tp const &);

protected:
    IBST_Node *Head;

private:
    std::pair<IBST_Node *, IBST_Node *> search_between(K_Tp const &) const;

    static size_t index(IBST_Node const &);

    static void destroy(IBST_Node &);
};

template<typename K_Tp, typename V_Tp>
Indexed_Binary_Search_Tree<K_Tp, V_Tp>::Indexed_Binary_Search_Tree(std::vector<IBST_Item> const &vec)
        :Head{nullptr}
{
    for (auto const &_item : vec)
    {
        this->insert(_item);
    }
}

template<typename K_Tp, typename V_Tp>
void Indexed_Binary_Search_Tree<K_Tp, V_Tp>::insert(const Indexed_Binary_Search_Tree::IBST_Item &item)
{
    auto *_node = new IBST_Node {item};
    this->insert(*_node);
}

template<typename K_Tp, typename V_Tp>
void Indexed_Binary_Search_Tree<K_Tp, V_Tp>::insert(Indexed_Binary_Search_Tree::IBST_Node &node)
{
    node.sink();
    if (this->Head == nullptr)
    {
        this->Head = &node;
        return;
    }
    K_Tp &_key = node.value().Key;
    IBST_Node *_pos;
    int _condition;
    for(IBST_Node *_ptr = this->Head;;)
    {
        if (_key == _ptr->Element.Key)
        {
            _pos = _ptr;
            _condition = 0;
            break;
        } else if (_key < _ptr->Element.Key) {
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

    switch (_condition)
    {
        case 0:
            _pos->Element.Value = node.Element.Value;
            break;
        case 1:
            _pos->Right_Child = &node;
            node.Father = _pos;
            for(IBST_Node * broad_cast = _pos;; broad_cast = broad_cast->Father, ++depth)
            {
                broad_cast->Size += 1;
                broad_cast->Depth = std::max(broad_cast->Depth, depth);
                if (broad_cast->Father == nullptr) break;
            }
            break;
        default:
            _pos->Left_Child = &node;
            node.Father = _pos;
            for(IBST_Node *broad_cast = _pos;; broad_cast = broad_cast->Father, ++depth)
            {
                broad_cast->Size += 1;
                broad_cast->Depth = std::max(broad_cast->Depth, depth);
                if (broad_cast->Father == nullptr) break;
            }
            break;
    }
}

template<typename K_Tp, typename V_Tp>
void Indexed_Binary_Search_Tree<K_Tp, V_Tp>::erase(const K_Tp &key)
{
    auto *_ptr = new IBST_Node {this->search(key)};
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
            if (_ptr->Father != nullptr)
            {
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
            Indexed_Binary_Search_Tree::destroy(*_ptr);
            break;
        default:
            throw;
    }
}

template<typename K_Tp, typename V_Tp>
typename Indexed_Binary_Search_Tree<K_Tp, V_Tp>::IBST_Node *Indexed_Binary_Search_Tree<K_Tp, V_Tp>::search(K_Tp const &key) const
{
    if (this->Head == nullptr) return nullptr;
    K_Tp _temp = this->Head->Element.Key;
    for (IBST_Node *_ptr_iterator {this->Head};;)
    {
        if (_temp == key)
        {
            return _ptr_iterator;
        } else if (_temp > key) {
            if (_ptr_iterator->Right_Child == nullptr)
            {
                return nullptr;
            } else {
                _ptr_iterator = _ptr_iterator->Right_Child;
            }
        } else {
            if (_ptr_iterator->Left_Child == nullptr)
            {
                return nullptr;
            } else {
                _ptr_iterator = _ptr_iterator->Left_Child;
            }
        }
        _temp = _ptr_iterator->value_c().Key;
    }
}

template<typename K_Tp, typename V_Tp>
std::pair<typename Indexed_Binary_Search_Tree<K_Tp, V_Tp>::IBST_Node *, typename Indexed_Binary_Search_Tree<K_Tp, V_Tp>::IBST_Node *> Indexed_Binary_Search_Tree<K_Tp, V_Tp>::search_between(const K_Tp &key) const
{
    if (this->Head == nullptr) return std::pair<IBST_Node*, IBST_Node*>{nullptr, nullptr};
    std::pair<IBST_Node *, IBST_Node *> _res {};
    K_Tp _temp = this->Head->Element.Key;
    for(IBST_Node *_ptr_iterator {this->Head};;)
    {
        if (_ptr_iterator->Right_Child != nullptr && key > _temp)
        {
            if (key < _ptr_iterator->Right_Child->Element.Key)
            {
                return std::pair<IBST_Node *, IBST_Node *>{_ptr_iterator, _ptr_iterator->Right_Child};
            } else {
                _ptr_iterator = _ptr_iterator->Right_Child;
            }
        } else if (_ptr_iterator->Left_Child != nullptr && key < _temp)
        {
            if (key > _ptr_iterator->Left_Child->Element.Key)
            {
                return std::pair<IBST_Node *, IBST_Node *>{_ptr_iterator->Left_Child, _ptr_iterator};
            } else {
                _ptr_iterator = _ptr_iterator->Left_Child;
            }
        }  else {
            return std::pair<IBST_Node*, IBST_Node*> {_ptr_iterator, nullptr};
        }
    }
}

template<typename K_Tp, typename V_Tp>
std::vector<typename Indexed_Binary_Search_Tree<K_Tp, V_Tp>::IBST_Item> Indexed_Binary_Search_Tree<K_Tp, V_Tp>::ascend() const
{
    size_t const _size = this->Head->Size;
    std::deque<IBST_Node *> _cache {};
    std::vector<IBST_Item> _res {};
    IBST_Node *_node {this->Head};

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
size_t Indexed_Binary_Search_Tree<K_Tp, V_Tp>::index(const Indexed_Binary_Search_Tree::IBST_Node &node)
{
    return node.Left_Child == nullptr ? 0 : node.Left_Child->size();
}

template<typename K_Tp, typename V_Tp>
void Indexed_Binary_Search_Tree<K_Tp, V_Tp>::destroy(Indexed_Binary_Search_Tree::IBST_Node &node)
{
    if (node.Right_Child != nullptr)
    {
        node.value() = node.Right_Child->Element;
        destroy(node.Right_Child);
    } else if (node.Left_Child != nullptr) {
        node.value() = node.Left_Child->Element;
        destroy(node.Left_Child);
    } else {
        node.sink();
        ~node();
    }
}

template<typename K_Tp, typename V_Tp>
typename Indexed_Binary_Search_Tree<K_Tp, V_Tp>::IBST_Item &Indexed_Binary_Search_Tree<K_Tp, V_Tp>::operator[](const size_t &index)
{
    if(index >= this->Head->Size) throw;
    size_t _idx_helper = 0;
    size_t _temp;
    for(IBST_Node *_ptr = this->Head;;)
    {
        _temp = Indexed_Binary_Search_Tree::index(*_ptr);
        if (_temp + _idx_helper == index)
        {
            return _ptr->Element;
        } else if (_temp + _idx_helper > index) {
            _ptr = _ptr->Left_Child;
        } else {
            _idx_helper += _temp + 1;
            _ptr = _ptr->Right_Child;
        }
    }
}

template<typename kt, typename vt>
Indexed_Binary_Search_Tree<kt, vt> make_IBST(std::vector<KW_Pair<kt ,vt>> const &vec)
{
    return Indexed_Binary_Search_Tree<kt, vt> {vec};
}



#endif //DATASTRUCTURE_INDEXED_BINARY_SEARCH_TREE_HPP
