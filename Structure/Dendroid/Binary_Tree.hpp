#ifndef DATASTRUCTURE_BINARY_TREE_HPP
#define DATASTRUCTURE_BINARY_TREE_HPP

#include "../Abstract/Abstract_Tree.hpp"
#include "../Linear/Deque_Chain.hpp"
#include <vector>

template<typename Tp>
struct Binary_Node {
    explicit Binary_Node(Tp const & = Tp{});

    [[nodiscard]] inline size_t locate() const;

    [[nodiscard]] std::vector<size_t> path() const;

    [[nodiscard]] inline size_t degree() const;

    [[nodiscard]] inline size_t level() const;

    void swap_pos(Binary_Node<Tp> &op);

    void resize(size_t const &);

    void broadcast();

    void sink();

    Binary_Node<Tp> *Left_Child;

    Binary_Node<Tp> *Right_Child;

    Binary_Node<Tp> *Father;

    size_t Depth;

    size_t Size;

    size_t Child_num;

    Tp Element;
};

template<typename Tp>
class Binary_Tree: virtual public Tree<Tp, Binary_Node> {
public:
    Binary_Tree();

    Binary_Tree &operator=(Binary_Tree<Tp> const &) noexcept = default;

    Binary_Tree &operator=(Binary_Tree<Tp> &&) noexcept = default;

    Binary_Tree(Binary_Tree<Tp> const &) noexcept = default;

    Binary_Tree(Binary_Tree<Tp> &&) noexcept = default;

    ~Binary_Tree() = default;

    void bind_top(Binary_Node<Tp> &);

    [[nodiscard]] inline bool full() const;

    [[nodiscard]] inline size_t degree() const;

    [[nodiscard]] inline size_t depth() const;

    [[nodiscard]] inline size_t weight() const;

    [[nodiscard]] inline bool empty() const;

    Binary_Node<Tp> &top_c() const;

    Binary_Node<Tp> &top();

    bool complete() const;

    void clear();

    class BT_base_iterator: std::iterator<std::forward_iterator_tag, Tp> {
    public:
        explicit BT_base_iterator(Binary_Tree<Tp> &);

        BT_base_iterator(Binary_Tree<Tp> &, Tree_Iterator_Methods const &);

        BT_base_iterator(BT_base_iterator const &) noexcept = default;

        BT_base_iterator(BT_base_iterator &&) noexcept = default;

        BT_base_iterator &operator=(BT_base_iterator const &) noexcept = default;

        BT_base_iterator &operator=(BT_base_iterator &&) noexcept = default;

        Tp &operator*();

        Tp *operator->();

        virtual inline bool operator<(BT_base_iterator const &) const;

        virtual inline bool operator>(BT_base_iterator const &) const;

        virtual inline bool operator==(BT_base_iterator const &) const;

        virtual inline bool operator!=(BT_base_iterator const &) const;

        virtual inline bool operator<=(BT_base_iterator const &) const;

        virtual inline bool operator>=(BT_base_iterator const &) const;

        BT_base_iterator &operator++();

        BT_base_iterator const operator++(int) const;

        template<Tree_Iterator_Methods methods>
        BT_base_iterator &iterator_plus_processor();

        inline void straight_left(bool const &);

        Binary_Node<Tp> *Ptr;

        size_t Index;

    protected:
        Deque_C<Binary_Node<Tp> *> Cache_Container;

        Binary_Tree<Tp> *Owner_Tree;
    };

    class BT_base_const_iterator: std::iterator<std::forward_iterator_tag, Tp> {
    public:
        explicit BT_base_const_iterator(Binary_Tree<Tp> const &);

        BT_base_const_iterator(Binary_Tree<Tp> const &, Tree_Iterator_Methods const &);

        BT_base_const_iterator(BT_base_const_iterator const &) noexcept = default;

        BT_base_const_iterator(BT_base_const_iterator &&) noexcept = default;

        BT_base_const_iterator &operator=(BT_base_const_iterator const &) noexcept = default;

        BT_base_const_iterator &operator=(BT_base_const_iterator &&) noexcept = default;

        Tp &operator*() const;

        Tp *operator->() const;

        virtual inline bool operator<(BT_base_const_iterator const &) const;

        virtual inline bool operator>(BT_base_const_iterator const &) const;

        virtual inline bool operator==(BT_base_const_iterator const &) const;

