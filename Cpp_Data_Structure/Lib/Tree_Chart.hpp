#ifndef DATASTRUCTURE_TREE_CHART_HPP
#define DATASTRUCTURE_TREE_CHART_HPP

#include <iostream>
#include <iterator>

template<class Tree>
class Tree_Print: public Tree
{
public:
    Tree_Print(std::ostream &, Tree const &);

    std::ostream &operator<<(std::ostream &);
};

template<class Tree>
Tree_Print<Tree>::Tree_Print(std::ostream &out, const Tree &tree) {
    out << tree;
}

template<class Tree>
std::ostream &Tree_Print<Tree>::operator<<(std::ostream &out) {
    return out;
}


#endif //DATASTRUCTURE_TREE_CHART_HPP
