#ifndef DATASTRUCTURE_DATAFRAME_TRANSFORMER_HPP
#define DATASTRUCTURE_DATAFRAME_TRANSFORMER_HPP

#include <array>
#include <vector>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>

class csv_frame {
public:

    ~csv_frame() {
        f.close();
        f.clear();
    }

    explicit csv_frame(char const *x) {
        path = const_cast<char *>(x);
        f.open(x, std::ios::in);
        _init_();
    }

    void _init_() {
        std::vector<std::string> temp_table;
        std::ifstream temp_f(path);
        std::string temp_string;
        while (temp_f.good()) {
            std::getline(temp_f, temp_string);
            temp_table.emplace_back(temp_string);
        }
        temp_f.close();
        temp_table.pop_back();
        size_t rows = temp_table.size() - 1;

        std::stringstream temp_string_stream;
        temp_string_stream << temp_table[0]; // load columns name into string stream.
        while (temp_string_stream.good()) {
            std::getline(temp_string_stream, temp_string, ',');
            column_names.emplace_back(temp_string);
        }
        size_t columns = column_names.size();
        shape = std::pair<int, int>(rows, columns);

        for (int iter = 1; iter != temp_table.size(); iter++) {
            std::vector<std::string> temp_container;
            temp_container.clear();
            temp_string_stream.clear();
            temp_string_stream << temp_table[iter];
            while (temp_string_stream.good()) {
                std::getline(temp_string_stream, temp_string, ',');
                temp_container.emplace_back(temp_string);
            }
            table.emplace_back(temp_container);
        }
    }

    std::ostream &print(std::ostream &out = std::cout) {
        print_columns(out);
        for (auto &&iter : table) {
            std::copy(std::begin(iter), std::end(iter),
                      std::ostream_iterator<std::string>(out, "\t"));
            out << std::endl;
        }
        out << std::endl;
        return out;
    }

    std::ostream &print_columns(std::ostream &out = std::cout) {
        std::copy(std::begin(column_names), std::end(column_names),
                  std::ostream_iterator<std::string>(out, "  "));
        out << std::endl;
        return out;
    }

    std::pair<int, int> size() {
        return shape;
    }

    std::pair<std::vector<std::string>, std::vector<std::vector<std::string>>> interface() {
        return std::pair<std::vector<std::string>, std::vector<std::vector<std::string>>>(column_names, table);
    }

private:

    std::vector<std::string> column_names;
    std::vector<std::vector<std::string>> table;
    std::pair<int, int> shape{};
    std::ifstream f{};
    char *path;
};


class array_maker {
public:
    explicit array_maker(csv_frame &x) {
        std::pair<std::vector<std::string>, std::vector<std::vector<std::string>>> packet = x.interface();
        Work_Done_Flag = false;

        shape = x.size();
        column_names = packet.first;
        Source = packet.second;
        _init_implement();
        _init_scan();

        for (int i = 0; i != shape.second; i++) {
            ADF.emplace_back(std::vector<int> {});
        }
    }

    void _init_implement() {
        int columns = shape.second;
        const bool temp = false;
        for (int i = 0; i < columns; i++) {
            indivisible.emplace_back(temp);
            done.emplace_back(temp);
        }
    }

    std::ostream &Report(std::ostream &out = std::cout) {
        out << "Data can" << (Work_Done_Flag ? "" : "not") << " be generated to an array at this time." << std::endl;
        if (!Work_Done_Flag) {
            out << "To complete the conversion, you need to do finish below columns transformation:" << std::endl;
            for (int iter = 0; iter != shape.second; iter++) {
                if (!done[iter]) {
                    out << column_names[iter] << ": " << Source[0][iter] << '\t' << Source[1][iter]
                        << '\t' << Source[2][iter] << '\t' << "..." << std::endl;
                }
            }
        }
        return out;
    }

