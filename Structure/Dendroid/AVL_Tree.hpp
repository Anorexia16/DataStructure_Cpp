#ifndef DATASTRUCTURE_AVL_TREE_HPP
#define DATASTRUCTURE_AVL_TREE_HPP

#include "../Linear/Deque_Chain.hpp"

template<typename K_Tp, typename V_Tp>
class AVL_Tree
{
protected:
    struct AVL_Node
    {
        AVL_Node(K_Tp const &, V_Tp const &);

        size_t Depth;

        V_Tp Value;

        K_Tp Key;

        AVL_Node *Father;

        AVL_Node *Right;

        AVL_Node *Left;
    };

    static std::pair<AVL_Node *, size_t> imbalance_seek(AVL_Node const &);

    static inline ssize_t bf(AVL_Node const &);

    void LL_rotate(AVL_Node &);

    void RR_rotate(AVL_Node &);

    void LR_rotate(AVL_Node &);

    void RL_rotate(AVL_Node &);

    AVL_Node *Head;

    size_t Size;

public:
    AVL_Tree();

    V_Tp search(K_Tp const &) const;

    bool exist(K_Tp const &) const;
    
    [[nodiscard]] bool empty() const;

    [[nodiscard]] size_t size() const;

    [[nodiscard]] std::vector<V_Tp> ascend() const;

    void insert(K_Tp const &, V_Tp const &);

    void insert(AVL_Node &);

    void erase(K_Tp const &);
};

template<typename K_Tp, typename V_Tp>
AVL_Tree<K_Tp, V_Tp>::AVL_Node::AVL_Node(const K_Tp &key, const V_Tp &value)
:Key{key},Value{value}, Depth{1}, Father{}, Left{}, Right{} {}

template<typename K_Tp, typename V_Tp>
AVL_Tree<K_Tp, V_Tp>::AVL_Tree()
:Head{nullptr}, Size{} {}

template<typename K_Tp, typename V_Tp>
V_Tp AVL_Tree<K_Tp, V_Tp>::search(const K_Tp &key) const
{
    if (this->Head == nullptr) return V_Tp{};
    K_Tp _temp = this->Head->Key;
    for (AVL_Node *_ptr_iterator {this->Head};;)
    {
        if (_temp == key)
        {
            return _ptr_iterator->Value;
        } else if (_temp > key) {
            if (_ptr_iterator->Right == nullptr)
            {
                return V_Tp{};
            } else {
                _ptr_iterator = _ptr_iterator->Right;
            }
        } else {
            if (_ptr_iterator->Left == nullptr)
            {
                return V_Tp{};
            } else {
                _ptr_iterator = _ptr_iterator->Left;
            }
        }
        _temp = _ptr_iterator->Key;
    }
}

template<typename K_Tp, typename V_Tp>
bool AVL_Tree<K_Tp, V_Tp>::exist(const K_Tp &) const {
    if (this->Head == nullptr) return V_Tp{};
    K_Tp _temp = this->Head->Key;
    for (AVL_Node *_ptr_iterator {this->Head};;)
    {
        if (_temp == key)
        {
            return true;
        } else if (_temp > key) {
            if (_ptr_iterator->Right == nullptr)
            {
                return false;
            } else {
                _ptr_iterator = _ptr_iterator->Right;
            }
        } else {
            if (_ptr_iterator->Left == nullptr)
            {
                return false;
            } else {
                _ptr_iterator = _ptr_iterator->Left;
            }
        }
        _temp = _ptr_iterator->Key;
    }
}

template<typename K_Tp, typename V_Tp>
std::vector<V_Tp> AVL_Tree<K_Tp, V_Tp>::ascend() const
{
    size_t const _size = this->Size;
    Deque_C<AVL_Node *> _cache {};
    std::vector<V_Tp> _res {};
    AVL_Node *_node {this->Head};
    _res.reserve(_size);

    for(size_t _idx = 0; _idx != _size; ++_idx)
    {
        if (_node->Left!= nullptr && _node->Right!= nullptr)
        {
            _cache.template emplace_back(_node->Right);
            _res.template emplace_back(_node->Value);
            _node = _node->Left;
        } else if (_node->Left!= nullptr) {
            _res.template emplace_back(_node->Value);
            _node = _node->Left;
        } else {
            _res.template emplace_back(_node->Value);
            _node = &_cache.back();
            _cache.pop_back();
        }
    }
    return _res;
}

template<typename K_Tp, typename V_Tp>
void AVL_Tree<K_Tp, V_Tp>::insert(K_Tp const &key, V_Tp const & value)
{
    auto *_node = new AVL_Node {key, value};
    this->insert(*_node);
}

