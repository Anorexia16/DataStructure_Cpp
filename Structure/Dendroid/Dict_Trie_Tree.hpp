#ifndef DATASTRUCTURE_DICT_TRIE_TREE_HPP
#define DATASTRUCTURE_DICT_TRIE_TREE_HPP

#include <string>
#include <vector>
#include <stack>

struct Dict_Node
{
    Dict_Node *Right;
    Dict_Node *Down;
    bool means;
    char c;
};

class Raw_Dict {
protected:
    Dict_Node *Root;

public:
    Raw_Dict();

    template<template<typename elem, typename =std::allocator<elem>>class Cont>
    explicit Raw_Dict(Cont<std::string> const &);

    template<unsigned long long n>
    void insert(char const (&)[n]);

    void insert(std::string const &);

    [[nodiscard]] Dict_Node *prefix_search(std::string const &) const;

    template<unsigned long long n>
    [[nodiscard]] Dict_Node *prefix_search(char const (&)[]) const;

    [[nodiscard]] static std::vector<std::string> groups(Dict_Node *);

    static Dict_Node *input(Dict_Node *, char const &, std::string &);

    static Dict_Node *input(Dict_Node *, char const &);

    [[nodiscard]] Dict_Node *begin() const;
};

class Dict final {
public:
    Dict();

    template<template<typename elem, typename =std::allocator<elem>>class Cont>
    void import(Cont<std::string> const &);

    void import(std::initializer_list<std::string> const &);

    template<unsigned long long n>
    void emplace(char const (&)[n]);

    void emplace(std::string const &);

    void init();
    void input(char const &);
    std::vector<std::string>
    release();

protected:
    Dict_Node *pattern;
    std::string cache;
    Raw_Dict dict;
};

Dict::Dict()
:pattern{}, dict{}, cache{} {}

void Dict::init() {
    pattern = dict.begin();
    cache.clear();
}

void Dict::input(const char &c) {
    pattern = Raw_Dict::input(pattern, c, cache);
}

std::vector<std::string> Dict::release() {
    std::vector<std::string> vec = Raw_Dict::groups(pattern);
    for (auto &iter:vec) iter.insert(0, cache);
    return vec;
}

template<template<typename elem, typename =std::allocator<elem>>class Cont>
void Dict::import(const Cont<std::string> &container) {
    for (auto const &iter:container) insert(iter);
}

void Dict::import(const std::initializer_list<std::string> &init_list) {
    for (auto const&iter:init_list) dict.insert(iter);
}

template<unsigned long long int n>
void Dict::emplace(const char (&raw)[n]) {
    dict.insert(raw);
}

void Dict::emplace(const std::string &str) {
    dict.insert(str);
}

Raw_Dict::Raw_Dict()
        :Root{new Dict_Node{nullptr,nullptr, false,'~'}} {}

template<template<typename elem, typename =std::allocator<elem>>class Cont>
Raw_Dict::Raw_Dict(const Cont<std::string> &container)
        :Root{new Dict_Node{nullptr,nullptr, false, '~'}}
{
    for (auto const &iter:container) {
        this->insert(iter);
    }
}

template<unsigned long long int n>
void Raw_Dict::insert(char const (&str)[n]) {
    Dict_Node *_building_iterator = this->Root;
    for(unsigned long long bi=0; bi!=n-1;++bi) {
        while (true) {
            if (_building_iterator->c == '~') {
                _building_iterator->c = str[bi];
                _building_iterator->Right = new Dict_Node{nullptr, nullptr, false, '~'};
                _building_iterator->Down = new Dict_Node{nullptr, nullptr, false, '~'};
                if (bi == n - 2) _building_iterator->means = true;
                _building_iterator = _building_iterator->Down;
                break;
            } else if (_building_iterator->c > str[bi]) {
                _building_iterator->Right = new Dict_Node{_building_iterator->Right, _building_iterator->Down,
                                                          _building_iterator->means, _building_iterator->c};
                _building_iterator->Down = new Dict_Node{nullptr, nullptr, false, '~'};
                _building_iterator->c = str[bi];
                if (bi == n - 2) _building_iterator->means = true;
                _building_iterator = _building_iterator->Down;
                break;
            } else if (_building_iterator->c == str[bi]) {
                if (bi == n - 2) _building_iterator->means = true;
                _building_iterator = _building_iterator->Down;
                break;
            } else {
                _building_iterator = _building_iterator->Right;
                continue;
            }
        }
    }
}

