#ifndef DATASTRUCTURE_REFERENCE_MAP_HPP
#define DATASTRUCTURE_REFERENCE_MAP_HPP

struct Reference_Map
{
    explicit Reference_Map(unsigned long long = 600);

    template<class cls, typename type>
    type &operator[](cls &);

    size_t const Capacity;

    void **Container;
};

Reference_Map::Reference_Map(unsigned long long int capacity)
:Container{new void* [capacity]}, Capacity{capacity} {for(size_t i=0;i !=Capacity;++i) Container[i]= nullptr;}

template<class cls, typename type>
type &Reference_Map::operator[](cls &key) {
    void* ptr = static_cast<void *>(&key);
    char ptr_str[8];
    sprintf(ptr_str, "%x", ptr);
    unsigned long long hash = 0x0;
    for (unsigned short i=0; ptr_str[i]!='\000' ;++i)
    {
        hash *= 16;
        hash += ptr_str[i]-'0'>9? ptr_str[i]-'0'-39 : ptr_str[i]-'0';
    }
    unsigned int hash_in1 = hash%100;
    hash/=100;
    unsigned int hash_in2 = hash%53;
    unsigned int hash_in3 = hash%31;
    unsigned int hash_in4 = hash%79;
    unsigned long HV = hash_in1 + hash_in2 * 2 + hash_in3 * 3 + hash_in4 * 4;
    HV %= Capacity;
    for (;Container[HV]!= nullptr;++HV) {
        try {

        } catch (...) {
            continue;
        }
        if (HV==Capacity) HV=0;
    }
    Container[HV] = static_cast<void*>(new type {});
    return *static_cast<type*>(Container[HV]);
}

#endif //DATASTRUCTURE_REFERENCE_MAP_HPP
