#ifndef DATASTRUCTURE_PAIRING_HEAP_HPP
#define DATASTRUCTURE_PAIRING_HEAP_HPP

#include <queue>

template<class I>
class Pairing_Heap {
protected:
    struct args {
        I elem;
        args *father, *left, *brother;
    };

    args *Root;

    args *pair(args *, args *);

public:
    Pairing_Heap();

    void emplace(I const &);

    void merge(Pairing_Heap &);

    void erase();

    I front() const;
};

template<class I>
Pairing_Heap<I>::Pairing_Heap():
Root {nullptr} {}

template<class I>
I Pairing_Heap<I>::front() const {
    return Root!= nullptr? Root->elem: I{};
}

template<class I>
void Pairing_Heap<I>::erase() {
    if (Root == nullptr) throw;
    std::queue<args *> children {};
    args *iter = Root->left, *temp;
    while (iter!= nullptr) {
        children.push(iter);
        temp = iter;
        iter = iter->brother;
        temp->brother = nullptr;
    }
    while (children.size()>1) {
        temp = children.front();
        children.pop();
        temp = pair(temp, children.front());
        children.pop();
        children.push(temp);
    }
    Root = children.front();
}

template<class I>
void Pairing_Heap<I>::emplace(const I &key) {
    auto *heap = new args {key, nullptr, nullptr, nullptr};
    Root = pair(Root, heap);
}

template<class I>
typename Pairing_Heap<I>::args *Pairing_Heap<I>::
        pair(Pairing_Heap::args *a, Pairing_Heap::args *b) {
    if (a == nullptr) return b;
    if (b== nullptr||a->elem>b->elem) {
        return pair(b, a);
    }
    b->brother = a->left;
    a->left = b;
    b->father = a->father;
    return a;
}

template<class I>
void Pairing_Heap<I>::merge(Pairing_Heap &op) {
    Root = pair(Root, op.Root);
    op.Root = nullptr;
}

#endif //DATASTRUCTURE_PAIRING_HEAP_HPP
