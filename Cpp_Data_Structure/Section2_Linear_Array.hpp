#ifndef DATASTRUCTURE_SECTION2_LINEAR_ARRAY_HPP // 数据结构与算法第五章习题练习
#define DATASTRUCTURE_SECTION2_LINEAR_ARRAY_HPP

#include "../Structure/Linear/Array_List.hpp"
#include <algorithm>
#include <cmath>

// assistance interface
template<typename T>
class arrayList02 : public ArrayList<T> {
public:
    explicit arrayList02(int const &);

    void expand(int const &);

    void trim_to_size();

    void set_size(int const &);

    void set_size();

    T &operator[](int const &);

    [[nodiscard]] size_t cap() const;

    bool operator==(arrayList02<T> const &) const;

    bool operator!=(arrayList02<T> const &) const;

    bool operator<(arrayList02<T> const &) const;

    void push_back(const T &);

    void pop_back();

    void swap(ArrayList <T> &);

    void reserve(int const &);

    T set(int const &, T);

    void clear();

    void remove_range(int const &, int const &);

    int last_index_of(T const &);

    void erase_new(int const &, int const &);

    void reverse();

    void left_shift(int const &);

    void clockwise(int const &);

    void half();

    arrayList02<T> meld(arrayList02<T> const &);

    arrayList02<T> merge(arrayList02<T> const &);

    void split(T *&, T *&);
};

template<typename T>
arrayList02<T>::arrayList02(int const &capacity):ArrayList<T>::ArrayList{capacity}{}

template<typename T>
size_t arrayList02<T>::cap() const
{
    return this->Capacity;
}

// 2.1
// 1) false; 2) 4; 3) a,mod_five,Error,Error 4) 0, 2, -1;
// 2) void, void, void; 6) (e, a, f, g, b, mod_five, h, d)

// 2.2
// [a, b, c, d, e], [f, a, b, c, d, e], [f, a, b, g, mod_five, d, e],
// [f, a, b, g, c, d, e, h], [a, b, g, c, d, e, h], [a, b, g, mod_five, e, h]

// 2.3
template<typename T, template<typename elem, typename = std::allocator<elem>> class CONT>
void changeLength2D_Linear(ArrayList <ArrayList<T>> &op, CONT<int> const &tar)
{
    ArrayList <T> temp{};
    for (auto iter = 0; iter != op.size(); iter++)
    {
        temp = ArrayList<T>(tar[iter]);
        std::copy(op[iter], op[iter] + op[iter].size(), temp);
        op[iter] = temp;
    }
}

// 2.4
template<typename T>
void arrayList02<T>::expand(int const &x)
{
    if (x < this->size()) throw;
    T *temp = new T[x];
    this->Container = temp;
}

// 2.5
template<typename T>
void arrayList02<T>::trim_to_size()
{
    (this->size() > 1) ? this->set_size(this->size()) : this->set_size(1);
}

// 2.6
template<typename T>
void arrayList02<T>::set_size(int const &x)
{
    int temp = (this->size() > x) ? x : this->size();
    T *temp_container = new T[x];
    std::copy(this->Container, this->Container + temp, temp_container);
    this->Container = temp_container;
    this->Capacity = x;
}

template<typename T>
void arrayList02<T>::set_size()
{
    T *temp_container = new T[2 * this->size()];
    std::copy(this->Container, this->Container + this->size(), temp_container);
    this->Container = temp_container;
    this->Capacity = 2 * this->size();
}

// 2.7
template<typename T>
T &arrayList02<T>::operator[](int const &x)
{
    this->_index_check(x);
    return this->Container[x];
}

// 2.8
template<typename T>
bool arrayList02<T>::operator==(const arrayList02<T> &op) const
{
    if (this->size != op.size()) return false;
    for (auto i = 0; i != op.size; i++)
    {
        if (this[i] != op[i]) return false;
    }
    return true;
}

// 2.9
template<typename T>
bool arrayList02<T>::operator!=(const arrayList02<T> &op) const
{
    if (this->size != op.size()) return true;
    for (auto i = 0; i != op.size; i++)
    {
        if (this[i] != op[i]) return true;
    }
    return false;
}

// 2.10
template<typename T>
bool arrayList02<T>::operator<(const arrayList02<T> &op) const
{
    int temp = (this->size() > op.size()) ? op.size() : this->size();
    for (auto iter = 0; iter != temp; iter++)
    {
        if (this[iter] >= op[iter]) return false;
    }
    return this->size() <= op.size();
}

// 2.11
template<typename T>
void arrayList02<T>::push_back(const T &x)
{
    if (this->Size == this->Capacity) this->set_size(this->Size + 1);
    this->Container[this->Size] = x;
    this->Size += 1;
}

// 2.12
template<typename T>
void arrayList02<T>::pop_back()
{
    if (this->empty()) throw;
    this->Container[this->size() - 1] = T();
    this->Size -= 1;
}

// 2.13
template<typename T>
void arrayList02<T>::swap(ArrayList<T> &x)
{
    ArrayList<T> &temp = x;
    *x = *this;
    *this = *temp;
}

