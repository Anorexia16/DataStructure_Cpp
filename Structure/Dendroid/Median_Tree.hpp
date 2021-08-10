#ifndef DATASTRUCTURE_MEDIAN_TREE_HPP
#define DATASTRUCTURE_MEDIAN_TREE_HPP

typedef long long long_t;

template<class cls>
class Median_Tree final {
private:
    struct node final {
        cls value;
        long_t size{};
        node *father, * left, *right;
        node() = default;
    };

    node *top;

    bool child(node *);

    long_t size(node *);

    long_t balance(node *);
public:
    void insert(cls const &);

    cls front() const;

    void pop();
};

template<class cls>
void Median_Tree<cls>::insert(const cls &value) {
    if (top== nullptr) {
        top = new node {value, 1};
        return;
    }
    node *iter = top;
    while(true) {
        if (iter->left == nullptr&&value<iter->value) {
            iter->left= new node {value, 1, iter};
            return;
        } if (iter->right == nullptr && value>= iter->value) {
            iter->right = new node {value, 1, iter};
            return;
        } if (iter->left!= nullptr && value<iter->value&&
        value>=iter->left->value) {
            iter->left = new node {value, 1, iter, iter->left, nullptr};
            iter->left->left->father = iter->left;
            return;
        } if (iter->right != nullptr&& value>=iter->value&&
        value<iter->right->value) {
            iter->right = new node {value, 1, iter, nullptr, iter->right};
            iter->right->right->father = iter->right;
            return;
        } if (value>=iter->value) {
            iter =iter->right;
        } else {
            iter = iter->left;
        }
    }
}

template<class cls>
cls Median_Tree<cls>::front() const {
    return top->value;
}

template<class cls>
void Median_Tree<cls>::pop() {
    if (top->size==1) {
        top = nullptr;
        return;
    }
    node *iter = top, *rc = top;
    switch (top->size % 2) {
        case 0:
            while(iter->right!= nullptr) {
                iter=iter->right;
                while(iter->left!= nullptr) iter=iter->left;
                rc->value = iter->value;
            }
            child(iter)? iter->father->left = nullptr: iter->father->right= nullptr;
            break;
        default:
            while(iter->left!= nullptr) {
                iter=iter->left;
                while(iter->right!= nullptr) iter=iter->right;
                rc->value = iter->value;
            }
            child(iter)? iter->father->left = nullptr: iter->father->right= nullptr;
            break;
    }
}

template<class cls>
long_t Median_Tree<cls>::size(Median_Tree::node *ptr) {
    return ptr== nullptr?0:ptr->size;
}

template<class cls>
long_t Median_Tree<cls>::balance(Median_Tree::node *ptr) {
    return size(ptr)%2==0? size(ptr->right)- size(ptr->left)==1:
           size(ptr->right)== size(ptr->left);
}

template<class cls>
bool Median_Tree<cls>::child(node *ptr) {
    return ptr->father->right==ptr;
}

#endif //DATASTRUCTURE_MEDIAN_TREE_HPP
