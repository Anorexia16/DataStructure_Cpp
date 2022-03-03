#ifndef DATASTRUCTURE_ADJACENT_LIST_HPP
#define DATASTRUCTURE_ADJACENT_LIST_HPP

#include <iostream>
#include <Linear/Stack_Chain.hpp>
#include <Linear/Queue_Chain.hpp>
#include <Abstract/Abstract_Graph.hpp>
#include <Assistance/Node_Unidirectional.hpp>


struct Gn
{
    size_t Weight{1};

    ssize_t At{-1};

    Gn *Bro {nullptr};
};

template<size_t num, bool bidirectional = true, bool is_weighted = false>
struct Adjacent_List: public Graph
{
    Adjacent_List();

    [[nodiscard]] constexpr size_t vertices() const override;

    [[nodiscard]] size_t edges() const override;

    [[nodiscard]] size_t degree(size_t const &) const override;

    [[nodiscard]] size_t in_degree(size_t const &) const override;

    [[nodiscard]] size_t out_degree(size_t const &) const override;

    [[nodiscard]] bool exist_edge(size_t const &, size_t const &) const override;

    [[nodiscard]] constexpr bool directed() const override;

    [[nodiscard]] constexpr bool weighted() const override;

    void insert_edge(size_t const &, size_t const &, size_t const &) override;

    void remove_edge(size_t const &, size_t const &) override;

    std::ostream &DFS(std::ostream &, size_t const &);

    std::ostream &BFS(std::ostream &, size_t const &);

    Gn Container[num];
};

template<size_t num, bool bidirectional, bool is_weighted>
Adjacent_List<num, bidirectional, is_weighted>::Adjacent_List()
:Container{} {}

template<size_t num, bool bidirectional, bool is_weighted>
constexpr size_t Adjacent_List<num, bidirectional, is_weighted>::vertices() const
{
    return num;
}

template<size_t num, bool bidirectional, bool is_weighted>
size_t Adjacent_List<num, bidirectional, is_weighted>::edges() const
{
    size_t n = 0;
    for(size_t i=0; i!=num; ++i)
    {
       for(Gn *iter = Container[i].Bro; iter != nullptr; iter=iter->Bro) ++n;
    }
    return n;
}

template<size_t num, bool bidirectional, bool is_weighted>
size_t Adjacent_List<num, bidirectional, is_weighted>::degree(const size_t &i) const
{
    size_t n = 0;
    for(Gn *iter = Container[i].Bro; iter->Bro != nullptr; iter=iter->Bro) ++n;
    if (!bidirectional)
    {
        for (int j = 0; j != num; ++j)
        {
            for (Gn *iter = Container[j].Bro; iter != nullptr; iter = iter->Bro)
                if (iter->At == i)
                {
                    ++n;
                    break;
                }
        }
    }
    return n;
}

template<size_t num, bool bidirectional, bool is_weighted>
size_t Adjacent_List<num, bidirectional, is_weighted>::in_degree(const size_t &i) const
{
    size_t n = 0;
    for(int j=0; j!=num; ++j)
    {
        for(Gn *iter = Container[j].Bro; iter != nullptr; iter=iter->Bro)
            if (iter->At ==i)
            {
                ++n;
                break;
            }
    }
    return n;
}

template<size_t num, bool bidirectional, bool is_weighted>
size_t Adjacent_List<num, bidirectional, is_weighted>::out_degree(const size_t &i) const
{
    size_t n = 0;
    for(Gn *iter = Container[i].Bro; iter != nullptr; iter=iter->Bro) ++n;
    return n;
}

template<size_t num, bool bidirectional, bool is_weighted>
bool Adjacent_List<num, bidirectional, is_weighted>::exist_edge(const size_t &i, const size_t &j) const
{
    for (Gn *iter = Container[i].Bro; iter != nullptr; iter = iter->Bro)
        if (iter->At == j)
            return true;
    return false;
}