template<typename K_Tp, typename V_Tp>
void AVL_Tree<K_Tp, V_Tp>::insert(AVL_Tree::AVL_Node &node)
{
    if (this->Head == nullptr) {
        this->Head = new AVL_Node {node};
        ++this->Size;
        return;
    }
    
    K_Tp &_key = node.Key;
    for(AVL_Node *_ptr = this->Head;;)
    {
        if (_key == _ptr->Key)
        {
            _ptr->Value = node.Value;
            return;
        } else if (_key < _ptr->Key)
        {
            if (_ptr->Left != nullptr) _ptr = _ptr->Left;
            else {
                _ptr->Left = &node;
                node.Father = _ptr;
                for(AVL_Node *broad_cast = _ptr; broad_cast!= nullptr; broad_cast = broad_cast->Father)
                {
                    broad_cast->Depth = std::max(broad_cast->Left == nullptr ? 0:  broad_cast->Left->Depth + 1,
                                                 broad_cast->Right == nullptr ? 0:  broad_cast->Right->Depth + 1);
                }
                break;
            }
        } else {
            if (_ptr->Right != nullptr) _ptr = _ptr->Right;
            else {
                _ptr = _ptr;
                _ptr->Right = &node;
                node.Father = _ptr;
                for(AVL_Node * broad_cast = _ptr; broad_cast!= nullptr; broad_cast = broad_cast->Father)
                {
                    broad_cast->Depth = std::max(broad_cast->Left == nullptr ? 0:  broad_cast->Left->Depth,
                                                 broad_cast->Right == nullptr ? 0:  broad_cast->Right->Depth) + 1;
                }
                break;
            }
        }
    }

    std::pair<AVL_Node *, size_t> _imbalance_info = imbalance_seek(node);
    if (_imbalance_info.first == nullptr) return;

    AVL_Node &_imbalance_node = *_imbalance_info.first;
    switch (_imbalance_info.second)
    {
        case 0b00:
            LL_rotate(_imbalance_node);
            break;
        case 0b01:
            LR_rotate(_imbalance_node);
            break;
        case 0b10:
            RL_rotate(_imbalance_node);
            break;
        case 0b11:
            RR_rotate(_imbalance_node);
            break;
        default:
            throw;
    }
    ++this->Size;
}

template<typename K_Tp, typename V_Tp>
void AVL_Tree<K_Tp, V_Tp>::erase(const K_Tp &) {

}

template<typename K_Tp, typename V_Tp>
ssize_t AVL_Tree<K_Tp, V_Tp>::bf(AVL_Tree::AVL_Node const &node) {
    return (node.Left == nullptr ? 0 : node.Left->Depth)
            - (node.Right == nullptr ? 0 : node.Right->Depth);
}

template<typename K_Tp, typename V_Tp>
std::pair<typename AVL_Tree<K_Tp, V_Tp>::AVL_Node *, size_t> AVL_Tree<K_Tp, V_Tp>::imbalance_seek(const AVL_Tree::AVL_Node &node) {
    bool PL = true, GL;
    size_t _bf;
    AVL_Node *_res;

    for(AVL_Node const *_ptr = &node;; _ptr = _ptr->Father) {
        if (_ptr->Father == nullptr)
        {
            return std::pair<AVL_Node*, size_t> {nullptr, 0b00};
        } else {
            _bf = AVL_Tree::bf(*_ptr->Father);
            if (_bf == 2 || _bf == -2) {
                GL = _ptr->Father->Left == _ptr;
                _res = PL? _ptr->Left : _ptr->Right;
                break;
            } else {
                PL = _ptr->Father->Left == _ptr;
            }
        }
    }
    
    size_t _condition = static_cast<size_t>(!GL) * 2 + static_cast<size_t>(!PL);
    return std::pair<AVL_Node*, size_t> {_res, _condition};
}

template<typename K_Tp, typename V_Tp>
void AVL_Tree<K_Tp, V_Tp>::LL_rotate(AVL_Tree::AVL_Node &node) {
    AVL_Node *_a = node.Father->Father;
    AVL_Node *_b = node.Father;
    AVL_Node *_br = _b->Right;
    if (this->Head == _a) this->Head = _b;
    _b->Father = _a->Father;
    _a->Father = _b;
    if (_b->Father != nullptr) {
        _b->Father->Left == _a ? _b->Father->Left = _b : _b->Father->Right = _b;
    }
    _b->Right = _a;
    _a->Left = _br;
    if (_br != nullptr) _br->Father = _a;
    _a->Depth = _b->Depth - 1;

    for(AVL_Node *_bp = _b->Father;; _bp = _bp->Father) {
        if (_bp == nullptr) break;
        _bp->Depth = std::max(_bp->Left == nullptr ? 0:  _bp->Left->Depth,
                              _bp->Right == nullptr ? 0:  _bp->Right->Depth) + 1;
    }
}

