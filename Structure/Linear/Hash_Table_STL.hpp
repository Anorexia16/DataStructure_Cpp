#ifndef DATASTRUCTURE_HASH_TABLE_STL_HPP
#define DATASTRUCTURE_HASH_TABLE_STL_HPP

#include <vector>
#include <functional>

template<typename K_Tp, typename V_Tp>
class Key_Value_Pair
{
public:
    K_Tp key;
    V_Tp value;
};

template <typename Tp>
size_t static_to_size(Tp const &value)
{
    return static_cast<size_t>(value);
}

template<typename K_Tp, typename V_Tp>
class Hash_Table_STL {
public:
    explicit Hash_Table_STL(size_t (*)(K_Tp const &) = static_to_size<K_Tp>, size_t const & =100);

    explicit Hash_Table_STL(std::function<size_t(K_Tp const &)> const &, size_t const & = 100);

    Hash_Table_STL &operator=(Hash_Table_STL<K_Tp, V_Tp> const &) noexcept = default;

    Hash_Table_STL &operator=(Hash_Table_STL<K_Tp, V_Tp> &&) noexcept = default;

    Hash_Table_STL(Hash_Table_STL<K_Tp, V_Tp> const &) noexcept = default;

    Hash_Table_STL(Hash_Table_STL<K_Tp, V_Tp> &&) noexcept = default;

    ~Hash_Table_STL() = default;

    void clear() noexcept;

    [[nodiscard]] size_t size() const;

    [[nodiscard]] bool empty() const;

    V_Tp &operator[](K_Tp const &);

    void remove(K_Tp const &);

    V_Tp find(K_Tp const &) const;

    bool exist(K_Tp const &) const;

protected:
    class Hash_Bucket_STL
    {
    public:
        Hash_Bucket_STL(): R_Container{}, count_flag{0} {}

        ~Hash_Bucket_STL() = default;

        V_Tp &cover(K_Tp const &);

        void destroy(K_Tp const &);

        V_Tp find(K_Tp const &) const;

        bool exist(K_Tp const &) const;

        size_t count_flag;

    protected:
        std::vector<Key_Value_Pair<K_Tp, V_Tp>> R_Container;
    };

    std::vector<Hash_Bucket_STL> Container;

    std::function<size_t(K_Tp const &)> Transform_Func;

    size_t Size;
};

template<typename K_Tp, typename V_Tp>
V_Tp &Hash_Table_STL<K_Tp, V_Tp>::Hash_Bucket_STL::cover(const K_Tp &key)
{
    for(auto &&iterator: this->R_Container)
    {
        if (key == iterator.key) return iterator.value;
    }
    this->count_flag = 1;
    this->R_Container.template emplace_back(Key_Value_Pair{key, V_Tp{}});
    return this->R_Container.rbegin()->value;
}

template<typename K_Tp, typename V_Tp>
void Hash_Table_STL<K_Tp, V_Tp>::Hash_Bucket_STL::destroy(K_Tp const &key)
{
    for(auto iterator=std::begin(this->R_Container); iterator!=std::end(this->R_Container); ++iterator)
    {
        if (key == (*iterator).key)
        {
            this->R_Container.erase(iterator);
            this->count_flag = -1;
            return;
        }
    }
}

template<typename K_Tp, typename V_Tp>
V_Tp Hash_Table_STL<K_Tp, V_Tp>::Hash_Bucket_STL::find(const K_Tp &key) const
{
    for(auto &&iterator: this->R_Container)
    {
        if (key == iterator.key) return iterator.value;
    }
    throw;
}

template<typename K_Tp, typename V_Tp>
bool Hash_Table_STL<K_Tp, V_Tp>::Hash_Bucket_STL::exist(const K_Tp &key) const
{
    for(auto &&iterator: this->R_Container)
    {
        if (key == iterator.key) return true;
    }
    return false;
}

template<typename K_Tp, typename V_Tp>
Hash_Table_STL<K_Tp, V_Tp>::Hash_Table_STL(size_t (*func)(const K_Tp &), size_t const &Capacity)
:Transform_Func{std::function<size_t(K_Tp const &)>(func)}, Container{}, Size{}
{for(auto i = 0;i!=Capacity;++i) Container.template emplace_back(Hash_Bucket_STL{});}

template<typename K_Tp, typename V_Tp>
Hash_Table_STL<K_Tp, V_Tp>::Hash_Table_STL(const std::function<size_t(const K_Tp &)> &func, size_t const &Capacity)
:Transform_Func{func}, Container{}, Size{} {for(auto i = 0;i!=Capacity;++i) Container.template emplace_back(Hash_Bucket_STL{});}

template<typename K_Tp, typename V_Tp>
void Hash_Table_STL<K_Tp, V_Tp>::clear() noexcept
{
    this->Container.clear();
}

template<typename K_Tp, typename V_Tp>
size_t Hash_Table_STL<K_Tp, V_Tp>::size() const
{
    return this->Size;
}

template<typename K_Tp, typename V_Tp>
bool Hash_Table_STL<K_Tp, V_Tp>::empty() const
{
    return this->Size==0;
}

template<typename K_Tp, typename V_Tp>
V_Tp &Hash_Table_STL<K_Tp, V_Tp>::operator[](const K_Tp &key)
{
    Hash_Bucket_STL &tar = this->Container[this->Transform_Func(key)];
    V_Tp &value = tar.cover(key);
    this->Size += tar.count_flag;
    tar.count_flag = 0;
    return value;
}

template<typename K_Tp, typename V_Tp>
void Hash_Table_STL<K_Tp, V_Tp>::remove(const K_Tp &key)
{
    Hash_Bucket_STL &tar = this->Container[this->Transform_Func(key)];
    tar.destroy(key);
    this->Size += tar.count_flag;
    tar.count_flag = 0;
}

template<typename K_Tp, typename V_Tp>
V_Tp Hash_Table_STL<K_Tp, V_Tp>::find(const K_Tp &key) const
{
    return this->Container[this->Transform_Func(key)].find(key);
}

template<typename K_Tp, typename V_Tp>
bool Hash_Table_STL<K_Tp, V_Tp>::exist(const K_Tp &key) const
{
    return this->Container[this->Transform_Func(key)].exist(key);
}


#endif //DATASTRUCTURE_HASH_TABLE_STL_HPP