        virtual inline bool operator!=(BT_base_const_iterator const &) const;

        virtual inline bool operator<=(BT_base_const_iterator const &) const;

        virtual inline bool operator>=(BT_base_const_iterator const &) const;

        BT_base_const_iterator &operator++();

        BT_base_const_iterator const operator++(int) const;

        template<Tree_Iterator_Methods methods>
        BT_base_const_iterator &iterator_plus_processor();

        Binary_Node<Tp> const *Ptr;

        size_t Index;

    protected:
        Deque_C<Binary_Node<Tp> const*> Cache_Container;

        Binary_Tree<Tp> const *Owner_Tree;

    private:
        inline void straight_left(bool const &);
    };


    BT_base_iterator begin();

    BT_base_iterator end();

    BT_base_const_iterator cbegin() const;

    BT_base_const_iterator cend() const;

    inline void to_prev();

    inline void to_inner();

    inline void to_post();

    inline void to_scope();

    static void path_compaction(Binary_Tree<Tp> &);

    static void path_compaction(Binary_Node<Tp> &);

    static void path_splitting(Binary_Tree<Tp> &);

    static void path_halving(Binary_Tree<Tp> &);

    template<class cls>
    friend Binary_Tree<cls> merge_binary_tree(Binary_Tree<cls> &a_tree, Binary_Tree<cls> &b_tree);

    template<class cls>
    friend Binary_Tree<cls> unite_binary_tree(Binary_Tree<cls> &a_tree, Binary_Tree<cls> &b_tree);

    Binary_Node<Tp> &find(Tp const &);

    Binary_Node<Tp> &get(size_t const &);

    mutable Tree_Iterator_Methods Method;

protected:
    Binary_Node<Tp> *Top;

    size_t *Size;
};

template<typename Tp>
Binary_Tree<Tp>::BT_base_iterator::BT_base_iterator(Binary_Tree<Tp> &Tree)
        : Cache_Container{}, Owner_Tree{&Tree}, Ptr{&Tree.top()}, Index{0} {}

template<typename Tp>
Binary_Tree<Tp>::BT_base_iterator::BT_base_iterator(Binary_Tree<Tp> &Tree, Tree_Iterator_Methods const &method)
        :Cache_Container{}, Owner_Tree{&Tree}, Ptr{&Tree.top()}, Index{0} {
    switch (method) {
        case Tree_Iterator_Methods::Scope:
            switch (this->Ptr->Child_num) {
                case 2:
                    this->Cache_Container.emplace_back(this->Ptr->Left_Child);
                    this->Cache_Container.emplace_back(this->Ptr->Right_Child);
                    break;
                case 1:
                    this->Cache_Container.emplace_back(this->Ptr->Left_Child);
                    break;
                default:
                    break;
            }
            break;
        case Tree_Iterator_Methods::Inner:
            this->straight_left(true);
        case Tree_Iterator_Methods::Post:
            this->straight_left(false);
        case Tree_Iterator_Methods::Prev:
            break;
    }
}

template<typename Tp>
Tp &Binary_Tree<Tp>::BT_base_iterator::operator*() {
    return this->Ptr->Element;
}

template<typename Tp>
Tp *Binary_Tree<Tp>::BT_base_iterator::operator->() {
    return &this->Ptr->Element;
}

template<typename Tp>
bool Binary_Tree<Tp>::BT_base_iterator::operator<(const Binary_Tree::BT_base_iterator &op) const {
    if (static_cast<void *>(this->Owner_Tree) == static_cast<void *>(op.Owner_Tree)) throw;
    return this->Ptr->Element < op.Ptr->Element;
}

template<typename Tp>
bool Binary_Tree<Tp>::BT_base_iterator::operator>(const Binary_Tree::BT_base_iterator &op) const {
    if (static_cast<void *>(this->Owner_Tree) == static_cast<void *>(op.Owner_Tree)) throw;
    return this->Ptr->Element >op.Ptr->Element;
}

template<typename Tp>
bool Binary_Tree<Tp>::BT_base_iterator::operator==(const Binary_Tree::BT_base_iterator &op) const {
    return this->Owner_Tree == op.Owner_Tree && this->Index == op.Index;
}

template<typename Tp>
bool Binary_Tree<Tp>::BT_base_iterator::operator!=(const Binary_Tree::BT_base_iterator &op) const {
    return this->Owner_Tree != op.Owner_Tree || this->Index != op.Index;
}

