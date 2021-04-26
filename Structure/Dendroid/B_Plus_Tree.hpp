#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedLocalVariable"
#ifndef DATASTRUCTURE_B_PLUS_TREE_HPP
#define DATASTRUCTURE_B_PLUS_TREE_HPP

template<typename K_Tp, typename V_Tp, size_t order>
class B_Plus_Tree
{
private:
    struct Node
    {
        explicit Node(bool index):Is_index{index} {}

        const bool Is_index;

        size_t Size {0};
    };

    void spilt(Node &, size_t const & = 1);

    void destroy(Node &);

public:
    struct Index_Node: public Node
    {
        Index_Node();

        K_Tp Keys[order + 1];

        Node *Paths[order + 1];

        Index_Node *Father;
    };

    struct Data_Node: public Node
    {
        Data_Node();

        K_Tp Keys[order + 1];

        V_Tp Data[order + 1];

        Index_Node *Father;

        Data_Node *Left_Brother;

        Data_Node *Right_Brother;
    };

    B_Plus_Tree();

    void reindex(Index_Node &, K_Tp const &, K_Tp const &);

    void insert(K_Tp const &, V_Tp const &);

    V_Tp search(K_Tp const &) const;

    bool exist(K_Tp const &) const;

    void erase(K_Tp const &);

    mutable Index_Node *IC;

    mutable Data_Node *DC;

    Node *Root;

    Node *PR;

    K_Tp KR;

    V_Tp VR;

};

template<typename K_Tp, typename V_Tp, size_t order>
B_Plus_Tree<K_Tp, V_Tp, order>::Index_Node::Index_Node()
        :Keys{}, Paths{}, Father{nullptr},  Node(true){}

template<typename K_Tp, typename V_Tp, size_t order>
B_Plus_Tree<K_Tp, V_Tp, order>::Data_Node::Data_Node()
        :Keys{}, Data{}, Father{nullptr}, Left_Brother{nullptr}, Right_Brother{nullptr}, Node(false) {}

template<typename K_Tp, typename V_Tp, size_t order>
B_Plus_Tree<K_Tp, V_Tp, order>::B_Plus_Tree()
        :Root{}, DC{}, IC{} {}

template<typename K_Tp, typename V_Tp, size_t order>
void B_Plus_Tree<K_Tp, V_Tp, order>::insert(const K_Tp &key, const V_Tp &value) {
    if (this->Root == nullptr)
    {
        this->Root = new Data_Node{};
        DC = static_cast<Data_Node*>(this->Root);
        DC->Keys[0] = key;
        DC->Data[0] = value;
        ++Root->Size;
        return;
    }

    Node *_iter {this->Root};
    while (true)
    {
        if (!_iter->Is_index) {
            DC = static_cast<Data_Node *>(_iter);
            if (DC->Keys[0] > key) {
                if (_iter->Size == order) {
                    VR = value;
                    KR = key;
                    this->spilt(*_iter, 0);
                } else {
                    K_Tp _word = DC->Keys[0];
                    for (size_t i = _iter->Size; i > 0; --i) {
                        DC->Data[i] = DC->Data[i - 1];
                        DC->Keys[i] = DC->Keys[i - 1];
                    }
                    DC->Data[0] = value;
                    DC->Keys[0] = key;
                    ++_iter->Size;
                    if (DC->Father != nullptr) {
                        this->reindex(*DC->Father, _word, key);
                    }
                }
                return;
            } else if (DC->Keys[_iter->Size - 1] < key) {
                if (_iter->Size == order) {
                    VR = value;
                    KR = key;
                    this->spilt(*_iter, 2);
                } else {
                    DC->Data[_iter->Size] = value;
                    DC->Keys[_iter->Size] = key;
                    ++_iter->Size;
                }
                return;
            } else if (DC->Keys[_iter->Size - 1] == key) {
                DC->Data[_iter->Size - 1] = value;
                return;
            }
            for (size_t _i = 0; _i < _iter->Size - 2; ++_iter)
            {
                if (DC->Keys[_i] == key) {
                    DC->Data[_i] = value;
                    return;
                } else if (key > DC->Keys[_i] && key < DC->Keys[_i + 1]) {
                    if (_iter->Size == order) {
                        VR = value;
                        KR = key;
                        this->spilt(*_iter, 1);
                    } else {
                        for (size_t _j = _iter->Size; _j > _i; --_j) {
                            DC->Keys[_j + 1] = DC->Keys[_j];
                            DC->Data[_j + 1] = DC->Data[_j];
                        }
                        DC->Data[_i + 1] = value;
                        DC->Keys[_i + 1] = key;
                        ++_iter->Size;
                    }
                    return;
                }
            }
        } else {
            IC = static_cast<Index_Node *>(_iter);
            if (IC->Keys[0] > key)
            {
                _iter = IC->Paths[0];
                continue;
            } else if (IC->Keys[_iter->Size - 1] <= key) {
                _iter = IC->Paths[_iter->Size - 1];
                continue;
            }
            for (size_t _i = 0; _i < _iter->Size - 2; ++_i)
            {
                if (key >= DC->Keys[_i] && key < DC->Keys[_i + 1])
                {
                    _iter = IC->Paths[_i];
                    continue;
                }
            }
        }
    }
}

