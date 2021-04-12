#ifndef DATASTRUCTURE_MAIN_TUI_HPP
#define DATASTRUCTURE_MAIN_TUI_HPP

#include "Preparing.hpp"

class DT_Interface
{
public:
    explicit DT_Interface() = default;

    void connect(std::ostream &out= std::cout, std::istream &in = std::cin);

    void disconnect();

private:
    Decision_Array_Transformer *DArray;
    DataFrame *Df;
};

void DT_Interface::connect(std::ostream &out, std::istream &in)
{
    std::string _in_word;
    ssize_t _in_num;
    out << "------------Decision Tree Text UI-----------" << std::endl;
    out << "Input file path to start preparing transform:" << std::endl;
    in >> _in_word;
    this->Df = &csv_read(_in_word);
    out << "Temp Array for transforming is generating." << std::endl;
    this->DArray = &make_array(*this->Df);
    this->Df = nullptr;
    out << "Generating done.\nSWitching to the order windows." << std::endl;
    while(true) {
        out << "~DT:";
        in >> _in_word;
        if (_in_word == "info")
        {
            Report(out, *this->DArray);
        } else if (_in_word == "exit") {
            out << "Disconnecting from the source file." << std::endl;
            this->disconnect();
            out << "Done." << std::endl;
            out << "------------Decision Tree Exited-----------" << std::endl;
            return;
        } else if (_in_word == "help") {
            out << "Decision Tree TUI order sets help:" << std::endl;
            out << "  info    ---- view whole array can be transform or not." << std::endl;
            out << "  cut x   ---- erase {x} and relevant Records" << std::endl;
            out << "  spe x   ---- transform {x} with particular written reflection(not recommend)." << std::endl;
            out << "  grp x y ---- transform numeric type column {x}." << std::endl;
            out << "Significant options:" << std::endl;
            out << "  /i  ---- Input column index x rather than its name.(cut, spe, grp)" << std::endl;
            out << "  /s  ---- Input column name x rather than its index.(cut, spe, grp)" << std::endl;
            out << "  /c  ---- Explaining that the transformed column is continuous.(spe, grp)" << std::endl;
        } else if (_in_word == "cut") {
            if (in.good()) in >> _in_word;
            else {
                out << "Func Error: cut requires index information." << std::endl;
                continue;
            }
            if (_in_word == "/s")
            {
                if (in.good())
                {
                    in >> _in_word;
                    ssize_t index = 0;
                    for(;index!=this->DArray->Column; ++index) {
                        if (_in_word == this->DArray->Column_Names[index]) break;
                    }
                    if (index==this->DArray->Column)
                    {
                        std::cout << "Name Error: Do not exist column named: " << _in_word <<"." << std::endl;
                    } else {
                        cut(*this->DArray, index);
                        std::cout << "Cutting for column \"" << _in_word << "\" has done." << std::endl;
                    }
                }
                else out << "Func Error: cut requires index information." <<std::endl;
            } else if (_in_word == "/i") {
                if (in.good())
                {
                    try {
                        in >> _in_num;
                    } catch (...) {
                        std::cout << "Func Error: this situation requires one integral type" << std::endl;
                    }
                    cut(*this->DArray, _in_num);
                    std::cout << "Cutting for column " << _in_num << " has done." << std::endl;
                } else {
                    std::cout << "Func Error: this situation requires one integral type" << std::endl;
                }
            } else {
                out << "Input Error: Do not exist option named " << _in_word << ".\nMaybe you can get assistance with \"help\"" <<std::endl;
                in.clear();
            }
        } else if (_in_word == "grp") {
            if (in.good()) in >> _in_word;
            else {
                out << "Func Error: grp requires index and numeric information." << std::endl;
                continue;
            }
            if (_in_word == "/i")
            {
                //TODO
            } else if (_in_word == "/s") {
                in >> _in_word;
                ssize_t index = 0;
                for(;index!=this->DArray->Column; ++index) {
                    if (_in_word == this->DArray->Column_Names[index]) break;
                }
                if (index==this->DArray->Column)
                {
                    std::cout << "Name Error: Do not exist column named: " << _in_word <<"." << std::endl;
                } else {
                    //TODO
                    std::cout << "Grouping for column \"" << _in_word << "\" has done." << std::endl;
                }
            } else {
                out << "Input Error: Do not exist option named " << _in_word << ".\nMaybe you can get assistance with \"help\"" <<std::endl;
                in.clear();
            }
        } else if (_in_word == "spe") {

        } else {
            out << "Input Error: Do not exist order named " << _in_word << ".\nMaybe you can get assistance with \"help\"." <<std::endl;
            in.clear();
        }
    }
}

void DT_Interface::disconnect() {
    this->DArray = nullptr;
    this->Df = nullptr;
}


#endif //DATASTRUCTURE_MAIN_TUI_HPP
