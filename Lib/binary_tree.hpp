#ifndef DATASTRUCTURE_BINARY_TREE_HPP
#define DATASTRUCTURE_BINARY_TREE_HPP

#include "settools.hpp"
#include "vector.hpp"
#include "deque.hpp"
#include "abstract.hpp"

namespace ax
{
    template<typename Tp>
    struct binary_node {
        explicit binary_node(Tp const & = Tp{});

        [[nodiscard]] inline size_t locate() const;

        [[nodiscard]] std::vector<size_t> path() const;

        [[nodiscard]] inline size_t degree() const;

        [[nodiscard]] inline size_t level() const;

        void swap_pos(binary_node<Tp> &op);

        void resize(size_t const &);

        void broadcast();

        void sink();

        binary_node<Tp> *Left_Child;

        binary_node<Tp> *Right_Child;

        binary_node<Tp> *Father;

        size_t Depth;

        size_t Size;

        size_t Child_num;

        Tp Element;
    };

    template<typename Tp>
    class binary_tree{
    public:
        binary_tree();

        binary_tree &operator=(binary_tree<Tp> const &) noexcept = default;

        binary_tree &operator=(binary_tree<Tp> &&) noexcept = default;

        binary_tree(binary_tree<Tp> const &) noexcept = default;

        binary_tree(binary_tree<Tp> &&) noexcept = default;

        ~binary_tree() = default;

        void bind_top(binary_node<Tp> &);

        [[nodiscard]] inline bool full() const;

        [[nodiscard]] inline size_t degree() const;

        [[nodiscard]] inline size_t depth() const;

        [[nodiscard]] inline size_t weight() const;

        [[nodiscard]] inline bool empty() const;

        binary_node<Tp> &top_c() const;

        binary_node<Tp> &top();

        [[nodiscard]] bool complete() const;

        void clear();

        class bt_base_iterator: std::iterator<std::forward_iterator_tag, Tp> {
        public:
            explicit bt_base_iterator(binary_tree<Tp> &);

            bt_base_iterator(binary_tree<Tp> &, Tree_Iterator_Methods const &);

            bt_base_iterator(bt_base_iterator const &) noexcept = default;

            bt_base_iterator(bt_base_iterator &&) noexcept = default;

            bt_base_iterator &operator=(bt_base_iterator const &) noexcept = default;

            bt_base_iterator &operator=(bt_base_iterator &&) noexcept = default;

            Tp &operator*();

            Tp *operator->();

            virtual inline bool operator<(bt_base_iterator const &) const;

            virtual inline bool operator>(bt_base_iterator const &) const;

            virtual inline bool operator==(bt_base_iterator const &) const;

            virtual inline bool operator!=(bt_base_iterator const &) const;

            virtual inline bool operator<=(bt_base_iterator const &) const;

            virtual inline bool operator>=(bt_base_iterator const &) const;

            bt_base_iterator &operator++();

            bt_base_iterator const operator++(int);

            template<Tree_Iterator_Methods methods>
            bt_base_iterator &iterator_plus_processor();

            inline void straight_left(bool const &);

            binary_node<Tp> *Ptr;

            size_t Index;

        protected:
            linked_deque<binary_node<Tp> *> Cache_Container;

            binary_tree<Tp> *Owner_Tree;
        };

        class BT_base_const_iterator {
        public:
            explicit BT_base_const_iterator(binary_tree<Tp> const &);

            BT_base_const_iterator(binary_tree<Tp> const &, Tree_Iterator_Methods const &);

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

            BT_base_const_iterator const operator++(int);

            template<Tree_Iterator_Methods methods>
            BT_base_const_iterator &iterator_plus_processor();

            binary_node<Tp> const *Ptr;

            size_t Index;

        protected:
            linked_deque<binary_node<Tp> const*> Cache_Container;

            binary_tree<Tp> const *Owner_Tree;

        private:
            inline void straight_left(bool const &);
        };


        bt_base_iterator begin();

        bt_base_iterator end();

        BT_base_const_iterator cbegin() const;

        BT_base_const_iterator cend() const;

