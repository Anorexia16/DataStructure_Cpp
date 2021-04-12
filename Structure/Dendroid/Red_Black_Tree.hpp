#ifndef DATASTRUCTURE_RED_BLACK_TREE_HPP
#define DATASTRUCTURE_RED_BLACK_TREE_HPP

#include <vector>
#include "../Assistance/Storage_Unit.hpp"

enum Rb_Color {Red= 1, Black = 0};

template<typename K_Tp, typename V_Tp>
class Rb_Node {
public:
    Rb_Node(K_Tp const &, V_Tp const &);

    Pair_Unit<K_Tp, V_Tp> Container;

    Rb_Color Color;

    Rb_Node *Left;

    Rb_Node *Right;

    Rb_Node *Father;
};

template<typename K_Tp, typename V_Tp>
class Rb_Tree {
public:
    explicit Rb_Tree(std::vector<Pair_Unit<K_Tp, V_Tp>> const &);

    Rb_Node<K_Tp, V_Tp> *search(K_Tp &&) const;

    void insert(K_Tp const &, V_Tp const &);

    void erase(K_Tp const &);

protected:
    void erase_node(Rb_Node<K_Tp, V_Tp> *);

    void l_rotate(Rb_Node<K_Tp, V_Tp> &);

    void r_rotate(Rb_Node<K_Tp, V_Tp> &);

    void insert_fix(Rb_Node<K_Tp, V_Tp> *);

    void erase_fix(Rb_Node<K_Tp,V_Tp> *, Rb_Node<K_Tp,V_Tp> *);

    Rb_Node<K_Tp, V_Tp> *Root;
};

template<typename K_Tp, typename V_Tp>
Rb_Node<K_Tp, V_Tp>::Rb_Node(K_Tp const &key, V_Tp const &value)
:Container{key, value}, Father{nullptr}, Right{nullptr}, Left{nullptr}, Color{Red} {}

template<typename K_Tp, typename V_Tp>
Rb_Tree<K_Tp, V_Tp>::Rb_Tree(std::vector<Pair_Unit<K_Tp, V_Tp>> const &vec)
:Root{nullptr} {
    for(auto const &iter: vec) {
        this->insert(iter.Key, iter.Value);
    }
}

template<typename K_Tp, typename V_Tp>
Rb_Node<K_Tp, V_Tp> *Rb_Tree<K_Tp, V_Tp>::search(K_Tp &&key) const{
    if (this->Root == nullptr) return nullptr;
    for(Rb_Node<K_Tp, V_Tp> *_iter {this->Root};;) {
        if (_iter->Container.Key == key) return _iter;
        else if (_iter->Container.Key > key) {
            if (_iter->Right == nullptr) return nullptr;
            else _iter = _iter->Right;
        } else {
            if (_iter->Left == nullptr) return nullptr;
            else _iter = _iter->Left;
        }
    }
}

template<typename K_Tp, typename V_Tp>
void Rb_Tree<K_Tp, V_Tp>::insert(K_Tp const &key, V_Tp const &value) {
    auto *_node = new Rb_Node<K_Tp, V_Tp> {key, value};

    if (this->Root == nullptr) {
        _node->Color = Black;
        this->Root = _node;
        return;
    }

    for(Rb_Node<K_Tp, V_Tp> *_ptr = {this->Root};;) {
        if (key == _ptr->Container.Key) {
            _ptr->Container.Value = value;
            return;
        } else if (key < _ptr->Container.Key) {
            if (_ptr->Left != nullptr) _ptr = _ptr->Left;
            else {
                _node->Father = _ptr;
                _ptr->Left = _node;
                if (_node->Father->Color == Red) insert_fix(_node);
                return;
            }
        } else {
            if (_ptr->Right != nullptr) _ptr = _ptr->Right;
            else {
                _node->Father = _ptr;
                _ptr->Right = _node;
                if (_node->Father->Color == Red) insert_fix(_node);
                return;
            }
        }
    }
}

template<typename K_Tp, typename V_Tp>
void Rb_Tree<K_Tp, V_Tp>::erase(K_Tp const &key) {
    if (this->Root == nullptr) {
        return;
    }

    Rb_Node<K_Tp, V_Tp> *_ptr = {this->Root};
    while(true) {
        if (key == _ptr->Container.Key) {
            break;
        } else if (key < _ptr->Container.Key) {
            if (_ptr->Left != nullptr) _ptr = _ptr->Left;
            else {
                return;
            }
        } else {
            if (_ptr->Right != nullptr) _ptr = _ptr->Right;
            else {
                return;
            }
        }
    }
    erase_node(_ptr);
}

