#ifndef DATASTRUCTURE_RED_BLACK_TREE_HPP
#define DATASTRUCTURE_RED_BLACK_TREE_HPP

template<typename K_Tp, typename V_Tp>
class Rb_Tree {
public:
    struct Rb_Node {
        Rb_Node *left, *right, *father;
        V_Tp value;
        K_Tp key;
        bool red;
    };

    Rb_Tree &operator=(Rb_Tree const &) noexcept = default;
    Rb_Tree &operator=(Rb_Tree &&) noexcept = default;
    Rb_Tree(Rb_Tree const &) noexcept = default;
    Rb_Tree(Rb_Tree &&) noexcept = default;
    ~Rb_Tree() = default;

    void insert(std::pair<K_Tp, V_Tp> const &);
    void emplace(K_Tp const &, V_Tp const &);
    void erase(K_Tp const &);

    V_Tp find(K_Tp const &) const;
    V_Tp &operator[](K_Tp const &);
    V_Tp &at(K_Tp const &);

    [[nodiscard]] unsigned long long size() const;
    [[nodiscard]] bool empty() const;

private:
    void insert_fix(Rb_Node *);
    void erase_fix(Rb_Node *);

    unsigned long long Size;
    Rb_Node *Root;
};

template<typename K_Tp, typename V_Tp>
void Rb_Tree<K_Tp, V_Tp>::insert(std::pair <K_Tp, V_Tp> const &) {

}

template<typename K_Tp, typename V_Tp>
void Rb_Tree<K_Tp, V_Tp>::emplace(const K_Tp &key, const V_Tp &value) {
    insert(std::pair<K_Tp, V_Tp> {key, value});
}

template<typename K_Tp, typename V_Tp>
void Rb_Tree<K_Tp, V_Tp>::erase(const K_Tp &) {

}

template<typename K_Tp, typename V_Tp>
V_Tp &Rb_Tree<K_Tp, V_Tp>::operator[](const K_Tp &key) {
    Rb_Node *iter=Root;
    while(iter!= nullptr) {
        if(key==iter->key) {
            return iter->value;
        } key>iter->key?
        iter=iter->right:iter=iter->left;
    }
    return *new V_Tp{};
}

template<typename K_Tp, typename V_Tp>
V_Tp Rb_Tree<K_Tp, V_Tp>::find(K_Tp const &key) const {
    Rb_Node *iter=Root;
    while(iter!= nullptr) {
        if(key==iter->key) {
            return iter->value;
        } key>iter->key?
            iter=iter->right:iter=iter->left;
    }
    return V_Tp{};
}

template<typename K_Tp, typename V_Tp>
V_Tp &Rb_Tree<K_Tp, V_Tp>::at(K_Tp const &key) {
    return this->operator[](key);
}

template<typename K_Tp, typename V_Tp>
unsigned long long Rb_Tree<K_Tp, V_Tp>::size() const {
    return Size;
}

template<typename K_Tp, typename V_Tp>
bool Rb_Tree<K_Tp, V_Tp>::empty() const {
    return Size==0;
}

template<typename K_Tp, typename V_Tp>
void Rb_Tree<K_Tp, V_Tp>::insert_fix(Rb_Tree::Rb_Node *) {

}

template<typename K_Tp, typename V_Tp>
void Rb_Tree<K_Tp, V_Tp>::erase_fix(Rb_Tree::Rb_Node *) {

}

#endif //DATASTRUCTURE_RED_BLACK_TREE_HPP