        inline void to_prev();

        inline void to_inner();

        inline void to_post();

        inline void to_scope();

        static void path_compaction(binary_tree<Tp> &);

        static void path_splitting(binary_tree<Tp> &);

        static void path_halving(binary_tree<Tp> &);

        template<class cls>
        friend binary_tree<cls> merge_binary_tree(binary_tree<cls> &a_tree, binary_tree<cls> &b_tree);

        template<class cls>
        friend binary_tree<cls> unite_binary_tree(binary_tree<cls> &a_tree, binary_tree<cls> &b_tree);

        binary_node<Tp> &find(Tp const &);

        binary_node<Tp> &get(size_t const &);

        mutable Tree_Iterator_Methods Method;

    protected:
        binary_node<Tp> *Top;

        size_t *Size;
    };

    template<typename Tp>
    struct lite_binary_tree
    {
        lite_binary_tree *Father, *Right, *Left;
        Tp Value;
    };

    template<typename K_Tp, typename V_Tp>
    class Binary_Search_Tree
    {
    public:
        struct Binary_Search_Node
        {
            Binary_Search_Node(K_Tp const &, V_Tp const &);

            Binary_Search_Node* Father;

            Binary_Search_Node* Right;

            Binary_Search_Node* Left;

            V_Tp Value;

            K_Tp Key;
        };

        explicit Binary_Search_Tree();

        Binary_Search_Node *search(K_Tp const &) const;

        [[nodiscard]] std::vector<V_Tp> ascend() const;

        void insert(K_Tp const &, V_Tp const &);

        void insert(Binary_Search_Node &);

        void erase(K_Tp const &);

    protected:
        Binary_Search_Node *Head;

    private:
        std::pair<Binary_Search_Node *, Binary_Search_Node *> search_between(K_Tp const &) const;

        static void destroy(Binary_Search_Node &);
    };

    template<typename K_Tp, typename V_Tp>
    Binary_Search_Tree<K_Tp, V_Tp>::Binary_Search_Node::Binary_Search_Node(const K_Tp &key, const V_Tp &value)
            :Key{key}, Value{value}, Left{nullptr}, Right{nullptr}, Father{nullptr} {}

    template<typename K_Tp, typename V_Tp>
    Binary_Search_Tree<K_Tp, V_Tp>::Binary_Search_Tree()
            :Head{nullptr} {}

    template<typename K_Tp, typename V_Tp>
    void Binary_Search_Tree<K_Tp, V_Tp>::insert(K_Tp const &key, V_Tp const &value)
    {
        auto *_node = new Binary_Search_Node {key, value};
        this->insert(*_node);
    }

    template<typename K_Tp, typename V_Tp>
    void Binary_Search_Tree<K_Tp, V_Tp>::insert(Binary_Search_Tree::Binary_Search_Node &node)
    {
        if (this->Head == nullptr) {
            this->Head = &node;
            return;
        }

        K_Tp &_key = node.Element.Key;
        Binary_Search_Node *_pos;
        int _condition;
        for(Binary_Search_Node *_ptr = this->Head;;)
        {
            if (_key == _ptr->Key)
            {
                _pos = _ptr;
                _condition = 0;
                break;
            } else if (_key < _ptr->Key) {
                if (_ptr->Left != nullptr) _ptr = _ptr->Left;
                else {
                    _pos = _ptr;
                    _condition = -1;
                    break;
                }
            } else {
                if (_ptr->Right != nullptr) _ptr = _ptr->Righta;
                else {
                    _pos = _ptr;
                    _condition = 1;
                    break;
                }
            }
        }

        switch (_condition)
        {
            case 0:
                _pos->Value = node.Value;
                break;
            case 1:
                _pos->Right = &node;
                node.Father = _pos;
                break;
            default:
                _pos->Left = &node;
                node.Father = _pos;
                break;
        }
    }

