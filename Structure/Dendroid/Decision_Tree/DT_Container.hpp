#ifndef DATASTRUCTURE_DT_CONTAINER_HPP
#define DATASTRUCTURE_DT_CONTAINER_HPP

#include <functional>
#include <iterator>
#include <string>
#include <vector>
#include <map>

struct DataFrame
{
    DataFrame() = default;

    [[nodiscard]] std::pair<size_t, size_t> shape() const noexcept;

    std::vector<std::string> Column_name;

    std::vector<std::vector<std::string>> Chart;

    size_t Row {0};

    size_t Column {0};

    friend std::ostream &operator<<(std::ostream &out, DataFrame const &df)
    {
        std::copy(std::begin(df.Column_name), std::end(df.Column_name),
                  std::ostream_iterator<std::string>(out, "  "));
        out << std::endl;
        for (auto &&iter : df.Chart) {
            std::copy(std::begin(iter), std::end(iter),
                      std::ostream_iterator<std::string>(out, "\t"));
            out << std::endl;
        }
        return out;
    }
};

struct Decision_Array_Transformer
{
    explicit Decision_Array_Transformer(DataFrame const &);

    std::vector<std::vector<std::string>> Trans_Table;

    std::vector<std::vector<std::string>> Source;

    std::vector<std::vector<size_t>> Chart;

    std::vector<std::string> Column_Names;

    std::vector<bool> Continuous;

    std::vector<bool> Done;

    bool Translation_Done;

    size_t Column;

    size_t Row;
};

struct Decision_Tree_Pool
{
    Decision_Tree_Pool() = default;

    std::vector<std::vector<std::string>> Trans_Table;

    std::vector<std::vector<size_t>> Container;

    std::vector<std::string> Column_Names;

    std::vector<size_t> Classification;

    std::vector<bool> Continuous;
};

struct Decode_Packages
{
    std::vector<bool> _standard;

    std::vector<std::pair<ssize_t, ssize_t>> _args;

    std::vector<std::string> _socket;

    std::vector<size_t> _refer;
};

struct DT_Node {
    std::vector<bool> Standard;

    std::vector<std::pair<ssize_t, ssize_t>*> Args;

    std::vector<std::vector<size_t>> *DataBase;

    std::vector<std::string*> Socket;

    std::vector<bool> Models;

    std::vector<size_t> Refer;
};

std::pair<size_t, size_t> DataFrame::shape() const noexcept
{
    return {Row, Column};
}

Decision_Array_Transformer::Decision_Array_Transformer(DataFrame const &df)
:Source{df.Chart}, Chart(df.Row, std::vector<size_t>(df.Column, 0)), Translation_Done{false}, Column_Names{df.Column_name},
    Continuous(df.Column, false), Done(df.Column, false) ,
    Trans_Table(df.Column, std::vector<std::string>{}), Row{df.Row}, Column{df.Column} {}

#endif //DATASTRUCTURE_DT_CONTAINER_HPP
