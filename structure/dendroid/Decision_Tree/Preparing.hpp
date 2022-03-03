#ifndef DATASTRUCTURE_PREPARING_HPP
#define DATASTRUCTURE_PREPARING_HPP

#include <set>
#include <map>
#include <cmath>
#include <vector>
#include <deque>
#include <sstream>
#include <fstream>
#include "DT_Container.hpp"

#include "../Normal_Algorithm/Sort/Select_Sort_Algorithm.hpp"

DataFrame &csv_read(std::string const &path)
{
    DataFrame &_res = *new DataFrame {};

    std::ifstream _csv;
    _csv.open(path, std::ios::in);

    std::deque<std::string> _lines {};
    std::string _temp_string;

    while(_csv.good())
    {
        std::getline(_csv, _temp_string);
        _lines.emplace_back(_temp_string);
    }

    _lines.pop_back();
    _csv.close();

    std::stringstream _str_stream;
    _str_stream << _lines.front();
    _lines.pop_front();

    while(_str_stream.good())
    {
        std::getline(_str_stream, _temp_string, ',');
        _res.Column_name.emplace_back(_temp_string);
    }
    size_t const column = _res.Column_name.size();

    int line = -1;
    while(!_lines.empty())
    {
        ++line;
        _res.Chart.emplace_back(std::vector<std::string>{});
        _res.Chart[line].reserve(column);
        _str_stream.clear();
        _str_stream << _lines.front();
        _lines.pop_front();
        while (_str_stream.good())
        {
            std::getline(_str_stream, _temp_string, ',');
            _res.Chart[line].emplace_back(_temp_string);
        }
    }
    _res.Row = _res.Chart.size();
    _res.Column = _res.Column_name.size();

    return _res;
}

size_t row_counter(Decision_Array_Transformer const &DArray, size_t const &index)
{
    std::vector<std::string> temp_vector;
    std::string temp_string;
    bool break_flag;
    for (auto && iter:DArray.Source) {
        break_flag = false;
        temp_string = iter[index];
        for (auto && iter2: temp_vector) {
            if (temp_string == iter2) {
                break_flag = true;
                break;
            }
        }
        if (break_flag) {
            continue;
        } else {
            temp_vector.emplace_back(temp_string);
        }
    }
    return temp_vector.size();
}

template<typename Tp>
Tp string_to(std::string const &str)
{
    std::stringstream ssm;
    ssm << str;
    Tp _res;
    ssm >> _res;
    return _res;
}

void cut(Decision_Array_Transformer &DArray, ssize_t const &dev)
{
    --DArray.Column;
    DArray.Column_Names.erase(std::begin(DArray.Column_Names) + dev);
    DArray.Trans_Table.erase(std::begin(DArray.Trans_Table) + dev);
    DArray.Continuous.erase(std::begin(DArray.Continuous) + dev);
    DArray.Done.erase(std::begin(DArray.Done) + dev);

    for(auto &iter : DArray.Source)
    {
        iter.erase(iter.begin()+dev);
    }
    for(auto &iter : DArray.Chart)
    {
        iter.erase(iter.begin()+dev);
    }
    for(size_t i=0; i != DArray.Column; ++i) if (!DArray.Done[i]) return;
    DArray.Translation_Done = true;
}

void grp(Decision_Array_Transformer &DArray, size_t const &dev, size_t const &nums)
{
    if (nums <= 1) return;
    std::vector<double> _sorting {};
    std::string _temp_str;
    for (size_t i=0; i != DArray.Row; ++i)
    {
        _sorting.emplace_back(string_to<double>(DArray.Source[i][dev]));
    }
    select_sort<double>(_sorting);
    double branch[nums-1];
    size_t idx = 0;

    for (size_t i = 0; i!= nums-1; ++i)
    {
        idx += (DArray.Row-i - 1)/nums + 1;
        branch[i] = _sorting[idx];
        _temp_str = std::to_string(_sorting[idx]);
        DArray.Trans_Table[dev].emplace_back("~ " + _temp_str.substr(0, std::min(_temp_str.find('.')+3, _temp_str.size())));
    }

    bool _max;
    double _temp;
    for (size_t i=0; i!= DArray.Row; ++i)
    {
        _max = true;
        _temp = string_to<double>(DArray.Source[i][dev]);
        for (size_t j=0 ; j!=nums-1; ++j)
        {
            if (_temp < branch[j])
            {
                DArray.Chart[i][dev] = j;
                _max = false;
                break;
            }
        }
        if (_max) DArray.Chart[i][dev] = nums-1;
    }
    DArray.Done[dev] = true;
    for(size_t i=0; i!= DArray.Column; ++i) if (!DArray.Done[i]) return;
    DArray.Translation_Done = true;
}

