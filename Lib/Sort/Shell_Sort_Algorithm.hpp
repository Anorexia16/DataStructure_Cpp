#ifndef DATASTRUCTURE_SHELL_SORT_ALGORITHM_HPP
#define DATASTRUCTURE_SHELL_SORT_ALGORITHM_HPP

#include <Iterations.hpp>

template<typename Tp, Iterable_Container Container>
void shell_sort(Container &container)
{
    if (container.size() == 0) return;
    size_t const nums = container.size();
    Tp _extra {};

    for (size_t gaps=nums/2; gaps>0; gaps/=2)
    {
        
    }
}

#endif //DATASTRUCTURE_SHELL_SORT_ALGORITHM_HPP
