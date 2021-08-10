#ifndef DATASTRUCTURE_TREAP_SET_HPP
#define DATASTRUCTURE_TREAP_SET_HPP

#include <iterator>
#include <random>

template<class cls>
class Treap_Set {
protected:
    struct args {
        cls item;
        size_t priority;
        args *father;
        args *right;
        args *left;
    };

    struct yield : public std::iterator<std::bidirectional_iterator_tag, cls> {
        yield(Treap_Set &set, args *node)
        :owner{set}, node{node} {}
        yield(): owner{*new Treap_Set{}}, node{nullptr} {}

        Treap_Set &owner;
        args *node;

        virtual const yield operator++(int);
        virtual const yield operator--(int);
        virtual yield &operator++();
        virtual yield &operator--();

        bool operator!=(yield const &);
        yield &operator=(yield const &);
        virtual cls *operator->();
        virtual cls &operator*();

    };

    struct reverse_yield : public std::iterator<std::bidirectional_iterator_tag, cls> {
        reverse_yield(Treap_Set &set, args *node)
        :owner{set}, node{node} {}
        reverse_yield(): owner{*new Treap_Set{}}, node{nullptr} {}

        Treap_Set &owner;
        args *node;

        const reverse_yield operator++(int);
        const reverse_yield operator--(int);
        reverse_yield &operator++();
        reverse_yield &operator--();

        bool operator!=(reverse_yield const &);
        reverse_yield &operator=(reverse_yield const &);
        cls *operator->();
        cls &operator*();

    };

    static std::random_device rd;
    static std::default_random_engine e;
    static std::uniform_int_distribution<size_t> ud;
    args *Root;

    inline size_t priority() {return ud(e);}
    void heapify(args *ptr);
    void remove(args *ptr);

    static args *as(args *);
    static args *ds(args *);

public:
    Treap_Set(std::initializer_list<cls> const &);
    template<typename Tp>
    Treap_Set(Tp *, size_t);

    cls operator[](size_t) const;
    void insert(cls const &);
    void erase(cls const &);
    bool exist(cls const &);

    yield begin();
    yield end();
    reverse_yield rbegin();
    reverse_yield rend();
};

template<class cls>
const typename Treap_Set<cls>::yield
Treap_Set<cls>::yield::operator++(int) {
    yield _n {*this};
    node = as(node);
    return _n;
}

template<class cls>
const typename Treap_Set<cls>::yield
Treap_Set<cls>::yield::operator--(int) {
    yield _n {*this};
    node = ds(node);
    return _n;
}

template<class cls>
typename Treap_Set<cls>::yield &
Treap_Set<cls>::yield::operator++() {
    node = as(node);
    return *this;
}

template<class cls>
typename Treap_Set<cls>::yield &
Treap_Set<cls>::yield::operator--() {
    node = ds(node);
    return *this;
}

template<class cls>
cls *Treap_Set<cls>::yield::
operator->() {
    return &node->item;
}

template<class cls>
cls &Treap_Set<cls>::yield
::operator*() {
    return node->item;
}

template<class cls>
bool Treap_Set<cls>::yield::operator!=(const Treap_Set::yield &op) {
    return this->node!=op.node;
}

template<class cls>
typename Treap_Set<cls>::yield &
Treap_Set<cls>::yield::operator=(const Treap_Set::yield &) = default;

template<class cls>
const typename Treap_Set<cls>::reverse_yield
Treap_Set<cls>::reverse_yield::operator++(int) {
    reverse_yield _n {*this};
    node = ds(node);
    return _n;
}

template<class cls>
const typename Treap_Set<cls>::reverse_yield
Treap_Set<cls>::reverse_yield::operator--(int) {
    reverse_yield _n {*this};
    node = as(node);
    return _n;
}

template<class cls>
typename Treap_Set<cls>::reverse_yield &
Treap_Set<cls>::reverse_yield::operator++() {
    node = ds(node);
    return *this;
}

template<class cls>
typename Treap_Set<cls>::reverse_yield &
Treap_Set<cls>::reverse_yield::operator--() {
    node = as(node);
    return *this;
}

template<class cls>
cls *Treap_Set<cls>::reverse_yield::operator->() {
    return &node->item;
}

template<class cls>
cls &Treap_Set<cls>::reverse_yield::operator*() {
    return node->item;
}

template<class cls>
bool Treap_Set<cls>::reverse_yield::operator!=(const Treap_Set::reverse_yield &op) {
    return this->node!=op.node;
}

template<class cls>
typename Treap_Set<cls>::reverse_yield &
Treap_Set<cls>::reverse_yield::operator=(const Treap_Set::reverse_yield &) = default;

template<class cls>
typename Treap_Set<cls>::args *
Treap_Set<cls>::as(Treap_Set::args *node) {
    if (node->right!= nullptr) {
        node = node->right;
        while(node->left != nullptr) node = node->left;
        return node;
    }
    if (node->father == nullptr) return nullptr;
    while(node->father!= nullptr&&node == node->father->right) {
        node = node->father;
    }
    return node->father;
}

template<class cls>
typename Treap_Set<cls>::args *
Treap_Set<cls>::ds(Treap_Set::args *node) {
    if (node->left!= nullptr) {
        node = node->left;
        while(node->right != nullptr) node = node->right;
        return node;
    }
    if (node->father == nullptr) return nullptr;
    while(node->father!= nullptr&&node == node->father->left) {
        node = node->father;
    }
    return node->father;
}

template<class cls>
typename std::random_device Treap_Set<cls>::rd;

