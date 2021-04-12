#ifndef DATASTRUCTURE_BINARY_SEARCH_TREE_HPP
#define DATASTRUCTURE_BINARY_SEARCH_TREE_HPP

#include <deque>
#include <iostream>

template<typename K_Tp, typename V_Tp>
class Binary_Search_Tree
{
public:
    struct Binary_Search_Node
    {
        Binary_Search_Node(K_Tp const &, V_Tp const &);

        Binary_Search_Node* Father;

        Binary_Search_Node* Right;

        Binary_Search_Node* Left;

        V_Tp Value;

        K_Tp Key;
    };

    explicit Binary_Search_Tree();

    Binary_Search_Node *search(K_Tp const &) const;

    [[nodiscard]] std::vector<V_Tp> ascend() const;

    void insert(K_Tp const &, V_Tp const &);

    void insert(Binary_Search_Node &);

    void erase(K_Tp const &);

protected:
    Binary_Search_Node *Head;

private:
    std::pair<Binary_Search_Node *, Binary_Search_Node *> search_between(K_Tp const &) const;

    static void destroy(Binary_Search_Node &);
};

template<typename K_Tp, typename V_Tp>
Binary_Search_Tree<K_Tp, V_Tp>::Binary_Search_Node::Binary_Search_Node(const K_Tp &key, const V_Tp &value)
        :Key{key}, Value{value}, Left{nullptr}, Right{nullptr}, Father{nullptr} {}

template<typename K_Tp, typename V_Tp>
Binary_Search_Tree<K_Tp, V_Tp>::Binary_Search_Tree()
:Head{nullptr} {}

template<typename K_Tp, typename V_Tp>
void Binary_Search_Tree<K_Tp, V_Tp>::insert(K_Tp const &key, V_Tp const &value)
{
    auto *_node = new Binary_Search_Node {key, value};
    this->insert(*_node);
}

template<typename K_Tp, typename V_Tp>
void Binary_Search_Tree<K_Tp, V_Tp>::insert(Binary_Search_Tree::Binary_Search_Node &node)
{
    if (this->Head == nullptr) {
        this->Head = &node;
        return;
    }

    K_Tp &_key = node.Element.Key;
    Binary_Search_Node *_pos;
    int _condition;
    for(Binary_Search_Node *_ptr = this->Head;;)
    {
        if (_key == _ptr->Key)
        {
            _pos = _ptr;
            _condition = 0;
            break;
        } else if (_key < _ptr->Key) {
            if (_ptr->Left != nullptr) _ptr = _ptr->Left;
            else {
                _pos = _ptr;
                _condition = -1;
                break;
            }
        } else {
            if (_ptr->Right != nullptr) _ptr = _ptr->Righta;
            else {
                _pos = _ptr;
                _condition = 1;
                break;
            }
        }
    }

    switch (_condition)
    {
        case 0:
            _pos->Value = node.Value;
            break;
        case 1:
            _pos->Right = &node;
            node.Father = _pos;
            break;
        default:
            _pos->Left = &node;
            node.Father = _pos;
            break;
    }
}

template<typename K_Tp, typename V_Tp>
void Binary_Search_Tree<K_Tp, V_Tp>::erase(const K_Tp &key)
{
    auto *_ptr = this->search(key);

    if (_ptr->Left == nullptr && _ptr->Right == nullptr)
    {
        if (_ptr->Father != nullptr)
        {
            _ptr->Key < _ptr->Father->Key? _ptr->Father->Left = nullptr: _ptr->Father->Right = nullptr;
        } else {
            this->Head = nullptr;
        }
    } else if (_ptr->Left != nullptr && _ptr->Right== nullptr) {
        if (_ptr->Father != nullptr)
        {
            _ptr->Key < _ptr->Father->Key ? _ptr->Father->Left = _ptr->Left : _ptr->Father->Right = _ptr->Left;
            _ptr->Left->Father = _ptr->Father;
        } else this->Head = _ptr->Left;
    } else if (_ptr->Right != nullptr && _ptr->Left == nullptr) {
        if (_ptr->Father != nullptr) {
            _ptr->Key < _ptr->Father->Key ? _ptr->Father->Left = _ptr->Right : _ptr->Father->Right = _ptr->Right;
            _ptr->Right->Father = _ptr->Father;
        } else this->Head = _ptr->Right;
    } else {
        Binary_Search_Tree::destroy(*_ptr);
    }
}

