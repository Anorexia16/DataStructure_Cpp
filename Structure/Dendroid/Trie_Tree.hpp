#ifndef DATASTRUCTURE_TRIE_TREE_HPP
#define DATASTRUCTURE_TRIE_TREE_HPP

#include <string>

struct Trie_Node
{
    explicit Trie_Node();

    size_t Count;

    size_t Prefix;

    Trie_Node *Children[26];
};

class Trie_Tree
{
public:
    Trie_Tree();

    void insert(std::string const &);

    [[nodiscard]] size_t search(std::string const &) const;

    [[nodiscard]] size_t search_prefix(std::string const &) const;

protected:
    Trie_Node *Root;
};

Trie_Node::Trie_Node
():
Count{0}, Prefix{0}, Children{}
{}

Trie_Tree::Trie_Tree():
Root{new Trie_Node{}}
{}

void Trie_Tree::insert(const std::string &str)
{
    Trie_Node *iterator = this->Root;
    size_t length=str.size();
    for(size_t si=0; si!=length; ++si)
    {
        if(iterator->Children[str[si]-'a'] == nullptr){
            iterator->Children[str[si]-'a'] = new Trie_Node {};
        }
        iterator = iterator->Children[str[si]-'a'];
        ++iterator->Prefix;
    }
    ++iterator->Count;
}

size_t Trie_Tree::search(const std::string &str) const
{
    Trie_Node *iterator = this->Root;
    for(size_t si=0;si!=str.size();++si)
    {
        if (iterator->Children[str[si]-'a'] == nullptr)
        {
            return 0;
        }
        iterator = iterator->Children[str[si]-'a'];
    }
    return iterator->Count;
}

size_t Trie_Tree::search_prefix(const std::string &str) const {
    Trie_Node *iterator = this->Root;
    for(size_t si=0;si!=str.size();++si)
    {
        if (iterator->Children[str[si]-'a'] == nullptr)
        {
            return 0;
        }
        iterator = iterator->Children[str[si]-'a'];
    }
    return iterator->Prefix;
}

#endif //DATASTRUCTURE_TRIE_TREE_HPP
