#ifndef DATASTRUCTURE_WINNER_TREE_HPP
#define DATASTRUCTURE_WINNER_TREE_HPP

#include <Assistance/Storage_Unit.hpp>
#include "binary_tree.hpp"
#include <iterator.hpp>
#include <queue>
#include <map>

namespace ax {
    template<typename K_Tp, typename V_Tp>
    class Winner_Tree
    {
    public:
        typedef KW_Pair<V_Tp, K_Tp> player;
        typedef lite_binary_tree<player> p_node;

        template<forward_iterator iter>
        explicit Winner_aTree(iter, iter);

        V_Tp &operator[](K_Tp const &);
        void replay(K_Tp const &, V_Tp const &);

        [[nodiscard]] size_t wins_count(K_Tp const &) const;
        [[nodiscard]] K_Tp winner() const;

    protected:
        p_node &winner_merge(p_node &, p_node &);
        std::map<K_Tp, V_Tp> Players;
        p_node *Root;
    };
}

#endif //DATASTRUCTURE_WINNER_TREE_HPP
