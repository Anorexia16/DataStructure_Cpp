#ifndef DATASTRUCTURE_STORAGE_UNIT_HPP
#define DATASTRUCTURE_STORAGE_UNIT_HPP

template<typename K_Tp, typename V_Tp>
struct KW_Pair
{
    KW_Pair();

    explicit KW_Pair(K_Tp const & , V_Tp const &);

    inline bool operator==(KW_Pair const &) const;

    inline bool operator!=(KW_Pair const &) const;

    bool operator<(KW_Pair const &) const;

    bool operator>(KW_Pair const &) const;

    bool operator<=(KW_Pair const &) const;

    bool operator>=(KW_Pair const &) const;

    inline bool operator==(K_Tp const &) const;

    inline bool operator!=(K_Tp const &) const;

    inline bool operator<(K_Tp const &) const;

    inline bool operator>(K_Tp const &) const;

    inline bool operator<=(K_Tp const &) const;

    inline bool operator>=(K_Tp const &) const;

    K_Tp Key;

    V_Tp Value;
};

template<typename K_Tp, typename V_Tp>
KW_Pair<K_Tp, V_Tp>::KW_Pair()
:Key{K_Tp{}}, Value{V_Tp{}} {}

template<typename K_Tp, typename V_Tp>
KW_Pair<K_Tp, V_Tp>::KW_Pair(const K_Tp &key, const V_Tp &value)
:Key{key}, Value{value} {}

template<typename K_Tp, typename V_Tp>
bool KW_Pair<K_Tp, V_Tp>::operator==(const KW_Pair &op) const
{
    return this->Key == op.Key && this->Value == op.Value;
}

template<typename K_Tp, typename V_Tp>
bool KW_Pair<K_Tp, V_Tp>::operator!=(const KW_Pair &op) const
{
    return this->Key != op.Key || this->Value != op.Value;
}

template<typename K_Tp, typename V_Tp>
bool KW_Pair<K_Tp, V_Tp>::operator<(const KW_Pair &op) const
{
    return this->Key<op.Key;
}

template<typename K_Tp, typename V_Tp>
bool KW_Pair<K_Tp, V_Tp>::operator>(const KW_Pair &op) const
{
    return this->Key>op.Key;
}

template<typename K_Tp, typename V_Tp>
bool KW_Pair<K_Tp, V_Tp>::operator<=(const KW_Pair &op) const
{
    return this->Key<=op.Key;
}

template<typename K_Tp, typename V_Tp>
bool KW_Pair<K_Tp, V_Tp>::operator>=(const KW_Pair &op) const
{
    return this->Key>=op.Key;
}

template<typename K_Tp, typename V_Tp>
bool KW_Pair<K_Tp, V_Tp>::operator==(const K_Tp &word) const
{
    return this->Key == word;
}

template<typename K_Tp, typename V_Tp>
bool KW_Pair<K_Tp, V_Tp>::operator!=(const K_Tp &word) const
{
    return this->Key != word;
}

template<typename K_Tp, typename V_Tp>
bool KW_Pair<K_Tp, V_Tp>::operator<(const K_Tp &word) const
{
    return this->Key < word;
}

template<typename K_Tp, typename V_Tp>
bool KW_Pair<K_Tp, V_Tp>::operator>(const K_Tp &word) const
{
    return this->Key > word;
}

template<typename K_Tp, typename V_Tp>
bool KW_Pair<K_Tp, V_Tp>::operator<=(const K_Tp &word) const
{
    return this->Key <= word;
}

template<typename K_Tp, typename V_Tp>
bool KW_Pair<K_Tp, V_Tp>::operator>=(const K_Tp &word) const
{
    return this->Key >= word;
}

#endif //DATASTRUCTURE_STORAGE_UNIT_HPP
