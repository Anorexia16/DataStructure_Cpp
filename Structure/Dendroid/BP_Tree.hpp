#ifndef DATASTRUCTURE_BP_TREE_HPP
#define DATASTRUCTURE_BP_TREE_HPP

#include <iterator>

struct Disk_Ptr {
    FILE* handle;
};

template<long order, class Key, class Value>
class BP_Tree final {
private:
    struct Extern_Node {
        bool leaf;
    };

    class Index_Node final: Extern_Node {
        Key Page[order];
        Extern_Node *To[order];
        long size;
    };

    class Data_Node final: Extern_Node {
        Key key;
        Value value;
        Data_Node *left, *right;
    };

    struct Ascending_Iterator: std::iterator<std::bidirectional_iterator_tag, Value>{
    public:
        Ascending_Iterator(BP_Tree * const &, Data_Node *, int);

        virtual const Ascending_Iterator operator++(int) const;
        virtual const Ascending_Iterator operator--(int) const;
        virtual Ascending_Iterator &operator++();
        virtual Ascending_Iterator &operator--();

        virtual bool operator>(BP_Tree::Ascending_Iterator const &) const;
        virtual bool operator<(BP_Tree::Ascending_Iterator const &) const;
        virtual bool operator>=(BP_Tree::Ascending_Iterator const &) const;
        virtual bool operator<=(BP_Tree::Ascending_Iterator const &) const;
        virtual bool operator==(BP_Tree::Ascending_Iterator const &) const;
        virtual bool operator!=(BP_Tree::Ascending_Iterator const &) const;

        virtual Value *operator->() {return &this->Pos->value;};
        virtual Value &operator*() {return this->Pos->value;};

    protected:
        BP_Tree * const Owner;
        Data_Node *Pos;
        int dev;
    };

    struct Reverse_Ascending_Iterator final:Ascending_Iterator {
        Reverse_Ascending_Iterator(BP_Tree * const &, Data_Node *, int x);

        const Reverse_Ascending_Iterator operator++(int) const;
        const Reverse_Ascending_Iterator operator--(int) const;
        Reverse_Ascending_Iterator &operator++();
        Reverse_Ascending_Iterator &operator--();

        bool operator>(BP_Tree::Reverse_Ascending_Iterator const &) const;
        bool operator<(BP_Tree::Reverse_Ascending_Iterator const &) const;
        bool operator>=(BP_Tree::Reverse_Ascending_Iterator const &) const;
        bool operator<=(BP_Tree::Reverse_Ascending_Iterator const &) const;
        bool operator==(BP_Tree::Reverse_Ascending_Iterator const &) const;
        bool operator!=(BP_Tree::Reverse_Ascending_Iterator const &) const;

        Value *operator->() {return &this->Pos->value;};
        Value &operator*() {return this->Pos->value;};
    };

    struct Const_Ascending_Iterator final:Ascending_Iterator {
        Const_Ascending_Iterator(BP_Tree * const &, Data_Node *, int x);

        Const_Ascending_Iterator operator++(int) const;
        Const_Ascending_Iterator operator--(int) const;
        Const_Ascending_Iterator &operator++();
        Const_Ascending_Iterator &operator--();

        bool operator>(BP_Tree::Const_Ascending_Iterator const &) const;
        bool operator<(BP_Tree::Const_Ascending_Iterator const &) const;
        bool operator>=(BP_Tree::Const_Ascending_Iterator const &) const;
        bool operator<=(BP_Tree::Const_Ascending_Iterator const &) const;
        bool operator==(BP_Tree::Const_Ascending_Iterator const &) const;
        bool operator!=(BP_Tree::Const_Ascending_Iterator const &) const;

        Value *operator->() {return &this->Pos->value;};
        Value &operator*() {return this->Pos->value;};
    };

    BP_Tree &operator=(BP_Tree const &) noexcept = default;
    BP_Tree &operator=(BP_Tree &&) noexcept = default;
    BP_Tree(BP_Tree const &) noexcept = default;
    BP_Tree(BP_Tree &&) noexcept = default;
    ~BP_Tree() = default;

    mutable Index_Node *Ic;
    mutable Data_Node *Dc;
    Data_Node *Ascending;
    Index_Node *Root;
    Key kr; Value vr;

