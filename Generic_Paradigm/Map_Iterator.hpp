#ifndef DATASTRUCTURE_MAP_ITERATOR_HPP
#define DATASTRUCTURE_MAP_ITERATOR_HPP

#include <vector>
#include <map>

template<typename K_Tp, typename V_Tp>
std::pair<std::vector<K_Tp>, std::vector<V_Tp>>
map_items (std::map<K_Tp, V_Tp> const &map)
{
    std::vector<K_Tp> K_Container {};
    std::vector<V_Tp> V_Container {};
    K_Container.reserve(map.size());
    V_Container.reserve(map.size());
    for (auto const &iter: map)
    {
        K_Container.template emplace_back(iter.first);
        V_Container.template emplace_back(iter.second);
    }
    return {K_Container, V_Container};
}

template<typename K_Tp, typename V_Tp>
std::vector<K_Tp>
map_keys (std::map<K_Tp, V_Tp> const &map)
{
    std::vector<K_Tp> K_Container {};
    K_Container.reserve(map.size());
    for (auto const &iter: map)
    {
        K_Container.template emplace_back(iter.first);
    }
    return K_Container;
}

template<typename K_Tp, typename V_Tp>
std::vector<V_Tp>
map_values (std::map<K_Tp, V_Tp> const &map)
{
    std::vector<V_Tp> V_Container {};
    V_Container.reserve(map.size());
    for (auto const &iter: map)
    {
        V_Container.template emplace_back(iter.second);
    }
    return V_Container;
}

template<typename I, typename II>
std::pair<II, I> pair_reverse(std::pair<I, II> const &pair) {
    return std::pair<II, I>{pair.second, pair.first};
}

#endif //DATASTRUCTURE_MAP_ITERATOR_HPP
