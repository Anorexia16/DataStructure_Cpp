#ifndef DATASTRUCTURE_MERGE_SORT_ALGORITHM_HPP
#define DATASTRUCTURE_MERGE_SORT_ALGORITHM_HPP

#include <vector>

template<class cls>
concept Iterable_Container = requires (cls instance)
{
    instance.operator[](0);
    instance.size();
};

template<class cls>
concept Iterable_Iterator = requires (cls iterator)
{
    cls(iterator);
    iterator.operator=(iterator);
    iterator.operator-(-1);
    ++iterator;
    --iterator;
};

template<typename Tp, Iterable_Container Container>
void merge_sort(Container &container)
{
    if (container.size() == 0) return;
    std::vector<Tp> extra {};
    size_t index {}, li{}, ri{};
    size_t const nums {container.size()};
    extra.resize(nums);

    for(size_t length =1;length<=nums;length*=2) {
        for(size_t i=0;i<(nums-1)/length+1;i+=2) {
            while(li!=length&&(ri!=length||ri+length*i!=nums)) {
                if (container[i+li]<=container[i+ri+length]) {
                    extra[index++] = container[i*length+li++];
                } else {
                    extra[index++] = container[i*length+ri++];
                }
            }
            while(li!=length) extra[index++] = container[i*length+li++];
            while(ri!=length||ri+length*i!=nums)
                extra[index++] = container[i*length+ri++];
            for (size_t j=0;j!=li+ri;++j) {
                container[i*length+j] = extra[j];
            }
            index = 0;
            li = 0;
            ri = 0;
        }
    }
}

template<typename Tp, Iterable_Iterator iterator>
void merge_sort(iterator begin, iterator end)
{
    if (begin == end) return;
    std::vector<Tp> extra {};
    size_t index {}, li{}, ri{};
    size_t const nums {end-begin};
    extra.resize(nums);

    for(size_t length =1;length<=nums;length*=2) {
        for(size_t i=0;i<(nums-1)/length+1;i+=2) {
            while(li!=length&&(ri!=length||ri+length*i!=nums)) {
                if (*(begin+i*length+li)<=*(begin+ri+i*length)) {
                    extra[index++] = *(begin+i*length+li++);
                } else {
                    extra[index++] = *(begin+i*length+ri++);
                }
            }
            while(li!=length) extra[index++] = *(begin+i*length+li++);
            while(ri!=length||ri+length*i!=nums)
                extra[index++] = *(begin+i*length+ri++);
            for (size_t j=0;j!=li+ri;++j) {
                *(begin+i*length+j) = extra[j];
            }
            index=0;
            li=0;
            ri=0;
        }
    }
}

#endif //DATASTRUCTURE_MERGE_SORT_ALGORITHM_HPP