// 2.14
template<typename T>
void arrayList02<T>::reserve(int const &capacity)
{
    if (capacity > this->cap()) this->set_size(capacity);
}

// 2.15
template<typename T>
T arrayList02<T>::set(int const &x, T elem)
{
    this->_index_check(x);
    T temp = this->Container[x];
    this->Container[x] = elem;
    return temp;
}

// 2.16
template<typename T>
void arrayList02<T>::clear()
{
    for (auto iter = 0; iter != this->Size; iter++) this->Container[iter].~T();
    this->Size = 0;
}

// 2.17
template<typename T>
void arrayList02<T>::remove_range(int const &start, int const &end)
{
    if (end < start) throw;
    this->_index_check(start);
    this->_index_check(end);
    std::move(this->Container + end, this->Container + this->size(), this->Container + start);
    for (auto iter = this->size() - end + start; iter != this->size(); iter++)
        this->Container[iter].~T();
    this->Size -= (end - start);
}

// 2.18
template<typename T>
int arrayList02<T>::last_index_of(const T &x)
{
    int temp_index = -1;
    for (auto iter = 0; iter != this->size(); iter++)
    {
        if (this->Container[iter] == x) temp_index = iter;
    }
    return temp_index;
}

// 2.19
// pass

// 2.20
// 1)
template<typename T>
void arrayList02<T>::erase_new(int const &index, int const &capacity)
{
    this->erase(index);
    if (this->size() <= this->cap() / 4)
        this->cap() / 2 > capacity ? this->reverse(std::floor(this->cap() / 2))
                                   : this->reverse(capacity);
}

// 2) pass

// 2.21
// pass

// 2.22
template<typename T>
void arrayList02<T>::reverse()
{
    int temp_tick = std::floor(this->size() / 2);
    T temp;
    for (int iter = 0; iter != temp_tick; iter++)
    {
        temp = this->Container[iter];
        this->Container[iter] = this->Container[this->size() - iter - 1];
        this->Container[this->size() - iter - 1] = temp;
    }
}

// 2.23
template<typename T>
void arrayList02<T>::left_shift(const int &x)
{
    this->remove_range(0, x);
}

// 2.24
template<typename T>
void arrayList02<T>::clockwise(int const &x)
{
    int temp;
    this->reserve();
    int temp_tick1 = std::floor(x / 2), temp_tick2 = std::floor(this->size() - x / 2);

    for (int iter = 0; iter != temp_tick1; iter++)
    {
        temp = this->Container[iter];
        this->Container[iter] = this->Container[this->size() - iter - 1];
        this->Container[this->size() - iter - 1] = temp;
    }

    for (int iter = x; iter != x + temp_tick2; iter++)
    {
        temp = this->Container[iter];
        this->Container[iter] = this->Container[this->size() - iter - 1];
        this->Container[this->size() - iter - 1] = temp;
    }
}

// 2.25
template<typename T>
void arrayList02<T>::half() {
    T temp[this->cap()];
    for (auto iter = 0; iter != this->size(); iter += 2)
    {
        temp[iter / 2] = this->Container[iter];
    }
    this->Container = temp;
    this->Size = std::floor(this->size() / 2 + 1);
}

// 2.26
// pass

// 2.27
// pass

// 2.28
template<typename T>
arrayList02<T> arrayList02<T>::meld(const arrayList02<T> &x)
{
    int temp = this->size() > x.size() ? x.size() : this->size();
    T container[x.cap() + this->cap()];
    for (auto iter = 0; iter != temp; iter++)
    {
        container[2 * iter] = this->Container[iter];
        container[2 * iter - 1] = x.Container[iter];
    }

    if (this->size() > x.xize())
    {
        for (auto iter = temp; iter != this->size(); iter++) container[iter + temp] = this->Container[iter];
    } else {
        for (auto iter = temp; iter != x.size(); iter++) container[iter + temp] = x.Container[iter];
    }

    auto result = arrayList02(x.cap() + this->cap());
    result.Size = x.size() + this->size();
    result.Container = container;
    return result;
}

// 2.29
template<typename T>
arrayList02<T> arrayList02<T>::merge(const arrayList02<T> &x) {
    T container[x.cap() + this->cap()];
    for (auto iter = 0; iter != this->size(); iter++) container[iter] = this->Container[iter];
    for (auto iter = 0; iter != x.size(); iter++) container[iter + this->size()] = x.Container[iter];

    auto result = arrayList02(x.cap() + this->cap());
    result.Size = x.size() + this->size();
    result.Container = container;
    return result;
}

//2.30
template<typename T>
void arrayList02<T>::split(T *&a, T *&b) {
    for (auto iter = 0; iter != this->size(); iter++)
    {
        if (iter % 2 == 0) a[iter / 2] = this->Container[iter];
        else b[(iter - 1) / 2] = this->Container[iter];
    }
}

// 2.31
// Details in header file

#endif //DATASTRUCTURE_SECTION2_LINEAR_ARRAY_HPP
