#ifndef DATASTRUCTURE_LEFTIST_TREE_HPP
#define DATASTRUCTURE_LEFTIST_TREE_HPP

#include "Binary_Tree.hpp"
#include <functional>
#include <iterator>

enum class LT_Index {Weight, Height};

template<class cls>
class Leftist_Tree {
public:
    explicit Leftist_Tree(enum LT_Index const &, bool const &);

    template<class Container_Type>
    explicit Leftist_Tree(Container_Type const &, enum LT_Index const &, bool const &);

    explicit Leftist_Tree(cls const &, enum LT_Index const &, bool const &);

    void insert(Binary_Node<cls> &);

    void insert(cls const &);

    void remove(cls const &);

    void merge(Leftist_Tree<cls> &);

    template<typename K_Tp>
    cls &find(K_Tp const &);

    Leftist_Tree &operator=(Leftist_Tree const &) noexcept = default;

    Leftist_Tree &operator=(Leftist_Tree &&) noexcept = default;

    Leftist_Tree(Leftist_Tree const &) noexcept = default;

    Leftist_Tree(Leftist_Tree &&) noexcept = default;

    [[nodiscard]] size_t weight() const;

    [[nodiscard]] size_t height() const;

    [[nodiscard]] bool empty() const;

    cls top() const;

    void clear();

    void pop();

    Binary_Node<cls> *Top;

protected:
    bool Compare_Flag;

    LT_Index Value_Flag;

private:
    static Binary_Node<cls> &merge_algorithm(Binary_Node<cls> & , Binary_Node<cls> &, LT_Index, bool);
};

template<class cls>
Leftist_Tree<cls>::Leftist_Tree(const LT_Index &index, const bool &reverse)
:Compare_Flag {reverse}, Value_Flag{index} , Top{nullptr} {}

template<class cls>
template<class Container_Type>
Leftist_Tree<cls>::Leftist_Tree(const Container_Type &container, const LT_Index &index, const bool &reverse)
:Compare_Flag {reverse}, Value_Flag{index} , Top{nullptr} {
    for (auto const &iter : container) {
        this->insert(iter);
    }
}

template<class cls>
Leftist_Tree<cls>::Leftist_Tree(const cls &value, const LT_Index &index, const bool &reverse)
        :Compare_Flag {reverse}, Value_Flag{index} , Top{new Binary_Node<cls> {value}} {}

template<class cls>
void Leftist_Tree<cls>::insert(const cls &value) {
    this->merge(*new Leftist_Tree {value, this->Value_Flag, this->Compare_Flag});
}

template<class cls>
void Leftist_Tree<cls>::insert(Binary_Node<cls> &node) {
    if (this->Top == nullptr) {
        this->Top = &node;
        return;
    }
    this->merge_algorithm(*this->Top, node, this->Value_Flag, this->Compare_Flag);
}

template<class cls>
void Leftist_Tree<cls>::remove(const cls &value) {

}

template<class cls>
void Leftist_Tree<cls>::merge(Leftist_Tree<cls> &op_tree) {
    if (this->Compare_Flag != op_tree.Compare_Flag || this->Value_Flag != op_tree.Value_Flag) throw;
    if (this->Top == nullptr) {
        this->Top = new Binary_Node<cls> {*op_tree.Top};
        op_tree.clear();
        return;
    }
    if (op_tree.Top == nullptr) return;
    this->Top = &Leftist_Tree::merge_algorithm(*this->Top, *op_tree.Top, this->Value_Flag, this->Compare_Flag);
}

template<class cls>
template<typename K_Tp>
cls &Leftist_Tree<cls>::find(const K_Tp &key) {
    return *new cls{};
}

template<class cls>
size_t Leftist_Tree<cls>::weight() const {
    return this->Top == nullptr? 0 :this->Top->size();
}

template<class cls>
size_t Leftist_Tree<cls>::height() const {
    return this->Top == nullptr ? 0 : this->Top->depth();
}

template<class cls>
bool Leftist_Tree<cls>::empty() const {
    return this->Top == nullptr;
}

template<class cls>
cls Leftist_Tree<cls>::top() const {
    if (this->empty()) throw;
    return this->Top->value_c();
}

template<class cls>
void Leftist_Tree<cls>::clear() {
    this->Top == nullptr;
}


template<class cls>
void Leftist_Tree<cls>::pop() {
    switch (this->Top->leaves_count()) {
        case 0:
            this->Top = nullptr;
            return;
        case 1:
            this->Top->left_p()->Father = this->Top->Father;
            this->Top = this->Top->left_p();
            return;
        default:
            Binary_Node<cls> *_ptr = this->Top->Father;
            this->Top = &Leftist_Tree::merge_algorithm(this->Top->left(), this->Top->right(), this->Value_Flag, this->Compare_Flag);
            this->Top->Father = _ptr;
            return;
    }
}

template<class cls>
Binary_Node<cls> &Leftist_Tree<cls>::merge_algorithm(Binary_Node<cls> &_a, Binary_Node<cls> &_b, LT_Index index, bool reverse) {
    if((!reverse && _a.value_c()<_b.value_c()) || (reverse && _a.value_c() > _b.value_c())) {
        _a.swap_pos(_b);
        return Leftist_Tree::merge_algorithm(_b, _a, index, reverse);
    }

    switch (_a.leaves_count()) {
        case 0:
            _a.link_d(_b);
            return _a;
        case 1:
            _a.link_d(_b);
            break;
        default:
            _a.Right_Child = &Leftist_Tree::merge_algorithm(_a.right(), _b, index, reverse);
            break;
    }

    if ((index == LT_Index::Height && _a.left().depth() < _a.right().depth()) ||
        (index == LT_Index::Weight && _a.left().size() < _b.right().size())) {
        Binary_Node<cls> *_temp_side = _a.Right_Child;
        _a.Right_Child = _a.Left_Child;
        _a.Left_Child = _temp_side;
    }
    return _a;
}

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont = std::vector>
Leftist_Tree<cls> make_LT(enum LT_Index index  = LT_Index::Height, bool reverse = false) {
    return Leftist_Tree<cls>(std::vector<cls>{}, index, reverse);
}

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
Leftist_Tree<cls> make_LT(Cont<cls> const &container, enum LT_Index index = LT_Index::Height, bool reverse=false) {
    return Leftist_Tree<cls>(container, index, reverse);
}

template<class cls>
Leftist_Tree<cls> make_LT(std::istream &&in, enum LT_Index index = LT_Index::Height, bool reverse = false) {
    std::vector<cls> vec{};
    std::move(std::istream_iterator<cls>(in), std::istream_iterator<cls>(), std::begin(vec));
    return Leftist_Tree<cls>(vec, index, reverse);
}

template<class cls>
Leftist_Tree<cls> make_LT(std::initializer_list<cls> const &list, enum LT_Index index = LT_Index::Height, bool reverse = false) {
    return Leftist_Tree<cls>(list, index, reverse);
}

template<class cls, size_t size>
Leftist_Tree<cls> make_LT(std::array<cls, size> const &array, enum LT_Index index = LT_Index::Height, bool reverse = false) {
    return Leftist_Tree<cls>(array, index, reverse);
}

template<class cls>
Leftist_Tree<cls> make_LT(cls const * const &ptr, size_t const &size, enum LT_Index index = LT_Index::Height, bool reverse = false) {
    std::vector<cls> vec{};
    for(auto i=0;i!=size; ++i) vec.template emplace_back(const_cast<cls>(ptr[i]));
    return Leftist_Tree<cls>(vec, index, reverse);
}

#endif //DATASTRUCTURE_LEFTIST_TREE_HPP