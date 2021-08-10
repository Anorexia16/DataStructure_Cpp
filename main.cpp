#include "Structure/Dendroid/Dict_Trie_Tree.hpp"
#include "Generic_Paradigm/Concurrent.hpp"


int main() {
    Dict dict {};
    dict.import({"as_inf", "acos", "acot"});
    dict.import({"inf", "pow", "sin", "sqrt"});
    dict.emplace("atan");
    dict.emplace("asin");
    dict.emplace("as_one_num");
    dict.init();
    dict.input('a');
    dict.input('s');
    auto vec1 = dict.release();
    dict.init();
    dict.input('s');
    auto vec2 = dict.release();
    return 0;
}