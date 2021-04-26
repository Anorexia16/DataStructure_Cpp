#ifndef DATASTRUCTURE_RED_BLACK_TREE_HPP
#define DATASTRUCTURE_RED_BLACK_TREE_HPP

#include "../Linear/Stack_Chain.hpp"

template<typename K_Tp, typename V_Tp>
struct Rb_Node
{
    Rb_Node(K_Tp const &, V_Tp const &);

    V_Tp Value;

    K_Tp Key;

    bool Red;

    Rb_Node *Father;

    Rb_Node *Right;

    Rb_Node *Left;
};

template<typename K_Tp, typename V_Tp>
Rb_Node<K_Tp, V_Tp>::Rb_Node(const K_Tp &key, const V_Tp &value)
:Value{value}, Key{key}, Red{true}, Father{nullptr}, Right{nullptr}, Left{nullptr} {}

template<typename K_Tp, typename V_Tp>
class Rb_Tree
{
public:
    explicit Rb_Tree();

    V_Tp search(K_Tp const &) const;

    bool exist(K_Tp const &) const;

    void insert(K_Tp const &, V_Tp const &);

    void erase(K_Tp const &);

protected:
    void insert_fixup(Rb_Node<K_Tp, V_Tp> &);

    void erase_fixup(Rb_Node<K_Tp, V_Tp> &);

    void l_rotate(Rb_Node<K_Tp, V_Tp> &);

    void r_rotate(Rb_Node<K_Tp, V_Tp> &);

    Rb_Node<K_Tp, V_Tp> *Root;
};

template<typename K_Tp, typename V_Tp>
Rb_Tree<K_Tp, V_Tp>::Rb_Tree()
:Root{nullptr} {}

template<typename K_Tp, typename V_Tp>
V_Tp Rb_Tree<K_Tp, V_Tp>::search(const K_Tp &key) const {
    if (Root == nullptr) return V_Tp{};

    for(Rb_Node<K_Tp, V_Tp> *iterator = Root;;)
    {
        if(iterator->Key == key) return iterator->Value;
        else if (iterator->Key > key)
        {
            if(iterator->Left != nullptr) iterator = iterator->Left;
            else return V_Tp{};
        } else {
            if (iterator->Right != nullptr) iterator = iterator->Right;
            else return V_Tp{};
        }
    }
}

template<typename K_Tp, typename V_Tp>
bool Rb_Tree<K_Tp, V_Tp>::exist(const K_Tp &key) const {
    if (Root == nullptr) return true;

    for(Rb_Node<K_Tp, V_Tp> *iterator = Root;;)
    {
        if(iterator->Key == key) return iterator->Value;
        else if (iterator->Key > key)
        {
            if(iterator->Left != nullptr) iterator = iterator->Left;
            else return false;
        } else {
            if (iterator->Right != nullptr) iterator = iterator->Right;
            else return false;
        }
    }
}

template<typename K_Tp, typename V_Tp>
void Rb_Tree<K_Tp, V_Tp>::insert(const K_Tp &key, const V_Tp &value) {
    if (this->Head == nullptr) {
        this->Head = new Rb_Node<K_Tp, V_Tp> {key, value};
        return;
    }

    for(Rb_Node<K_Tp, V_Tp> *_ptr = this->Head;;)
    {
        if (key == _ptr->Key)
        {
            _ptr->Value = value;
            break;
        } else if (key < _ptr->Key) {
            if (_ptr->Left != nullptr) _ptr = _ptr->Left;
            else {
                _ptr->Left = new Rb_Node<K_Tp, V_Tp> {key, value};
                if (_ptr->Red) insert_fixup(*_ptr->Left);
                break;
            }
        } else {
            if (_ptr->Right != nullptr) _ptr = _ptr->Right;
            else {
                _ptr->Right = new Rb_Node<K_Tp, V_Tp> {key, value};
                if (_ptr->Red) insert_fixup(*_ptr->Right);
                break;
            }
        }
    }
}

template<typename K_Tp, typename V_Tp>
void Rb_Tree<K_Tp, V_Tp>::erase(const K_Tp &key) {

}

template<typename K_Tp, typename V_Tp>
void Rb_Tree<K_Tp, V_Tp>::insert_fixup(Rb_Node<K_Tp, V_Tp> &node) {
    Rb_Node<K_Tp, V_Tp> *np = &node;
    Rb_Node<K_Tp, V_Tp> *gp = np->Father->Father;
    Rb_Node<K_Tp, V_Tp> *pp = np->Father;
    Rb_Node<K_Tp, V_Tp> *up = gp->Left == pp? gp->Right: gp->Left;

    while (true) {
        if (up != nullptr && up->Red) {
            break;
        }
    }
}

template<typename K_Tp, typename V_Tp>
void Rb_Tree<K_Tp, V_Tp>::erase_fixup(Rb_Node<K_Tp, V_Tp> &node) {

}

template<typename K_Tp, typename V_Tp>
void Rb_Tree<K_Tp, V_Tp>::l_rotate(Rb_Node<K_Tp, V_Tp> &node) {
    Rb_Node<K_Tp, V_Tp> &rc = *node.Right;
    node.Right = rc.Left;
    if (rc.Left != nullptr) rc.Left->Father = &node;
    rc.Father = node.Father;
    rc.Left = &node;
    if (node.Father != nullptr) {
        node.Father->Left == &node? node.Father->Left=&rc: node.Father->Right=&rc;
    } else {
        this->Root = &rc;
    }
    node.Father = &rc;
}

template<typename K_Tp, typename V_Tp>
void Rb_Tree<K_Tp, V_Tp>::r_rotate(Rb_Node<K_Tp, V_Tp> &node) {
    Rb_Node<K_Tp, V_Tp> &lc = *node.Left;
    node.Left = lc.Right;
    if (lc.Right != nullptr) lc.Right->Father = &node;
    lc.Father = node.Father;
    lc.Right = &node;
    if (node.Father != nullptr) {
        node.Father->Left == &node? node.Father->Left=&lc: node.Father->Right=&lc;
    } else {
        this->Root = &lc;
    }
    node.Father = &lc;
}

#endif //DATASTRUCTURE_RED_BLACK_TREE_HPP
