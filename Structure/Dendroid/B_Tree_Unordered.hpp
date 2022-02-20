#ifndef DATASTRUCTURE_B_TREE_UNORDERED_HPP
#define DATASTRUCTURE_B_TREE_UNORDERED_HPP

#include <Assistance/Storage_Unit.hpp>
#include <cstdlib>
#include <utility>

template<typename K_Tp, typename V_Tp, size_t order>
class B_Tree_Unordered
{
private:
    struct Node
    {
        Node();

        std::pair<bool, size_t> seek(K_Tp const &) const;

        KW_Pair<K_Tp, V_Tp> Container[order] {};

        Node* Table[order + 1] {};

        Node *Father = nullptr;

        size_t Size = 1;
    };

    void destroy(Node &, size_t const &);

    void spilt(Node &);
public:
    B_Tree_Unordered();

    void insert(K_Tp const &, V_Tp const &);

    V_Tp search(K_Tp const &) const;

    bool exist(K_Tp const &) const;

    void erase(K_Tp const &);

protected:
    Node *Root;
};

template<typename K_Tp, typename V_Tp, size_t order>
B_Tree_Unordered<K_Tp, V_Tp, order>::Node::Node() {if (order < 3) throw;}

template<typename K_Tp, typename V_Tp, size_t order>
std::pair<bool, size_t> B_Tree_Unordered<K_Tp, V_Tp, order>::Node::seek(const K_Tp &key) const
{
    size_t const _len = this->Size-1;
    if (_len == 0 || key < this->Container[0].Key) return std::pair<bool, size_t> {false, 0};
    if (this->Container[_len - 1] == key) return std::pair<bool, size_t> {true, _len - 1};
    if (this->Container[_len - 1] < key) return std::pair<bool, size_t> {false, _len};

    for(size_t _i = 0; _i < _len-1; ++ _i)
    {
        if (key == this->Container[_i].Key)
        {
            return std::pair<bool, size_t> {true, _i};
        }
        if (key > this->Container[_i].Key && key < this->Container[_i + 1].Key)
        {
            return std::pair<bool, size_t> {false, _i+1};
        }
    }
    return std::pair<bool, size_t> {false, _len};
}

template<typename K_Tp, typename V_Tp, size_t order>
B_Tree_Unordered<K_Tp, V_Tp, order>::B_Tree_Unordered()
        :Root{nullptr} {}

template<typename K_Tp, typename V_Tp, size_t order>
void B_Tree_Unordered<K_Tp, V_Tp, order>::insert(const K_Tp &key, const V_Tp &value)
{
    if (this->Root == nullptr)
    {
        this->Root = new Node {};
        this->Root->Container[0] = KW_Pair<K_Tp, V_Tp> {key, value};
        this->Root->Table[1] = nullptr;
        ++this->Root->Size;
        return;
    }

    Node *_iter {this->Root};
    std::pair<bool, size_t> _pair {};

    while (true)
    {
        _pair = _iter->seek(key);
        if (_pair.first)
        {
            _iter->Container[_pair.second].Value = value;
            return;
        } else {
            if (_iter->Table[_pair.second] != nullptr)
            {
                _iter = _iter->Table[_pair.second];
                continue;
            } else {
                for(size_t i = _iter->Size-1; i>=_pair.second; --i)
                {
                    _iter->Table[i + 1] = _iter->Table[i];
                }
                for(size_t i = _iter->Size-2; i>=_pair.second; --i)
                {
                    _iter->Container[i + 1] = _iter->Container[i];
                }
                _iter->Container[_pair.second] = KW_Pair<K_Tp,V_Tp>{key, value};
                _iter->Table[_pair.second] = nullptr;
                ++_iter->Size;
                if (_iter->Size > order) this->spilt(*_iter);
                break;
            }
        }
    }
}

