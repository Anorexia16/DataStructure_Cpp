#ifndef DATASTRUCTURE_ARRAY_LIST
#define DATASTRUCTURE_ARRAY_LIST

#include <iterator>
#include "../Abstract/Abstract_Linear_List.hpp"

template<typename T>
class ArrayList : LinearList<T>
{
public:
    explicit ArrayList(size_t const &);

    ArrayList(ArrayList<T> const &);

    ~ArrayList();

    [[nodiscard]] bool empty() const;

    [[nodiscard]] size_t size() const;

    T &operator[](int const &) const;

    size_t find(T const &) const;

    void erase(int const &);

    void insert(int const &, T const &);

    friend std::ostream &operator<<(std::ostream &out, ArrayList<T> const &x)
    {
        std::copy(x.Container, x.Container + x.Size, std::ostream_iterator<T>(out, " "));
        out << std::endl;
        return out;
    }

protected:
    inline void _index_check(int const &index) const;

    T *Container;
    size_t Capacity{};
    size_t Size{};
};

template<typename T>
ArrayList<T>::ArrayList(size_t const &capacity)
        : Container(new T[capacity]), Capacity{capacity}, Size{0} {}

template<typename T>
ArrayList<T>::ArrayList(ArrayList<T> const &copy)
        : Container{copy.Container}, Capacity{copy.Capacity}, Size{copy.Size} {}


template<typename T>
ArrayList<T>::~ArrayList()
{
    delete (Container);
}

template<typename T>
bool ArrayList<T>::empty() const
{
    return (Size == 0);
}

template<typename T>
size_t ArrayList<T>::size() const
{
    return Size;
}

template<typename T>
T &ArrayList<T>::operator[](int const &index) const
{
    _index_check(index);
    return Container[index];
}

template<typename T>
size_t ArrayList<T>::find(const T &elem) const
{
    for (auto iter = 0; iter != this->Size; iter++) {
        if (Container[iter] == elem) {
            return iter;
        }
    }
    return -1;
}

template<typename T>
void ArrayList<T>::insert(int const &index, T const &elem)
{
    if (Size == Capacity) throw;
    std::copy(Container + index, Container + Size, Container + index + 1);
    Container[index] = elem;
    Size += 1;
}

template<typename T>
void ArrayList<T>::erase(int const &index)
{
    std::copy(Container + index + 1, Container + Size, Container + index);
    Container[Size]--.~T();
    Size -= 1;
}

template<typename T>
void ArrayList<T>::_index_check(int const &index) const
{
    if (index < 0 || index > this->Size) throw;
}


#endif //DATASTRUCTURE_ARRAY_LIST