    void Create_Page();

    long Find(Index_Node *const, Key const &) const;

    void Broadcast(Index_Node *const, Key const &);

public:
    void insert(std::pair<Key, Value> const &);

    void insert(Key const &, Value const &);

    void remove(Key const &, Value const &);

    Value search(Key const &) const;

    Value &at(Key const &);

    Ascending_Iterator begin();
    Ascending_Iterator end();

    template <typename Tp>
    void emplace(Tp &&);
};

template<long order, class Key, class Value>
BP_Tree<order, Key, Value>::
Ascending_Iterator::Ascending_Iterator
(BP_Tree *const &tree, BP_Tree::Data_Node *pos, int x)
:Owner{tree}, Pos{pos}, dev{x} {}

template<long order, class Key, class Value>
typename BP_Tree<order, Key, Value>::Ascending_Iterator const
BP_Tree<order, Key, Value>::Ascending_Iterator::operator++(int) const {
    Ascending_Iterator tp {*this};
    this->operator++();
    return tp;
}

template<long order, class Key, class Value>
typename BP_Tree<order, Key, Value>::Ascending_Iterator const
BP_Tree<order, Key, Value>::Ascending_Iterator::operator--(int) const {
    Ascending_Iterator tp {*this};
    this->operator--();
    return tp;
}

template<long order, class Key, class Value>
typename BP_Tree<order, Key, Value>::Ascending_Iterator &
BP_Tree<order, Key, Value>::Ascending_Iterator::operator++() {
    Pos=Pos->right;++dev;
    return *this;
}

template<long order, class Key, class Value>
typename BP_Tree<order, Key, Value>::Ascending_Iterator &
BP_Tree<order, Key, Value>::Ascending_Iterator::operator--() {
    Pos=Pos->left;--dev;
    return *this;
}

template<long order, class Key, class Value>
bool BP_Tree<order, Key, Value>::Ascending_Iterator::operator>
(const BP_Tree::Ascending_Iterator &op) const {
    return dev>op.dev;
}

template<long order, class Key, class Value>
bool BP_Tree<order, Key, Value>::Ascending_Iterator::operator<
(const BP_Tree::Ascending_Iterator &op) const {
    return dev<op.dev;
}

template<long order, class Key, class Value>
bool BP_Tree<order, Key, Value>::Ascending_Iterator::operator>=
(const BP_Tree::Ascending_Iterator &op) const {
    return dev>=op.dev;
}

template<long order, class Key, class Value>
bool BP_Tree<order, Key, Value>::Ascending_Iterator::operator<=
(const BP_Tree::Ascending_Iterator &op) const {
    return dev<=op.dev;
}

template<long order, class Key, class Value>
bool BP_Tree<order, Key, Value>::Ascending_Iterator::operator==
(const BP_Tree::Ascending_Iterator &op) const {
    return dev==op.dev;
}

template<long order, class Key, class Value>
bool BP_Tree<order, Key, Value>::Ascending_Iterator::operator!=
(const BP_Tree::Ascending_Iterator &op) const {
    return dev!=op.dev;
}

template<long order, class Key, class Value>
BP_Tree<order, Key, Value>::
Reverse_Ascending_Iterator::Reverse_Ascending_Iterator
(BP_Tree *const &tree, BP_Tree::Data_Node *pos, int x)
:Ascending_Iterator{tree, pos, x} {}

template<long order, class Key, class Value>
typename BP_Tree<order, Key, Value>::Reverse_Ascending_Iterator const
BP_Tree<order, Key, Value>::Reverse_Ascending_Iterator::operator++(int) const {
    return Ascending_Iterator::operator++(0);
}

template<long order, class Key, class Value>
typename BP_Tree<order, Key, Value>::Reverse_Ascending_Iterator const
BP_Tree<order, Key, Value>::Reverse_Ascending_Iterator::operator--(int) const {
    return Ascending_Iterator::operator++(0);
}

template<long order, class Key, class Value>
template<typename Tp>
void BP_Tree<order, Key, Value>::emplace(Tp &&var) {
    std::pair<Key, Value> temp = std::forward<>(var);
    insert(temp);
}

#endif //DATASTRUCTURE_BP_TREE_HPP
