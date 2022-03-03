#ifndef DATASTRUCTURE_ARRAY_LIST
#define DATASTRUCTURE_ARRAY_LIST

#include "vector.hpp"
#include "abstract.hpp"

namespace ax {
    template<typename T>
    class array_list : linear_list<T>
    {
    public:
        explicit array_list(size_t const &);

        array_list(array_list<T> const &);

        ~array_list();

        [[nodiscard]] bool empty() const;

        [[nodiscard]] size_t size() const;

        T &operator[](int const &) const;

        size_t find(T const &) const;

        void erase(int const &);

        void insert(int const &, T const &);

        friend std::ostream &operator<<(std::ostream &out, array_list<T> const &x)
        {
            std::copy(x.Container, x.Container + x.Size, std::ostream_iterator<T>(out, " "));
            return out;
        }

    protected:
        inline void _index_check(int const &index) const;

        T *Container;
        size_t Capacity{};
        size_t Size{};
    };

    template<typename T,
            template<typename elem> class Cont = ax::vector>
    class array_list_stl : linear_list<T>
    {
    public:
        explicit array_list_stl();

        array_list_stl(array_list_stl const &);

        ~array_list_stl();

        [[nodiscard]] bool empty() const;

        [[nodiscard]] size_t size() const;

        T &operator[](int const &) const;

        size_t find(T const &) const;

        void erase(int const &);

        void insert(int const &, T const &);

        Cont<T> &operator*();

        Cont<T> *operator->();

        friend std::ostream &operator<<(std::ostream &out, array_list_stl const &x) {
            std::copy(std::begin(x.Container), std::end(x.Container), std::ostream_iterator<T>(out));
            return out;
        }

    protected:
        Cont<T> Container;
    };

    template<typename T,
            template<typename elem> class Cont>
    array_list_stl<T, Cont>::array_list_stl()
            : Container{Cont < T > {}} {}

    template<typename T,
            template<typename elem> class Cont>
    array_list_stl<T, Cont>::array_list_stl(array_list_stl const &copy)
            : Container{copy.Container} {}

    template<typename T,
            template<typename elem> class Cont>
    array_list_stl<T, Cont>::~array_list_stl()
    {
        for (auto &&iter: this->Container) iter.~T();
        delete (this);
    }

    template<typename T,
            template<typename elem> class Cont>
    bool array_list_stl<T, Cont>::empty() const
    {
        return this->Container.Size() == 0;
    }

    template<typename T,
            template<typename elem> class Cont>
    size_t array_list_stl<T, Cont>::size() const
    {
        return this->Container.Size();
    }

    template<typename T,
            template<typename elem> class Cont>
    T &array_list_stl<T, Cont>::operator[](int const &x) const
    {
        return this->Container[x];
    }

    template<typename T,
            template<typename elem> class Cont>
    size_t array_list_stl<T, Cont>::find(const T &x) const
    {
        for (auto &&iter: this->Container) {
            if (iter == x) return &iter - &this->Container[0];
        }
        return -1;
    }

    template<typename T,
            template<typename elem> class Cont>
    void array_list_stl<T, Cont>::erase(int const &x)
    {
        this->Container.erase(std::begin(this->Container) + x);
    }

    template<typename T,
            template<typename elem> class Cont>
    void array_list_stl<T, Cont>::insert(int const &index, const T &elem)
    {
        this->Container.insert(std::begin(this->Container) + index, elem);
    }

    template<typename T,
            template<typename elem> class Cont>
    Cont<T> &array_list_stl<T, Cont>::operator*() { return *&Container; }

    template<typename T,
            template<typename elem> class Cont>
    Cont<T> *array_list_stl<T, Cont>::operator->() { return &Container; }


    template<typename T>
    array_list<T>::array_list(size_t const &capacity)
            : Container(new T[capacity]), Capacity{capacity}, Size{0} {}

    template<typename T>
    array_list<T>::array_list(array_list<T> const &copy)
            : Container{copy.Container}, Capacity{copy.Capacity}, Size{copy.Size} {}


    template<typename T>
    array_list<T>::~array_list()
    {
        delete (Container);
    }

    template<typename T>
    bool array_list<T>::empty() const
    {
        return (Size == 0);
    }

    template<typename T>
    size_t array_list<T>::size() const
    {
        return Size;
    }

    template<typename T>
    T &array_list<T>::operator[](int const &index) const
    {
        _index_check(index);
        return Container[index];
    }

    template<typename T>
    size_t array_list<T>::find(const T &elem) const
    {
        for (auto iter = 0; iter != this->Size; iter++) {
            if (Container[iter] == elem) {
                return iter;
            }
        }
        return -1;
    }

    template<typename T>
    void array_list<T>::insert(int const &index, T const &elem)
    {
        if (Size == Capacity) throw;
        std::copy(Container + index, Container + Size, Container + index + 1);
        Container[index] = elem;
        Size += 1;
    }

    template<typename T>
    void array_list<T>::erase(int const &index)
    {
        std::copy(Container + index + 1, Container + Size, Container + index);
        Container[Size]--.~T();
        Size -= 1;
    }

    template<typename T>
    void array_list<T>::_index_check(int const &index) const
    {
        if (index < 0 || index > this->Size) throw;
    }
}

#endif //DATASTRUCTURE_ARRAY_LIST