template<typename K_Tp, typename V_Tp, size_t order>
void B_Plus_Tree<K_Tp, V_Tp, order>::reindex(B_Plus_Tree::Index_Node &node, K_Tp const &_word, K_Tp const &key)
{
    Index_Node* _ptr = &node;
    while (true)
    {
        bool _bf;
        for (size_t _j=0; _j!=static_cast<Node*>(_ptr)->Size;++_j)
        {
            if (_ptr->Keys[_j] == _word)
            {
                _ptr->Keys[_j] = key;
                _bf = _j != 0;
                break;
            }
        }
        if (_bf || _ptr->Father == nullptr) break;
        else {_ptr = _ptr->Father;}
    }
}

template<typename K_Tp, typename V_Tp, size_t order>
void B_Plus_Tree<K_Tp, V_Tp, order>::spilt(B_Plus_Tree::Node &node, const size_t &condition)
{
    if (!node.Is_index)
    {
        DC = static_cast<Data_Node*>(&node);
        auto* _page = new Data_Node{};
        if(condition == 0) {
            _page->Keys[0] = KR;
            _page->Keys[1] = DC->Keys[0];
            _page->Data[0] = VR;
            _page->Data[1] = DC->Data[0];

            for (size_t i = 0; i != order - 1; ++i) {
                DC->Keys[i] = DC->Keys[i + 1];
                DC->Data[i] = DC->Data[i + 1];
            }
            static_cast<Node *>(_page)->Size = 2;
            node.Size -= 1;

            if (DC->Left_Brother != nullptr) DC->Left_Brother->Right_Brother = _page;
            _page->Left_Brother = DC->Left_Brother;
            _page->Right_Brother = DC;
            DC->Left_Brother = _page;

            if (DC->Father != nullptr) {
                Index_Node *_fp = DC->Father;
                Node *_fbp = static_cast<Node *>(_fp);
                if (_fbp->Size == order) // TODO
                {
                    PR = _page;
                    this->spilt(*_fp, 0);
                } else {
                    size_t _fi = 0;

                    for (; _fi != _fbp->Size; ++_fi) {
                        if ((void *) (_fp->Paths[_fi]) == (void *) (DC)) break;
                    }
                    for (size_t i = _fbp->Size; i > _fi; --i) {
                        _fp->Keys[i] = _fp->Keys[i - 1];
                        _fp->Paths[i] = _fp->Paths[i - 1];
                    }
                    _fp->Keys[_fi] = _page->Keys[0];
                    _fp->Keys[_fi + 1] = DC->Keys[0];
                    _fp->Paths[_fi] = _page;
                    _fp->Paths[_fi + 1] = DC;
                    _page->Father = DC->Father;

                    ++_fbp->Size;
                }
            } else {
                auto *_rtp = new Index_Node{};
                _rtp->Keys[0] = _page->Keys[0];
                _rtp->Keys[1] = DC->Keys[0];
                _rtp->Paths[0] = _page;
                _rtp->Paths[1] = DC;
                _page->Father = _rtp;
                DC->Father = _rtp;
                this->Root = _rtp;
                static_cast<Node *>(_rtp)->Size = 2;
            }
        } else if(condition == 2) {
            _page->Keys[0] = DC->Keys[order - 1];
            _page->Data[0] = DC->Data[order - 1];
            _page->Keys[1] = KR;
            _page->Data[1] = VR;
            static_cast<Node *>(_page)->Size = 2;
            node.Size -= 1;

            if (DC->Right_Brother != nullptr) DC->Right_Brother->Left_Brother = _page;
            _page->Right_Brother = DC->Right_Brother;
            DC->Right_Brother = _page;
            _page->Left_Brother = DC;

            if (DC->Father != nullptr)
            {
                Index_Node *_fp = DC->Father;
                Node *_fbp = static_cast<Node *>(_fp);

                size_t _fi = 0;
                for (; _fi != _fbp->Size; ++_fi)
                {
                    if ((void *) (_fp->Paths[_fi]) == (void *) (DC)) break;
                }

                if (_fbp->Size == order)
                {
                    KR = DC->Keys[0];
                    PR = _page;
                    this->spilt(*_fbp, _fi == _fbp->Size - 1 ? 2 : 1);
                } else {
                    for (size_t i = _fbp->Size - 1; i > _fi; --i) {
                        _fp->Keys[i + 1] = _fp->Keys[i];
                        _fp->Paths[i + 1] = _fp->Paths[i];
                    }
                    _fp->Keys[_fi + 1] = _page->Keys[0];
                    _fp->Paths[_fi + 1] = _page;
                    _page->Father = DC->Father;

                    ++_fbp->Size;
                }
            } else {
                auto *_rtp = new Index_Node{};
                _rtp->Keys[1] = _page->Keys[0];
                _rtp->Keys[0] = DC->Keys[0];
                _rtp->Paths[1] = _page;
                _rtp->Paths[0] = DC;
                _page->Father = _rtp;
                DC->Father = _rtp;
                this->Root = _rtp;
                static_cast<Node *>(_rtp)->Size = 2;
            }
        } else {
            auto _idx = static_cast<size_t>(order/2+1);

            for(size_t i=0; i<=order-_idx; ++i)
            {
                _page->Keys[i] = DC->Keys[_idx + i];
                _page->Data[i] = DC->Data[_idx + i];
            }

            static_cast<Node *>(_page)->Size = order-_idx+1;
            node.Size = _idx;

            if(DC->Right_Brother != nullptr) DC->Right_Brother->Left_Brother = _page;
            _page->Right_Brother = DC->Right_Brother;
            DC->Right_Brother = _page;
            _page->Left_Brother = DC;

            if (DC->Father != nullptr)
            {
                Index_Node* _fp = DC->Father;
                Node* _fbp = static_cast<Node*>(_fp);
                size_t _fi = 0;

                for(; _fi!= _fbp->Size; ++_fi)
                {
                    if((void*)(_fp->Paths[_fi])==(void*)(DC)) break;
                }

                if(_fbp->Size == order)
                {
                    KR = _page->Keys[0];
                    this->spilt(*_fbp);
                } else {
                    for (size_t i = _fbp->Size - 1; i > _fi; --i) {
                        _fp->Keys[i + 1] = _fp->Keys[i];
                        _fp->Paths[i + 1] = _fp->Paths[i];
                    }
                    _fp->Keys[_fi + 1] = _page->Keys[0];
                    _fp->Paths[_fi + 1] = _page;
                    _page->Father = DC->Father;

                    ++_fbp->Size;
                }
            } else {
                auto* _rtp = new Index_Node {};
                _rtp->Keys[1] = _page->Keys[0];
                _rtp->Keys[0] = DC->Keys[0];
                _rtp->Paths[1] = _page;
                _rtp->Paths[0] = DC;
                _page->Father = _rtp;
                DC->Father = _rtp;
                this->Root = _rtp;
                static_cast<Node*>(_rtp)->Size = 2;
            }
        }
    } else {
        auto* _page = new Index_Node{};
        IC = static_cast<Index_Node*>(&node);
        if (condition == 0)
        {
            _page->Keys[0] = KR;
            _page->Keys[1] = IC->Keys[0];
            _page->Paths[0] = PR;
            _page->Paths[1] = IC->Paths[0];

            for (size_t i = 0; i != order - 1; ++i) {
                IC->Keys[i] = IC->Keys[i + 1];
                IC->Paths[i] = IC->Paths[i + 1];
            }
            static_cast<Node *>(_page)->Size = 2;
            node.Size -= 1;

            ((Node*)_page->Paths[0])->Is_index ? static_cast<Index_Node*>(_page->Paths[0])->Father = _page:
                    static_cast<Data_Node*>(_page->Paths[0])->Father = _page;
            ((Node*)_page->Paths[1])->Is_index ? static_cast<Index_Node*>(_page->Paths[1])->Father = _page:
                    static_cast<Data_Node*>(_page->Paths[1])->Father = _page;

            if (IC->Father != nullptr)
            {
                Index_Node* _fp = DC->Father;
                Node* _fbp = static_cast<Node*>(_fp);
                size_t _fi = 0;

                for(; _fi!= _fbp->Size; ++_fi)
                {
                    if((void*)(_fp->Paths[_fi])==(void*)(DC)) break;
                }
                if (_fbp->Size == order)
                {
                    PR = _page;
                    this->spilt(*_fp, _fi==0? 0: 1);
                } else {
                    for (size_t i = _fbp->Size - 1; i >= _fi; --i) {
                        _fp->Keys[i + 1] = _fp->Keys[i];
                        _fp->Paths[i + 1] = _fp->Paths[i];
                    }
                    _fp->Keys[_fi] = _page->Keys[0];
                    _fp->Keys[_fi + 1] = IC->Keys[0];
                    _fp->Paths[_fi] = _page;
                    _fp->Paths[_fi + 1] = IC;
                    _page->Father = IC->Father;

                    ++_fbp->Size;
                }
            } else {
                auto* _rtp = new Index_Node {};
                _rtp->Keys[0] = _page->Keys[0];
                _rtp->Keys[1] = IC->Keys[0];
                _rtp->Paths[0] = _page;
                _rtp->Paths[1] = IC;
                this->Root = _rtp;
                _page->Father = _rtp;
                IC->Father = _rtp;
                static_cast<Node*>(_rtp)->Size = 2;
            }
        } else if (condition == 2) {
            _page->Paths[0] = IC->Paths[order-1];
            _page->Keys[0] = IC->Keys[order-1];
            _page->Paths[1] = PR;
            _page->Keys[1] = KR;
            static_cast<Node*>(_page)->Size = 2;
            node.Size -= 2;

            ((Node*)_page->Paths[0])->Is_index ? static_cast<Index_Node*>(_page->Paths[0])->Father = _page:
                    static_cast<Data_Node*>(_page->Paths[0])->Father = _page;
            ((Node*)_page->Paths[1])->Is_index ? static_cast<Index_Node*>(_page->Paths[1])->Father = _page:
                    static_cast<Data_Node*>(_page->Paths[1])->Father = _page;

            if (IC->Father != nullptr)
            {
                Index_Node* _fp = IC->Father;
                Node* _fbp = static_cast<Node*>(_fp);
                size_t _fi = 0;

                for(; _fi!= _fbp->Size; ++_fi)
                {
                    if((void*)(_fp->Paths[_fi])==(void*)(DC)) break;
                }
                if(_fbp->Size == order)
                {
                    KR = _page->Keys[0];
                    this->spilt(*_fbp, _fi==_fbp->Size-1? 2: 1);
                } else {
                    for (size_t i = _fbp->Size - 1; i > _fi; --i) {
                        _fp->Keys[i + 1] = _fp->Keys[i];
                        _fp->Paths[i + 1] = _fp->Paths[i];
                    }
                    _fp->Keys[_fi + 1] = _page->Keys[0];
                    _fp->Paths[_fi + 1] = _page;
                    _page->Father = DC->Father;

                    ++_fbp->Size;
                }
            } else {
                auto* _rtp = new Index_Node {};
                _rtp->Keys[1] = _page->Keys[0];
                _rtp->Keys[0] = IC->Keys[0];
                _rtp->Paths[1] = _page;
                _rtp->Paths[0] = IC;
                this->Root = _rtp;
                _page->Father = _rtp;
                IC->Father = _rtp;
                static_cast<Node*>(_rtp)->Size = 2;
            }
        } else {
            auto _idx = static_cast<size_t>(order/2+1);

            /*
            for(size_t i=0; i<=order-_idx; ++i)
            {
                _page->Keys[i] = IC->Keys[_idx + i];
                _page->Paths[i] = IC->Paths[_idx + i];
                ((Node*)_page->Paths[i])->Is_index ? static_cast<Index_Node*>(_page->Paths[i])->Father = _page:
                        static_cast<Data_Node*>(_page->Paths[i])->Father = _page;
            }
            */

            static_cast<Node *>(_page)->Size = order-_idx+1;
            node.Size = _idx;

            if (DC->Father != nullptr)
            {
                Index_Node* _fp = IC->Father;
                Node* _fbp = static_cast<Node*>(_fp);
                size_t _fi = 0;

                for(; _fi!= _fbp->Size; ++_fi)
                {
                    if((void*)(_fp->Paths[_fi])==(void*)(IC)) break;
                }
                for(size_t i=_fbp->Size-1; i>_fi; --i)
                {
                    _fp->Keys[i+1] = _fp->Keys[i];
                    _fp->Paths[i+1] = _fp->Paths[i];
                }
                _fp->Keys[_fi+1] = _page->Keys[0];
                _fp->Paths[_fi+1] = _page;
                _page->Father = DC->Father;

                ++_fbp->Size;
                if(_fbp->Size == order) this->spilt(*_fbp);
            } else {
                auto* _rtp = new Index_Node {};
                _rtp->Keys[1] = _page->Keys[0];
                _rtp->Keys[0] = IC->Keys[0];
                _rtp->Paths[1] = _page;
                _rtp->Paths[0] = IC;
                _page->Father = _rtp;
                IC->Father = _rtp;
                this->Root = _rtp;
                static_cast<Node*>(_rtp)->Size = 2;
            }
        }
    }
}

