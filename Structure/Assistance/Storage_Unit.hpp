#ifndef DATASTRUCTURE_STORAGE_UNIT_HPP
#define DATASTRUCTURE_STORAGE_UNIT_HPP

template<typename K_Tp, typename V_Tp>
struct Pair_Unit
{
    Pair_Unit();

    explicit Pair_Unit(K_Tp const & , V_Tp const &);

    inline bool operator==(Pair_Unit const &) const;

    inline bool operator!=(Pair_Unit const &) const;

    bool operator<(Pair_Unit const &) const;

    bool operator>(Pair_Unit const &) const;

    bool operator<=(Pair_Unit const &) const;

    bool operator>=(Pair_Unit const &) const;

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
Pair_Unit<K_Tp, V_Tp>::Pair_Unit()
:Key{K_Tp{}}, Value{V_Tp{}} {}

template<typename K_Tp, typename V_Tp>
Pair_Unit<K_Tp, V_Tp>::Pair_Unit(const K_Tp &key, const V_Tp &value)
:Key{key}, Value{value} {}

template<typename K_Tp, typename V_Tp>
bool Pair_Unit<K_Tp, V_Tp>::operator==(const Pair_Unit &op) const
{
    return this->Key == op.Key && this->Value == op.Value;
}

template<typename K_Tp, typename V_Tp>
bool Pair_Unit<K_Tp, V_Tp>::operator!=(const Pair_Unit &op) const
{
    return this->Key != op.Key || this->Value != op.Value;
}

template<typename K_Tp, typename V_Tp>
bool Pair_Unit<K_Tp, V_Tp>::operator<(const Pair_Unit &op) const
{
    return this->Key<op.Key;
}

template<typename K_Tp, typename V_Tp>
bool Pair_Unit<K_Tp, V_Tp>::operator>(const Pair_Unit &op) const
{
    return this->Key>op.Key;
}

template<typename K_Tp, typename V_Tp>
bool Pair_Unit<K_Tp, V_Tp>::operator<=(const Pair_Unit &op) const
{
    return this->Key<=op.Key;
}

template<typename K_Tp, typename V_Tp>
bool Pair_Unit<K_Tp, V_Tp>::operator>=(const Pair_Unit &op) const
{
    return this->Key>=op.Key;
}

template<typename K_Tp, typename V_Tp>
bool Pair_Unit<K_Tp, V_Tp>::operator==(const K_Tp &word) const
{
    return this->Key == word;
}

template<typename K_Tp, typename V_Tp>
bool Pair_Unit<K_Tp, V_Tp>::operator!=(const K_Tp &word) const
{
    return this->Key != word;
}

template<typename K_Tp, typename V_Tp>
bool Pair_Unit<K_Tp, V_Tp>::operator<(const K_Tp &word) const
{
    return this->Key < word;
}

template<typename K_Tp, typename V_Tp>
bool Pair_Unit<K_Tp, V_Tp>::operator>(const K_Tp &word) const
{
    return this->Key > word;
}

template<typename K_Tp, typename V_Tp>
bool Pair_Unit<K_Tp, V_Tp>::operator<=(const K_Tp &word) const
{
    return this->Key <= word;
}

template<typename K_Tp, typename V_Tp>
bool Pair_Unit<K_Tp, V_Tp>::operator>=(const K_Tp &word) const
{
    return this->Key >= word;
}

#endif //DATASTRUCTURE_STORAGE_UNIT_HPP
