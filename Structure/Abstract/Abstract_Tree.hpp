#ifndef DATASTRUCTURE_ABSTRACT_TREE_HPP
#define DATASTRUCTURE_ABSTRACT_TREE_HPP

#include <cstddef>

enum class Tree_Iterator_Methods {Scope, Inner, Post, Prev};

template<typename Tp, template<typename> class Node>
class Tree
{
public:
    virtual Node<Tp> &top() = 0;

    virtual Node<Tp> &top_c() const = 0;

    [[nodiscard]] virtual size_t degree() const = 0;

    [[nodiscard]] virtual size_t depth() const = 0;

    [[nodiscard]] virtual size_t weight() const = 0;

    [[nodiscard]] virtual bool empty() const = 0;

    [[nodiscard]] virtual bool complete() const = 0;

    virtual Node<Tp> &find(Tp const &) = 0;

    virtual Node<Tp> &get(size_t const &) = 0;
};

template<typename Tp, template<typename> class Node, template<class cls> class Cont>
class Forest
{
public:
    virtual Node<Tp> &find(Tp const &) = 0;

    virtual Node<Tp> &get(size_t const &) = 0;

protected:
    Cont<Tree<Tp, Node> *> Container{};
};

#endif //DATASTRUCTURE_ABSTRACT_TREE_HPP
