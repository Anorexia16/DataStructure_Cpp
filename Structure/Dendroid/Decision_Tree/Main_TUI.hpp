#ifndef DATASTRUCTURE_MAIN_TUI_HPP
#define DATASTRUCTURE_MAIN_TUI_HPP

#include "Preparing.hpp"
#include "CART.hpp"

class DT_Interface
{
public:
    explicit DT_Interface() = default;

    void connect(std::ostream &out= std::cout, std::istream &in = std::cin);

    void File_Stream_Interface(std::ostream &out, std::istream &in);

    void Pretreatment_Interface(std::ostream &out, std::istream &in);

    void Pushing_Pool_Interface(std::ostream &out, std::istream &in);

    void Tree_Generate_Interface(std::ostream &out, std::istream&in);

    void disconnect();

private:
    static void console_color(int a, int b) { std::system(("color " + std::to_string(10 * a +b)).data());}
    Decision_Array_Transformer *DArray;
    Decision_Tree_Pool *DPool;
    Decode_Packages *DPct;
    DataFrame *Df;
    DT_Node *Root;
};

void DT_Interface::connect(std::ostream &out, std::istream &in)
{
    this->File_Stream_Interface(out, in);
    if (!this->DArray->Translation_Done) this->Pretreatment_Interface(out, in);
    else {
        this->Pushing_Pool_Interface(out, in);
    }
}

void DT_Interface::disconnect() {
    this->DArray = nullptr;
    this->Df = nullptr;
}

void DT_Interface::File_Stream_Interface(std::ostream &out, std::istream &in) {
    if (this->DArray!=nullptr &&this->DArray->Translation_Done) return;
    std::string _in_word;
    out << "------------Decision Tree Text UI-----------" << std::endl;
    if (this->DArray == nullptr) {
        out << "Input file path to start preparing transform:" << std::endl;
        in >> _in_word;
        this->Df = &csv_read(_in_word);
        out << "Temp Array for transforming is generating." << std::endl;
        this->DArray = &make_array(*this->Df);
        this->Df = nullptr;
        out << "Generating done.\nSWitching to the order windows." << std::endl;
    } else {
        out << "Recovering connection with data." << std::endl;
    }
}

