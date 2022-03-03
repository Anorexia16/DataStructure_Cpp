#ifndef DATASTRUCTURE_ABSTRACT_HPP
#define DATASTRUCTURE_ABSTRACT_HPP

#ifndef ax_size
#define ax_size
typedef unsigned long long size_t;
typedef long long ssize_t;
#endif

namespace ax
{
    class Graph
    {
    public:
        [[nodiscard]] constexpr virtual size_t vertices() const = 0;

        [[nodiscard]] virtual size_t edges() const = 0;

        [[nodiscard]] virtual size_t degree(size_t const &) const = 0;

        [[nodiscard]] virtual size_t in_degree(size_t const &) const = 0;

        [[nodiscard]] virtual size_t out_degree(size_t const &) const = 0;

        [[nodiscard]] virtual bool exist_edge(size_t const &, size_t const &) const = 0;

        [[nodiscard]] virtual constexpr bool directed() const = 0;

        [[nodiscard]] virtual constexpr bool weighted() const = 0;

        virtual void insert_edge(size_t const &, size_t const &, size_t const &) = 0;

        virtual void remove_edge(size_t const &, size_t const &) = 0;
    };

    template<typename T>
    class linear_list
    {
    public:
        virtual ~linear_list() = default;

        [[nodiscard]] virtual bool empty() const = 0;

        [[nodiscard]] virtual size_t size() const = 0;

        virtual size_t find(T const &) const = 0;

        virtual void erase(size_t const &) = 0;

        virtual void insert(size_t const &, T const &) = 0;

        virtual T &operator[](size_t const &) = 0;
    };

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
}

#endif //DATASTRUCTURE_ABSTRACT_HPP
