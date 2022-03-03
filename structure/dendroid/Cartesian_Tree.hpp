#ifndef DATASTRUCTURE_CARTESIAN_TREE_HPP
#define DATASTRUCTURE_CARTESIAN_TREE_HPP

#include <algorithm>
#include <array>

template<typename Tp, size_t n>
class Cartesian_Tree {
public:
    struct Cartesian_Node {
        Tp value;
        Cartesian_Node *left, *right, *father;
    };

    explicit Cartesian_Tree([[maybe_unused]] std::array<Tp, n> const &);

    std::array<Tp, n> heapify();

protected:
    Cartesian_Node *Root;
    void insert(Tp const &);
};

template<typename Tp, size_t n>
Cartesian_Tree<Tp, n>::Cartesian_Tree([[maybe_unused]] const std::array<Tp, n> &array)
:Root{nullptr}
{
    std::array<Tp, n> arr {array};
    std::sort(arr.begin(), arr.end());
    for ([[maybe_unused]] auto const &iter: arr) insert(iter);
}

template<typename Tp, size_t n>
std::array<Tp, n> Cartesian_Tree<Tp, n>::heapify() {
    std::array<Tp, n> _res {};
    size_t index {};
    if (n==0) return _res;
    Cartesian_Node *iterator=Root;
    while(iterator->left!= nullptr) iterator=iterator->left;
    _res[index++] = iterator->value;
    for(size_t i=1;i!=n;++i) {
        if (iterator->right== nullptr) {
            iterator=iterator->father;
        } else {
            iterator=iterator->right;
            while(iterator->left!= nullptr) iterator=iterator->left;
        }
        _res[index++] = iterator->value;
    }
    return _res;
}

template<typename Tp, size_t n>
void Cartesian_Tree<Tp, n>::insert(const Tp &x) {
    if (Root== nullptr) {
        Root = new Cartesian_Node {x, nullptr, nullptr, nullptr};
        return;
    }
    Cartesian_Node *iterator = Root;
    Cartesian_Node *res;
    while(true) {
        if (x<iterator->value) {
            res = new Cartesian_Node{x, iterator, nullptr, iterator->father};
            if (iterator->father!= nullptr) iterator->father->right = res;
            iterator->father = res;
            return;
        } else {
            if (iterator->right!= nullptr) {
                iterator = iterator->right;
            } else break;
        }
    }
    iterator->right = new Cartesian_Node {x, nullptr, nullptr, nullptr};
}

template<typename Tp, size_t n>
std::array<Tp, n> cartesian_heap(std::array<Tp, n> const &array) {
    return Cartesian_Tree<Tp, n>(array).heapify();
}

#endif //DATASTRUCTURE_CARTESIAN_TREE_HPP
