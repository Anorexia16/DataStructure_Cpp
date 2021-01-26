#ifndef DATASTRUCTURE_INSERT_SORT_HPP
#define DATASTRUCTURE_INSERT_SORT_HPP

template<typename Tp, bool reverse>
class Insert_Sorter {};

template<typename Tp>
class Insert_Sorter<Tp, true> {
public:
    template<class Container>
    explicit Insert_Sorter(Container &);

    Insert_Sorter &operator=(Insert_Sorter &&) noexcept = delete;

    Insert_Sorter &operator=(Insert_Sorter const &) = delete;

    Insert_Sorter(Insert_Sorter &&) noexcept = delete;

    Insert_Sorter(Insert_Sorter const &) = delete;

private:
    template<class Container>
    void operator()(Container &);
};

template<typename Tp>
template<typename Container>
Insert_Sorter<Tp, true>::Insert_Sorter(Container &container) {
    (*this)(container);
}

template<typename Tp>
template<typename Container>
void Insert_Sorter<Tp, true>::operator()(Container &container) {
    if (container.size()==0 || container.size()==1) return;
    auto zone = std::begin(container);
    auto iterator =  std::begin(container);
    Tp temp;
    bool flag;
    for(;zone!=std::end(container);) {
        temp = *(zone+1);
        iterator = std::begin(container);
        flag = false;
        for(;iterator!=std::end(container);++iterator) {
            if ((temp <= *iterator && temp >= *(iterator+1))||
            (iterator==std::begin(container) && (temp >= *iterator))) {
                std::inserter(temp, iterator);
                flag = true;
                break;
            }
        }
        if (!flag) {
            std::inserter(temp, zone++);
        }
        std::erase(++zone);
    }
}

template<typename Tp>
class Insert_Sorter<Tp, false> {
public:
    template<class Container>
    explicit Insert_Sorter(Container &);

    Insert_Sorter &operator=(Insert_Sorter &&) noexcept = delete;

    Insert_Sorter &operator=(Insert_Sorter const &) = delete;

    Insert_Sorter(Insert_Sorter &&) noexcept = delete;

    Insert_Sorter(Insert_Sorter const &) = delete;

private:
    template<class Container>
    void operator()(Container &);
};

template<typename Tp>
template<typename Container>
Insert_Sorter<Tp, false>::Insert_Sorter(Container &container) {
    (*this)(container);
}

template<typename Tp>
template<typename Container>
void Insert_Sorter<Tp, false>::operator()(Container &container) {
    if (container.size()==0 || container.size()==1) return;
    auto zone = std::begin(container);
    auto iterator =  std::begin(container);
    Tp temp;
    bool flag;
    for(;zone!=std::end(container);) {
        temp = *(zone+1);
        iterator = std::begin(container);
        flag = false;
        for(;iterator!=std::end(container);++iterator) {
            if ((temp <= *iterator && temp >= *(iterator+1))||
                (iterator==std::begin(container) && (temp >= *iterator))) {
                std::inserter(temp, iterator);
                flag = true;
                break;
            }
        }
        if (!flag) {
            std::inserter(temp, zone++);
        }
        std::erase(++zone);
    }
}

template<typename Tp, size_t n>
void Insert_Sort(std::array<Tp, n> &array, bool const &reverse = false) {
    if (reverse) {
        Insert_Sorter<Tp, true>{array};
    } else {
        Insert_Sorter<Tp, false>{array};
    }
}

template<typename Tp>
void Insert_Sort(std::initializer_list<Tp> &list, bool const &reverse = false) {
    if (reverse) {
        Insert_Sorter<Tp, true>{list};
    } else {
        Insert_Sorter<Tp, false>{list};
    }
}

template<typename Tp, template<typename elem, typename = std::allocator<elem>> class Cont>
void Insert_Sort(Cont<Tp> &cont, bool const &reverse = false) {
    if (reverse) {
        Insert_Sorter<Tp, true>{cont};
    } else {
        Insert_Sorter<Tp, false>{cont};
    }
}

template<typename Tp, typename Iterable_cls>
void Insert_Sort(Iterable_cls const &var, bool const &reverse = false) {
    if (reverse) {
        Insert_Sorter<Tp, true>{var};
    } else {
        Insert_Sorter<Tp, false>{var};
    }
}

#endif //DATASTRUCTURE_INSERT_SORT_HPP