void Raw_Dict::insert(const std::string &str) {
    unsigned long long const depth = str.size();
    Dict_Node *_building_iterator = this->Root;
    for(unsigned long long bi=0; bi!=depth;++bi) {
        while (true) {
            if (_building_iterator->c == '~') {
                _building_iterator->c = str[bi];
                _building_iterator->Right = new Dict_Node{nullptr, nullptr, false, '~'};
                _building_iterator->Down = new Dict_Node{nullptr, nullptr, false, '~'};
                if (bi == depth - 1) _building_iterator->means = true;
                _building_iterator = _building_iterator->Down;
                break;
            } else if (_building_iterator->c > str[bi]) {
                _building_iterator->Right = new Dict_Node{_building_iterator->Right,_building_iterator->Down,
                                                          _building_iterator->means, _building_iterator->c};
                _building_iterator->Down = new Dict_Node{nullptr, nullptr, false, '~'};
                _building_iterator->c = str[bi];
                if (bi == depth - 1) _building_iterator->means = true;
                _building_iterator = _building_iterator->Down;
                break;
            } else if (_building_iterator->c == str[bi]) {
                if (bi == depth - 1) _building_iterator->means = true;
                _building_iterator = _building_iterator->Down;
                break;
            } else {
                _building_iterator = _building_iterator->Right;
                continue;
            }
        }
    }
}

Dict_Node *Raw_Dict::prefix_search(const std::string &str) const {
    unsigned long long const depth = str.size();
    Dict_Node *_reading_iterator = Root;
    for(unsigned long long bi=0; bi!=depth; ++bi) {
        while (true) {
            if (_reading_iterator->c == '~'||_reading_iterator->c>str[bi]) return nullptr;
            else if (_reading_iterator->c == str[bi]) {
                break;
            } else {
                _reading_iterator = _reading_iterator->Right;
                continue;
            }
        }
        if (bi<depth-1) _reading_iterator = _reading_iterator->Down;
    }
    return _reading_iterator;
}

Dict_Node *Raw_Dict::begin() const {
    return new Dict_Node {nullptr, Root, false, '~'};
}

template<unsigned long long int n>
Dict_Node *Raw_Dict::prefix_search(char const (&str)[]) const {
    Dict_Node *_reading_iterator = this->Root;
    for(unsigned long long bi=0; bi!=n-1; ++bi) {
        while (true) {
            if (_reading_iterator->c == '~'||_reading_iterator->c>str[bi]) return nullptr;
            else if (_reading_iterator->c == str[bi]) {
                break;
            } else {
                _reading_iterator = _reading_iterator->Right;
                continue;
            }
        }
        if (bi<n-2) _reading_iterator = _reading_iterator->Down;
    }
    return _reading_iterator;
}

std::vector<std::string> Raw_Dict::groups(Dict_Node *node) {
    if (node == nullptr) return std::vector<std::string> {};
    std::vector<std::string> _res {};
    std::stack<std::string> SS {};
    std::stack<Dict_Node*> NS {};
    Dict_Node *_iter = node->Down;
    std::string _str {};

    while(!SS.empty()||_iter->Right!=nullptr||_iter->Down!=nullptr) {
        if (_iter->c!='~') {
            if (_iter->Right->c!='~') {
                NS.push(_iter->Right);
                SS.push(_str);
            }
            _str+=_iter->c;
            if (_iter->means) _res.emplace_back(_str);
            _iter=_iter->Down;
        } else if (_iter->c!='~'&&_iter->Right->c!='~') {
            _iter = _iter->Right;
        } else {
                _iter = NS.top();
                _str = SS.top();
                NS.pop();
                SS.pop();
        }
    }
    return _res;
}

Dict_Node *Raw_Dict::input
        (Dict_Node *node, const char &c, std::string &str) {
    if (node == nullptr) return nullptr;
    Dict_Node *_iter = node;
    _iter = _iter->Down;
    str.append(1, c);
    while (true) {
        if (_iter->c == '~'||_iter->c>c) return nullptr;
        else if (_iter->c==c) return _iter;
        else _iter = _iter->Right;
    }
}

Dict_Node *Raw_Dict::input(Dict_Node *node, char const &c) {
    if (node == nullptr) return nullptr;
    Dict_Node *_iter = node;
    _iter = _iter->Down;
    while (true) {
        if (_iter->c == '~'||_iter->c>c) return nullptr;
        else if (_iter->c==c) return _iter;
        else _iter = _iter->Right;
    }
}

#endif //DATASTRUCTURE_DICT_TRIE_TREE_HPP