template<typename K_Tp, typename V_Tp>
void AVL_Tree<K_Tp, V_Tp>::RR_rotate(AVL_Tree::AVL_Node &node) {
    AVL_Node *_a = node.Father->Father;
    AVL_Node *_b = node.Father;
    AVL_Node *_bl = _b->Left;
    if (this->Head == _a) this->Head = _b;
    _b->Father = _a->Father;
    _a->Father = _b;
    if (_b->Father != nullptr) {
        _b->Father->Right == _a ? _b->Father->Right = _b : _b->Father->Left = _b;
    }
    _b->Left = _a;
    _a->Right = _bl;
    if (_bl != nullptr) _bl->Father = _a;
    _a->Depth = _b->Depth - 1;

    for(AVL_Node *_bp = _b->Father;; _bp = _bp->Father) {
        if (_bp == nullptr) break;
        _bp->Depth = std::max(_bp->Left == nullptr ? 0:  _bp->Left->Depth + 1,
                              _bp->Right == nullptr ? 0:  _bp->Right->Depth + 1);
    }
}

template<typename K_Tp, typename V_Tp>
void AVL_Tree<K_Tp, V_Tp>::LR_rotate(AVL_Tree::AVL_Node &node) {
    AVL_Node *_a = node.Father->Father;
    AVL_Node *_b = node.Father;
    AVL_Node *_c = &node;
    if (this->Head == _a) this->Head = _c;
    _c->Father = _a->Father;
    if (_c->Father != nullptr) {
        _c->Father->Right == _a ? _c->Father->Right = _c : _c->Father->Left = _c;
    }
    _b->Right = _c->Left;
    _a->Left = _c->Right;
    _b->Father = _c;
    _a->Father = _c;
    if (_c->Left != nullptr) _c->Left->Father = _b;
    if (_c->Right != nullptr) _c->Right->Father = _a;
    _c->Left = _b;
    _c->Right = _a;

    _b->Depth -= 1;
    _a->Depth -= 2;
    _c->Depth = _a->Depth + 1;
    for(AVL_Node *_bp = _c->Father;; _bp = _bp->Father) {
        if (_bp == nullptr) break;
        _bp->Depth = std::max(_bp->Left == nullptr ? 0:  _bp->Left->Depth + 1,
                              _bp->Right == nullptr ? 0:  _bp->Right->Depth + 1);
    }
}

template<typename K_Tp, typename V_Tp>
void AVL_Tree<K_Tp, V_Tp>::RL_rotate(AVL_Tree::AVL_Node &node) {
    AVL_Node *_a = node.Father->Father;
    AVL_Node *_b = node.Father;
    AVL_Node *_c = &node;
    if (this->Head == _a) this->Head = _c;
    _c->Father = _a->Father;
    if (_c->Father != nullptr) {
        _c->Father->Right == _a ? _c->Father->Right = _c : _c->Father->Left = _c;
    }
    _b->Left = _c->Right;
    _a->Right = _c->Left;
    _b->Father = _c;
    _a->Father = _c;
    if (_c->Left != nullptr) _c->Left->Father = _a;
    if (_c->Right != nullptr) _c->Right->Father = _b;
    _c->Right = _b;
    _c->Left = _a;

    _b->Depth -= 1;
    _a->Depth -= 2;
    _c->Depth = _a->Depth + 1;
    for(AVL_Node *_bp = _c->Father;; _bp = _bp->Father) {
        if (_bp == nullptr) break;
        _bp->Depth = std::max(_bp->Left == nullptr ? 0:  _bp->Left->Depth + 1,
                              _bp->Right == nullptr ? 0:  _bp->Right->Depth + 1);
    }
}

template<typename K_Tp, typename V_Tp>
bool AVL_Tree<K_Tp, V_Tp>::empty() const {
    return this->Head == nullptr;
}

template<typename K_Tp, typename V_Tp>
size_t AVL_Tree<K_Tp, V_Tp>::size() const {
    return this->Size;
}

template<typename kt, typename vt>
AVL_Tree<kt, vt> make_avl(std::vector<Pair_Unit<kt, vt>> const &cont) {
    return AVL_Tree<kt, vt> {};
}


#endif //DATASTRUCTURE_AVL_TREE_HPP
