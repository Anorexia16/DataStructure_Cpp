#ifndef DATASTRUCTURE_RED_BLACK_TREE_HPP
#define DATASTRUCTURE_RED_BLACK_TREE_HPP

#include <iterator>

template<typename K_Tp, typename V_Tp>
class RB_Tree final
{
private:
    struct lite_pair {K_Tp key; V_Tp value;};

    struct RB_Node
            {
        lite_pair container;
        RB_Node *father{}, left{}, right{};
        bool red {true};

        template<typename arg1, typename arg2>
        RB_Node(arg1 &&key, arg2 &&value);

        template<typename arg1, typename arg2>
        RB_Node(arg1 &&key, arg2 &&value, RB_Node *f, RB_Node *l, RB_Node *r, bool c);

    } *root;

    struct RB_iter:std::iterator<std::bidirectional_iterator_tag, lite_pair>
            {
        RB_Node *index;

        explicit RB_iter(RB_Node *ptr): index{ptr} {}

        lite_pair *operator->() {return &index->container;}
        lite_pair &operator*() {return index->container;}

        RB_iter operator++(int) const;
        RB_iter operator--(int) const;
        RB_iter &operator++();
        RB_iter &operator--();

        bool operator==(RB_iter const &) const;
        bool operator!=(RB_iter const &) const;
        bool operator>=(RB_iter const &) const;
        bool operator<=(RB_iter const &) const;
        bool operator>(RB_iter const &) const;
        bool operator<(RB_iter const &) const;
    };

    void insert_fix(RB_Node *);
    void erase_fix(RB_Node *);
    inline bool il(RB_Node *);

    bool is_black(RB_Node *) const;
    RB_Node *travel(K_Tp const &);
    void insert(RB_Node *);
    void remove(RB_Node *);

    size_t Size{};

public:
    void push(std::pair<K_Tp, V_Tp> const &);

    void push(K_Tp const &, V_Tp const &);

    void push(K_Tp &&, V_Tp &&);

    template<typename arg1, typename arg2>
    void emplace(std::pair<arg1, arg2> const &);

    template<typename arg1, typename arg2>
    void emplace(arg1 &&, arg2 &&);

    V_Tp find(K_Tp const &) const;

    bool exist(K_Tp const &);

    V_Tp &at(K_Tp const &);

    [[nodiscard]] size_t size() const;

    [[nodiscard]] bool empty() const;

    void erase(K_Tp const &);

    void clear();

    RB_iter begin();

    RB_iter end();
};

template<typename K_Tp, typename V_Tp>
template<typename arg1, typename arg2>
RB_Tree<K_Tp, V_Tp>::RB_Node::RB_Node(arg1 &&key, arg2 &&value):
        container{std::forward<>(key), std::forward<>(value)} {}

template<typename K_Tp, typename V_Tp>
template<typename arg1, typename arg2>
RB_Tree<K_Tp, V_Tp>::RB_Node::RB_Node(arg1 &&key, arg2 &&value, RB_Tree::RB_Node *f, RB_Tree::RB_Node *l,
                                      RB_Tree::RB_Node *r, bool c):
        container{std::forward<>(key), std::forward<>(value)},
        father{f}, left{l}, right{r}, red{c} {}

template<typename K_Tp, typename V_Tp>
typename RB_Tree<K_Tp, V_Tp>::RB_iter &RB_Tree<K_Tp, V_Tp>::RB_iter::operator++()
{
    if(index->right != nullptr)
    {
        index = index->right;
        while(index->left != nullptr)
            index = index->left;
    } else if (index->father != nullptr)
    {
        index = index->father;
    } else {index = nullptr;}
}

template<typename K_Tp, typename V_Tp>
typename RB_Tree<K_Tp, V_Tp>::RB_iter &RB_Tree<K_Tp, V_Tp>::RB_iter::operator--()
{
    if(index->left != nullptr)
    {
        index = index->left;
        while(index->right != nullptr)
            index = index->right;
    } else if (index->father != nullptr)
    {
        index = index->father;
    } else {index = nullptr;}
}