template<size_t num, bool bidirectional, bool is_weighted>
constexpr bool Adjacent_List<num, bidirectional, is_weighted>::directed() const
{
    return !bidirectional;
}

template<size_t num, bool bidirectional, bool is_weighted>
constexpr bool Adjacent_List<num, bidirectional, is_weighted>::weighted() const
{
    return is_weighted;
}

template<size_t num, bool bidirectional, bool is_weighted>
void Adjacent_List<num, bidirectional, is_weighted>::insert_edge(const size_t &i, const size_t &j, const size_t &weight)
{
    Gn *_new = new Gn {};
    _new->At = static_cast<ssize_t>(j);
    _new->Weight = weight;
    _new->Bro = nullptr;
    Gn *pos = &this->Container[i];
    for (;pos->Bro!=nullptr;pos=pos->Bro);
    pos->Bro = _new;
    if (bidirectional)
    {
        Gn *_new2 = new Gn{};
        _new2->At = static_cast<ssize_t>(i);
        _new2->Weight = weight;
        _new2->Bro = nullptr;
        Gn *pos2 = &this->Container[j];
        for (;pos2->Bro!=nullptr;pos2=pos2->Bro);
        pos2->Bro = _new;
    }
}

template<size_t num, bool bidirectional, bool is_weighted>
void Adjacent_List<num, bidirectional, is_weighted>::remove_edge(const size_t &i, const size_t &j)
{
    for (Gn *iter = &Container[i]; iter->Bro != nullptr; iter = iter->Bro)
        if (iter->Bro->At == j)
        {
            iter->Bro = iter->Bro->Bro;
            break;
        }
    if (bidirectional)
    {
        for (Gn *iter = &Container[j]; iter->Bro != nullptr; iter = iter->Bro)
            if (iter->Bro->At == i)
            {
                iter->Bro = iter->Bro->Bro;
                break;
            }
    }
}

template<size_t num, bool bidirectional, bool is_weighted>
std::ostream &Adjacent_List<num, bidirectional, is_weighted>::DFS(std::ostream &out, size_t const &begin) {
    out << "depth first search on graph:" <<std::endl << begin << ' ';
    bool traversed[num];
    ssize_t _iter = static_cast<ssize_t>(begin)-1;

    traversed[begin] = true;
    Stack_C<Gn*> _stack {};
    Gn *pi = Container[_iter].Bro;

    if (pi!=nullptr)
    {
        if (pi->Bro!= nullptr) _stack.push(pi->Bro);
    }

    while(!_stack.empty())
    {
        if (pi->Bro != nullptr) _stack.push(pi->Bro);
        if (pi->At!=-1 && !traversed[pi->At])
        {
            _iter = pi->At;
            traversed[_iter] = true;
            std::cout << _iter << ' ';
            if (Container[_iter].Bro != nullptr)
            {
                pi = Container[_iter].Bro;
            } else {
                pi = _stack.top();
                _stack.pop();
            }
        } else {
            pi = _stack.top();
            _stack.pop();
        }
    }
    out << std::endl;
    return out;
}

template<size_t num, bool bidirectional, bool is_weighted>
std::ostream &Adjacent_List<num, bidirectional, is_weighted>::BFS(std::ostream &out, size_t const &begin) {
    out << "breadth first search on graph:" <<std::endl << begin << ' ';
    bool traversed[num];
    size_t _iter;

    traversed[begin] = true;
    Queue_C<size_t> _queue {};
    for(Gn *iter=Container[begin-1].Bro; iter != nullptr; iter=iter->Bro)
        _queue.enqueue(iter->At);

    while(!_queue.empty())
    {
        _iter = _queue.front();
        out << _iter << ' ';
        _queue.dequeue();
        for(Gn *iter=Container[_iter].Bro; iter != nullptr; iter=iter->Bro)
        {
            if (!traversed[iter->At])
            {
                traversed[iter->At] = true;
                _queue.enqueue(iter->At);
            }
        }
    }
    out << std::endl;
    return out;
}

#endif //DATASTRUCTURE_ADJACENT_LIST_HPP