template<typename Tp>
bool Binary_Tree<Tp>::BT_base_iterator::operator<=(const Binary_Tree::BT_base_iterator &op) const {
    if (this->Owner_Tree != op.Owner_Tree) throw;
    return this->Ptr->Element<=op.Ptr->Element;
}

template<typename Tp>
bool Binary_Tree<Tp>::BT_base_iterator::operator>=(const Binary_Tree::BT_base_iterator &op) const {
    if (this->Owner_Tree != op.Owner_Tree) throw;
    return this->Ptr->Element>=op.Ptr->Element;
}

template<typename Tp>
void Binary_Tree<Tp>::BT_base_iterator::straight_left(bool const &flag) {
    Binary_Tree<Tp>::BT_base_iterator iterator {*this};
    for (;; iterator.Ptr = iterator.Ptr->Left_Child) {
        if (iterator.Ptr->Child_num == 0) break;
        if (flag) iterator.Cache_Container.emplace_back(iterator.Ptr);
    }
    *this = iterator;
}

template<typename Tp>
typename Binary_Tree<Tp>::BT_base_iterator &Binary_Tree<Tp>::BT_base_iterator::operator++() {
    switch (this->Owner_Tree->Method) {
        case Tree_Iterator_Methods::Scope:
            *this = this->template iterator_plus_processor<Tree_Iterator_Methods::Scope>();
            break;
        case Tree_Iterator_Methods::Prev:
            *this = this->template iterator_plus_processor<Tree_Iterator_Methods::Prev>();
            break;
        case Tree_Iterator_Methods::Inner:
            *this = this->template iterator_plus_processor<Tree_Iterator_Methods::Inner>();
            break;
        case Tree_Iterator_Methods::Post:
            *this = this->template iterator_plus_processor<Tree_Iterator_Methods::Post>();
            break;
    }
    return *this;
}

template<typename Tp>
const typename Binary_Tree<Tp>::BT_base_iterator Binary_Tree<Tp>::BT_base_iterator::operator++(int) const {
    Binary_Tree::BT_base_iterator res {*this};
    ++res;
    return res;
}

template<typename Tp>
template<Tree_Iterator_Methods methods>
typename Binary_Tree<Tp>::BT_base_iterator &Binary_Tree<Tp>::BT_base_iterator::iterator_plus_processor() {

    Deque_C<Binary_Node<Tp> *> &container {this->Cache_Container};
    Binary_Node<Tp> * temp {this->Cache_Container.front()};
    Binary_Node<Tp> * &ptr {this->Ptr};

    switch (methods) {
        case Tree_Iterator_Methods::Scope:
            if (container.empty()) {
                ptr = nullptr;
                ++this->Index;
                return *this;
            }

            container.pop_front();
            switch (temp->Child_num) {
                case 2:
                    container.emplace_back(temp->Left_Child);
                    container.emplace_back(temp->Right_Child);
                    break;
                case 1:
                    container.emplace_back(temp->Left_Child);
                    break;
                default:
                    break;
            }
            ptr = temp;
            break;

        case Tree_Iterator_Methods::Inner:

            if (ptr->Child_num == 2) {
                ptr = ptr->Right_Child;
                this->straight_left(true);
            } else if (!container.empty()) {
                ptr = container.back();
                container.pop_back();
            } else {
                ptr = nullptr;
            }
            break;

        case Tree_Iterator_Methods::Prev:
            if (ptr->Child_num == 0 && container.empty()) {
                ptr = nullptr;
                ++this->Index;
                return *this;
            }

            switch (ptr->Child_num) {
                case 2:
                    container.emplace_back(ptr);
                    ptr = ptr->Left_Child;
                    break;
                case 1:
                    ptr = ptr->Left_Child;
                default:
                    ptr = container.back()->Right_Child;
                    container.pop_back();
            }
            break;

        case Tree_Iterator_Methods::Post:
            if (this->Index + 1 == this->Owner_Tree->weight()) {
                ptr = nullptr;
                break;
            }

            switch (ptr->Father->Child_num) {
                case 2:
                    if (ptr->Father == container.back()) {
                        ptr = ptr->Father;
                        container.pop_back();
                    } else {
                        container.emplace_back(ptr->Father);
                        ptr = ptr->Father->Right_Child;
                        this->straight_left(false);
                    }
                    break;
                case 1:
                    ptr = ptr->Father;
                    break;
                default:
                    throw;
            }

        default:
            break;
    }
    ++this->Index;
    return *this;
}

