#ifndef DATASTRUCTURE_AVL_TREE_HPP
#define DATASTRUCTURE_AVL_TREE_HPP

#include <cstdlib>

template<typename K_Tp, typename  V_Tp>
class AVL_Tree{
private:
    struct kwarg {
        V_Tp value;
        K_Tp key;
        kwarg *left;
        kwarg *right;
        kwarg *father;
        size_t depth;
        V_Tp &operator*() {return value;}
    };

    static bool unbalance(kwarg *);

    static size_t abs(size_t, size_t);

    static bool child(kwarg *);

    static void update(kwarg *);

    void insert_fix(kwarg *);

    void lt(kwarg *);

    void rt(kwarg *);

    kwarg *root {};

public:
    void insert(K_Tp const &, V_Tp const &);

    kwarg *search(K_Tp const &) const;

    bool exist(K_Tp const &) const;
};

template<typename Tp>
class AVL_Tree<Tp, Tp> {
    struct arg {
        Tp value;
        arg *left;
        arg *right;
        arg *father;
        size_t depth;
        Tp &operator*() {return value;}
    };

    static bool unbalance(arg *);

    static size_t abs(size_t, size_t);

    static bool child(arg *);

    static void update(arg *);

    void insert_fix(arg *);

    void lt(arg *);

    void rt(arg *);

    arg *root {};

public:
    void insert(Tp const &);

    arg *search(Tp const &) const;

    bool exist(Tp const &) const;
};

template<typename K_Tp, typename V_Tp>
bool AVL_Tree<K_Tp, V_Tp>::unbalance(AVL_Tree::kwarg *node) {
    return abs(node->left== nullptr?0:node->left->depth,
               node->right== nullptr?0:node->right->depth)>1;
}

template<typename K_Tp, typename V_Tp>
size_t AVL_Tree<K_Tp, V_Tp>::abs(size_t x, size_t y) {
    return x>y?x-y:y-x;
}

template<typename K_Tp, typename V_Tp>
bool AVL_Tree<K_Tp, V_Tp>::child(AVL_Tree::kwarg *node) {
    return node->father->right==node;
}

template<typename K_Tp, typename V_Tp>
void AVL_Tree<K_Tp, V_Tp>::update(AVL_Tree::kwarg *node) {
    size_t ld, rd;
    for(kwarg *iter=node;iter!= nullptr;iter=iter->father) {
        ld = iter->left== nullptr?0:iter->left->depth;
        rd = iter->right== nullptr?0:iter->right->depth;
        iter->depth = ld>rd? ld+1: rd+1;
    }
}

template<typename K_Tp, typename V_Tp>
void AVL_Tree<K_Tp, V_Tp>::insert(const K_Tp &key, const V_Tp &value) {
    if (root == nullptr) {
        root = new kwarg {key, value, nullptr, nullptr, nullptr, 1};
        return;
    }
    kwarg *iter = root;
    while(true) {
        if (iter->key==key) {
            iter->value = value;
            return;
        } if (key<iter->key) {
            if (iter->left==nullptr) {
                iter->left=new kwarg {key, value, nullptr, nullptr, iter, 1};
                update(iter);
                insert_fix(iter->left);
                return;
            } else iter=iter->left;
        } else {
            if (iter->right==nullptr) {
                iter->right=new kwarg {key,value, nullptr, nullptr, iter, 1};
                update(iter);
                insert_fix(iter->right);
                return;
            } else iter=iter->right;
        }
    }
}

template<typename K_Tp, typename V_Tp>
typename AVL_Tree<K_Tp, V_Tp>::kwarg *AVL_Tree<K_Tp, V_Tp>::search(const K_Tp &key) const {
    if (root == nullptr) return nullptr;
    kwarg *iter = root;
    while(true) {
        if (iter->key==key) {
            return iter;
        } if (key<iter->key) {
            if (iter->left==nullptr) {
                return nullptr;
            } else iter=iter->left;
        } else {
            if (iter->right==nullptr) {
                return nullptr;
            } else iter=iter->right;
        }
    }
}

template<typename K_Tp, typename V_Tp>
bool AVL_Tree<K_Tp, V_Tp>::exist(const K_Tp &key) const {
    if (root == nullptr) return false;
    kwarg *iter = root;
    while(true) {
        if (iter->key==key) {
            return true;
        } if (key<iter->key) {
            if (iter->left==nullptr) {
                return false;
            } else iter=iter->left;
        } else {
            if (iter->right==nullptr) {
                return false;
            } else iter=iter->right;
        }
    }
}

template<typename K_Tp, typename V_Tp>
void AVL_Tree<K_Tp, V_Tp>::insert_fix(AVL_Tree::kwarg *var) {
    kwarg *temp;
    int df, uf{};
    for (kwarg *iter=var;iter->father!= nullptr;iter=iter->father) {
        df = uf;
        uf = child(iter);
        if (unbalance(iter->father)) {
            switch (df + uf * 2) {
                case 0:
                    lt(iter);
                    return;
                case 1:
                    rt(temp);
                    lt(temp);
                    return;
                case 2:
                    lt(temp);
                    rt(temp);
                    return;
                default:
                    rt(iter);
                    return;
            }
        }
        temp = iter;
    }
}

