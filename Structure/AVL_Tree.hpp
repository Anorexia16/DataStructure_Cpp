#ifndef DATASTRUCTURE_AVL_TREE_HPP
#define DATASTRUCTURE_AVL_TREE_HPP

#include <deque>
#include "Storage_Unit.hpp"
#include "Binary_Tree.hpp"

template<typename K_Tp, typename V_Tp>
class AVL_Tree
{
public:
    using AVL_Node = Binary_Node<Pair_Unit<K_Tp, V_Tp>>;

    using AVL_Item = Pair_Unit<K_Tp, V_Tp>;

    explicit AVL_Tree(std::vector<AVL_Item> const &);

    AVL_Node *search(K_Tp const &) const;

    [[nodiscard]] std::vector<AVL_Item> ascend() const;

    void insert(AVL_Item const &);

    void insert(AVL_Node &);

    void erase(K_Tp const &);

protected:
    static std::pair<AVL_Node *, size_t> imbalance_seek(AVL_Node const &);

    static inline bool is_imbalance(AVL_Node const &);

    static inline ssize_t bf(AVL_Node const &);

    void LL_rotate(AVL_Node &);

    void RR_rotate(AVL_Node &);

    void LR_rotate(AVL_Node &);

    void RL_rotate(AVL_Node &);

    AVL_Node *Head;
};

template<typename K_Tp, typename V_Tp>
AVL_Tree<K_Tp, V_Tp>::AVL_Tree(const std::vector<AVL_Item> &cont)
:Head{nullptr} {for(auto const &_iter:cont) this->insert(_iter);}