template<typename K_Tp, typename V_Tp, size_t order>
V_Tp B_Plus_Tree<K_Tp, V_Tp, order>::search(const K_Tp &key) const
{
    if (this->Root == nullptr)
    {
        return V_Tp{};
    }

    Node* _iter {this->Root};
    while(true)
    {
        if (!_iter->Is_index) {
            DC = static_cast<Data_Node *>(_iter);
            if (DC->Keys[0] > key || DC->Keys[_iter->Size - 1] < key) {
                return V_Tp{};
            } else if (DC->Keys[_iter->Size - 1] == key) {
                return DC->Data[_iter->Size-1];
            }
            for (size_t _i = 0; _i < _iter->Size - 2; ++_i) {
                if (DC->Keys[_i] == key) {
                    return DC->Data[_i];
                } else if (key > DC->Keys[_i] && key < DC->Keys[_i + 1]) {
                    return V_Tp{};
                }
            }
        } else {
            IC = static_cast<Index_Node *>(_iter);
            if (IC->Keys[0] > key) {
                _iter = IC->Paths[0];
                continue;
            } else if (IC->Keys[_iter->Size - 1] <= key) {
                _iter = IC->Paths[_iter->Size - 1];
                continue;
            }
            for (size_t _i = 0; _i < _iter->Size - 1; ++_i) {
                if (key >= IC->Keys[_i] && key < IC->Keys[_i + 1]) {
                    _iter = IC->Paths[_i];
                    break;
                }
            }
        }
    }
}

