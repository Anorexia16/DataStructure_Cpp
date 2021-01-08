#ifndef DATASTRUCTURE_INFINITY_CALCULATIONS_C_HPP
#define DATASTRUCTURE_INFINITY_CALCULATIONS_C_HPP

#include "../Structure/Chain_Bidirectional_Circle.hpp"
#include <iostream>
#include <utility>
#include <cmath>


using namespace std::rel_ops;
size_t const MAX_LEN = 30;
enum class Sign {
    pos, neg
};

class Infinity_Calculator_C {
public:
    explicit Infinity_Calculator_C(long const &x = 0);

    explicit Infinity_Calculator_C(ChainBC<long> const &, Sign const &);

    Infinity_Calculator_C(Infinity_Calculator_C const &);

    Infinity_Calculator_C reverse();

    Infinity_Calculator_C &reverse_r();

    Infinity_Calculator_C operator+(Infinity_Calculator_C const &);

    Infinity_Calculator_C operator-(Infinity_Calculator_C const &);

    Infinity_Calculator_C operator*(Infinity_Calculator_C const &);

    Infinity_Calculator_C operator/(Infinity_Calculator_C const &);

    Infinity_Calculator_C operator%(Infinity_Calculator_C const &);

    Infinity_Calculator_C &operator+=(Infinity_Calculator_C const &);

    Infinity_Calculator_C &operator-=(Infinity_Calculator_C const &);

    Infinity_Calculator_C &operator*=(Infinity_Calculator_C const &);

    Infinity_Calculator_C &operator/=(Infinity_Calculator_C const &);

    Infinity_Calculator_C &operator%=(Infinity_Calculator_C const &);

    Infinity_Calculator_C &operator=(Infinity_Calculator_C const &);

    bool operator==(Infinity_Calculator_C const &) const;

    bool operator>(Infinity_Calculator_C const &) const;

    bool operator<(Infinity_Calculator_C const &) const;

    friend std::ostream &operator<<(std::ostream &out, Infinity_Calculator_C const &op);

private:
    static inline bool abs_greater(Infinity_Calculator_C const &, Infinity_Calculator_C const &);

    static long const Node_Limit = 10000;

    inline void Sign_Chain_Checker();

    ChainBC<long> Storage;

    Sign Sign_Register;
};


Infinity_Calculator_C::Infinity_Calculator_C(long const &x) :
        Storage{ChainBC < long > {MAX_LEN}} {
    Sign_Register = x >= 0 ? Sign::pos : Sign::neg;
    long const Ax = std::abs(x);
    if (Ax < Node_Limit) {
        Storage.insert(0, x);
    } else if (Ax > Node_Limit && Ax < std::pow(Node_Limit, 2)) {
        Storage.insert(0, x / Node_Limit);
        Storage.insert(0, x % Node_Limit);
    } else {
        Storage.insert(0, x / std::pow(Node_Limit, 2));
        Storage.insert(0, (x / Node_Limit) % Node_Limit);
        Storage.insert(0, x % Node_Limit);
    }
}

Infinity_Calculator_C::Infinity_Calculator_C(ChainBC<long> const &op, Sign const &s)
        : Storage{op}, Sign_Register{s} {}


Infinity_Calculator_C::Infinity_Calculator_C(Infinity_Calculator_C const &op)
        : Storage{op.Storage} { Sign_Register = op.Sign_Register; }

Infinity_Calculator_C &Infinity_Calculator_C::operator=(Infinity_Calculator_C const &op) = default;

Infinity_Calculator_C Infinity_Calculator_C::reverse() {
    return Infinity_Calculator_C{this->Storage, this->Sign_Register == Sign::pos ? Sign::neg : Sign::pos};
}

Infinity_Calculator_C &Infinity_Calculator_C::reverse_r() {
    this->Sign_Register = this->Sign_Register == Sign::pos ? Sign::neg : Sign::pos;
    return *this;
}

void Infinity_Calculator_C::Sign_Chain_Checker() {
    NodeB_Iter<long> check_iterator{this->Storage.head()};
    NodeB_Iter<long> checker_flag{this->Storage.head()};

    for (; check_iterator->next_ptr() != this->Storage.head(); ++check_iterator) {
        if (check_iterator->next().value_c() != 0) checker_flag = check_iterator;
    }
    if (checker_flag == this->Storage.head()) {
        this->Storage = ChainBC<long>(50);
        this->Storage.insert(0, 0);
    }
    if (checker_flag->next_ptr() != this->Storage.head()) {
        checker_flag->link_after(*this->Storage.head());
        this->Storage.head()->link_front(*checker_flag);
        size_t size = 0;
        NodeB_Iter<long> size_iterator{this->Storage.head()};
        for (; size_iterator->next_ptr() != this->Storage.head(); ++size_iterator, size += 1) {}
        this->Storage.resize(size);
    }
}