std::vector<std::string> column_set(Decision_Array_Transformer &DArray, size_t const &dev)
{
    std::vector<std::string> _res {};
    std::set<std::string> _temp {};
    for (size_t i=0; i!=DArray.Row; ++i)
    {
        _temp.insert(DArray.Source[i][dev]);
    }
    _res.reserve(_temp.size());
    for(auto const &iter: _temp)
    {
        _res.emplace_back(iter);
    }
    return _res;
}

void specialise(Decision_Array_Transformer &DArray, size_t const &dev, std::vector<std::string> const &str_vec, std::vector<size_t> const &idx_vec)
{
    std::string _temp;
    for (size_t i=0; i!=DArray.Row; ++i)
    {
        _temp = DArray.Source[i][dev];
        for(size_t j=0;j!=str_vec.size(); ++j)
        {
            if(_temp == str_vec[j])
            {
                DArray.Chart[i][dev] = idx_vec[j];
                break;
            }
        }
    }
    DArray.Done[dev] = true;
    for(size_t i=0; i!= DArray.Column; ++i) if (!DArray.Done[i]) return;
    for (size_t i=0;i!=str_vec.size(); ++i)
        DArray.Trans_Table[dev].emplace_back("@ " + str_vec[i]);
    DArray.Translation_Done = true;
}

void array_sharp(Decision_Array_Transformer &DArray)
{
    std::vector<int> _tc_list;
    size_t _temp;
    std::string _temp_name;
    for (size_t iter=0; iter != DArray.Column; ++iter)
    {
        _temp = row_counter(DArray, iter);
        if (_temp == 2)
        {
            _temp_name = DArray.Source[0][iter];
            DArray.Trans_Table[iter].emplace_back("@ " + _temp_name);
            for (auto iter2 = 0; iter != DArray.Row; ++iter2)
            {
                if (DArray.Source[iter2][iter] != _temp_name) {
                    DArray.Trans_Table[iter].emplace_back("@ " + DArray.Source[iter2][iter]);
                    break;
                }
            }
            for (auto iter3 = 0; iter3 != DArray.Row; ++iter3)
            {
                if (DArray.Source[iter3][iter] == _temp_name)
                {
                    DArray.Chart[iter3][iter] = 1;
                } else {
                    DArray.Chart[iter3][iter] = 0;
                }
            }
            DArray.Done[iter] = true;
        } else if (_temp == 1){
            _tc_list.emplace_back(iter - _tc_list.size());
        } else {
            continue;
        }
    }

    for(auto const &iter2: _tc_list)
    {
        cut(DArray, iter2);
    }
    for(size_t i=0; i != DArray.Column; ++i) if (!DArray.Done[i]) return;
    DArray.Translation_Done = true;
}

Decision_Array_Transformer &make_array(DataFrame const &df)
{
    Decision_Array_Transformer &_res = *new Decision_Array_Transformer {df};
    array_sharp(_res);
    return _res;
}

std::ostream &Report(std::ostream &out, Decision_Array_Transformer const &DArray) {
    out << "Data can" << (DArray.Translation_Done ? "" : "not") << " be generated to an array at this time." << std::endl;
    if (!DArray.Translation_Done) {
        out << "To complete the conversion, you need to do finish below columns transformation:" << std::endl;
        for (int iter = 0; iter != DArray.Column; iter++) {
            if (!DArray.Done[iter]) {
                out << DArray.Column_Names[iter] << (!DArray.Continuous[iter]? ": ": "(continuous): ") << DArray.Source[0][iter] << " " << DArray.Source[1][iter]
                    << " " << DArray.Source[2][iter] << " ..." << std::endl;
            } else {
                out << DArray.Column_Names[iter] << (!DArray.Continuous[iter]? "(transformed)": "(transformed, continuous)") << DArray.Chart[0][iter] << " " << DArray.Chart[1][iter]
                    << " " << DArray.Chart[2][iter] << " ..." << std::endl;
            }
        }
    }
    return out;
}

#endif //DATASTRUCTURE_PREPARING_HPP