    template<typename K_Tp, typename V_Tp>
    void Binary_Search_Tree<K_Tp, V_Tp>::erase(const K_Tp &key)
    {
        auto *_ptr = this->search(key);

        if (_ptr->Left == nullptr && _ptr->Right == nullptr)
        {
            if (_ptr->Father != nullptr)
            {
                _ptr->Key < _ptr->Father->Key? _ptr->Father->Left = nullptr: _ptr->Father->Right = nullptr;
            } else {
                this->Head = nullptr;
            }
        } else if (_ptr->Left != nullptr && _ptr->Right== nullptr) {
            if (_ptr->Father != nullptr)
            {
                _ptr->Key < _ptr->Father->Key ? _ptr->Father->Left = _ptr->Left : _ptr->Father->Right = _ptr->Left;
                _ptr->Left->Father = _ptr->Father;
            } else this->Head = _ptr->Left;
        } else if (_ptr->Right != nullptr && _ptr->Left == nullptr) {
            if (_ptr->Father != nullptr) {
                _ptr->Key < _ptr->Father->Key ? _ptr->Father->Left = _ptr->Right : _ptr->Father->Right = _ptr->Right;
                _ptr->Right->Father = _ptr->Father;
            } else this->Head = _ptr->Right;
        } else {
            Binary_Search_Tree::destroy(*_ptr);
        }
    }

    template<typename K_Tp, typename V_Tp>
    typename Binary_Search_Tree<K_Tp, V_Tp>::Binary_Search_Node *Binary_Search_Tree<K_Tp, V_Tp>::search(K_Tp const &key) const
    {
        if (this->Head == nullptr) return nullptr;
        K_Tp _temp = this->Head->Key;
        for (Binary_Search_Node *_ptr_iterator {this->Head};;)
        {
            if (_temp == key) {
                return _ptr_iterator;
            } else if (_temp > key) {
                if (_ptr_iterator->Right == nullptr)
                {
                    return nullptr;
                } else {
                    _ptr_iterator = _ptr_iterator->Right;
                }
            } else {
                if (_ptr_iterator->Left == nullptr)
                {
                    return nullptr;
                } else {
                    _ptr_iterator = _ptr_iterator->Left;
                }
            }
            _temp = _ptr_iterator->Key;
        }
    }

    template<typename K_Tp, typename V_Tp>
    std::pair<typename Binary_Search_Tree<K_Tp, V_Tp>::Binary_Search_Node *, typename Binary_Search_Tree<K_Tp, V_Tp>::Binary_Search_Node *> Binary_Search_Tree<K_Tp, V_Tp>::search_between(const K_Tp &key) const {
        if (this->Head == nullptr) return std::pair<Binary_Search_Node*, Binary_Search_Node*>{nullptr, nullptr};
        std::pair<Binary_Search_Node *, Binary_Search_Node *> _res {};
        K_Tp _temp = this->Head->Key;
        for(Binary_Search_Node *_ptr_iterator {this->Head};;)
        {
            if (_ptr_iterator->Right != nullptr && key > _temp)
            {
                if (key < _ptr_iterator->Right->Key)
                {
                    return std::pair<Binary_Search_Node *, Binary_Search_Node *>{_ptr_iterator, _ptr_iterator->Right};
                } else {
                    _ptr_iterator = _ptr_iterator->Right;
                }
            } else if (_ptr_iterator->Left != nullptr && key < _temp)
            {
                if (key > _ptr_iterator->Left->Key)
                {
                    return std::pair<Binary_Search_Node *, Binary_Search_Node *>{_ptr_iterator->Left, _ptr_iterator};
                } else {
                    _ptr_iterator = _ptr_iterator->Left;
                }
            }  else {
                return std::pair<Binary_Search_Node*, Binary_Search_Node*> {_ptr_iterator, nullptr};
            }
        }
    }

