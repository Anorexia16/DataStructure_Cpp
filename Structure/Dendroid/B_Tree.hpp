#ifndef DATASTRUCTURE_BP_TREE_HPP
#define DATASTRUCTURE_B_TREE_HPP

#include <cstdlib>

struct seek_ans {
    bool found {};
    size_t pos {};
};

template<size_t n>
constexpr size_t min_arg() {return (n+1)/2-1;}

template<size_t n>
constexpr size_t max_arg() {return n-1;}

template<typename K_Tp, typename V_Tp, size_t order>
class B_Tree{
protected:
    struct Node{
        Node() = default;

        K_Tp Keys[order-1] {};

        V_Tp Args[order-1] {};

        Node* Paths[order] {};

        Node *Father {};

        size_t Size {};

        seek_ans seek(K_Tp const &) const;

        void emplace(K_Tp const &, V_Tp const &, size_t);
    };

    Node *Root {};

    void spilt(Node &, K_Tp const &, V_Tp const &, size_t);

public:
    B_Tree() = default;

    void insert(K_Tp const &, V_Tp const &);

    V_Tp search(K_Tp const &) const;

    bool exist(K_Tp const &) const;

    void erase(K_Tp const &);
};

template<typename K_Tp, typename V_Tp, size_t order>
seek_ans B_Tree<K_Tp, V_Tp, order>::Node::seek(const K_Tp &key) const {
    size_t const _len = this->Size-1;
    if (_len == 0 || key < this->Container[0].Key) return seek_ans {false, 0};
    if (this->Container[_len - 1] == key) return seek_ans {true, _len - 1};
    if (this->Container[_len - 1] < key) return seek_ans {false, _len};

    for(size_t _i = 0; _i < _len-1; ++ _i)
    {
        if (key == Keys[_i])
        {
            return seek_ans {true, _i};
        }
        if (key > Keys[_i] && key < Keys[_i + 1])
        {
            return seek_ans {false, _i+1};
        }
    }
    return seek_ans {false, _len};
}

template<typename K_Tp, typename V_Tp, size_t order>
void B_Tree<K_Tp, V_Tp, order>::Node::emplace
(const K_Tp &key, const V_Tp &value, size_t pos) {
    for (size_t i=Size-1;i>=pos;--i) Paths[i+1] = Paths[i];
    for (size_t i=Size-2;i>=pos;--i) {
        Args[i+1] = Args[i];
        Keys[i+1] = Keys[i];
    }
    Keys[pos] = key;
    Args[pos] = value;
    Paths[pos] = nullptr;
    ++Size;
}

template<typename K_Tp, typename V_Tp, size_t order>
void B_Tree<K_Tp, V_Tp, order>::spilt
        (B_Tree::Node &node, const K_Tp &key, const V_Tp &value, size_t pos) {
    Node *_ln = new Node {}, *_rn = new Node{};
    bool done {};
    for (size_t i=0;i+i>=pos<(order-1)/2;++i) {
        _ln->Keys[i+i>=pos] = node.Keys[i];
        _ln->Args[i+i>=pos] = node.Args[i];
    }
    for (size_t i=(order-1)/2;i<order;++i) {

    }
}

template<typename K_Tp, typename V_Tp, size_t order>
void B_Tree<K_Tp, V_Tp, order>::insert(const K_Tp &key, const V_Tp &value) {
    if (Root == nullptr) {
        Root = new Node{};
        Root->Keys[0] = key;
        Root->Args[0] = value;
        ++Root->Size;
        return;
    }

    Node *iter {Root};
    seek_ans seeker;
    while(true) {
        seeker = iter->seek(key);
        if (seeker.found) {
            iter->Args[seeker.pos] = value;
            return;
        } else {
            if (iter->Paths[seeker.pos]!= nullptr) {
                iter = iter->Paths[seeker.pos];
                continue;
            } else {
                if (iter->Size != max_arg<order>()) {
                    iter->emplace(key, value, seeker.pos);
                } else {
                    spilt(*iter, key, value, seeker.pos);
                }
                return;
            }
        }
    }
}

template<typename K_Tp, typename V_Tp, size_t order>
V_Tp B_Tree<K_Tp, V_Tp, order>::search(const K_Tp &key) const {
    if (Root == nullptr) {
        return V_Tp{};
    }

    Node *iter {Root};
    seek_ans seeker;
    while(true) {
        seeker = iter->seek(key);
        if (seeker.found) {
            return iter->Args[seeker.pos];
        } else {
            if (iter->Paths[seeker.pos]!= nullptr) {
                iter = iter->Paths[seeker.pos];
                continue;
            } else {
                return V_Tp {};
            }
        }
    }
}

template<typename K_Tp, typename V_Tp, size_t order>
bool B_Tree<K_Tp, V_Tp, order>::exist(const K_Tp &key) const {
    if (Root == nullptr) {
        return false;
    }

    Node *iter {Root};
    seek_ans seeker;
    while(true) {
        seeker = iter->seek(key);
        if (seeker.found) {
            return true;
        } else {
            if (iter->Paths[seeker.pos]!= nullptr) {
                iter = iter->Paths[seeker.pos];
                continue;
            } else {
                return false;
            }
        }
    }
}

template<typename K_Tp, typename V_Tp, size_t order>
void B_Tree<K_Tp, V_Tp, order>::erase(const K_Tp &key) {

}


#endif //DATASTRUCTURE_BP_TREE_HPP
