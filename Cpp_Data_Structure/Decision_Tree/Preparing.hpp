#ifndef DATASTRUCTURE_PREPARING_HPP
#define DATASTRUCTURE_PREPARING_HPP

#include <deque>
#include <sstream>
#include <fstream>
#include "DT_Container.hpp"

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

void cut(Decision_Array_Transformer &array, ssize_t const &dev)
{
    --array.Column;
    array.Column_Names.erase(std::begin(array.Column_Names) + dev);
    array.Trans_Table.erase(std::begin(array.Trans_Table) + dev);
    array.Continuous.erase(std::begin(array.Continuous) + dev);
    array.Done.erase(std::begin(array.Done) + dev);

    for(auto &iter : array.Source)
    {
        iter.erase(iter.begin()+dev);
    }
}

void array_sharp(Decision_Array_Transformer &array)
{
    std::vector<int> _tc_list;
    size_t _temp;
    std::string _temp_name;
    for (size_t iter=0; iter!=array.Column; ++iter)
    {
        _temp = row_counter(array, iter);
        if (_temp == 2)
        {
            _temp_name = array.Source[0][iter];
            array.Trans_Table[iter][0] = _temp_name;
            for (auto iter2 = 0; iter!=array.Row; ++iter2)
            {
                if (array.Source[iter2][iter] != _temp_name) {
                    array.Trans_Table[iter][1] = array.Source[iter2][iter];
                    break;
                }
            }
            for (auto iter3 = 0; iter!=array.Row; ++iter3)
            {
                if (array.Source[iter3][iter] == _temp_name)
                {
                    array.Chart[iter3][iter] = 1;
                } else {
                    array.Chart[iter3][iter] = 0;
                }
            }
            array.Done[iter] = true;
        } else if (_temp == 1){
            _tc_list.emplace_back(iter - _tc_list.size());
        } else {
            continue;
        }
    }
    for(auto const &iter2: _tc_list)
    {
        cut(array, iter2);
    }
    for(size_t i=0; i!= array.Column; ++i) if (!array.Done[i]) return;
    array.Translation_Done = true;
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
                out << DArray.Column_Names[iter] << ": " << DArray.Source[0][iter] << '\t' << DArray.Source[1][iter]
                    << '\t' << DArray.Source[2][iter] << '\t' << "..." << std::endl;
            }
        }
    }
    return out;
}

#endif //DATASTRUCTURE_PREPARING_HPP
