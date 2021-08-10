#ifndef DATASTRUCTURE_MAX_HEAP_HPP
#define DATASTRUCTURE_MAX_HEAP_HPP

#include <vector>

template<typename Tp>
class Heap
{
public:
    Heap();

    template<size_t n>
    explicit Heap(Tp (&)[n]);

    template<class Iterable_Container>
    explicit Heap
    (Iterable_Container const &);

    void pop_front();

    Tp front() const;

    void reverse(size_t);

    void push_back(Tp);

    template<class ...Args>
    void emplace_back(Args &&...);

    void heapify(size_t);

    std::vector<Tp> items() const;

    std::vector<Tp> ascend();

    static std::vector<Tp> heap_ascend(std::vector<Tp> &);

protected:
    unsigned long long Capacity;

    unsigned long long Size;

    Tp *Container;
};

template<typename Tp>
Heap<Tp>::Heap()
:Container{}, Capacity{128}, Size{} {
    Container = new Tp [Capacity];
}

template<typename Tp>
template<class Iterable_Container>
Heap<Tp>::Heap(const Iterable_Container &cont)
:Container{}, Capacity{2*cont.index()}, Size{cont.index()}
{
    Container = new Tp[2*cont.index()];
    for (unsigned long long i=0; i!=cont.index(); ++i)
    {
        *(this->Container+i) = cont[i];
    }
    for(size_t i= cont.index() / 2 - 1; i != -1; --i)
        heapify(i);
}

template<typename Tp>
template<size_t n>
Heap<Tp>::Heap(Tp (&array)[n])
:Container{}, Capacity{2*n}, Size{n}
{
    Container = new Tp[2*n];
    for (unsigned long long i=0; i!=n;++i)
    {
        *(this->Container+i) = *(array+i);
    }
    for(size_t i=n/2-1;i!=-1;--i)
        heapify(i);
}

template<typename Tp>
void Heap<Tp>::push_back
(Tp value)
{
    if (Size == Capacity)
    {
        Tp *_new_cont = new Tp [static_cast<unsigned long long>(1.5*Capacity)];
        for (unsigned long long i=0;i!=Size; ++i) _new_cont[i] = Container[i];
        Capacity = static_cast<unsigned long long>(1.5*Capacity);
        Container = _new_cont;
    }
    Container[Size++] = value;
    Tp _temp;
    for(size_t i=Size-1; i!=0;i=(i-1)/2) {
        if (Container[i]>Container[(i-1)/2])
        {
            _temp = Container[1];
            Container[i] = Container[(i-1)/2];
            Container[(i-1)/2] = _temp;
        }
    }
}


template<typename Tp>
template<class... Args>
void Heap<Tp>::emplace_back
(Args &&...args)
{
    this->push_back(Tp{args...});
}

template<typename Tp>
void Heap<Tp>::pop_front()
{
    --Size;
    Container[0] = Container[Size];
    heapify(0);
}

template<typename Tp>
Tp Heap<Tp>::front() const
{
    return Container[0];
}

template<typename Tp>
void Heap<Tp>::reverse(size_t num) {
    Tp *_cont = Container;
    Tp *ct = new Tp[num] {};
    for (size_t i=0;i!= num>Size?Size:num;++i) {
        ct[i] = Container[i];
    }
    Capacity = num;
    Size = num>Size?Size:num;
    Container = ct;
    delete [] _cont;
}

template<typename Tp>
void Heap<Tp>::heapify(size_t index) {
    size_t _i = index;
    Tp _temp;
    while(2*_i+1<Size)
    {
        if(Container[_i]>=Container[2*_i+1])
        {
            if(2*2+2<Size && Container[_i]<Container[2*_i+2])
            {
                _temp = Container[_i];
                Container[_i] = Container[2*_i+2];
                Container[2*_i+2] = _temp;
                _i = 2*_i+2;
                continue;
            } else return;
        } else {
            if(2*_i+2<Size && Container[2*_i+1]<Container[2*_i+2])
            {
                _temp = Container[_i];
                Container[_i] = Container[2*_i+2];
                Container[2*_i+2] = _temp;
                _i = 2*_i+2;
                continue;
            } else {
                _temp = Container[_i];
                Container[_i] = Container[2*_i+1];
                Container[2*_i+1] = _temp;
                _i = 2*_i+1;
                continue;
            }
        }
    }
}

template<typename Tp>
std::vector<Tp> Heap<Tp>::items() const {
    std::vector<Tp> _res {};
    _res.reserve(Size);
    for(size_t i=0; i!=Size;++i)
        _res.template emplace_back(Container[i]);
    return _res;
}

template<typename Tp>
std::vector<Tp> Heap<Tp>::ascend() {
    std::vector<Tp> _res {};
    _res.reserve(Size);
    for(;Size!=0;) {
        _res.template emplace_back(front());
        pop_front();
    }
    return _res;
}

template<typename Tp>
std::vector<Tp> Heap<Tp>::heap_ascend(std::vector<Tp> &vec) {
    std::vector<Tp> _res {};
    _res.reserve(vec.size());
    for(;!vec.empty();) {
        _res.template emplace_back(vec[0]);
        vec[0] = vec.back();
        vec.pop_back();
        size_t _i = 0;
        Tp _temp;
        while(2*_i+1<vec.size())
        {
            if(vec[_i]>=vec[2*_i+1])
            {
                if(2*2+2<vec.size() && vec[_i]<vec[2*_i+2])
                {
                    _temp = vec[_i];
                    vec[_i] = vec[2*_i+2];
                    vec[2*_i+2] = _temp;
                    _i = 2*_i+2;
                    continue;
                } else break;
            } else {
                if(2*_i+2<vec.size() && vec[2*_i+1]<vec[2*_i+2])
                {
                    _temp = vec[_i];
                    vec[_i] = vec[2*_i+2];
                    vec[2*_i+2] = _temp;
                    _i = 2*_i+2;
                    continue;
                } else {
                    _temp = vec[_i];
                    vec[_i] = vec[2*_i+1];
                    vec[2*_i+1] = _temp;
                    _i = 2*_i+1;
                    continue;
                }
            }
        }
    }
    return _res;
}

#endif //DATASTRUCTURE_MAX_HEAP_HPP