template<typename Tp>
Binary_Tree<Tp>::BT_base_const_iterator::BT_base_const_iterator(const Binary_Tree<Tp> &Tree)
        : Cache_Container{}, Owner_Tree{&Tree}, Ptr{&Tree.top_c()}, Index{0} {}

template<typename Tp>
Binary_Tree<Tp>::BT_base_const_iterator::BT_base_const_iterator(const Binary_Tree<Tp> &Tree, const Tree_Iterator_Methods &method)
        :Cache_Container{}, Owner_Tree{&Tree}, Ptr{&Tree.top_c()}, Index{0} {
    switch (method) {
        case Tree_Iterator_Methods::Scope:
            switch (this->Ptr->Child_num) {
                case 2:
                    this->Cache_Container.emplace_back(this->Ptr->Left_Child);
                    this->Cache_Container.emplace_back(this->Ptr->Right_Child);
                    break;
                case 1:
                    this->Cache_Container.emplace_back(this->Ptr->Left_Child);
                    break;
                default:
                    break;
            }
            break;
        case Tree_Iterator_Methods::Inner:
            this->straight_left(true);
        case Tree_Iterator_Methods::Post:
            this->straight_left(false);
        case Tree_Iterator_Methods::Prev:
            break;
    }
}

template<typename Tp>
Tp &Binary_Tree<Tp>::BT_base_const_iterator::operator*() const {
    return this->Ptr->Element;
}

template<typename Tp>
Tp *Binary_Tree<Tp>::BT_base_const_iterator::operator->() const {
    return &this->Ptr->Element;
}

template<typename Tp>
bool Binary_Tree<Tp>::BT_base_const_iterator::operator<(const Binary_Tree::BT_base_const_iterator &op) const {
    if (this->Owner_Tree == op.Owner_Tree) throw;
    return this->Ptr->Element<op.Ptr->Element;
}

template<typename Tp>
bool Binary_Tree<Tp>::BT_base_const_iterator::operator>(const Binary_Tree::BT_base_const_iterator &op) const {
    if (this->Owner_Tree == op.Owner_Tree) throw;
    return this->Ptr->Element>op.Ptr->Element;
}

template<typename Tp>
bool Binary_Tree<Tp>::BT_base_const_iterator::operator==(const Binary_Tree::BT_base_const_iterator &op) const {
    return this->Owner_Tree == op.Owner_Tree && this->Index == op.Index;
}

template<typename Tp>
bool Binary_Tree<Tp>::BT_base_const_iterator::operator!=(const Binary_Tree::BT_base_const_iterator &op) const {
    return this->Owner_Tree != op.Owner_Tree || this->Index != op.Index;
}

template<typename Tp>
bool Binary_Tree<Tp>::BT_base_const_iterator::operator<=(const Binary_Tree::BT_base_const_iterator &op) const {
    if (this->Owner_Tree == op.Owner_Tree) throw;
    return this->Ptr->Element<=op.Ptr->Element;
}

template<typename Tp>
bool Binary_Tree<Tp>::BT_base_const_iterator::operator>=(const Binary_Tree::BT_base_const_iterator &op) const {
    if (this->Owner_Tree == op.Owner_Tree) throw;
    return this->Ptr->Element>=op.Ptr->Element;
}

template<typename Tp>
typename Binary_Tree<Tp>::BT_base_const_iterator &Binary_Tree<Tp>::BT_base_const_iterator::operator++() {
    switch (this->Owner_Tree->Method) {
        case Tree_Iterator_Methods::Scope:
            *this = this->template iterator_plus_processor<Tree_Iterator_Methods::Scope>();
            break;
        case Tree_Iterator_Methods::Prev:
            *this = this->template iterator_plus_processor<Tree_Iterator_Methods::Prev>();
            break;
        case Tree_Iterator_Methods::Inner:
            *this = this->template iterator_plus_processor<Tree_Iterator_Methods::Inner>();
            break;
        case Tree_Iterator_Methods::Post:
            *this = this->template iterator_plus_processor<Tree_Iterator_Methods::Post>();
            break;
    }
    return *this;
}

template<typename Tp>
const typename Binary_Tree<Tp>::BT_base_const_iterator Binary_Tree<Tp>::BT_base_const_iterator::operator++(int) const {
    Binary_Tree::BT_base_iterator res {*this};
    ++res;
    return res;
}