template<class cls>
typename std::default_random_engine Treap_Set<cls>::e
        {Treap_Set<cls>::rd()};

template<class cls>
typename std::uniform_int_distribution<size_t>
        Treap_Set<cls>::ud (0, SIZE_MAX);

template<class cls>
Treap_Set<cls>::Treap_Set(const std::initializer_list<cls> &list)
:Root {nullptr} {
    size_t const _s = list.size();
    for (size_t _i{}; _i!=_s; ++_i) {
        insert(*(list.begin()+_i));
    }
}

template<class cls>
template<typename Tp>
Treap_Set<cls>::Treap_Set(Tp *ptr, size_t size)
:Root {nullptr} {
    for (size_t i=0;i!=size;++i) {
        insert(ptr[i]);
    }
}

template<class cls>
void Treap_Set<cls>::insert(const cls &item) {
    if (Root == nullptr) {
        Root = new args {item, priority(), nullptr, nullptr, nullptr};
        return;
    }
    args *iter = Root;
    while(true)
    {
        if (iter->item==item) {
            return;
        } if (iter->item > item) {
            if (iter->left!= nullptr) {
                iter = iter->left;
            } else {
                iter->left = new args
                        {item, priority(), iter, nullptr, nullptr};
                heapify(iter->left);
                return;
            }
        } else {
            if (iter->right != nullptr) {
                iter = iter->right;
            } else {
                iter->right = new args
                        {item, priority(), iter, nullptr, nullptr};
                heapify(iter->right);
                return;
            }
        }
    }
}

template<class cls>
void Treap_Set<cls>::erase(const cls &item) {
    if (Root == nullptr) return;
    args *iter = Root;
    while(true)
    {
        if (iter->item == item) {
            remove(iter);
            return;
        } if (iter->item > item) {
            if (iter->left!= nullptr) {
                iter = iter->left;
            } else return;
        } else {
            if (iter->right != nullptr) {
                iter = iter->right;
            } else return;
        }
    }
}

template<class cls>
bool Treap_Set<cls>::exist(const cls &item) {
    if (Root == nullptr) return false;
    args *_i {Root};
    while(true) {
        if (_i->item == item) return true;
        if (_i->item > item) {
            if (_i->left!= nullptr) _i = _i->left;
            else return false;
        } else {
            if (_i->right!= nullptr) _i = _i->right;
            else return false;
        }
    }
}

template<class cls>
cls Treap_Set<cls>::operator[](size_t) const {
    return nullptr;
}

template<class cls>
void Treap_Set<cls>::heapify(Treap_Set::args *ptr) {
    args *fp;
    while(ptr!=nullptr&&ptr->father!= nullptr&&
    ptr->priority>ptr->father->priority) {
        fp = ptr->father;
        if (fp->left==ptr) {
            if (fp->father == nullptr) Root = ptr;
            else fp->father->left == fp ?
                        fp->father->left = ptr:
                        fp->father->right = ptr;
            ptr->father = fp->father;
            fp->father = ptr;
            fp->left = ptr->right;
            if (ptr->right!= nullptr) ptr->right->father = fp;
            ptr->right = fp;
        } else {
            if (fp->father == nullptr) Root = ptr;
            else fp->father->left == fp ?
                        fp->father->left = ptr:
                        fp->father->right = ptr;
            ptr->father = fp->father;
            fp->father = ptr;
            fp->right = ptr->left;
            if (ptr->left!= nullptr) ptr->left->father = fp;
            ptr->left = fp;
        }
        ptr = ptr->father;
    }
}

template<class cls>
void Treap_Set<cls>::remove(Treap_Set::args *ptr) {
    args *iter = ptr;
    while(true) {
        if (iter->left == nullptr&&iter->right== nullptr) {
            if (iter->father== nullptr) Root = nullptr;
            else iter->father->left == iter?
                        iter->father->left = nullptr:
                        iter->father->right = nullptr;
            reindex(iter->father);
            return;
        } else if (iter->left== nullptr&&iter->right!=nullptr) {
            if (iter->father== nullptr) Root = iter->right;
            else iter->father->left == iter?
                        iter->father->left = iter->right:
                        iter->father->right = iter->right;
            iter->right->father = iter->father;
            reindex(iter->father);
            return;
        } else if (iter->right == nullptr&&iter->left!= nullptr) {
            if (iter->father == nullptr) Root = iter->left;
            else iter->father->left ==iter?
                        iter->father->left = iter->left:
                        iter->father->right = iter->left;
            iter->left->father = iter->father;
            reindex(iter->father);
            return;
        } else {
            iter = iter->right;
            while(iter->left!= nullptr) iter = iter->left;
            ptr->key = iter->key;
            ptr->value = iter->value;
            ptr = iter;
            continue;
        }
    }
}

template<class cls>
typename Treap_Set<cls>::yield Treap_Set<cls>::begin() {
    args *iter = Root;
    while(iter->left != nullptr) iter= iter->left;
    return Treap_Set::yield{*this, iter};
}

template<class cls>
typename Treap_Set<cls>::yield Treap_Set<cls>::end() {
    return Treap_Set::yield{*this, nullptr};
}

template<class cls>
typename Treap_Set<cls>::reverse_yield Treap_Set<cls>::rbegin() {
    args *iter = Root;
    while(iter->right != nullptr) iter= iter->right;
    return Treap_Set::reverse_yield{*this, iter};
}

template<class cls>
typename Treap_Set<cls>::reverse_yield Treap_Set<cls>::rend() {
    return Treap_Set::reverse_yield{*this, nullptr};
}

#endif //DATASTRUCTURE_TREAP_SET_HPP