template<typename K_Tp, typename V_Tp, size_t order>
bool B_Plus_Tree<K_Tp, V_Tp, order>::exist(const K_Tp &key) const
{
    if (this->Root == nullptr)
    {
        return false;
    }

    Node* _iter {this->Root};
    while(true)
    {
        if (!_iter->Is_index) {
            DC = static_cast<Data_Node *>(_iter);
            if (DC->Keys[0] > key || DC->Keys[_iter->Size - 1] < key) {
                return false;
            } else if (DC->Keys[_iter->Size - 1] < key) {
                return true;
            } else if (DC->Keys[_iter->Size - 1] == key) {
                return &DC->Data[_iter->Size-1];
            }
            for (size_t _i = 0; _i < _iter->Size - 2; ++_i) {
                if (DC->Keys[_i] == key) {
                    return true;
                } else if (key > DC->Keys[_i] && key < DC->Keys[_i + 1]) {
                    return false;
                }
            }
        } else {
            IC = static_cast<Index_Node *>(_iter);
            if (IC->Keys[0] > key) {
                _iter = IC->Paths[0];
                continue;
            } else if (IC->Keys[_iter->Size - 1] <= key) {
                _iter = IC->Paths[_iter->Size - 1];
                continue;
            }
            for (size_t _i = 0; _i < _iter->Size - 1; ++_i) {
                if (key >= IC->Keys[_i] && key < IC->Keys[_i + 1]) {
                    _iter = IC->Paths[_i];
                    break;
                }
            }
        }
    }
}