template<typename Tp>
template<Tree_Iterator_Methods methods>
typename Binary_Tree<Tp>::BT_base_const_iterator &Binary_Tree<Tp>::BT_base_const_iterator::iterator_plus_processor() {
    Deque_C<Binary_Node<Tp> const *> &container {this->Cache_Container};
    Binary_Node<Tp> const *temp {this->Cache_Container.front()};
    Binary_Node<Tp> const * &ptr {this->Ptr};

    switch (methods) {
        case Tree_Iterator_Methods::Scope:
            if (container.empty()) {
                ptr = this->Owner_Tree->Top;
                ++this->Index;
                return *this;
            }

            container.pop_front();
            switch (temp->Child_num) {
                case 2:
                    container.emplace_back(temp->Left_Child);
                    container.emplace_back(temp->Right_Child);
                    break;
                case 1:
                    container.emplace_back(temp->Left_Child);
                    break;
                default:
                    break;
            }
            ptr = temp;
            break;

        case Tree_Iterator_Methods::Inner:
            if (ptr->Child_num == 2) {
                ptr = ptr->Right_Child;
                this->straight_left(true);
            } else if (!container.empty()) {
                ptr = container.back();
                container.pop_back();
            } else {
                ptr = this->Owner_Tree->Top;
            }
            break;

        case Tree_Iterator_Methods::Prev:
            if (ptr->Child_num == 0 && container.empty())
                ptr = this->Owner_Tree->Top;
            switch (ptr->Child_num) {
                case 2:
                    container.emplace_back(ptr);
                    ptr = ptr->Left_Child;
                    break;
                case 1:
                    ptr = ptr->Left_Child;
                    break;
                default:
                    ptr = container.back()->Left_Child;
                    container.pop_back();
                    break;
            }
            break;

        case Tree_Iterator_Methods::Post:
            if (this->Index + 1 == this->Owner_Tree->weight()) {
                ptr = this->Owner_Tree->Top;
                break;
            }

            switch (ptr->Father->Child_num) {
                case 2:
                    if (ptr->Father== container.back()) {
                        ptr = ptr->Father;
                        container.pop_back();
                    } else {
                        container.emplace_back(ptr->Father);
                        ptr = ptr->Father->Right_Child;
                        this->straight_left(false);
                    }
                    break;
                case 1:
                    ptr = ptr->Father;
                    break;
                default:
                    throw;
            }

        default:
            break;
    }
    ++this->Index;
    return *this;
}

template<typename Tp>
void Binary_Tree<Tp>::BT_base_const_iterator::straight_left(const bool &flag) {
    Binary_Tree<Tp>::BT_base_const_iterator iterator {*this};
    for (;; iterator.Ptr = iterator.Ptr->Left_Child) {
        if (iterator.Ptr->Child_num == 0) break;
        if (flag) iterator.Cache_Container.emplace_back(iterator.Ptr);
    }
    *this = iterator;
}

template<typename Tp>
Binary_Node<Tp>::Binary_Node(const Tp &value)
        :Size{1}, Depth{1}, Child_num{}, Element{value}, Father{nullptr}, Left_Child{nullptr}, Right_Child{nullptr} {}

template<typename Tp>
size_t Binary_Node<Tp>::locate() const {
    if (this->Father == nullptr) return 2;
    else if (this->Father->Left_Child == this) return 0;
    else if (this->Father->Right_Child == this) return 1;
    return 3;
}

template<typename Tp>
std::vector<size_t> Binary_Node<Tp>::path() const {
    std::vector<size_t> res {};
    for (const Binary_Node<Tp>* node = this;node->Father!= nullptr ; node = node->Father) {
        res.template emplace_back(node->locate());
    }
    return res;
}

template<typename Tp>
size_t Binary_Node<Tp>::degree() const {
    return this->Child_num;
}

template<typename Tp>
size_t Binary_Node<Tp>::level() const {
    size_t res {};
    for (Binary_Node<Tp> node = *this; node.Father!= nullptr; node = *(node.Father), ++res);
    return res;
}

