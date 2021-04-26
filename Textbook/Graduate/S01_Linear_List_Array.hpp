#ifndef DATASTRUCTURE_LINEAR_LIST_H
#define DATASTRUCTURE_LINEAR_LIST_H

#include <cmath>
#include <iterator>
#include "../../Structure/Abstract/Abstract_Linear_List.hpp"

template<typename T>
class arrayList_Ti : LinearList<T>
{
public:
    explicit arrayList_Ti(int const &x)
            : Container{new T[x]}, Capacity{x}, Size{0} {};

    arrayList_Ti(arrayList_Ti<T> &copy)
            : Container{copy.Container}, Capacity{copy.Capacity}, Size{copy.Size} {};

    ~arrayList_Ti() {
        for (auto &&iter: this->Container) iter.~T();
        delete (this->Container);
    }

    // 1 - 13
    T &min_pop();

    void reverse();

    void delete_all(T const &);

    void delete_sorted_range(T const &, T const &);

    void delete_range(T const &, T const &);

    void unique();

    arrayList_Ti<T> merge(arrayList_Ti<T> const &);

    void change(int const &);

    void search_sorted(T const &);

    void circle_move(int const &);

    T &mid_pos(arrayList_Ti<T> const &, arrayList_Ti<T> const &);

    T &main_elem();

    int min_elem();

protected:
    T *Container;
    int Capacity;
    int Size;
};

// 1
template<typename T>
T &arrayList_Ti<T>::min_pop()
{
    if (this->Size == 0) throw;
    int index = 0;
    T element = this->Container[0];
    for (auto iter = 0; iter != this->Size; iter++)
    {
        if (this->Container[iter] < element) index = iter;
        element = this->Container[index];
    }
    if (this->Size > 0) this->Container[index] = this->Container[this->Size - 1];
    this->Container[this->Size - 1].~T();
    this->Size -= 1;
    return element;
}

// 2
template<typename T>
void arrayList_Ti<T>::reverse()
{
    T temp{};
    for (auto iter = 0; iter != this->Size / 2; iter++)
    {
        temp = this->Container[iter];
        this->Container[iter] = this->Container[this->Size - 1 - iter];
        this->Container[this->Size - 1 - iter] = temp;
    }
    temp.~T();
}

// 3
template<typename T>
void arrayList_Ti<T>::delete_all(const T &element)
{
    int times = 0;
    for (auto iter = 0; iter != this->Size; iter++)
    {
        if (this->Container[iter] == element) times++;
        else this->Container[iter - times] = this->Container[iter];
    }
    for (auto iter = this->Size - times; iter != this->Size; iter++)
        this->Container[iter].~T();
    this->Size -= times;
}

// 4
template<typename T>
void arrayList_Ti<T>::delete_sorted_range(const T &s, const T &t)
{
    if (this->Size == 0 || s > t) throw;
    int end = 0;
    for (; end != this->Size && this->Container[end] > s; end++);
    int start = end;
    for (; end != this->Size && this->Container[end] > t; end++);
    for (; end < this->Size; end++, start++)
        this->Container[start] = this->Container[end];
    for (auto iter = end; iter != this->Size; iter++)
        this->Container.~T();
    this->Size -= end - start;
}

// 5
template<typename T>
void arrayList_Ti<T>::delete_range(const T &s, const T &t)
{
    int times = 0;
    for (auto iter = 0; iter != this->Size; iter++)
    {
        if (s <= this->Container[iter] && this->Container[iter] <= t) times++;
        else this->Container[iter - times] = this->Container[iter];
    }
    for (auto iter = this->Size - times; iter != this->Size; iter++)
        this->Container[iter].~T();
    this->Size -= times;
}

// 6
template<typename T>
void arrayList_Ti<T>::unique()
{
    int times = 0;
    T element{};
    for (auto iter = 0; iter != this->Size; iter++)
    {
        if (element == this->Container[iter]) times++;
        else {
            this->Container[iter - times] = this->Container[iter];
            element = this->Container[iter];
        }
    }
    for (auto iter = this->Size - times; iter != this->Size; iter++)
        this->Container[iter].~T();
    this->Size -= times;
}

// 7
template<typename T>
arrayList_Ti<T> arrayList_Ti<T>::merge(const arrayList_Ti<T> &x)
{
    arrayList_Ti<T> temp(this->Capacity + x.Capacity);
    temp.Size = this->Size + x.Size;
    int iter1 = 0, iter2 = 0;
    while (iter1 != this->Capacity && iter2 != x.Capacity)
    {
        if (this->Container[iter1] <= x.Container[iter2])
        {
            temp.Container[iter1 + iter2] = this->Capacity[iter1];
            iter1++;
        } else {
            temp.Container[iter1 + iter2] = x.Capacity[iter2];
            iter2++;
        }
    }
    for (; iter1 != this->Capacity; iter1++) temp.Container[iter1 + iter2] = this->Capacity[iter1];
    for (; iter2 != x.Capacity; iter2++) temp.Container[iter1 + iter2] = x.Capacity[iter2];
    return temp;
}