bool Infinity_Calculator_C::operator==(Infinity_Calculator_C const &op) const {
    if (this->Sign_Register != op.Sign_Register) return false;
    if (this->Storage.size() != op.Storage.size()) return false;
    NodeB_Iter<long> iterator_4this = this->Storage.head_c()->next_ptr();
    NodeB_Iter<long> iterator_4op = op.Storage.head_c()->next_ptr();
    for (; iterator_4this != this->Storage.head_c(); ++iterator_4this, ++iterator_4op) {
        if (iterator_4this.value_c() != iterator_4op.value_c()) return false;
    }
    return true;
}

bool Infinity_Calculator_C::abs_greater(Infinity_Calculator_C const &op1, Infinity_Calculator_C const &op2) {
    if (op1.Storage.size() > op2.Storage.size()) return true;
    if (op1.Storage.size() < op2.Storage.size()) return false;

    NodeB<long> *iterator_r4op1 = op1.Storage.head_c()->prev_ptr();
    NodeB<long> *iterator_r4op2 = op2.Storage.head_c()->prev_ptr();
    for (; iterator_r4op1 != op1.Storage.head_c() && iterator_r4op2 != op2.Storage.head_c();
           --iterator_r4op1, --iterator_r4op2) {
        if (iterator_r4op1->value_c() > iterator_r4op2->value_c()) return true;
        else if (iterator_r4op1->value_c() < iterator_r4op2->value_c()) return false;
    }
    return false;
}

bool Infinity_Calculator_C::operator>(Infinity_Calculator_C const &op) const {
    if (this->Sign_Register == Sign::pos && op.Sign_Register == Sign::neg) return true;
    if (this->Sign_Register == Sign::neg && op.Sign_Register == Sign::pos) return false;
    return Infinity_Calculator_C::abs_greater(*this, op);
}

bool Infinity_Calculator_C::operator<(Infinity_Calculator_C const &op) const {
    if (this->Sign_Register == Sign::neg && op.Sign_Register == Sign::pos) return true;
    if (this->Sign_Register == Sign::pos && op.Sign_Register == Sign::neg) return false;
    return !Infinity_Calculator_C::abs_greater(*this, op);
}

Infinity_Calculator_C Infinity_Calculator_C::operator+(Infinity_Calculator_C const &op) {
    if (this->Sign_Register == Sign::pos && op.Sign_Register == Sign::pos) {
        ChainBC<long> Container{MAX_LEN};
        NodeB_Iter<long> iterator_4this{this->Storage.head_c()->next_ptr()};
        NodeB_Iter<long> iterator_4op{op.Storage.head_c()->next_ptr()};
        NodeB_Iter<long> iterator_link = Container.head();
        bool Carry_Flag = false;
        long temp;

        for (; iterator_4this != this->Storage.head_c() && iterator_4op != op.Storage.head_c();
               ++iterator_4this, ++iterator_4op, ++iterator_link) {
            temp = (*iterator_4this)() + (*iterator_4op)() + (Carry_Flag ? 1 : 0);
            Carry_Flag = temp > Node_Limit;
            iterator_link->link_after(*new NodeB<long>(temp % Node_Limit, &iterator_link, iterator_link->next_ptr()));
            iterator_link->next_ptr()->next().link_front(iterator_link->next());
        }

        if (iterator_4this != this->Storage.head_c()) {
            for (; iterator_4this != this->Storage.head_c(); ++iterator_4this) {
                temp = iterator_4this.value_c() + (Carry_Flag ? 1 : 0);
                Carry_Flag = temp > Node_Limit;
                iterator_link->link_after(
                        *new NodeB<long>{temp % Node_Limit, &iterator_link, iterator_link->next_ptr()});
                iterator_link->next_ptr()->next().link_front(iterator_link->next());
                ++iterator_link;
            }
        } else if (iterator_4op != op.Storage.head_c()) {
            for (; iterator_4op != op.Storage.head_c(); ++iterator_4op) {
                temp = iterator_4op.value_c() + (Carry_Flag ? 1 : 0);
                Carry_Flag = temp > Node_Limit;
                iterator_link->link_after(
                        *new NodeB<long>{temp % Node_Limit, &iterator_link, iterator_link->next_ptr()});
                iterator_link->next_ptr()->next().link_front(iterator_link->next());
                ++iterator_link;
            }
        }
        if (Carry_Flag) {
            iterator_link->link_after(*new NodeB<long>{1, &iterator_link, iterator_link->next_ptr()});
            iterator_link->next_ptr()->next().link_front(iterator_link->next());
        }

        return Infinity_Calculator_C(Container, Sign::pos);
    } else if (this->Sign_Register == Sign::pos && op.Sign_Register == Sign::neg) {
        return *this
        Infinity_Calculator_C No_Limits_Calculator_L(op.Storage, Sign::pos);
    } else if (this->Sign_Register == Sign::neg && op.Sign_Register == Sign::pos) {
        return (const_cast<Infinity_Calculator_C &>(op)
        No_Limits_Calculator_L
        No_Limits_Calculator_L(op.Storage, Sign::pos)).reverse();
    } else {
        Infinity_Calculator_C temp{this->Storage, Sign::pos};
        return (temp
        Infinity_Calculator_C No_Limits_Calculator_L(op.Storage, Sign::pos)).reverse();
    }
}