template<typename Tp>
void Binary_Node<Tp>::swap_pos(Binary_Node<Tp> &op) {
    Binary_Node<Tp> *_temp_father_ptr = this->Father;
    switch (this->locate()) {
        case 0:
            switch (op.locate()) {
                case 0:
                    op.Father->Left_Child = this;
                    break;
                case 1:
                    op.Father->Right_Child = this;
                    break;
                default:
                    break;
            }
            this->Father->Left_Child = &op;
            this->Father = op.Father;
            op.Father = _temp_father_ptr;
            return;
        case 1:
            switch (op.locate()) {
                case 0:
                    op.Father->Left_Child = this;
                    break;
                case 1:
                    op.Father->Right_Child = this;
                    break;
                default:
                    break;
            }
            this->Father->Right_Child = &op;
            this->Father = op.Father;
            op.Father = _temp_father_ptr;
            return;
        default:
            switch (op.locate()) {
                case 0:
                    op.Father->Left_Child = this;
                    break;
                case 1:
                    op.Father->Right_Child = this;
                    break;
                default:
                    break;
            }
            this->Father = op.Father;
            op.Father = _temp_father_ptr;
            return;
    }
}

template<typename Tp>
void Binary_Node<Tp>::sink() {
    this->Father = nullptr;
    this->Left_Child = nullptr;
    this->Right_Child = nullptr;
    this->Size = 1;
    this->Depth = 1;
}

template<typename Tp>
void Binary_Node<Tp>::resize(const size_t &n) {
    this->Size = n;
}

template<typename Tp>
void Binary_Node<Tp>::broadcast() {
    for(Binary_Node<Tp> *_ptr {this->Father};;_ptr = _ptr->Father) {
        if (_ptr == nullptr) break;
        _ptr->Size = _ptr->Left_Child == nullptr? 0 : _ptr->Left_Child->Size +
                                                      _ptr->Right_Child == nullptr? 0 : _ptr->Right_Child->Size + 1;
        _ptr->Depth = std::max(_ptr->Left_Child == nullptr? 0 : _ptr->Left_Child->Depth,
                               _ptr->Right_Child == nullptr? 0 : _ptr->Right_Child->Depth) + 1;
    }
}

template<typename Tp>
Binary_Tree<Tp>::Binary_Tree()
        :Method{Tree_Iterator_Methods::Scope}, Top{nullptr}, Size{nullptr} {}

template<typename Tp>
void Binary_Tree<Tp>::bind_top(Binary_Node<Tp> &value) {
    this->Top = &value;
    this->Size = &this->Top->Size;
}

template<typename Tp>
Binary_Node<Tp> &Binary_Tree<Tp>::top() {
    if(this->Top == nullptr) this->Top = new Binary_Node<Tp> {Tp{}};
    return *(this->Top);
}

template<typename Tp>
Binary_Node<Tp> &Binary_Tree<Tp>::top_c() const {
    if(this->Top == nullptr) throw;
    return *(this->Top);
}

template<typename Tp>
bool Binary_Tree<Tp>::complete() const {
    Tree_Iterator_Methods method = this->Method;
    this->Method = Tree_Iterator_Methods::Scope;
    bool jump_flag = true;

    for(auto iter {this->cbegin()}; iter != this->cend(); ++iter) {
        if (jump_flag) {
            if (iter.Ptr->Child_num != 2) jump_flag = false;
        } else {
            if (iter.Ptr->Child_num != 0) {
                this->Method = method;
                return false;
            }
        }
    }
    this->Method = method;
    return true;
}

template<typename Tp>
size_t Binary_Tree<Tp>::degree() const {
    Tree_Iterator_Methods method = this->Method;
    this->Method = Tree_Iterator_Methods::Scope;
    size_t Degree = 0;

    for(auto iter {this->cbegin()}; iter != this->cend(); ++iter)
        Degree = (Degree < iter.Ptr->Child_num) ? iter.Ptr->Child_num : Degree;
    this->Method = method;
    return Degree;
}

template<typename Tp>
size_t Binary_Tree<Tp>::depth() const {
    return this->Top->Depth;
}

template<typename Tp>
size_t Binary_Tree<Tp>::weight() const {
    if (this->Size == nullptr) return 0;
    return *this->Size;
}