template<typename K_Tp, typename V_Tp, size_t order>
void B_Plus_Tree<K_Tp, V_Tp, order>::erase(const K_Tp &key) {
    if (this->Root == nullptr) {
        return;
    }

    Node *_iter{this->Root};
    while (true) {
        if (!_iter->Is_index) {
            DC = static_cast<Data_Node *>(_iter);
            if (DC->Keys[0] > key || DC->Keys[_iter->Size - 1] < key) {
                return;
            } else if (DC->Keys[_iter->Size - 1] == key) {
                if (_iter->Size == 1) {
                    this->destroy(*_iter);
                } else {
                    --_iter->Size;
                }
                return;
            }
            for (size_t _i = 0; _i < _iter->Size - 2; ++_i) {
                if (DC->Keys[_i] == key) {
                    if (_iter->Size == 1) {
                        this->destroy(*_iter);
                    } else {
                        for (size_t _j = _i; _j < _iter->Size - 2; ++_j) {
                            DC->Keys[_j] = DC->Keys[_j + 1];
                            DC->Data[_j] = DC->Data[_j + 1];
                        }
                        --_iter->Size;
                    }
                    return;
                } else if (key > DC->Keys[_i] && key < DC->Keys[_i + 1]) {
                    return;
                }
            }
        } else {
            IC = static_cast<Index_Node *>(_iter);
            if (IC->Keys[0] > key) {
                _iter = IC->Paths[0];
                continue;
            } else if (IC->Keys[_iter->Size - 1] <= key) {
                _iter = IC->Paths[_iter->Size - 1];
                continue;
            }
            for (size_t _i = 0; _i < _iter->Size - 1; ++_i) {
                if (key >= IC->Keys[_i] && key < IC->Keys[_i + 1]) {
                    _iter = IC->Paths[_i];
                    break;
                }
            }
        }
    }
}

template<typename K_Tp, typename V_Tp, size_t order>
void B_Plus_Tree<K_Tp, V_Tp, order>::destroy(B_Plus_Tree::Node &node) {
    Node *_iter = &node;
    while (true) {
        if (!_iter->Is_index) {
            DC = static_cast<Data_Node *>(_iter);
            if (DC->Father == nullptr) {
                this->Root = nullptr;
                return;
            } else {
                KR = DC->Keys[0];

            }
        }
    }
}

#endif //DATASTRUCTURE_B_PLUS_TREE_HPP