Infinity_Calculator_C &Infinity_Calculator_C::operator+=(Infinity_Calculator_C const &op) {
    if (this->Sign_Register == Sign::pos && op.Sign_Register == Sign::pos) {
        NodeB_Iter<long> iterator_4this{this->Storage.head_c()->next_ptr()};
        NodeB_Iter<long> iterator_4op{op.Storage.head_c()->next_ptr()};
        bool Carry_Flag = false;

        for (; iterator_4this != this->Storage.head_c() && iterator_4op != op.Storage.head_c();
               ++iterator_4this, ++iterator_4op) {
            (*iterator_4this)() += iterator_4op.value_c() + (Carry_Flag ? 1 : 0);
            Carry_Flag = iterator_4this.value_c() > Node_Limit;
            (*iterator_4this)() = iterator_4this.value_c() % Node_Limit;
        }

        if (iterator_4this != this->Storage.head_c()) {
            for (; iterator_4this != this->Storage.head_c(); ++iterator_4this) {
                (*iterator_4this)() += (Carry_Flag ? 1 : 0);
                Carry_Flag = (*iterator_4this)() > Node_Limit;
                (*iterator_4this)() = iterator_4this.value_c() % Node_Limit;
            }
        } else if (iterator_4op != op.Storage.head_c()) {
            for (; iterator_4op != op.Storage.head_c(); ++iterator_4op) {
                iterator_4this->link_after(*new NodeB<long>{iterator_4op.value_c() + (Carry_Flag ? 1 : 0) % Node_Limit,
                                                            &iterator_4this, iterator_4this->next_ptr()});
                Carry_Flag = iterator_4this->next().value_c() > Node_Limit;
                iterator_4this->next_ptr()->next().link_front(iterator_4this->next());
                ++iterator_4this;
            }
        }
        if (Carry_Flag) {
            iterator_4this->link_after(*new NodeB<long>{1, &iterator_4this, iterator_4this->next_ptr()});
            iterator_4this->next_ptr()->next().link_front(iterator_4this->next());
        }

        return *this;
    } else if (this->Sign_Register == Sign::pos && op.Sign_Register == Sign::neg) {
        return *this -= Infinity_Calculator_C(op.Storage, Sign::pos);
    } else if (this->Sign_Register == Sign::neg && op.Sign_Register == Sign::pos) {
        return (*this -= Infinity_Calculator_C(op.Storage, Sign::pos)).reverse_r();
    } else {
        this->reverse_r();
        return (*this += *new Infinity_Calculator_C(op.Storage, Sign::pos)).reverse_r();
    }
}