template<typename Tp>
bool Binary_Tree<Tp>::full() const {
    Tree_Iterator_Methods method = this->Method;
    this->Method = Tree_Iterator_Methods::Scope;
    bool level_flag = true;
    size_t index = 0;
    size_t elem_num = 1;

    for(BT_base_const_iterator iter {this->cbegin()}; iter!=this->cend();++iter, ++index) {
        if (index == elem_num) {
            index = 0;
            elem_num *= 2;
        }

        if (level_flag) {
            if (iter.Ptr->Child_num == 0) {
                if (index != 0) return false;
                else {
                    level_flag = false;
                }
            } else if (iter.Ptr->Child_num == 1) {
                return false;
            }
        } else {
            if (iter.Ptr->Child_num != 0) return false;
        }

    }
    this->Method = method;
    return true;
}

template<typename Tp>
void Binary_Tree<Tp>::clear() {
    this->Method = Tree_Iterator_Methods::Scope;
    this->Size = nullptr;
    this->Top = nullptr;
}

template<typename Tp>
Binary_Node<Tp> &Binary_Tree<Tp>::find(const Tp &value) {
    for (auto iter = this->begin(); iter != this->end() ; ++iter) {
        if (iter.Ptr->Element == value) return *iter.Ptr;
    }
    return *new Binary_Node{Tp{}};
}

template<typename Tp>
Binary_Node<Tp> &Binary_Tree<Tp>::get(const size_t &index) {
    if (index >= this->weight()) throw;
    auto iter = this->begin();
    for (size_t count = 0; count != index ; ++iter, ++count);
    return *iter.Ptr;
}

template<typename Tp>
bool Binary_Tree<Tp>::empty() const {
    return this->Top == nullptr;
}

template<typename Tp>
typename Binary_Tree<Tp>::BT_base_iterator Binary_Tree<Tp>::begin() {
    return BT_base_iterator(*this, this->Method);
}

template<typename Tp>
typename Binary_Tree<Tp>::BT_base_iterator Binary_Tree<Tp>::end() {
    BT_base_iterator res {*this};
    res.Index = this->weight();
    return res;
}

template<typename Tp>
typename Binary_Tree<Tp>::BT_base_const_iterator Binary_Tree<Tp>::cbegin() const {
    return BT_base_const_iterator{*this, this->Method};
}

template<typename Tp>
typename Binary_Tree<Tp>::BT_base_const_iterator Binary_Tree<Tp>::cend() const {
    BT_base_const_iterator res {*this};
    res.Index = this->weight();
    return res;
}

template<typename Tp>
void Binary_Tree<Tp>::to_prev() {
    this->Method = Tree_Iterator_Methods::Prev;
}

template<typename Tp>
void Binary_Tree<Tp>::to_inner() {
    this->Method = Tree_Iterator_Methods::Inner;
}

template<typename Tp>
void Binary_Tree<Tp>::to_post() {
    this->Method = Tree_Iterator_Methods::Post;
}

template<typename Tp>
void Binary_Tree<Tp>::to_scope() {
    this->Method = Tree_Iterator_Methods::Scope;
}

template<typename Tp>
void Binary_Tree<Tp>::path_compaction(Binary_Tree<Tp> &tree) {

    for(auto iter=tree.begin();iter!=tree.end();++iter) {
        iter.Ptr->Father= tree.Top;
    }
}

template<typename Tp>
void Binary_Tree<Tp>::path_splitting(Binary_Tree<Tp> &tree) {
    Binary_Tree<Tp>::path_compaction(tree);
}

template<typename Tp>
void Binary_Tree<Tp>::path_halving(Binary_Tree<Tp> &tree) {
    Binary_Tree<Tp>::path_compaction(tree);
}

template<typename cls>
Binary_Tree<cls> merge_binary_tree(Binary_Tree<cls> &a_tree, Binary_Tree<cls> &b_tree) {
    Binary_Tree<cls> new_tree {};
    new_tree.Top = new Binary_Node<cls> {cls{}};
    new_tree.Top->Left_Child = a_tree.Top;
    new_tree.Top->Right_Child = b_tree.Top;
    a_tree.Top->Father = new_tree;
    b_tree.Top->Father = new_tree;
    return new_tree;
}

template<class cls>
Binary_Tree<cls> unite_binary_tree(Binary_Tree<cls> &a_tree, Binary_Tree<cls> &b_tree) {
    switch (a_tree.Top->Child_num) {
        case 0:
            a_tree.Top->Left_Child = b_tree.Top;
            break;
        case 1:
            a_tree.Top->Right_Child = b_tree.Top;
            break;
        default:
            break;
    }
    b_tree.Top->Father = a_tree.Top;
    return a_tree;
}

#endif //DATASTRUCTURE_BINARY_TREE_HPP