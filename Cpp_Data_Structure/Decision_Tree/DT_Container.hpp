#ifndef DATASTRUCTURE_DT_CONTAINER_HPP
#define DATASTRUCTURE_DT_CONTAINER_HPP

#include <iterator>
#include <string>
#include <vector>
#include <map>

class DataFrame
{
public:
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

std::pair<size_t, size_t> DataFrame::shape() const noexcept
{
    return {Row, Column};
}

struct Decision_Array_Transformer
{
    explicit Decision_Array_Transformer(DataFrame const &);

    std::vector<std::map<size_t, std::string>> Trans_Table;

    std::vector<std::vector<std::string>> Source;

    std::vector<std::vector<unsigned>> Chart;

    std::vector<std::string> Column_Names;

    std::vector<bool> Continuous;

    std::vector<bool> Done;

    bool Translation_Done;

    size_t Column;

    size_t Row;
};

Decision_Array_Transformer::Decision_Array_Transformer(DataFrame const &df)
:Source{df.Chart}, Chart(df.Row, std::vector<unsigned>(df.Column, 0)), Translation_Done{false}, Column_Names{df.Column_name},
    Continuous(df.Column, false), Done(df.Column, false) ,
    Trans_Table(df.Column, std::map<size_t, std::string>{}), Row{df.Row}, Column{df.Column} {}


#endif //DATASTRUCTURE_DT_CONTAINER_HPP
