#ifndef DATASTRUCTURE_TREAP_S_HPP
#define DATASTRUCTURE_TREAP_S_HPP

#include <random>

template<typename K_Tp, typename V_Tp>
class Treap_S {
public:
    Treap_S(std::initializer_list<K_Tp> const &,
            std::initializer_list<V_Tp> const &);

    template<class I, class II>
    Treap_S(I *, II *, size_t);

    void emplace(K_Tp const &, V_Tp const &);

    void insert(std::pair<K_Tp, V_Tp> const &);

    V_Tp &find(K_Tp const &) const;

    bool exist(K_Tp const &) const;

    void erase(K_Tp const &);

protected:
    struct kwargs {
        K_Tp key;
        V_Tp value;
        size_t priority;
        kwargs *father, *right, *left;
    };

    static std::random_device rd;
    static std::default_random_engine e;
    static std::uniform_int_distribution<size_t> ud;
    kwargs *Root;

    inline size_t priority() {return ud(e);}
    void heapify(kwargs *ptr);
    void merge(kwargs* ptr);
};

template<typename K_Tp, typename V_Tp>
Treap_S<K_Tp, V_Tp>::Treap_S
(const std::initializer_list<K_Tp> &keys, const std::initializer_list<V_Tp> &values)
:Root {nullptr} {
    if (keys.size() != values.size()) return;
    size_t const _e{keys.size()};
    for (size_t _b{}; _b!=_e; ++_b) {
        this->emplace(*(keys.begin()+_b), *(values.begin()+_b));
    }
}

template<typename K_Tp, typename V_Tp>
template<class I, class II>
Treap_S<K_Tp, V_Tp>::Treap_S(I *key, II *value, size_t size):
Root {}
{
    for (size_t i=0;i!=size;++i)
    this->emplace(*(key+i), *(value+i));
}

template<typename K_Tp, typename V_Tp>
void Treap_S<K_Tp, V_Tp>::emplace(const K_Tp &key, const V_Tp &value) {
    if (Root == nullptr) {
        Root = new kwargs {key, value, priority(), nullptr, nullptr, nullptr};
        return;
    }
    kwargs *iter = Root;
    while(true)
    {
        if (iter->key==key) {
            iter->value = value;
            return;
        } if (iter->key > key) {
            if (iter->left!= nullptr) {
                iter = iter->left;
            } else {
                iter->left = new kwargs
                        {key, value, priority(), iter, nullptr, nullptr};
                heapify(iter->left);
                return;
            }
        } else {
            if (iter->right != nullptr) {
                iter = iter->right;
            } else {
                iter->right = new kwargs
                        {key, value, priority(), iter, nullptr, nullptr};
                heapify(iter->right);
                return;
            }
        }
    }
}

template<typename K_Tp, typename V_Tp>
void Treap_S<K_Tp, V_Tp>::insert(const std::pair<K_Tp, V_Tp> &pair) {
    this->emplace(pair.first, pair.second);
}

template<typename K_Tp, typename V_Tp>
V_Tp &Treap_S<K_Tp, V_Tp>::find(const K_Tp &key) const {
    if (Root == nullptr) return *new V_Tp{};
    kwargs* _i {};
    while(true) {
        if (_i->key == key) return _i->value;
        if (_i->key>key) {
            if (_i->left!= nullptr) _i = _i->left;
            else return *new V_Tp {};
        } else {
            if (_i->right!= nullptr) _i = _i->right;
            else return *new V_Tp {};
        }
    }
}

template<typename K_Tp, typename V_Tp>
bool Treap_S<K_Tp, V_Tp>::exist(const K_Tp &key) const {
    if (Root == nullptr) return false;
    kwargs *_i {Root};
    while(true) {
        if (_i->key == key) return true;
        if (_i->key>key) {
            if (_i->left!= nullptr) _i = _i->left;
            else return false;
        } else {
            if (_i->right!= nullptr) _i = _i->right;
            else return false;
        }
    }
}

template<typename K_Tp, typename V_Tp>
void Treap_S<K_Tp, V_Tp>::erase(const K_Tp &key) {
    if (Root == nullptr) return;
    kwargs *iter = Root;
    while(true)
    {
        if (iter->key==key) {
            merge(iter);
            return;
        } if (iter->key > key) {
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

template<typename K_Tp, typename V_Tp>
void Treap_S<K_Tp, V_Tp>::heapify(Treap_S::kwargs *ptr) {
    kwargs *fp;
    while(ptr!= nullptr&&ptr->father!= nullptr&&
    ptr->priority>fp->priority) {

    }
}

template<typename K_Tp, typename V_Tp>
void Treap_S<K_Tp, V_Tp>::merge(Treap_S::kwargs *ptr) {

}

#endif //DATASTRUCTURE_TREAP_S_HPP