template<typename K_Tp, typename V_Tp>
void Rb_Tree<K_Tp, V_Tp>::erase_node(Rb_Node<K_Tp, V_Tp> *_ptr) {
    if(_ptr->Left == nullptr && _ptr->Right == nullptr) {
        if (_ptr->Father == nullptr) {
            this->Root == nullptr;
        } else {
            Rb_Node<K_Tp, V_Tp> *bp =_ptr->Father->Left == _ptr ? _ptr->Father->Right : _ptr->Left;
            _ptr->Father->Right == _ptr? _ptr->Father->Right = nullptr: _ptr->Father->Left = nullptr;
            if(_ptr->Color == Black && (bp == nullptr || (bp->Left != nullptr || bp->Right != nullptr))) this->erase_fix(nullptr, _ptr->Father);
        }
    } else if (_ptr->Left == nullptr) {
        if (_ptr->Father == nullptr) {
            this->Root = _ptr->Right;
        } else {
            _ptr->Father->Right == _ptr ? _ptr->Father->Right = _ptr->Right : _ptr->Father->Left = _ptr->Right;
            _ptr->Right->Father = _ptr->Father;
        }
        if(_ptr->Color == Black) erase_fix(_ptr->Left, _ptr->Father);
    } else if (_ptr->Right == nullptr) {
        if (_ptr->Father == nullptr) {
            this->Root = _ptr->Left;
        } else {
            _ptr->Father->Right == _ptr ? _ptr->Father->Right = _ptr->Left: _ptr->Father->Left = _ptr->Left;
            _ptr->Left->Father = _ptr->Father;
        }
        if(_ptr->Color == Black) erase_fix(_ptr->Right, _ptr->Father);
    } else {
        Rb_Node<K_Tp, V_Tp> *_iter {_ptr->Right};
        while(_iter->Left != nullptr) {
            _iter = _iter->Left;
        }
        _ptr->Container = _iter->Container;
        erase_node(_iter);
    }
}

template<typename K_Tp, typename V_Tp>
void Rb_Tree<K_Tp, V_Tp>::insert_fix(Rb_Node<K_Tp, V_Tp> *ptr) {

}

template<typename K_Tp, typename V_Tp>
void Rb_Tree<K_Tp, V_Tp>::erase_fix(Rb_Node<K_Tp,V_Tp> *cp, Rb_Node<K_Tp, V_Tp> *pp) {

}

template<typename K_Tp, typename V_Tp>
void Rb_Tree<K_Tp, V_Tp>::l_rotate(Rb_Node<K_Tp, V_Tp> &node) {
    Rb_Node<K_Tp,V_Tp> *_rc = node.Right;
    node.Right = _rc->Left;
    if (_rc->Left != nullptr) _rc->Left->Father = &node;
    _rc->Father = node.Father;
    if (node.Father != nullptr)
        node.Father->Left == &node ? node.Father->Left=_rc : node.Father->Right=_rc;
    _rc->Left = &node;
    node.Father = _rc;
    if (this->Root == &node) this->Root = _rc;
}

template<typename K_Tp, typename V_Tp>
void Rb_Tree<K_Tp, V_Tp>::r_rotate(Rb_Node<K_Tp, V_Tp> &node) {
    Rb_Node<K_Tp, V_Tp> *_lc = node.Left;
    node.Left = _lc == nullptr ? nullptr:_lc->Right;
    if (_lc->Right != nullptr) _lc->Right->Father = &node;
    _lc->Father = node.Father;
    if (node.Father != nullptr)
        node.Father->Left == &node ? node.Father->Left=_lc : node.Father->Right=_lc;
    _lc->Right = &node;
    node.Father = _lc;
}


template<typename kt, typename vt>
Rb_Tree<kt, vt> make_rb(std::vector<Pair_Unit<kt, vt>> const &vec) {
    return Rb_Tree<kt, vt> {vec};
}


#endif //DATASTRUCTURE_RED_BLACK_TREE_HPP
