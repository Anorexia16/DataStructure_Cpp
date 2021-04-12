#ifndef DATASTRUCTURE_LEFTIST_TREE_HPP
#define DATASTRUCTURE_LEFTIST_TREE_HPP

#include <array>

template<class cls>
class Leftist_Tree {
public:
    struct Leftist_Node
    {
        explicit Leftist_Node(cls const &);

        Leftist_Node *Father;

        Leftist_Node *Right;

        Leftist_Node *Left;

        size_t Depth;

        cls Value;
    };

    explicit Leftist_Tree(bool = false);

    void insert(Leftist_Node &);

    void insert(cls const &);

    void merge(Leftist_Tree<cls> &);

    [[nodiscard]] size_t size() const;

    [[nodiscard]] bool empty() const;

    cls top() const;

    void pop();

private:
    Leftist_Node &merge_algorithm(Leftist_Node & , Leftist_Node &);

protected:
    Leftist_Node *Top;

    bool Reverse;

    size_t Size;
};

template<class cls>
Leftist_Tree<cls>::Leftist_Node::Leftist_Node(const cls &value)
:Value{value},Father{}, Left{nullptr}, Right{nullptr}, Depth{1} {}

template<class cls>
Leftist_Tree<cls>::Leftist_Tree(bool reverse)
:Top{nullptr}, Size{}, Reverse{reverse} {}


template<class cls>
void Leftist_Tree<cls>::insert(const cls &value) {
    this->insert(*new Leftist_Node {value});
}

template<class cls>
void Leftist_Tree<cls>::insert(Leftist_Tree<cls>::Leftist_Node &node) {
    if (this->Top == nullptr) {
        this->Top = &node;
        this->Size = 1;
        return;
    }
    this->merge_algorithm(*this->Top, node);
    ++this->Size;
}

template<class cls>
void Leftist_Tree<cls>::merge(Leftist_Tree<cls> &op_tree) {
    if (this->Top == nullptr) {
        this->Top = op_tree.Top;
        op_tree.Top = nullptr;
        return;
    }
    if (op_tree.Top == nullptr) return;
    this->Top = &Leftist_Tree::merge_algorithm(*this->Top, *op_tree.Top);
    this->Size += op_tree.Size;
}


template<class cls>
size_t Leftist_Tree<cls>::size() const {
    return this->Size;
}

template<class cls>
bool Leftist_Tree<cls>::empty() const {
    return this->Top == nullptr;
}

template<class cls>
cls Leftist_Tree<cls>::top() const {
    if (this->Top == nullptr) return cls{};
    return this->Top->Value;
}

template<class cls>
void Leftist_Tree<cls>::pop() {
    if(this->Top->Left==nullptr && this->Top->Right== nullptr)
    {
        this->Top = nullptr;
    } else if (this->Top->Right == nullptr) {
        this->Top->Left->Father = nullptr;
        this->Top = this->Top->Left;
    } else {
        this->Top = &this->merge_algorithm(*this->Top->Left, *this->Top->Right);
    }
    --this->Size;
}

template<class cls>
typename Leftist_Tree<cls>::Leftist_Node &Leftist_Tree<cls>::merge_algorithm(Leftist_Tree::Leftist_Node &_a, Leftist_Node &_b) {
    if((!this->Reverse && _a.Value<_b.Value) || (this->Reverse && _a.Value > _b.Value)) {
        Leftist_Node *_temp_father_ptr = _a.Father;
        if (_a.Father != nullptr && _a.Father->Left == &_a) {
            _a.Father->Left == &_b;
        } else if (_a.Father != nullptr && _a.Father->Right == &_a) {
            _a.Father->Right = &_b;
        }
        if (_b.Father != nullptr && _b.Father->Left == &_b) {
            _b.Father->Left = &_a;
        } else if (_b.Father != nullptr && _b.Father->Right == &_b) {
            _b.Father->Right = &_a;
        }
        _a.Father = _b.Father;
        _b.Father = _temp_father_ptr;
        if(this->Top == &_a) this->Top = &_b;
        else if(this->Top == &_b) this->Top = &_a;
        return this->merge_algorithm(_b, _a);
    }

    if (_a.Left == nullptr)
    {
        _a.Left = &_b;
        _b.Father = &_a;

        for(Leftist_Node *_node = &_a;_node != nullptr; _node = _node->Father)
        {
            _node->Depth = std::max(_node->Left==nullptr? 0: _node->Left->Depth, _node->Right==nullptr? 0 : _node->Right->Depth) + 1;
        }
        return _a;
    } else if (_a.Right == nullptr) {
        _a.Right = &_b;
        _b.Father = &_a;
        for(Leftist_Node *_node = &_a;_node != nullptr; _node = _node->Father)
        {
            _node->Depth = std::max(_node->Left==nullptr? 0: _node->Left->Depth, _node->Right==nullptr? 0 : _node->Right->Depth) + 1;
        }
    } else {
        _a.Right = &this->merge_algorithm(*_a.Right, _b);
    }

    if (_a.Left->Depth < _a.Right->Depth) {
        Leftist_Node *_temp_side = _a.Right;
        _a.Right = _a.Left;
        _a.Left = _temp_side;
    }
    return _a;
}



template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
Leftist_Tree<cls> make_LT(bool reverse = false) {
    return Leftist_Tree<cls>(reverse);
}

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
Leftist_Tree<cls> make_LT(Cont<cls> const &container, bool reverse=false) {
    Leftist_Tree<cls> _res {reverse};
    for(auto const &iter: container) _res.insert(iter);
    return _res;
}

template<class cls>
Leftist_Tree<cls> make_LT(std::initializer_list<cls> const &list, bool reverse = false) {
    Leftist_Tree<cls> _res {reverse};
    for(auto const &iter: list) _res.insert(iter);
    return _res;
}

template<class cls, size_t size>
Leftist_Tree<cls> make_LT(std::array<cls, size> const &array, bool reverse = false) {
    Leftist_Tree<cls> _res {reverse};
    for(auto const &iter: array) _res.insert(iter);
    return _res;
}

template<class cls, size_t size>
Leftist_Tree<cls> make_LT(cls const ptr[size] , bool reverse = false) {
    Leftist_Tree<cls> _res {reverse};
    for(auto i=0;i!=size; ++i) _res.insert(ptr[i]);
    return _res;
}

#endif //DATASTRUCTURE_LEFTIST_TREE_HPP