template<typename K_Tp, typename V_Tp>
typename Binary_Search_Tree<K_Tp, V_Tp>::Binary_Search_Node *Binary_Search_Tree<K_Tp, V_Tp>::search(K_Tp const &key) const
{
    if (this->Head == nullptr) return nullptr;
    K_Tp _temp = this->Head->Key;
    for (Binary_Search_Node *_ptr_iterator {this->Head};;)
    {
        if (_temp == key) {
            return _ptr_iterator;
        } else if (_temp > key) {
            if (_ptr_iterator->Right == nullptr)
            {
                return nullptr;
            } else {
                _ptr_iterator = _ptr_iterator->Right;
            }
        } else {
            if (_ptr_iterator->Left == nullptr)
            {
                return nullptr;
            } else {
                _ptr_iterator = _ptr_iterator->Left;
            }
        }
        _temp = _ptr_iterator->Key;
    }
}

template<typename K_Tp, typename V_Tp>
std::pair<typename Binary_Search_Tree<K_Tp, V_Tp>::Binary_Search_Node *, typename Binary_Search_Tree<K_Tp, V_Tp>::Binary_Search_Node *> Binary_Search_Tree<K_Tp, V_Tp>::search_between(const K_Tp &key) const {
    if (this->Head == nullptr) return std::pair<Binary_Search_Node*, Binary_Search_Node*>{nullptr, nullptr};
    std::pair<Binary_Search_Node *, Binary_Search_Node *> _res {};
    K_Tp _temp = this->Head->Key;
    for(Binary_Search_Node *_ptr_iterator {this->Head};;)
    {
        if (_ptr_iterator->Right != nullptr && key > _temp)
        {
            if (key < _ptr_iterator->Right->Key)
            {
                return std::pair<Binary_Search_Node *, Binary_Search_Node *>{_ptr_iterator, _ptr_iterator->Right};
            } else {
                _ptr_iterator = _ptr_iterator->Right;
            }
        } else if (_ptr_iterator->Left != nullptr && key < _temp)
        {
            if (key > _ptr_iterator->Left->Key)
            {
                return std::pair<Binary_Search_Node *, Binary_Search_Node *>{_ptr_iterator->Left, _ptr_iterator};
            } else {
                _ptr_iterator = _ptr_iterator->Left;
            }
        }  else {
            return std::pair<Binary_Search_Node*, Binary_Search_Node*> {_ptr_iterator, nullptr};
        }
    }
}

template<typename K_Tp, typename V_Tp>
std::vector<V_Tp> Binary_Search_Tree<K_Tp, V_Tp>::ascend() const
{
    size_t const _size = this->Head->Size;
    std::deque<Binary_Search_Node *> _cache {};
    std::vector<V_Tp> _res {};
    Binary_Search_Node *_node {this->Head};

    for(size_t _idx = 0; _idx != _size; ++_idx) {
        if (_node->Right != nullptr) {
            _cache.template emplace_back(_node->Right);
            _res.template emplace_back(_node->Value);
            _node = _node->Left_Child;
        } else if (_node->Left != nullptr) {
            _res.template emplace_back(_node->Value);
            _node = _node->Left;
         }else {
            _res.template emplace_back(_node->Value);
            _node = &_cache.back();
            _cache.pop_back();
        }
    }
    return _res;
}

template<typename K_Tp, typename V_Tp>
void Binary_Search_Tree<K_Tp, V_Tp>::destroy(Binary_Search_Tree::Binary_Search_Node &node)
{
    if (node.Right != nullptr)
    {
        node.Key = node.Right->Key;
        node.Value = node.Right->Value;
        destroy(*node.Right);
    } else if (node.Left != nullptr) {
        node.Key = node.Left->Key;
        node.Value = node.Left->Value;
        destroy(*node.Left);
    } else {
        if (node.Father != nullptr)
        {
            (node.Key< node.Father->Key) ?node.Father->Left = nullptr : node.Father->Right = nullptr;
        }
        ~node();
    }
}

template<typename kt, typename vt>
Binary_Search_Tree<kt, vt> make_BST(std::vector<Pair_Unit<kt ,vt>> const &vec)
{
    return Binary_Search_Tree<kt, vt> {vec};
}


#endif //DATASTRUCTURE_BINARY_SEARCH_TREE_HPP