Infinity_Calculator_C Infinity_Calculator_C::operator-(Infinity_Calculator_C const &op) {
    if (this->Sign_Register == Sign::pos && op.Sign_Register == Sign::pos) {
        if (this->abs_greater(*this, op)) {
            ChainBC<long> Container{MAX_LEN};
            NodeB_Iter<long> iterator_4this{this->Storage.head_c()->next_ptr()};
            NodeB_Iter<long> iterator_4op{op.Storage.head_c()->next_ptr()};
            NodeB_Iter<long> iterator_link{Container.head()};
            bool Carry_Flag = false;
            long temp;

            for (; iterator_4this != this->Storage.head_c() && iterator_4op != op.Storage.head_c();
                   ++iterator_4this, ++iterator_4op, ++iterator_link) {
                temp = iterator_4this.value_c() - iterator_4op.value_c() - (Carry_Flag ? 1 : 0);
                Carry_Flag = iterator_4this.value_c() < 0;
                iterator_link->link_after(*new NodeB<long>{Carry_Flag ? temp + Node_Limit : temp, &iterator_link,
                                                           iterator_link->next_ptr()});
                iterator_link->next_ptr()->next().link_front(iterator_link->next());
            }
            if (iterator_4this != this->Storage.head_c()) {
                for (; iterator_4this != this->Storage.head_c(); ++iterator_4this) {
                    temp = iterator_4this.value_c() - (Carry_Flag ? 1 : 0);
                    Carry_Flag = temp < 0;
                    iterator_link->link_after(*new NodeB<long>{Carry_Flag ? temp + Node_Limit : temp, &iterator_link,
                                                               iterator_link->next_ptr()});
                    iterator_link->next_ptr()->next().link_front(iterator_link->next());
                    iterator_link = iterator_link->next_ptr();
                }
            }

            Infinity_Calculator_C result{Container, Sign::pos};
            result.Sign_Chain_Checker();
            return result;
        } else if (*this == op) {
            return Infinity_Calculator_C{0};
        } else {
            ChainBC<long> Container{MAX_LEN};
            NodeB<long> *iterator_4this = this->Storage.head_c()->next_ptr();
            NodeB<long> *iterator_4op = op.Storage.head_c()->next_ptr();
            NodeB<long> *iterator_link = Container.head();
            bool Carry_Flag = false;
            long temp;

            for (; iterator_4this != this->Storage.head_c() && iterator_4op != op.Storage.head_c();
                   iterator_4this = iterator_4this->next_ptr(), iterator_4op = iterator_4op->next_ptr(), iterator_link = iterator_link->next_ptr()) {

            }

            Infinity_Calculator_C result{Container, Sign::neg};
            result.Sign_Chain_Checker();
            return result;
        }
    } else if (this->Sign_Register == Sign::pos && op.Sign_Register == Sign::neg) {
        return *this
        Infinity_Calculator_C No_Limits_Calculator_L(op.Storage, Sign::pos);
    } else if (this->Sign_Register == Sign::neg && op.Sign_Register == Sign::pos) {
        return (*this
        No_Limits_Calculator_L
        No_Limits_Calculator_L(op.Storage, Sign::pos)).reverse();
    } else {
        Infinity_Calculator_C temp{this->Storage, Sign::pos};
        return (temp
        Infinity_Calculator_C No_Limits_Calculator_L(op.Storage, Sign::pos)).reverse();
    }
}

Infinity_Calculator_C &Infinity_Calculator_C::operator-=(Infinity_Calculator_C const &op) {
    if (this->Sign_Register == Sign::pos && op.Sign_Register == Sign::pos) {
        return *new Infinity_Calculator_C(0);
    } else if (this->Sign_Register == Sign::pos && op.Sign_Register == Sign::neg) {
        return *this += Infinity_Calculator_C(op.Storage, Sign::pos);
    } else if (this->Sign_Register == Sign::neg && op.Sign_Register == Sign::pos) {
        return (*this += Infinity_Calculator_C(op.Storage, Sign::pos)).reverse_r();
    } else {
        Infinity_Calculator_C temp{this->Storage, Sign::pos};
        return (temp -= *new Infinity_Calculator_C(op.Storage, Sign::pos)).reverse_r();
    }
}

Infinity_Calculator_C Infinity_Calculator_C::operator*(Infinity_Calculator_C const &op) {
    Infinity_Calculator_C Result(ChainBC < long > {MAX_LEN},
                                 this->Sign_Register == op.Sign_Register ? Sign::pos : Sign::neg);

    return Result;
}

Infinity_Calculator_C &Infinity_Calculator_C::operator*=(Infinity_Calculator_C const &op) {
    this->Sign_Register = this->Sign_Register == op.Sign_Register ? Sign::pos : Sign::neg;
    return *this;
}

Infinity_Calculator_C Infinity_Calculator_C::operator/(Infinity_Calculator_C const &op) {
    Infinity_Calculator_C Result(ChainBC < long > {MAX_LEN},
                                 this->Sign_Register == op.Sign_Register ? Sign::pos : Sign::neg);

    return Result;
}

Infinity_Calculator_C &Infinity_Calculator_C::operator/=(Infinity_Calculator_C const &op) {

    this->Sign_Register = this->Sign_Register == op.Sign_Register ? Sign::pos : Sign::neg;
    return *this;
}

Infinity_Calculator_C Infinity_Calculator_C::operator%(Infinity_Calculator_C const &op) {
    Infinity_Calculator_C Result(ChainBC < long > {MAX_LEN},
                                 this->Sign_Register == op.Sign_Register ? Sign::pos : Sign::neg);

    return Result;
}

Infinity_Calculator_C &Infinity_Calculator_C::operator%=(Infinity_Calculator_C const &op) {

    this->Sign_Register = this->Sign_Register == op.Sign_Register ? Sign::pos : Sign::neg;
    return *this;
}

std::ostream &operator<<(std::ostream &out, Infinity_Calculator_C const &op) {
    out << (op.Sign_Register == Sign::pos ? "+" : "-");
    NodeB_Iter<long> iterator{op.Storage.head_c()->prev_ptr()};
    for (; iterator != op.Storage.head_c(); --iterator) {
        if ((*iterator)() == 0) std::cout << "0000";
        else out << (*iterator)();
    }
    out << std::endl;
    return out;
}

#endif //DATASTRUCTURE_INFINITY_CALCULATIONS_C_HPP