    void _init_scan() {
        std::vector<int> temp_cut_list;
        int temp_counter;
        std::string temp_name;
        for (auto iter = 0; iter!=this->size().second; iter++) {
            temp_counter = _row_counter(iter);
            if (temp_counter == 2) {
                temp_name = Source[0][iter];
                for (auto iter3 = 0; iter!=this->size().first; iter3++) {
                    if (Source[iter3][iter] == temp_name) {
                        Source[iter3][iter] = "1";
                    } else {
                        Source[iter3][iter] = "0";
                    }
                }
                done[iter] = true;
            } else if (temp_counter == 1) {
                temp_cut_list.emplace_back(iter - temp_cut_list.size());
            } else {
                continue;
            }
            for (auto && iter2: temp_cut_list) {
                cut(iter2);
            }
        }
    }

    inline std::vector<int> _string_transform_tools(int const &inner_num, std::ostream& out = std::cout, std::istream& in = std::cin) const {
        auto temp_string_list = _row_set(inner_num);

        out << "You are excepted to sort them by using numbers:" << std::endl;
        std::copy(std::begin(temp_string_list), std::end(temp_string_list), std::ostream_iterator<std::string>(out, " "));
        out << "use "
            << temp_string_list.size() << " numbers to sort them, and 0 for the minimum, and then "
            << temp_string_list.size() << " for the maximum." << std::endl;

        std::vector<int> temp_sorter;
        std::copy(std::istream_iterator<int>(in), std::istream_iterator<int>(), temp_sorter.begin());
        return temp_sorter;
    }

    inline void _string_transform (int const &inner_num, std::ostream& out = std::cout, std::istream& in = std::cin) {
        out << "whether this list in string is indivisible?(Y/N)" << std::endl;
        std::string temp_string;
        in >> temp_string;
        (temp_string == "y"||temp_string =="Y")? indivisible[inner_num] = true: indivisible[inner_num] = false;
    }

    int _row_counter(int const &index) const {
        std::vector<std::string> temp_vector;
        std::string temp_string;
        bool break_flag;
        for (auto && iter:Source) {
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

    std::vector<std::string> _row_set(int const &index) const {
        std::vector<std::string> temp_vector;
        std::string temp_string;
        bool break_flag;
        for (auto && iter:Source) {
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
        return temp_vector;
    }

    void cut(const std::string &x) {
        int tick = std::find(std::begin(column_names), std::end(column_names), x) - std::begin(column_names);
        shape.second -= 1;

        column_names.erase(std::begin(column_names) + tick);
        indivisible.erase(std::begin(indivisible) + tick);
        done.erase(std::begin(done) + tick);

        for (auto && iter: Source) {
            iter.erase(std::begin(iter) + tick);
        }
    }

    void cut(const int &tick) {
        shape.second -= 1;

        column_names.erase(std::begin(column_names) + tick);
        indivisible.erase(std::begin(indivisible) + tick);
        done.erase(std::begin(done) + tick);

        for (auto && iter: Source) {
            iter.erase(std::begin(iter) + tick);
        }
    }

    std::pair<int, int> size() {
        return this->shape;
    }

private:
    static inline std::vector<double> string_to_double(std::vector<std::string> &x) {
        char *temp;
        char *empty;
        std::vector<double> temp_container;
        for (auto &&iter: x) {
            size_t len = iter.length();
            temp = new char[len + 1];
            strcpy(temp, iter.c_str());
            temp_container.emplace_back(strtod(temp, &empty));
        }
        return temp_container;
    }

    std::vector<std::vector<std::string>> Source;
    std::vector<std::vector<int>> ADF;
    std::vector<std::string> column_names;
    std::pair<int, int> shape;

    std::vector<bool> indivisible{};
    std::vector<bool> done{};
    bool Work_Done_Flag;

};

template <template <template <typename = int, typename =std::allocator<int>> class COL_CONT = std::vector, std::allocator<COL_CONT<>>> class ROW_CONT>
class DataFrame_Shape_Locker {
    static const std::pair<size_t, size_t> *shape_pointer;
    static std::pair<size_t, size_t> shape;

    explicit DataFrame_Shape_Locker(std::vector<std::vector<int>> const &x): vector(x) {
        DataFrame_Shape_Locker::shape_pointer = new std::pair<size_t, size_t> {x.size(), x[0].size()};
    }

private:
    std::vector<std::vector<int>> vector;

};

#endif //DATASTRUCTURE_DATAFRAME_TRANSFORMER_HPP