template<typename K_Tp, typename V_Tp, size_t order>
void B_Tree_Unordered<K_Tp, V_Tp, order>::spilt(B_Tree_Unordered::Node &node)
{
    auto _idx = static_cast<size_t>((node.Size - 1) / 2);
    auto *_ln = new Node {};
    auto *_rn = new Node {};
    for(size_t _i=0;_i<_idx; ++_i) _ln->Container[_i] = node.Container[_i];
    for(size_t _i=0;_i<node.Size-_idx-2;++_i) _rn->Container[_i] = node.Container[_idx + _i + 1];
    for(size_t _i=0;_i<_idx; ++_i) _ln->Table[_i] = node.Table[_i];
    for(size_t _i=0;_i<node.Size-_idx-1;++_i) _rn->Table[_i] = node.Table[_i + _idx];

    _ln->Size = _idx + 1;
    _rn->Size = node.Size - _idx - 1;
    if(node.Father == nullptr)
    {
        auto &_top = *new Node {};
        _top.Container[0] = node.Container[_idx];
        _top.Table[0] = _ln;
        _top.Table[1] = _rn;
        _ln->Father = &_top;
        _rn->Father = &_top;
        _top.Size = 2;
        this->Root = &_top;
    } else {
        auto *_fp = node.Father;
        size_t _i = 0;
        for(; _i != _fp->Size; ++ _i) {
            if (_fp->Table[_i] == &node) break;
        }
        _ln->Father = _fp;
        _rn->Father = _fp;
        _fp->Table[_i] = _rn;
        for(size_t _j=_fp->Size-2;_j>=_i;--_j)
        {
            _fp->Container[_j + 1] = _fp->Container[_j];
        }
        for(size_t _j=_fp->Size-1;_j>=_i;--_j)
        {
            _fp->Table[_j + 1] = _fp->Table[_j];
        }
        _fp->Container[_i] = node.Container[_idx];
        _fp->Table[_i] = _ln;
        ++_fp->Size;
        if (_fp->Size > order) this->spilt(*_fp);
    }
}

template<typename K_Tp, typename V_Tp, size_t order>
void B_Tree_Unordered<K_Tp, V_Tp, order>::erase(const K_Tp &key)
{
    if (this->Root == nullptr) return;
    Node *_iter = this->Root;
    std::pair<bool, size_t> _pair {};

    while (true)
    {
        _pair = _iter->seek(key);
        if (_pair.first)
        {
            this->destroy(*_iter, _pair.second);
            return;
        } else {
            if (_iter->Table[_pair.second] != nullptr)
            {
                _iter = _iter->Table[_pair.second];
                continue;
            } else {
                return;
            }
        }
    }
}

template<typename K_Tp, typename V_Tp, size_t order>
void B_Tree_Unordered<K_Tp, V_Tp, order>::destroy(B_Tree_Unordered::Node &_iter, const size_t &index) {
    if (_iter.Table[index] == nullptr && _iter.Table[index + 1] == nullptr)
    {
        for(size_t _i=index; _i <_iter.Size-2;++_i)
        {
            _iter.Container[_i] = _iter.Container[_i + 1];
        }
        for(size_t _i=index; _i<_iter.Size-1;++_i)
        {
            _iter.Table[_i] = _iter.Table[_i + 1];
        }
        _iter.Container[_iter.Size - 2] = KW_Pair<K_Tp,V_Tp> {};
        _iter.Table[_iter.Size - 1] = nullptr;
        --_iter.Size;
        if (_iter.Size == 1)
        {
            size_t _i = 0;
            for(; _i != _iter.Father->Size; ++ _i)
            {
                if (_iter.Father->Table[_i] == &_iter) _iter.Father->Table[_i] = nullptr;
            }
        }
    } else if (_iter.Table[index] != nullptr)
    {
        Node *_temp = _iter.Table[index];
        _iter.Container[index] = _temp->Container[_temp->Size - 2];
        this->destroy(*_temp, _temp->Size-2);
    } else {
        Node *_temp = _iter.Table[index + 1];
        _iter.Container[index] = _temp->Container[0];
        this->destroy(*_temp, 0);
    }
}

template<typename K_Tp, typename V_Tp, size_t order>
V_Tp B_Tree_Unordered<K_Tp, V_Tp, order>::search (const K_Tp &key) const
{
    Node *_iter {this->Root};
    std::pair<bool, size_t> _pair {};

    while(true)
    {
        _pair = _iter->seek(key);
        if(_pair.first)
        {
            return _iter->Container[_pair.second].Value;
        } else {
            if (_iter->Table[_pair.second] != nullptr)
            {
                _iter = _iter->Table[_pair.second];
                continue;
            } else {
                return V_Tp{};
            }
        }
    }
}

template<typename K_Tp, typename V_Tp, size_t order>
bool B_Tree_Unordered<K_Tp, V_Tp, order>::exist(const K_Tp &key) const
{
    Node *_iter {this->Root};
    std::pair<bool, size_t> _pair {};

    while(true)
    {
        _pair = _iter->seek(key);
        if(_pair.first)
        {
            return true;
        } else {
            if (_iter->Table[_pair.second] != nullptr)
            {
                _iter = _iter->Table[_pair.second];
                continue;
            } else {
                return false;
            }
        }
    }
}



#endif //DATASTRUCTURE_B_TREE_UNORDERED_HPP