    template<typename K_Tp, typename V_Tp>
    std::vector<V_Tp> Binary_Search_Tree<K_Tp, V_Tp>::ascend() const
    {
        size_t const _size = this->Head->Size;
        deque<Binary_Search_Node *> _cache {};
        std::vector<V_Tp> _res {};
        Binary_Search_Node *_node {this->Head};

        for(size_t _idx = 0; _idx != _size; ++_idx) {
            if (_node->Right != nullptr) {
                _cache.template emplace_back(_node->Right);
                _res.template emplace_back(_node->Value);
                _node = _node->Left_Child;
            } else if (_node->Left != nullptr) {
                _res.template emplace_back(_node->Value);
                _node = _node->Left;
            }else {
                _res.template emplace_back(_node->Value);
                _node = &_cache.back();
                _cache.pop_back();
            }
        }
        return _res;
    }

    template<typename K_Tp, typename V_Tp>
    void Binary_Search_Tree<K_Tp, V_Tp>::destroy(Binary_Search_Tree::Binary_Search_Node &node)
    {
        if (node.Right != nullptr)
        {
            node.Key = node.Right->Key;
            node.Value = node.Right->Value;
            destroy(*node.Right);
        } else if (node.Left != nullptr) {
            node.Key = node.Left->Key;
            node.Value = node.Left->Value;
            destroy(*node.Left);
        } else {
            if (node.Father != nullptr)
            {
                (node.Key< node.Father->Key) ?node.Father->Left = nullptr : node.Father->Right = nullptr;
            }
            ~node();
        }
    }

    template<typename kt, typename vt>
    Binary_Search_Tree<kt, vt> make_binary_search_tree(vector<pair < kt ,vt>> const &vec)
{
    return Binary_Search_Tree<kt, vt> {vec};
}

    template<typename Tp>
    binary_tree<Tp>::bt_base_iterator::bt_base_iterator(binary_tree<Tp> &Tree)
            : Cache_Container{}, Owner_Tree{&Tree}, Ptr{&Tree.top()}, Index{0} {}

    template<typename Tp>
    binary_tree<Tp>::bt_base_iterator::bt_base_iterator(binary_tree<Tp> &Tree, Tree_Iterator_Methods const &method)
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
    Tp &binary_tree<Tp>::bt_base_iterator::operator*() {
        return this->Ptr->Element;
    }

    template<typename Tp>
    Tp *binary_tree<Tp>::bt_base_iterator::operator->() {
        return &this->Ptr->Element;
    }

    template<typename Tp>
    bool binary_tree<Tp>::bt_base_iterator::operator<(const binary_tree::bt_base_iterator &op) const {
        if (static_cast<void *>(this->Owner_Tree) == static_cast<void *>(op.Owner_Tree)) throw;
        return this->Ptr->Element < op.Ptr->Element;
    }

    template<typename Tp>
    bool binary_tree<Tp>::bt_base_iterator::operator>(const binary_tree::bt_base_iterator &op) const {
        if (static_cast<void *>(this->Owner_Tree) == static_cast<void *>(op.Owner_Tree)) throw;
        return this->Ptr->Element >op.Ptr->Element;
    }

    template<typename Tp>
    bool binary_tree<Tp>::bt_base_iterator::operator==(const binary_tree::bt_base_iterator &op) const {
        return this->Owner_Tree == op.Owner_Tree && this->Index == op.Index;
    }

    template<typename Tp>
    bool binary_tree<Tp>::bt_base_iterator::operator!=(const binary_tree::bt_base_iterator &op) const {
        return this->Owner_Tree != op.Owner_Tree || this->Index != op.Index;
    }

    template<typename Tp>
    bool binary_tree<Tp>::bt_base_iterator::operator<=(const binary_tree::bt_base_iterator &op) const {
        if (this->Owner_Tree != op.Owner_Tree) throw;
        return this->Ptr->Element<=op.Ptr->Element;
    }

    template<typename Tp>
    bool binary_tree<Tp>::bt_base_iterator::operator>=(const binary_tree::bt_base_iterator &op) const {
        if (this->Owner_Tree != op.Owner_Tree) throw;
        return this->Ptr->Element>=op.Ptr->Element;
    }

    template<typename Tp>
    void binary_tree<Tp>::bt_base_iterator::straight_left(bool const &flag) {
        binary_tree<Tp>::bt_base_iterator iterator {*this};
        for (;; iterator.Ptr = iterator.Ptr->Left_Child) {
            if (iterator.Ptr->Child_num == 0) break;
            if (flag) iterator.Cache_Container.emplace_back(iterator.Ptr);
        }
        *this = iterator;
    }