template<typename K_Tp, typename V_Tp>
void RB_Tree<K_Tp, V_Tp>::insert(RB_Tree::RB_Node *info)
{
    if (this->root == nullptr)
        root = info;
    K_Tp const &key = info->container.key;
    RB_Node *iter = root;
    while(iter!= nullptr)
    {
        if (iter->container.key == key)
        {
            iter->container.value = info->container.value;
            return;
        }
        if (iter->container.key > key)
        {
            if (iter->left != nullptr)
            {
                iter = iter->left;
            } else {
                iter->left = info;
            }
        } else {
            if (iter->right != nullptr)
            {
                iter = iter->rifht;
            } else {
                iter->right = info;
            }
        }
    }
    ++Size;
    insert_fix(info);
}

template<typename K_Tp, typename V_Tp>
void RB_Tree<K_Tp, V_Tp>::remove(RB_Tree::RB_Node *node)
{
    --Size;

    if (node->left== nullptr && node->right == nullptr)
    {
        bool extra_black {!node->red};
        if (root == node) {
            root = nullptr;
            return;
        } else {
            node->father->left == node ?
            node->father->left = nullptr: node->father->right = nullptr;
            if (extra_black) erase_fix(node->father);
        }
    }
    if (node->right != nullptr)
    {
        RB_Node *temp = node->right;
        while(temp->left!= nullptr) temp=temp->left;
        node->container = temp->container;
        remove(temp);
    } else {
        RB_Node *temp = node->left;
        while(temp->right!= nullptr) temp=temp->right;
        node->container = temp->container;
        remove(temp);
    }
}

template<typename K_Tp, typename V_Tp>
typename RB_Tree<K_Tp, V_Tp>::RB_iter RB_Tree<K_Tp, V_Tp>::RB_iter::operator++(int) const
{
    RB_iter temp {*this};
    ++(*this);
    return temp;
}

template<typename K_Tp, typename V_Tp>
typename RB_Tree<K_Tp, V_Tp>::RB_iter RB_Tree<K_Tp, V_Tp>::RB_iter::operator--(int) const
{
    RB_iter temp {*this};
    --(*this);
    return temp;
}

template<typename K_Tp, typename V_Tp>
bool RB_Tree<K_Tp, V_Tp>::RB_iter::operator==(const RB_Tree::RB_iter &rhv) const
{
    return index==rhv.index;
}

template<typename K_Tp, typename V_Tp>
bool RB_Tree<K_Tp, V_Tp>::RB_iter::operator!=(const RB_Tree::RB_iter &rhv) const
{
    return index!=rhv.index;
}

template<typename K_Tp, typename V_Tp>
bool RB_Tree<K_Tp, V_Tp>::RB_iter::operator>=(const RB_Tree::RB_iter &) const
{
    return index->container.key>=index->container.key;
}

template<typename K_Tp, typename V_Tp>
bool RB_Tree<K_Tp, V_Tp>::RB_iter::operator<=(const RB_Tree::RB_iter &) const
{
    return index->container.key<=index->container.key;
}

template<typename K_Tp, typename V_Tp>
bool RB_Tree<K_Tp, V_Tp>::RB_iter::operator<(const RB_Tree::RB_iter &) const
{
    return index->container.key<index->container.key;
}

template<typename K_Tp, typename V_Tp>
bool RB_Tree<K_Tp, V_Tp>::RB_iter::operator>(const RB_Tree::RB_iter &) const
{
    return index->container.key>index->container.key;
}

template<typename K_Tp, typename V_Tp>
void RB_Tree<K_Tp, V_Tp>::push(const std::pair<K_Tp, V_Tp> &pair)
{
    auto *node = new RB_Node {pair.first, pair.second};
    insert(node);
}

template<typename K_Tp, typename V_Tp>
void RB_Tree<K_Tp, V_Tp>::push(const K_Tp &key, const V_Tp &value)
{
    auto *node = new RB_Node {key, value};
    insert(node);
}

template<typename K_Tp, typename V_Tp>
void RB_Tree<K_Tp, V_Tp>::push(K_Tp &&key, V_Tp &&value)
{
    auto *node = new RB_Node {std::move(key), std::move(value)};
    insert(node);
}

