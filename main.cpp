#include "Structure/B_Tree.hpp"
#include "Structure/B_Plus_Tree.hpp"


int main() {
    B_Tree<int, int, 5> _tree {};
    _tree.insert(3, 3);
    _tree.insert(8, 8);
    _tree.insert(31, -7);
    _tree.insert(11, 11);
    _tree.insert(23, 23);
    _tree.insert(29, 29);
    _tree.insert(50, 23);
    _tree.insert(28, 29);
    _tree.insert(50, 50);
    _tree.insert(53, 53);
    _tree.erase(29);
    _tree.erase(28);
    _tree.erase(31);

    B_Plus_Tree<int, int, 5> _tree2{};
    _tree2.insert(1, 3);
    _tree2.insert(3, 2);
    _tree2.insert(4, 3);
    _tree2.insert(2, 7);
    _tree2.insert(5,0);
    _tree2.insert(9, -1);
    auto t = (B_Plus_Tree<int, int, 5>::Index_Node*)_tree2.Root;
    for (size_t i = 11; i!=25; ++i)
    {
        _tree2.insert(i, i+6);
    }
    t = (B_Plus_Tree<int, int, 5>::Index_Node*)_tree2.Root;
    for (int q = -11; q!= -27; --q)
    {
        _tree2.insert(q, q -3);
    }

    t = (B_Plus_Tree<int, int, 5>::Index_Node*)_tree2.Root;
    auto se = _tree2.search(-21);
    auto S = ((B_Plus_Tree<int, int, 5>::Data_Node*)((B_Plus_Tree<int, int, 5>::Index_Node*)t->Paths[0])->Paths[0]);
    auto end = "Debug Hook";
}