void DT_Interface::Pretreatment_Interface(std::ostream &out, std::istream &in)
{
    std::string _in_word;
    ssize_t _in_num;
    while(in.good()) {
        out << "~DT:";
        in >> _in_word;
        if (_in_word == "info") {
            Report(out, *this->DArray);
            if (this->DArray->Translation_Done) out << "Pretreatment work done. Run \"push\" when ready to next phase." << std::endl;
        } else if (_in_word == "exit") {
            out << "Disconnecting from the source file." << std::endl;
            this->disconnect();
            out << "Done." << std::endl;
            out << "------------Decision Tree Exited-----------" << std::endl;
            return;
        } else if (_in_word == "hang") {
            out << "Hanging now." << std::endl;
            out << "------------Decision Tree Offline-----------" << std::endl;
            return;
        } else if (_in_word == "help") {
            out << "Decision Tree TUI order sets help:" << std::endl;
            out << "  info    ---- view whole array can be transform or not." << std::endl;
            out << "  exit    ---- exit TUI ang clean all data." << std::endl;
            out << "  hang    ---- leave TUI without cleaning any reference." << std::endl;
            out << "  cut x   ---- erase {x} and relevant Records" << std::endl;
            out << "  spe x   ---- transform {x} with particular written reflection(not recommend)." << std::endl;
            out << "  grp x y ---- transform numeric type column {x}." << std::endl;
            out << "  cot x   ---- transform particular column as continuous attributes" << std::endl;
            out << "Significant options:" << std::endl;
            out << "  /i  ---- Input column ticks x rather than its name.(cut, spe, grp)" << std::endl;
            out << "  /s  ---- Input column name x rather than its ticks.(cut, spe, grp)" << std::endl;
        } else if (_in_word == "cut") {
            if (in.good()) in >> _in_word;
            else {
                out << "Func Error: cut requires ticks information." << std::endl;
                continue;
            }
            if (_in_word == "/s") {
                if (in.good()) {
                    in >> _in_word;
                    ssize_t index = 0;
                    for (; index != this->DArray->Column; ++index) {
                        if (_in_word == this->DArray->Column_Names[index]) break;
                    }
                    if (index == this->DArray->Column) {
                        out << "Name Error: Do not exist column named: " << _in_word << "." << std::endl;
                    } else {
                        cut(*this->DArray, index);
                        out << "Cutting for column \"" << _in_word << "\" has done." << std::endl;
                        out << "Column indexes rebuilt." << std::endl;
                        in.clear();
                        continue;
                    }
                } else out << "Func Error: cut requires ticks information." << std::endl;
                in.clear();
                continue;
            } else if (_in_word == "/i") {
                if (in.good()) {
                    try {
                        in >> _in_num;
                    } catch (...) {
                        out << "Func Error: this situation requires one integral type" << std::endl;
                        in.clear();
                        continue;
                    }
                    cut(*this->DArray, _in_num);
                    out << "Cutting for column " << _in_num << " has done." << std::endl;
                    out << "Column indexes rebuilt." << std::endl;
                    in.clear();
                    continue;
                } else {
                    out << "Func Error: this situation requires one integral type." << std::endl;
                    in.clear();
                    continue;
                }
            } else {
                out << "Input Error: Do not exist option named " << _in_word
                    << ".\nMaybe you can get assistance with \"help\"" << std::endl;
                in.clear();
                continue;
            }
        } else if (_in_word == "grp") {
            if (in.good()) in >> _in_word;
            else {
                out << "Func Error: grp requires ticks and numeric information." << std::endl;
                in.clear();
                continue;
            }
            ssize_t _in_num_plus = -1;
            if (_in_word == "/i") {
                if (in.good()) in >> _in_num;
                if (in.good()) in >> _in_num_plus;
                if (_in_num_plus == -1) {
                    out << "Func Error: this situation requires two integral type args." << std::endl;
                    in.clear();
                    continue;
                }
                grp(*this->DArray, _in_num, _in_num_plus);
                out << "Grouping for column " << _in_num << " has done." << std::endl;
                in.clear();
                continue;
            } else if (_in_word == "/s") {
                in >> _in_word;
                ssize_t index = 0;
                for (; index != this->DArray->Column; ++index) {
                    if (_in_word == this->DArray->Column_Names[index]) break;
                }
                if (index == this->DArray->Column) {
                    out << "Name Error: Do not exist column named: " << _in_word << "." << std::endl;
                } else {
                    if (in.good()) in >> _in_num_plus;
                    if (_in_num_plus == 1) {
                        out << "Grouping algorithm requires args #2 as one integral number";
                        in.clear();
                    }
                    grp(*this->DArray, index, _in_num_plus);
                    out << "Grouping for column named \"" << _in_word << "\" has done." << std::endl;
                    in.clear();
                }
            } else {
                out << "Input Error: Do not exist option named " << _in_word
                    << ".\nMaybe you can get assistance with \"help\"" << std::endl;
                in.clear();
            }
        } else if (_in_word == "spe") {
            if (in.good()) in >> _in_word;
            else {
                out << "Func Error: grp requires ticks and numeric information." << std::endl;
                in.clear();
                continue;
            }
            if (_in_word == "/i") {
                _in_num = -1;
                if (in.good()) in >> _in_num;
                if (_in_num == -1) {
                    out << "Func Error: this situation requires one positive integral type" << std::endl;
                    in.clear();
                    continue;
                } else {
                    auto _vec = column_set(*this->DArray, _in_num);
                    out << "To specialise column " << _in_num << ". Give unique orders to transform them: " << std::endl
                        << "String Contents: ";
                    std::copy(std::begin(_vec), std::end(_vec), std::ostream_iterator<std::string>(out, " "));
                    out << std::endl;
                    std::vector<size_t> _vec2(_vec.size(), 0);
                    std::copy(std::istream_iterator<size_t>(in), std::istream_iterator<size_t>(), std::begin(_vec2));
                    specialise(*this->DArray, _in_num, _vec, _vec2);
                    out << "Specialising for column " << _in_num << " has done." << std::endl;
                    in.clear();
                    continue;
                }
            } else if (_in_word == "/s") {
                in >> _in_word;
                ssize_t index = 0;
                for (; index != this->DArray->Column; ++index) {
                    if (_in_word == this->DArray->Column_Names[index]) break;
                }
                if (index == this->DArray->Column) {
                    out << "Name Error: Do not exist column named: " << _in_word << "." << std::endl;
                } else {
                    auto _vec = column_set(*this->DArray, index);
                    out << "To specialise column named \"" << _in_word << "\". Give unique orders to transform them: " << std::endl
                        << "String Contents: ";
                    std::copy(std::begin(_vec), std::end(_vec), std::ostream_iterator<std::string>(out, " "));
                    out << std::endl;
                    std::vector<size_t> _vec2(_vec.size(), 0);
                    std::copy(std::istream_iterator<size_t>(in), std::istream_iterator<size_t>(), std::begin(_vec2));
                    specialise(*this->DArray, index, _vec, _vec2);
                    out << "Specialising for column named \"" << _in_word << "\" has done." << std::endl;
                    in.clear();
                    continue;
                }
            } else {
                out << "Input Error: Do not exist option named " << _in_word
                    << ".\nMaybe you can get assistance with \"help\"." << std::endl;
                in.clear();
            }
        } else if (_in_word == "cot") {
            if (in.good()) in >> _in_word;
            else {
                out << "Func Error: grp requires ticks and numeric information." << std::endl;
                in.clear();
                continue;
            }
            if (_in_word == "/i") {
                _in_num = -1;
                if (in.good()) in >> _in_num;
                if (_in_num == -1) {
                    out << "Func Error: this situation requires one positive integral type" << std::endl;
                    in.clear();
                    continue;
                } else {
                    this->DArray->Continuous[_in_num] = true;
                    out << "Column " << _in_num << " is continuous now." << std::endl;
                    this->DArray->Done[_in_num] = true;
                    in.clear();
                    continue;
                }
            } else if (_in_word == "/s") {
                in >> _in_word;
                ssize_t index = 0;
                for (; index != this->DArray->Column; ++index) {
                    if (_in_word == this->DArray->Column_Names[index]) break;
                }
                if (index == this->DArray->Column) {
                    out << "Name Error: Do not exist column named: " << _in_word << "." << std::endl;
                } else {
                    this->DArray->Continuous[index] = true;
                    out << "Column name \"" << _in_word << "\" is continuous now." << std::endl;
                    this->DArray->Done[index] = true;
                    in.clear();
                    continue;
                }
            } else {
                out << "Input Error: Do not exist option named " << _in_word
                    << ".\nMaybe you can get assistance with \"help\"." << std::endl;
                in.clear();
            }
        } else if (_in_word == "push") {
            in.clear();
            if (this->DArray->Translation_Done) {
                this->Pushing_Pool_Interface(out, in);
                return;
            } else {
                out << "Input Error: Do not exist order named " << _in_word << ".\nMaybe you can get assistance with \"help\"." <<std::endl;
                in.clear();
                continue;
            }
        }
        else {
            out << "Input Error: Do not exist order named " << _in_word << ".\nMaybe you can get assistance with \"help\"." <<std::endl;
            in.clear();
            continue;
        }
    }
}

