#ifndef DATASTRUCTURE_LEFTIST_TREE_HPP
#define DATASTRUCTURE_LEFTIST_TREE_HPP

#include <utility.hpp>
#include <iterator.hpp>

template<class cls>
class Leftist_Tree
{
public:
    struct Leftist_Node
    {
        explicit Leftist_Node(cls const &);

        Leftist_Node *Father, *Right, *Left;

        size_t Depth;
        cls Value;
    };

    explicit Leftist_Tree();

    template<class ...Args>
    void emplace(Args ...);
    void push(cls const &);
    void push(cls &&);

    [[nodiscard]] bool empty() const;
    void merge(Leftist_Tree<cls> &);
    cls top() const;
    void pop();

private:
    Leftist_Node &merge_algorithm(Leftist_Node & , Leftist_Node &);

protected:
    Leftist_Node *Top;
};

template<class cls>
Leftist_Tree<cls>::Leftist_Node::Leftist_Node(const cls &value)
        :Value{value}, Father{nullptr}, Left{nullptr}, Right{nullptr}, Depth{1} {}

template<class cls>
Leftist_Tree<cls>::Leftist_Tree(): Top{nullptr} {}


template<class cls>
template<class ...Args>
void Leftist_Tree<cls>::emplace(Args... args)
{
    if (Top == nullptr) {
        Top = new Leftist_Node {args...};
        return;
    }
    merge_algorithm(*Top, *new Leftist_Node{args...});
}

template<class cls>
void Leftist_Tree<cls>::merge(Leftist_Tree<cls> &op_tree)
{
    if (Top == nullptr) {
        Top = op_tree.Top;
        op_tree.Top = nullptr;
        return;
    }
    if (op_tree.Top == nullptr) return;
    Top = &Leftist_Tree::merge_algorithm(*Top, *op_tree.Top);
}

template<class cls>
bool Leftist_Tree<cls>::empty() const
{
    return Top == nullptr;
}

template<class cls>
cls Leftist_Tree<cls>::top() const
{
    if (Top == nullptr) return cls{};
    return Top->Value;
}

template<class cls>
void Leftist_Tree<cls>::pop()
{
    if(Top->Left==nullptr && Top->Right== nullptr)
    {
        Top = nullptr;
    } else if (Top->Right == nullptr)
    {
        Top->Left->Father = nullptr;
        Top = Top->Left;
    } else {
        Top->Left->Father = nullptr;
        Top = &merge_algorithm(*Top->Left, *Top->Right);
    }
}

template<class cls>
typename Leftist_Tree<cls>::Leftist_Node
&Leftist_Tree<cls>::merge_algorithm
(Leftist_Tree::Leftist_Node &node_a, Leftist_Node &node_b)
{
    if(node_a.Value < node_b.Value) {
        Leftist_Node *_temp_father_ptr = node_a.Father;
        if (node_a.Father != nullptr && node_a.Father->Left == &node_a)
        {
            node_a.Father->Left == &node_b;
        } else if (node_a.Father != nullptr && node_a.Father->Right == &node_a)
        {
            node_a.Father->Right = &node_b;
        }
        if (node_b.Father != nullptr && node_b.Father->Left == &node_b)
        {
            node_b.Father->Left = &node_a;
        } else if (node_b.Father != nullptr && node_b.Father->Right == &node_b)
        {
            node_b.Father->Right = &node_a;
        }
        node_a.Father = node_b.Father;
        node_b.Father = _temp_father_ptr;
        if(Top == &node_a) this->Top = &node_b;
        else if(Top == &node_b) this->Top = &node_a;
        return merge_algorithm(node_b, node_a);
    }

    if (node_a.Left == nullptr)
    {
        node_a.Left = &node_b;
        node_b.Father = &node_a;

        for(Leftist_Node *_node = &node_a; _node != nullptr; _node = _node->Father)
        {
            _node->Depth = ax::max(_node->Left==nullptr? 0: _node->Left->Depth,
                                    _node->Right==nullptr? 0 : _node->Right->Depth) + 1;
        }
        return node_a;
    } else if (node_a.Right == nullptr) {
        node_a.Right = &node_b;
        node_b.Father = &node_a;
        for(Leftist_Node *_node = &node_a; _node != nullptr; _node = _node->Father)
        {
            _node->Depth = ax::max(_node->Left==nullptr? 0: _node->Left->Depth,
                                    _node->Right==nullptr? 0 : _node->Right->Depth) + 1;
        }
    } else {
        node_a.Right = &merge_algorithm(*node_a.Right, node_b);
    }

    if (node_a.Left->Depth < node_a.Right->Depth)
    {
        Leftist_Node *_temp_side = node_a.Right;
        node_a.Right = node_a.Left;
        node_a.Left = _temp_side;
    }
    return node_a;
}

template<class cls>
void Leftist_Tree<cls>::push(cls &&rhv)
{
    if (Top == nullptr) {
        Top = new Leftist_Node {ax::move(rhv)};
        return;
    }
    merge_algorithm(*Top, *new Leftist_Node{ax::move(rhv)});
}

template<class cls>
void Leftist_Tree<cls>::push(cls const &lhv)
{
    if (Top == nullptr) {
        Top = new Leftist_Node {lhv};
        return;
    }
    merge_algorithm(*Top, *new Leftist_Node{lhv});
}

template<class cls>
Leftist_Tree<cls> make_leftist_tree()
{
    return Leftist_Tree<cls>{};
}

template<ax::forward_iterator Iter>
decltype(auto) make_leftist_tree(Iter begin, Iter end)
{
    Leftist_Tree<decltype(remove_reference(*begin))> tree {};
    for(auto iter=begin;iter!=end;++iter)
    {
        tree.template emplace(*iter);
    }
    return tree;
}

#endif //DATASTRUCTURE_LEFTIST_TREE_HPP