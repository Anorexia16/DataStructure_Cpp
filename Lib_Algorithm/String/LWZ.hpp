#ifndef DATASTRUCTURE_LWZ_HPP
#define DATASTRUCTURE_LWZ_HPP

#include "Re.hpp"
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <map>

class LWZ_Compressor
{
public:
    static void LWZ_Compress(std::string const &, std::string const & = "", std::string const & = "");

    static std::vector<std::string> &LWZ_Encoding(std::vector<std::string> const &, std::string const &);

    static std::vector<std::string> &LWZ_Decoding(std::vector<std::string> const &, std::string const &);

    static std::string Ascii_Queue();
};

void LWZ_Compressor::LWZ_Compress(std::string const &source_file, std::string const  &target_name,
                                  std::string const &character_set)
{
    std::ifstream reader {};
    reader.open(source_file, std::ios::in);

    std::vector<std::string> _vec;
    std::string _temp;

    while (reader.good())
    {
        std::getline(reader, _temp);
        _vec.emplace_back(_temp);
    }
    reader.close();

    std::string const & _set = character_set.empty() ? *new std::string {LWZ_Compressor::Ascii_Queue()}: character_set;
    std::vector<std::string> &_compressed_codes = LWZ_Compressor::LWZ_Encoding(_vec, _set);

    std::ofstream writer {};
    std::string _name = (target_name.empty() ? Re::split(source_file, ".")[0] : target_name) + ".zzz";
    writer.open(_name, std::ios::out);
    while(!_compressed_codes.empty())
    {
        writer << *_compressed_codes.begin() << std::endl;
        _compressed_codes.erase(_compressed_codes.begin());
    }
    writer.close();
}

std::vector<std::string> &LWZ_Compressor::LWZ_Encoding(std::vector<std::string> const &content, std::string const &character_set)
{
    std::vector<std::string> &_res = *new std::vector<std::string> (content.size(), "");

    std::map<std::string, size_t> _map;
    size_t const _cs = character_set.size();
    size_t const _ds = content.size();

    size_t _idx = 0;
    size_t _len;

    for(size_t _i = 0; _i != _cs; ++_i, ++_idx) _map[character_set.substr(_i, 1)] =_idx;

    for(size_t _l = 0; _l != _ds; ++_l)
    {
        _len = content[_l].size();
        std::string const &_temp_str = content[_l];
        for (size_t _dev = 0; _dev != _len;)
        {
            for(size_t _word_len = 1 ; _word_len+_dev <= _len ;)
            {
                if (_map.count(_temp_str.substr(_dev, _word_len + 1)) != 0)
                {
                    ++_word_len;
                    if (_word_len + _dev == _len)
                    {
                        _res[_l] += std::to_string(_map[_temp_str.substr(_dev, _word_len)]);
                        _dev += _word_len;
                        ++_idx;
                        break;
                    }
                } else
                    {
                    _res[_l] += std::to_string(_map[_temp_str.substr(_dev, _word_len)]);
                    _map[_temp_str.substr(_dev, _word_len+1)] = _idx;
                    _dev += _word_len;
                    ++_idx;
                    break;
                }
            }
        }
    }

    return _res;
}

std::vector<std::string> &
LWZ_Compressor::LWZ_Decoding(const std::vector<std::string> &word, const std::string &translation)
{
    std::vector<std::string> &_res = *new std::vector<std::string> {};
    return _res;
}

std::string LWZ_Compressor::Ascii_Queue()
{
    std::string _res {};
    _res.reserve();
    for (char c = 32; c<126; ++c) _res += c;
    return _res;
}

#endif //DATASTRUCTURE_LWZ_HPP