template<typename K_Tp, typename V_Tp>
typename AVL_Tree<K_Tp, V_Tp>::AVL_Node *AVL_Tree<K_Tp, V_Tp>::search(const K_Tp &key) const
{
    if (this->Head == nullptr) return nullptr;
    K_Tp _temp = this->Head->value_c().Key;
    for (AVL_Node *_ptr_iterator {this->Head};;)
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
std::vector<typename AVL_Tree<K_Tp, V_Tp>::AVL_Item> AVL_Tree<K_Tp, V_Tp>::ascend() const
{
    size_t const _size = this->Head->size();
    std::deque<AVL_Node *> _cache {};
    std::vector<AVL_Item> _res {};
    AVL_Node *_node {this->Head};

    for(size_t _idx = 0; _idx != _size; ++_idx)
    {
        switch (_node->leaves_count())
        {
            case 2:
                _cache.template emplace_back(_node->Right_Child);
                _res.template emplace_back(_node->value_c());
                _node = _node->Left_Child;
                break;
            case 1:
                _res.template emplace_back(_node->value_c());
                _node = _node->Left_Child;
                break;
            default:
                _res.template emplace_back(_node->value_c());
                _node = &_cache.back();
                _cache.pop_back();
                break;
        }
    }
    return _res;
}

template<typename K_Tp, typename V_Tp>
void AVL_Tree<K_Tp, V_Tp>::insert(const AVL_Tree::AVL_Item &item)
{
    auto *_node = new AVL_Node {item};
    this->insert(*_node);
}

template<typename K_Tp, typename V_Tp>
void AVL_Tree<K_Tp, V_Tp>::insert(AVL_Tree::AVL_Node &node)
{
    node.sink();
    if (this->Head == nullptr) {
        this->Head = new AVL_Node {node};
        return;
    }
    K_Tp &_key = node.value().Key;
    AVL_Node *_pos;
    int _condition;
    for(AVL_Node *_ptr = this->Head;;)
    {
        if (_key == _ptr->value().Key)
        {
            _pos = _ptr;
            _condition = 0;
            break;
        } else if (_key < _ptr->value().Key)
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

    switch (_condition)
    {
        case 0:
            _pos->value().Value = node.value().Value;
            return;
        case 1:
            _pos->Right_Child = &node;
            node.Father = _pos;
            for(AVL_Node * broad_cast = _pos;; broad_cast = broad_cast->Father)
            {
                broad_cast->size_r() += 1;
                broad_cast->Depth = std::max(broad_cast->Left_Child == nullptr ? 0:  broad_cast->Left_Child->Depth + 1,
                                             broad_cast->Right_Child == nullptr ? 0:  broad_cast->Right_Child->Depth + 1);
                if (broad_cast->Father == nullptr) break;
            }
            break;
        default:
            _pos->Left_Child = &node;
            node.Father = _pos;
            for(AVL_Node *broad_cast = _pos;; broad_cast = broad_cast->Father)
            {
                broad_cast->size_r() += 1;
                broad_cast->Depth = std::max(broad_cast->Left_Child == nullptr ? 0:  broad_cast->Left_Child->Depth + 1,
                                             broad_cast->Right_Child == nullptr ? 0:  broad_cast->Right_Child->Depth + 1);
                if (broad_cast->Father == nullptr) break;
            }
            break;
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
}

template<typename K_Tp, typename V_Tp>
void AVL_Tree<K_Tp, V_Tp>::erase(const K_Tp &) {

}

template<typename K_Tp, typename V_Tp>
ssize_t AVL_Tree<K_Tp, V_Tp>::bf(AVL_Tree::AVL_Node const &node) {
    return (node.Left_Child == nullptr ? 0 : node.Left_Child->depth())
            - (node.Right_Child == nullptr ? 0 : node.Right_Child->depth());
}

template<typename K_Tp, typename V_Tp>
bool AVL_Tree<K_Tp, V_Tp>::is_imbalance(AVL_Tree::AVL_Node const &node) {
    ssize_t _bf = bf(node);
    return _bf == 2 || _bf == -2;
}

template<typename K_Tp, typename V_Tp>
std::pair<typename AVL_Tree<K_Tp, V_Tp>::AVL_Node *, size_t> AVL_Tree<K_Tp, V_Tp>::imbalance_seek(const AVL_Tree::AVL_Node &node) {
    bool PL = true, GL;
    AVL_Node *_res;

    for(AVL_Node const *_ptr = &node;; _ptr = _ptr->Father) {
        if (_ptr->Father == nullptr) {
            return std::pair<AVL_Node*, size_t> {nullptr, 0b00};
        } else if (is_imbalance(*_ptr->Father)) {
            GL = _ptr->Father->Left_Child == _ptr;
            _res = PL ? _ptr->Left_Child : _ptr->Right_Child;
            break;
        } else {
            PL = _ptr->Father->Left_Child == _ptr;
        }
    }
    size_t _condition = static_cast<size_t>(!GL) * 2 + static_cast<size_t>(!PL);
    return std::pair<AVL_Node*, size_t> {_res, _condition};
}

template<typename K_Tp, typename V_Tp>
void AVL_Tree<K_Tp, V_Tp>::LL_rotate(AVL_Tree::AVL_Node &node) {
    AVL_Node *_a = node.Father->Father;
    AVL_Node *_b = node.Father;
    AVL_Node *_br = _b->Right_Child;
    if (this->Head == _a) this->Head = _b;
    _b->Father = _a->Father;
    _a->Father = _b;
    if (_b->Father != nullptr) {
        _b->Father->Left_Child == _a ? _b->Father->Left_Child = _b : _b->Father->Right_Child = _b;
    }
    _b->Right_Child = _a;
    _a->Left_Child = _br;
    if (_br != nullptr) _br->Father = _a;

    size_t _bs = _b->size(), _brs = _br == nullptr? 0 : _br->size();
    _b->size_r() = _a->size();
    _a->size_r() += _brs - _bs;
    _a->Depth = _b->Depth - 1;

    for(AVL_Node *_bp = _b->Father;; _bp = _bp->Father) {
        if (_bp == nullptr) break;
        _bp->Depth = std::max(_bp->Left_Child == nullptr ? 0:  _bp->Left_Child->Depth + 1,
                              _bp->Right_Child == nullptr ? 0:  _bp->Right_Child->Depth + 1);
    }
}

template<typename K_Tp, typename V_Tp>
void AVL_Tree<K_Tp, V_Tp>::RR_rotate(AVL_Tree::AVL_Node &node) {
    AVL_Node *_a = node.Father->Father;
    AVL_Node *_b = node.Father;
    AVL_Node *_bl = _b->Left_Child;
    if (this->Head == _a) this->Head = _b;
    _b->Father = _a->Father;
    _a->Father = _b;
    if (_b->Father != nullptr) {
        _b->Father->Right_Child == _a ? _b->Father->Right_Child = _b : _b->Father->Left_Child = _b;
    }
    _b->Left_Child = _a;
    _a->Right_Child = _bl;
    if (_bl != nullptr) _bl->Father = _a;

    size_t _bs = _b->size(), _bls = _bl == nullptr ? 0 :_bl->size();
    _b->size_r() = _a->size();
    _a->size_r() += _bls - _bs;
    _a->Depth = _b->Depth - 1;

    for(AVL_Node *_bp = _b->Father;; _bp = _bp->Father) {
        if (_bp == nullptr) break;
        _bp->Depth = std::max(_bp->Left_Child == nullptr ? 0:  _bp->Left_Child->Depth + 1,
                              _bp->Right_Child == nullptr ? 0:  _bp->Right_Child->Depth + 1);
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
        _c->Father->Right_Child == _a ? _c->Father->Right_Child = _c : _c->Father->Left_Child = _c;
    }
    _b->Right_Child = _c->Left_Child;
    _a->Left_Child = _c->Right_Child;
    _b->Father = _c;
    _a->Father = _c;
    if (_c->Left_Child != nullptr) _c->Left_Child->Father = _b;
    if (_c->Right_Child != nullptr) _c->Right_Child->Father = _a;
    _c->Left_Child = _b;
    _c->Right_Child = _a;

    size_t _bs = _b->size(), _as = _a->size(),
            _crs = _c->Right_Child == nullptr ?0:_c->Right_Child->size();
    _b->size_r() -= 1;
    _a->size_r() += _crs - _bs;
    _c->size_r() = _as;

    _b->Depth -= 1;
    _a->Depth -= 2;
    _c->Depth = _a->Depth + 1;
    for(AVL_Node *_bp = _c->Father;; _bp = _bp->Father) {
        if (_bp == nullptr) break;
        _bp->Depth = std::max(_bp->Left_Child == nullptr ? 0:  _bp->Left_Child->Depth + 1,
                              _bp->Right_Child == nullptr ? 0:  _bp->Right_Child->Depth + 1);
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
        _c->Father->Right_Child == _a ? _c->Father->Right_Child = _c : _c->Father->Left_Child = _c;
    }
    _b->Left_Child = _c->Right_Child;
    _a->Right_Child = _c->Left_Child;
    _b->Father = _c;
    _a->Father = _c;
    if (_c->Left_Child != nullptr) _c->Left_Child->Father = _a;
    if (_c->Right_Child != nullptr) _c->Right_Child->Father = _b;
    _c->Right_Child = _b;
    _c->Left_Child = _a;

    size_t _bs = _b->size(), _as = _a->size(),
            _cls = _c->Left_Child == nullptr ?0:_c->Left_Child->size();
    _b->size_r() -= 1;
    _a->size_r() += _cls - _bs;
    _c->size_r() = _as;

    _b->Depth -= 1;
    _a->Depth -= 2;
    _c->Depth = _a->Depth + 1;
    for(AVL_Node *_bp = _c->Father;; _bp = _bp->Father) {
        if (_bp == nullptr) break;
        _bp->Depth = std::max(_bp->Left_Child == nullptr ? 0:  _bp->Left_Child->Depth + 1,
                              _bp->Right_Child == nullptr ? 0:  _bp->Right_Child->Depth + 1);
    }
}

template<typename kt, typename vt>
AVL_Tree<kt, vt> make_avl(std::vector<Pair_Unit<kt, vt>> const &cont) {
    return AVL_Tree<kt, vt> {cont};
}


#endif //DATASTRUCTURE_AVL_TREE_HPP
