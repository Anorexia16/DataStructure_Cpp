#ifndef DATASTRUCTURE_ARRAY_MATHEMATICS_HPP
#define DATASTRUCTURE_ARRAY_MATHEMATICS_HPP


template<typename Tp, unsigned long long size>
Tp *diff(Tp const (&array) [size])
{
    Tp _res[size-1] {};
    for(unsigned long long i=0; i!=size-1; ++i)
    {
        _res[i] = array[i+1] - array[i];
    }
    return _res;
}

template<typename Tp, unsigned long long size>
Tp *&prefix_sum(Tp const (&array) [size])
{
    auto _res= new Tp[size] {array[0]};
    for (unsigned long long i =1; i!=size; ++i)
    {
        _res[i] = _res[i-1] + array[i];
    }
    return _res;
}

#endif //DATASTRUCTURE_ARRAY_MATHEMATICS_HPP
