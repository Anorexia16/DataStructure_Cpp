#ifndef DATASTRUCTURE_HASH_TABLE_HPP
#define DATASTRUCTURE_HASH_TABLE_HPP

#include "settools.hpp"
#include <functional>

namespace ax 
{
    template <typename Tp>
    size_t static_to_size(Tp const &value)
    {
        return static_cast<size_t>(value);
    }

    template<typename K_Tp, typename V_Tp>
    class hash_table {
    public:
        explicit hash_table(size_t (*)(K_Tp const &) = static_to_size<K_Tp>, size_t const & =100);

        explicit hash_table(std::function<size_t(K_Tp const &)> const &, size_t const & = 100);

        hash_table &operator=(hash_table<K_Tp, V_Tp> const &) noexcept = default;

        hash_table &operator=(hash_table<K_Tp, V_Tp> &&) noexcept = default;

        hash_table(hash_table<K_Tp, V_Tp> const &) noexcept = default;

        hash_table(hash_table<K_Tp, V_Tp> &&) noexcept = default;

        ~hash_table() = default;

        void clear() noexcept;

        [[nodiscard]] size_t size() const;

        [[nodiscard]] bool empty() const;

        V_Tp &operator[](K_Tp const &);

        void remove(K_Tp const &);

        V_Tp find(K_Tp const &) const;

        bool exist(K_Tp const &) const;

    protected:
        class hash_bucket
        {
        public:
            hash_bucket(): R_Container{}, count_flag{0} {}

            ~hash_bucket() = default;

            V_Tp &cover(K_Tp const &);

            void destroy(K_Tp const &);

            V_Tp find(K_Tp const &) const;

            bool exist(K_Tp const &) const;

            size_t count_flag;

        protected:
            std::vector<pair<K_Tp, V_Tp>> R_Container;
        };

        std::vector<hash_bucket> Container;

        std::function<size_t(K_Tp const &)> Transform_Func;

        size_t Size;
    };

    template<typename K_Tp, typename V_Tp>
    V_Tp &hash_table<K_Tp, V_Tp>::hash_bucket::cover(const K_Tp &key)
    {
        for(auto &&iterator: this->R_Container)
        {
            if (key == iterator.key) return iterator.value;
        }
        this->count_flag = 1;
        this->R_Container.template emplace_back(pair{key, V_Tp{}});
        return this->R_Container.rbegin()->value;
    }

    template<typename K_Tp, typename V_Tp>
    void hash_table<K_Tp, V_Tp>::hash_bucket::destroy(K_Tp const &key)
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
    V_Tp hash_table<K_Tp, V_Tp>::hash_bucket::find(const K_Tp &key) const
    {
        for(auto &&iterator: this->R_Container)
        {
            if (key == iterator.key) return iterator.value;
        }
        throw;
    }

    template<typename K_Tp, typename V_Tp>
    bool hash_table<K_Tp, V_Tp>::hash_bucket::exist(const K_Tp &key) const
    {
        for(auto &&iterator: this->R_Container)
        {
            if (key == iterator.key) return true;
        }
        return false;
    }

    template<typename K_Tp, typename V_Tp>
    hash_table<K_Tp, V_Tp>::hash_table(size_t (*func)(const K_Tp &), size_t const &Capacity)
            :Transform_Func{std::function<size_t(K_Tp const &)>(func)}, Container{}, Size{}
    {for(auto i = 0;i!=Capacity;++i) Container.template emplace_back(hash_bucket{});}

    template<typename K_Tp, typename V_Tp>
    hash_table<K_Tp, V_Tp>::hash_table(const std::function<size_t(const K_Tp &)> &func, size_t const &Capacity)
            :Transform_Func{func}, Container{}, Size{} {for(auto i = 0;i!=Capacity;++i) Container.template emplace_back(hash_bucket{});}

    template<typename K_Tp, typename V_Tp>
    void hash_table<K_Tp, V_Tp>::clear() noexcept
    {
        this->Container.clear();
    }

    template<typename K_Tp, typename V_Tp>
    size_t hash_table<K_Tp, V_Tp>::size() const
    {
        return this->Size;
    }

    template<typename K_Tp, typename V_Tp>
    bool hash_table<K_Tp, V_Tp>::empty() const
    {
        return this->Size==0;
    }

    template<typename K_Tp, typename V_Tp>
    V_Tp &hash_table<K_Tp, V_Tp>::operator[](const K_Tp &key)
    {
        hash_bucket &tar = this->Container[this->Transform_Func(key)];
        V_Tp &value = tar.cover(key);
        this->Size += tar.count_flag;
        tar.count_flag = 0;
        return value;
    }

    template<typename K_Tp, typename V_Tp>
    void hash_table<K_Tp, V_Tp>::remove(const K_Tp &key)
    {
        hash_bucket &tar = this->Container[this->Transform_Func(key)];
        tar.destroy(key);
        this->Size += tar.count_flag;
        tar.count_flag = 0;
    }

    template<typename K_Tp, typename V_Tp>
    V_Tp hash_table<K_Tp, V_Tp>::find(const K_Tp &key) const
    {
        return this->Container[this->Transform_Func(key)].find(key);
    }

    template<typename K_Tp, typename V_Tp>
    bool hash_table<K_Tp, V_Tp>::exist(const K_Tp &key) const
    {
        return this->Container[this->Transform_Func(key)].exist(key);
    }
}

#endif //DATASTRUCTURE_HASH_TABLE_HPP
