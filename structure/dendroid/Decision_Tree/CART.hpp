#ifndef DATASTRUCTURE_CART_HPP
#define DATASTRUCTURE_CART_HPP

#include "Preparing.hpp"
#include "DT_Container.hpp"

bool leq(ssize_t a, ssize_t, ssize_t n) {return a <= n;} //false

bool bwn(ssize_t a, ssize_t m, ssize_t n) {return a > m && a <= n;} //true

Decode_Packages&
Translation_Decoder(
        std::vector<std::vector<std::string>> const &codes,
        std::vector<bool> const &continuous)
{
    std::vector<std::pair<ssize_t, ssize_t>> _args;
    std::vector<std::string> _socket;
    std::vector<bool> _standard;
    std::vector<size_t> _refer;
    std::stringstream _sst;
    std::string _temp;
    double _temp_num;
    size_t counter;

    for (size_t ci=0; ci!=codes.size(); ++ci)
    {
        if (continuous[ci])
        {
            counter = 0;
            for(auto const &iter: codes[ci])
            {
                _temp = iter;
                if (_temp[0] == '~') {
                    _temp = _temp.substr(2, _temp.size()-2);
                    _sst << _temp;
                    _sst >> _temp_num;
                    _standard.emplace_back(false);
                    _args.emplace_back(std::pair<size_t, size_t>{0, counter});
                    _socket.emplace_back("<= " + (std::to_string(_temp_num).substr(0, std::to_string(_temp_num).find('.') + 3)));
                    ++counter;
                } else if (_temp[0] == '@') {
                    _temp = _temp.substr(2, _temp.size()-2);
                    _standard.emplace_back(false);
                    _args.emplace_back(std::pair<size_t, size_t>{0, counter});
                    _socket.emplace_back("<= " + _temp);
                    ++counter;
                }
                _refer.emplace_back(ci);
            }
        } else {
            counter = 0;
            std::string _ts2;
            for(auto const &iter: codes[ci])
            {
                _temp = iter;
                if (_temp[0] == '~') {

                    _temp = _temp.substr(2, _temp.size()-2);
                    _sst << _temp;
                    _sst >> _temp_num;
                    _standard.emplace_back(true);
                    _args.emplace_back(std::pair<size_t, size_t>{counter-1, counter});
                    _socket.emplace_back((counter == 0? "<= ": _ts2) + _temp);
                    _ts2 = "> " +_temp + " and <= ";
                    ++counter;
                } else if (_temp[0] == '@') {
                    _temp = _temp.substr(2, _temp.size()-2);
                    _standard.emplace_back(true);
                    _args.emplace_back(std::pair<size_t, size_t>{counter-1, counter});
                    _socket.emplace_back("is " + _temp);
                    ++counter;
                }
                _refer.emplace_back(ci);
            }
        }
    }
    return *new Decode_Packages{_standard, _args, _socket, _refer};
}

std::vector<long double> gini_vec(DT_Node const &node)
{
    std::vector<long double> _res {};
    long double const samples = node.DataBase->size();
    size_t const items = node.Socket.size();
    _res.reserve(items);

    double belongs, not_belongs, b_truth, nb_truth, b_false, nb_false;
    bool using_leq, classification;
    ssize_t right, left;
    size_t column;
    long double gini;

    for (size_t fci=0; fci != items; ++fci)
    {
        gini = 0;
        belongs = 0;
        not_belongs = 0;
        b_truth = 0;
        nb_truth = 0;
        b_false = 0;
        nb_false = 0;
        column = node.Refer[fci];
        using_leq = !node.Standard[fci];
        left = node.Args[fci]->first;
        right = node.Args[fci]->second;
        for (size_t ri=0; ri!=node.DataBase->size(); ++ri)
        {
            classification = node.Models[ri];
            if (using_leq) {
                if(leq(static_cast<ssize_t>((*node.DataBase)[ri][column]), left, right)) {
                    if (classification) {
                        ++b_truth;
                        ++belongs;
                    } else {
                        ++nb_truth;
                        ++not_belongs;
                    }
                } else {
                    if (classification) {
                        ++b_false;
                        ++belongs;
                    } else {
                        ++nb_false;
                        ++not_belongs;
                    }
                }
            } else {
                if(bwn(static_cast<ssize_t>((*node.DataBase)[ri][column]), left, right)) {
                    if (classification) {
                        ++b_truth;
                        ++belongs;
                    } else {
                        ++nb_truth;
                        ++not_belongs;
                    }
                } else {
                    if (classification) {
                        ++b_false;
                        ++belongs;
                    } else {
                        ++nb_false;
                        ++not_belongs;
                    }
                }
            }
        }
        if (belongs != 0) gini += belongs/samples * (1 - pow(b_truth/belongs ,2) - pow(b_false/belongs ,2));
        if (not_belongs != 0) gini += not_belongs/samples * (1 - pow(nb_truth/not_belongs ,2) - pow(nb_false/not_belongs ,2));
        _res.emplace_back(gini);
    }
    return _res;
}

#endif //DATASTRUCTURE_CART_HPP