void DT_Interface::Pushing_Pool_Interface(std::ostream &out, std::istream &in)
{
    std::string _in_word;
    if (this->DArray== nullptr||!this->DArray->Translation_Done)
    {
        out << "Not ready to init one pool now. Back to establish phase now." << std::endl;
        this->DArray == nullptr ? this->File_Stream_Interface(out, in) : this->Pretreatment_Interface(out, in);
        return;
    } else {
        out << "Pushing reference symbols into data pool." << std::endl;
        this->DPool = new Decision_Tree_Pool {};
        this->DPool->Column_Names = this->DArray->Column_Names;
        this->DPool->Trans_Table = this->DArray->Trans_Table;
        this->DPool->Continuous = this->DArray->Continuous;
        out << "Select one item from column names as classification" << std::endl;
        out << "Assistance about existed column names: " << std::endl;
        std::copy(std::begin(this->DPool->Column_Names), std::end(this->DPool->Column_Names),
                  std::ostream_iterator<std::string>(out, " "));
        out << std::endl;
        in >> _in_word;
        auto _idx = string_to<ssize_t>(_in_word);
        this->DPool->Classification.resize(this->DArray->Row);
        for(size_t i=0; i!=this->DArray->Row; ++i)
        {
            this->DPool->Classification[i] = this->DArray->Chart[i][_idx] == 0? 0: 1;
        }
        cut(*this->DArray, _idx);
        this->DPool->Container = this->DArray->Chart;
        out << "\nPushing done. Original data has been casted" << std::endl;
        this->DArray = nullptr;
        out << "Automatic generating decision tree...";
        this->Tree_Generate_Interface(out, in);
    }
}

void DT_Interface::Tree_Generate_Interface(std::ostream &out, std::istream &in)
{
    out << "Decision Trees are formed by CART(Classification and Regression Tree) algorithm, \nwhich calculate "
           "minimum Value of Gini ticks of each decision tree." << std::endl;
    this->DPct = &Translation_Decoder(this->DPool->Trans_Table, this->DPool->Continuous);
    out << "Decision tree root is on the initialization now." << std::endl;
    std::vector<std::pair<ssize_t, ssize_t>*> _args {};
    std::vector<std::string*> _sockets {};
    std::vector<bool> _model {};
    _sockets.resize(this->DPct->_args.size());
    _model.resize(this->DPool->Classification.size());
    _args.resize(this->DPct->_args.size());
    for (size_t ri=0;ri!=this->DPool->Classification.size();++ri)
    {
        _model[ri] = this->DPool->Classification[ri] != 0;
    }
    for (size_t ri=0;ri!=this->DPct->_args.size();++ri)
    {
        _sockets[ri] = &this->DPct->_socket[ri];
        _args[ri] = &this->DPct->_args[ri];
    }
    this->Root = new DT_Node{this->DPct->_standard, _args, &this->DPool->Container,
                             _sockets, _model, this->DPct->_refer};
    out << "Decision tree root generated." << std::endl;
    gini_vec(*this->Root);
}


#endif //DATASTRUCTURE_MAIN_TUI_HPP