    template<typename Tp>
    typename binary_tree<Tp>::bt_base_iterator &binary_tree<Tp>::bt_base_iterator::operator++() {
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
    const typename binary_tree<Tp>::bt_base_iterator binary_tree<Tp>::bt_base_iterator::operator++(int) {
        binary_tree::bt_base_iterator res {*this};
        ++(*this);
        return res;
    }

    template<typename Tp>
    template<Tree_Iterator_Methods methods>
    typename binary_tree<Tp>::bt_base_iterator &binary_tree<Tp>::bt_base_iterator::iterator_plus_processor() {

        linked_deque<binary_node<Tp> *> &container {this->Cache_Container};
        binary_node<Tp> * temp {this->Cache_Container.front()};
        binary_node<Tp> * &ptr {this->Ptr};

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
    binary_tree<Tp>::BT_base_const_iterator::BT_base_const_iterator(const binary_tree<Tp> &Tree)
            : Cache_Container{}, Owner_Tree{&Tree}, Ptr{&Tree.top_c()}, Index{0} {}

    template<typename Tp>
    binary_tree<Tp>::BT_base_const_iterator::BT_base_const_iterator(const binary_tree<Tp> &Tree, const Tree_Iterator_Methods &method)
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
    Tp &binary_tree<Tp>::BT_base_const_iterator::operator*() const {
        return this->Ptr->Element;
    }

    template<typename Tp>
    Tp *binary_tree<Tp>::BT_base_const_iterator::operator->() const {
        return &this->Ptr->Element;
    }

    template<typename Tp>
    bool binary_tree<Tp>::BT_base_const_iterator::operator<(const binary_tree::BT_base_const_iterator &op) const {
        if (this->Owner_Tree == op.Owner_Tree) throw;
        return this->Ptr->Element<op.Ptr->Element;
    }

    template<typename Tp>
    bool binary_tree<Tp>::BT_base_const_iterator::operator>(const binary_tree::BT_base_const_iterator &op) const {
        if (this->Owner_Tree == op.Owner_Tree) throw;
        return this->Ptr->Element>op.Ptr->Element;
    }

    template<typename Tp>
    bool binary_tree<Tp>::BT_base_const_iterator::operator==(const binary_tree::BT_base_const_iterator &op) const {
        return this->Owner_Tree == op.Owner_Tree && this->Index == op.Index;
    }

    template<typename Tp>
    bool binary_tree<Tp>::BT_base_const_iterator::operator!=(const binary_tree::BT_base_const_iterator &op) const {
        return this->Owner_Tree != op.Owner_Tree || this->Index != op.Index;
    }

    template<typename Tp>
    bool binary_tree<Tp>::BT_base_const_iterator::operator<=(const binary_tree::BT_base_const_iterator &op) const {
        if (this->Owner_Tree == op.Owner_Tree) throw;
        return this->Ptr->Element<=op.Ptr->Element;
    }

    template<typename Tp>
    bool binary_tree<Tp>::BT_base_const_iterator::operator>=(const binary_tree::BT_base_const_iterator &op) const {
        if (this->Owner_Tree == op.Owner_Tree) throw;
        return this->Ptr->Element>=op.Ptr->Element;
    }

    template<typename Tp>
    typename binary_tree<Tp>::BT_base_const_iterator &binary_tree<Tp>::BT_base_const_iterator::operator++() {
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
    const typename binary_tree<Tp>::BT_base_const_iterator binary_tree<Tp>::BT_base_const_iterator::operator++(int) {
        binary_tree::bt_base_iterator res {*this};
        ++(*this);
        return res;
    }

    template<typename Tp>
    template<Tree_Iterator_Methods methods>
    typename binary_tree<Tp>::BT_base_const_iterator &binary_tree<Tp>::BT_base_const_iterator::iterator_plus_processor() {
        linked_deque<binary_node<Tp> const *> &container {this->Cache_Container};
        binary_node<Tp> const *temp {this->Cache_Container.front()};
        binary_node<Tp> const * &ptr {this->Ptr};

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
    void binary_tree<Tp>::BT_base_const_iterator::straight_left(const bool &flag) {
        binary_tree<Tp>::BT_base_const_iterator iterator {*this};
        for (;; iterator.Ptr = iterator.Ptr->Left_Child) {
            if (iterator.Ptr->Child_num == 0) break;
            if (flag) iterator.Cache_Container.emplace_back(iterator.Ptr);
        }
        *this = iterator;
    }

    template<typename Tp>
    binary_node<Tp>::binary_node(const Tp &value)
            :Size{1}, Depth{1}, Child_num{}, Element{value}, Father{nullptr}, Left_Child{nullptr}, Right_Child{nullptr} {}

    template<typename Tp>
    size_t binary_node<Tp>::locate() const {
        if (this->Father == nullptr) return 2;
        else if (this->Father->Left_Child == this) return 0;
        else if (this->Father->Right_Child == this) return 1;
        return 3;
    }

    template<typename Tp>
    std::vector<size_t> binary_node<Tp>::path() const {
        std::vector<size_t> res {};
        for (const binary_node<Tp>* node = this; node->Father != nullptr ; node = node->Father) {
            res.template emplace_back(node->locate());
        }
        return res;
    }

    template<typename Tp>
    size_t binary_node<Tp>::degree() const {
        return this->Child_num;
    }

    template<typename Tp>
    size_t binary_node<Tp>::level() const {
        size_t res {};
        for (binary_node<Tp> node = *this; node.Father != nullptr; node = *(node.Father), ++res);
        return res;
    }

    template<typename Tp>
    void binary_node<Tp>::swap_pos(binary_node<Tp> &op) {
        binary_node<Tp> *_temp_father_ptr = this->Father;
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
    void binary_node<Tp>::sink() {
        this->Father = nullptr;
        this->Left_Child = nullptr;
        this->Right_Child = nullptr;
        this->Size = 1;
        this->Depth = 1;
    }

    template<typename Tp>
    void binary_node<Tp>::resize(const size_t &n) {
        this->Size = n;
    }

    template<typename Tp>
    void binary_node<Tp>::broadcast() {
        for(binary_node<Tp> *_ptr {this->Father};; _ptr = _ptr->Father) {
            if (_ptr == nullptr) break;
            _ptr->Size = _ptr->Left_Child == nullptr? 0 : _ptr->Left_Child->Size +
                                                          _ptr->Right_Child == nullptr? 0 : _ptr->Right_Child->Size + 1;
            _ptr->Depth = std::max(_ptr->Left_Child == nullptr? 0 : _ptr->Left_Child->Depth,
                                   _ptr->Right_Child == nullptr? 0 : _ptr->Right_Child->Depth) + 1;
        }
    }

    template<typename Tp>
    binary_tree<Tp>::binary_tree()
            :Method{Tree_Iterator_Methods::Scope}, Top{nullptr}, Size{nullptr} {}

    template<typename Tp>
    void binary_tree<Tp>::bind_top(binary_node<Tp> &value) {
        this->Top = &value;
        this->Size = &this->Top->Size;
    }

    template<typename Tp>
    binary_node<Tp> &binary_tree<Tp>::top() {
        if(this->Top == nullptr) this->Top = new binary_node<Tp> {Tp{}};
        return *(this->Top);
    }

    template<typename Tp>
    binary_node<Tp> &binary_tree<Tp>::top_c() const {
        if(this->Top == nullptr) throw;
        return *(this->Top);
    }

    template<typename Tp>
    bool binary_tree<Tp>::complete() const {
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
    size_t binary_tree<Tp>::degree() const {
        Tree_Iterator_Methods method = this->Method;
        this->Method = Tree_Iterator_Methods::Scope;
        size_t Degree = 0;

        for(auto iter {this->cbegin()}; iter != this->cend(); ++iter)
            Degree = (Degree < iter.Ptr->Child_num) ? iter.Ptr->Child_num : Degree;
        this->Method = method;
        return Degree;
    }

    template<typename Tp>
    size_t binary_tree<Tp>::depth() const {
        return this->Top->Depth;
    }

    template<typename Tp>
    size_t binary_tree<Tp>::weight() const {
        if (this->Size == nullptr) return 0;
        return *this->Size;
    }

    template<typename Tp>
    bool binary_tree<Tp>::full() const {
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
    void binary_tree<Tp>::clear() {
        this->Method = Tree_Iterator_Methods::Scope;
        this->Size = nullptr;
        this->Top = nullptr;
    }

    template<typename Tp>
    binary_node<Tp> &binary_tree<Tp>::find(const Tp &value) {
        for (auto iter = this->begin(); iter != this->end() ; ++iter) {
            if (iter.Ptr->Element == value) return *iter.Ptr;
        }
        return *new binary_node{Tp{}};
    }

    template<typename Tp>
    binary_node<Tp> &binary_tree<Tp>::get(const size_t &index) {
        if (index >= this->weight()) throw;
        auto iter = this->begin();
        for (size_t count = 0; count != index ; ++iter, ++count);
        return *iter.Ptr;
    }

    template<typename Tp>
    bool binary_tree<Tp>::empty() const {
        return this->Top == nullptr;
    }

    template<typename Tp>
    typename binary_tree<Tp>::bt_base_iterator binary_tree<Tp>::begin() {
        return bt_base_iterator(*this, this->Method);
    }

    template<typename Tp>
    typename binary_tree<Tp>::bt_base_iterator binary_tree<Tp>::end() {
        bt_base_iterator res {*this};
        res.Index = this->weight();
        return res;
    }

    template<typename Tp>
    typename binary_tree<Tp>::BT_base_const_iterator binary_tree<Tp>::cbegin() const {
        return BT_base_const_iterator{*this, this->Method};
    }

    template<typename Tp>
    typename binary_tree<Tp>::BT_base_const_iterator binary_tree<Tp>::cend() const {
        BT_base_const_iterator res {*this};
        res.Index = this->weight();
        return res;
    }

    template<typename Tp>
    void binary_tree<Tp>::to_prev() {
        this->Method = Tree_Iterator_Methods::Prev;
    }

    template<typename Tp>
    void binary_tree<Tp>::to_inner() {
        this->Method = Tree_Iterator_Methods::Inner;
    }

    template<typename Tp>
    void binary_tree<Tp>::to_post() {
        this->Method = Tree_Iterator_Methods::Post;
    }

    template<typename Tp>
    void binary_tree<Tp>::to_scope() {
        this->Method = Tree_Iterator_Methods::Scope;
    }

    template<typename Tp>
    void binary_tree<Tp>::path_compaction(binary_tree<Tp> &tree) {

        for(auto iter=tree.begin();iter!=tree.end();++iter) {
            iter.Ptr->Father= tree.Top;
        }
    }

    template<typename Tp>
    void binary_tree<Tp>::path_splitting(binary_tree<Tp> &tree) {
        binary_tree<Tp>::path_compaction(tree);
    }

    template<typename Tp>
    void binary_tree<Tp>::path_halving(binary_tree<Tp> &tree) {
        binary_tree<Tp>::path_compaction(tree);
    }

    template<typename cls>
    binary_tree<cls> merge_binary_tree(binary_tree<cls> &a_tree, binary_tree<cls> &b_tree) {
        binary_tree<cls> new_tree {};
        new_tree.Top = new binary_node<cls> {cls{}};
        new_tree.Top->Left_Child = a_tree.Top;
        new_tree.Top->Right_Child = b_tree.Top;
        a_tree.Top->Father = new_tree;
        b_tree.Top->Father = new_tree;
        return new_tree;
    }

    template<class cls>
    binary_tree<cls> unite_binary_tree(binary_tree<cls> &a_tree, binary_tree<cls> &b_tree) {
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

}

#endif //DATASTRUCTURE_BINARY_TREE_HPP