template<typename K_Tp, typename V_Tp>
void AVL_Tree<K_Tp, V_Tp>::lt(AVL_Tree::kwarg *var) {
    kwarg *fv = var->father;
    if (root==fv) root=var;
    else child(fv) ? fv->father->right=var: fv->father->left=var;
    var->father = fv->father;
    fv->left = var->right;
    if (var->right!= nullptr) var->right->father=fv;
    fv->father = var;
    var->right = fv;
    update(fv);
}

template<typename K_Tp, typename V_Tp>
void AVL_Tree<K_Tp, V_Tp>::rt(AVL_Tree::kwarg *var) {
    kwarg *fv = var->father;
    if (root==fv) root=var;
    else child(fv) ? fv->father->right=var: fv->father->left=var;
    var->father = fv->father;
    fv->right = var->left;
    if (var->left != nullptr) var->left->father=fv;
    fv->father = var;
    var->left = fv;
    update(fv);
}

template<typename Tp>
void AVL_Tree<Tp, Tp>::insert(const Tp &elem) {
    if (root == nullptr) {
        root = new arg {elem, nullptr, nullptr, nullptr, 1};
        return;
    }
    arg *iter = root;
    while(true) {
        if (iter->value==elem) {
            return;
        } if (elem<iter->value) {
            if (iter->left==nullptr) {
                iter->left=new arg {elem, nullptr, nullptr, iter, 1};
                update(iter);
                insert_fix(iter->left);
                return;
            } else iter=iter->left;
        } else {
            if (iter->right==nullptr) {
                iter->right=new arg {elem, nullptr, nullptr, iter, 1};
                update(iter);
                insert_fix(iter->right);
                return;
            } else iter=iter->right;
        }
    }
}

template<typename Tp>
typename AVL_Tree<Tp, Tp>::arg *AVL_Tree<Tp, Tp>::search(const Tp &key) const {
    if (root == nullptr) return nullptr;
    arg *iter = root;
    while(true) {
        if (iter->key==key) {
            return iter;
        } if (key<iter->key) {
            if (iter->left==nullptr) {
                return nullptr;
            } else iter=iter->left;
        } else {
            if (iter->right==nullptr) {
                return nullptr;
            } else iter=iter->right;
        }
    }
}

template<typename Tp>
bool AVL_Tree<Tp, Tp>::exist(const Tp &key) const {
    if (root == nullptr) return false;
    arg *iter = root;
    while(true) {
        if (iter->key==key) {
            return true;
        } if (key<iter->key) {
            if (iter->left==nullptr) {
                return false;
            } else iter=iter->left;
        } else {
            if (iter->right==nullptr) {
                return false;
            } else iter=iter->right;
        }
    }
}

template<typename Tp>
size_t AVL_Tree<Tp, Tp>::abs(size_t x, size_t y) {
    return x>y?x-y:y-x;
}

template<typename Tp>
bool AVL_Tree<Tp, Tp>::unbalance(typename AVL_Tree<Tp, Tp>::arg *node) {
    return abs(node->left== nullptr?0:node->left->depth,
               node->right== nullptr?0:node->right->depth)>1;
}

template<typename Tp>
bool AVL_Tree<Tp, Tp>::child(typename AVL_Tree<Tp, Tp>::arg *node) {
    return node->father->right==node;
}

template<typename Tp>
void AVL_Tree<Tp, Tp>::update(typename AVL_Tree<Tp, Tp>::arg *node) {
    size_t ld, rd;
    for(arg *iter=node;iter!= nullptr;iter=iter->father) {
        ld = iter->left== nullptr?0:iter->left->depth;
        rd = iter->right== nullptr?0:iter->right->depth;
        iter->depth = ld>rd? ld+1: rd+1;
    }
}

template<typename Tp>
void AVL_Tree<Tp, Tp>::insert_fix(AVL_Tree<Tp, Tp>::arg *var) {
    arg *temp;
    int df, uf{};
    for (arg *iter=var;iter->father!= nullptr;iter=iter->father) {
        df = uf;
        uf = child(iter);
        if (unbalance(iter->father)) {
            switch (df + uf * 2) {
                case 0:
                    lt(iter);
                    return;
                case 1:
                    rt(temp);
                    lt(temp);
                    return;
                case 2:
                    lt(temp);
                    rt(temp);
                    return;
                default:
                    rt(iter);
                    return;
            }
        }
        temp = iter;
    }
}

template<typename Tp>
void AVL_Tree<Tp, Tp>::lt(AVL_Tree<Tp, Tp>::arg *var) {
    arg *fv = var->father;
    if (root==fv) root=var;
    else child(fv) ? fv->father->right=var: fv->father->left=var;
    var->father = fv->father;
    fv->left = var->right;
    if (var->right!= nullptr) var->right->father=fv;
    fv->father = var;
    var->right = fv;
    update(fv);
}

template<typename Tp>
void AVL_Tree<Tp, Tp>::rt(AVL_Tree<Tp, Tp>::arg *var) {
    arg *fv = var->father;
    if (root==fv) root=var;
    else child(fv) ? fv->father->right=var: fv->father->left=var;
    var->father = fv->father;
    fv->right = var->left;
    if (var->left != nullptr) var->left->father=fv;
    fv->father = var;
    var->left = fv;
    update(fv);
}

#endif //DATASTRUCTURE_AVL_TREE_HPP