template<typename K_Tp, typename V_Tp>
template<typename arg1, typename arg2>
void RB_Tree<K_Tp, V_Tp>::emplace(const std::pair<arg1, arg2> &pair)
{
    auto *node = new RB_Node {pair.first, pair.second};
    insert(node);
}

template<typename K_Tp, typename V_Tp>
template<typename arg1, typename arg2>
void RB_Tree<K_Tp, V_Tp>::emplace(arg1 &&key, arg2 &&value)
{
    auto *node = new RB_Node {std::forward<>(key), std::forward<>(value)};
    insert(node);
}

template<typename K_Tp, typename V_Tp>
size_t RB_Tree<K_Tp, V_Tp>::size() const
{
    return Size;
}

template<typename K_Tp, typename V_Tp>
bool RB_Tree<K_Tp, V_Tp>::empty() const
{
    return Size==0;
}

template<typename K_Tp, typename V_Tp>
bool RB_Tree<K_Tp, V_Tp>::exist(const K_Tp &key)
{
    RB_Node *tar = travel(key);
    return tar != nullptr;
}

template<typename K_Tp, typename V_Tp>
V_Tp RB_Tree<K_Tp, V_Tp>::find(const K_Tp &key) const
{
    RB_Node *tar = travel(key);
    return tar != nullptr ? tar->container.value : V_Tp{};
}

template<typename K_Tp, typename V_Tp>
V_Tp &RB_Tree<K_Tp, V_Tp>::at(const K_Tp &key)
{
    RB_Node *tar = travel(key);
    return tar != nullptr ? tar->container.value : *new V_Tp{};
}

template<typename K_Tp, typename V_Tp>
void RB_Tree<K_Tp, V_Tp>::erase(const K_Tp &key)
{
    RB_Node *tar = travel(key);
    if (tar != nullptr) remove(tar);
}

template<typename K_Tp, typename V_Tp>
void RB_Tree<K_Tp, V_Tp>::clear()
{
    Size = 0;
    for(RB_iter r_iter=std::begin(*this);;)
    {
        RB_Node *temp = r_iter.index;
        ++r_iter;
        delete *temp;
        if (r_iter.index == nullptr) return;
    }
}

template<typename K_Tp, typename V_Tp>
typename RB_Tree<K_Tp, V_Tp>::RB_Node *RB_Tree<K_Tp, V_Tp>::travel(const K_Tp &key)
{
    if (this->root == nullptr) return nullptr;
    RB_Node *iter = root;
    while(iter!= nullptr) {
        if (iter->container.key == key)
        {
            return iter;
        }
        iter = il(iter) ? iter->left: iter->right;
    }
}

template<typename K_Tp, typename V_Tp>
typename RB_Tree<K_Tp, V_Tp>::RB_iter RB_Tree<K_Tp, V_Tp>::begin()
{
    RB_Node *sm = root;
    while(sm->left != nullptr) sm=sm->left;
    return RB_iter {this, root};
}

template<typename K_Tp, typename V_Tp>
typename RB_Tree<K_Tp, V_Tp>::RB_iter RB_Tree<K_Tp, V_Tp>::end()
{
    return RB_iter {this, nullptr};
}

template<typename K_Tp, typename V_Tp>
bool RB_Tree<K_Tp, V_Tp>::is_black(RB_Tree::RB_Node *node) const
{
    return node == nullptr || !node->red;
}

template<typename K_Tp, typename V_Tp>
bool RB_Tree<K_Tp, V_Tp>::il(RB_Tree::RB_Node *ptr) {return ptr->father->left == ptr;}

template<typename K_Tp, typename V_Tp>
void RB_Tree<K_Tp, V_Tp>::insert_fix(RB_Tree::RB_Node *node)
{
    if (root == node)
    {
        node->red = false;
        return;
    }
    if (!node->father->red)
        return;

}

template<typename K_Tp, typename V_Tp>
void RB_Tree<K_Tp, V_Tp>::erase_fix(RB_Tree::RB_Node *)
{

}

#endif //DATASTRUCTURE_RED_BLACK_TREE_HPP