// 8
template<typename T>
void arrayList_Ti<T>::change(int const &index)
{
    T temp{};
    int index2 = this->Size - index;
    for (int iter = 0; iter != this->Size / 2; iter++)
    {
        temp = this->Container[iter];
        this->Container[iter] = this->Container[this->Size - 1 - iter];
        this->Container[this->Size - 1 - iter] = temp;
    }
    for (int iter = 0; iter != index2 / 2; iter++)
    {
        temp = this->Container[iter];
        this->Container[iter] = this->Container[this->Size - 1 - iter];
        this->Container[this->Size - 1 - iter] = temp;
    }
    for (int iter = index2; iter != (this->Size + index2) / 2; iter++)
    {
        temp = this->Container[iter];
        this->Container[iter] = this->Container[this->Size - 1 - iter];
        this->Container[this->Size - 1 - iter] = temp;
    }
}

// 9
template<typename T>
void arrayList_Ti<T>::search_sorted(const T &x)
{
    if (this->Capacity - this->Size < 1) throw;
    int start = 0, end = this->Size - 1;
    T temp;
    while (start != end)
    {
        if (this->Container[(start + end + 1) / 2] == x)
        {
            temp = this->Container[(start + end + 1) / 2];
            this->Container[(start + end + 1) / 2] = this->Container[(start + end + 1) / 2 + 1];
            this->Container[(start + end + 1) / 2 + 1] = temp;
            return;
        } else if (this->Container[(start + end + 1) / 2] < x) start = (start + end + 1) / 2;
        else end = (start + end + 1) / 2;
    }
    for (auto iter = start; iter != this->Size; iter++)
        this->Container[iter + 1] = this->Container[iter];
    this->Container[start] = x;
    temp.~T();
}

// 10
template<typename T>
void arrayList_Ti<T>::circle_move(int const &bits)
{
    T temp;
    for (auto iter = 0; iter != bits / 2; iter++)
    {
        temp = this->Container[iter];
        this->Container[iter] = this->Container[bits - 1 - iter];
        this->Container[bits - 1 - iter] = temp;
    }
    for (auto iter = bits; iter != (this->Size + bits) / 2; iter++)
    {
        temp = this->Container[iter];
        this->Container[iter] = this->Container[this->Size - 1 - iter];
        this->Container[this->Size - 1 - iter] = temp;
    }
    for (auto iter = 0; iter != this->Size; iter++)
    {
        temp = this->Container[iter];
        this->Container[iter] = this->Container[this->Size - 1 - iter];
        this->Container[this->Size - 1 - iter] = temp;
    }
    temp.~T();
}

// 11
template<typename T>
T &arrayList_Ti<T>::mid_pos(arrayList_Ti<T> const &arr1, arrayList_Ti<T> const &arr2)
{
    int begin1 = 0, end1 = arr1.Size, begin2 = 0, end2 = arr2.Size;
    while (true)
    {
        if (arr1.Container[std::ceil((begin1 + end1) / 2)] < arr2.Container[std::ceil((begin2 + end2) / 2)])
        {
            begin1 = (begin1 + end1) / 2;
            end2 = (begin2 + end2) / 2;
        } else if (arr1.Container[std::ceil((begin1 + end1) / 2)] == arr2.Container[std::ceil((begin2 + end2) / 2)]) {
            return arr1.Container[std::ceil((begin1 + end1) / 2)];
        } else {
            end1 = (begin1 + end1) / 2;
            begin2 = (begin2 + end2) / 2;
        }
        if (end2 - begin2 == 1)
            return arr1.Container[std::ceil((begin1 + end1) / 2)] > arr2.Container[std::ceil((begin1 + end1) / 2)] ?
                   arr1.Container[std::ceil((begin1 + end1) / 2)] : arr2.Container[std::ceil((begin1 + end1) / 2)];
    }
}

// 12
template<typename T>
T &arrayList_Ti<T>::main_elem()
{
    int counter = 0;
    T elem;
    for (auto &&iter: this->Container)
    {
        if (counter == 0)
        {
            elem = iter;
            counter++;
        } else {
            elem == iter ? counter++ : counter--;
        }
    }
    counter = 0;
    for (auto &&iter : this->Container)
    {
        if (elem == iter) counter++;
    }
    return counter > this->Size / 2 ? elem : T();
}

// 13
template<typename T>
int arrayList_Ti<T>::min_elem()
{
    int stack[this->Size];
    for (int iter = 0; iter != this->Size; iter++) stack[iter] = 0;
    for (auto &&iter: this->Container)
    {
        if (iter > 0 && iter <= this->Size) stack[iter - 1] = 1;
    }
    for (int iter = 0; iter != this->Size; iter++) if (stack[iter] == 0) return iter + 1;
}

#endif //DATASTRUCTURE_LINEAR_LIST_H