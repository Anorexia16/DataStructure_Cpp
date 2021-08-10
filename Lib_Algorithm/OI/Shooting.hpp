#ifndef DATASTRUCTURE_SHOOTING_HPP
#define DATASTRUCTURE_SHOOTING_HPP

#include <vector>
#include <array>
#include <random>
#include <iostream>

struct One {
    long long id {};
    long double turns {};
};

template<long long num, long long turns>
std::array<One, num> exp() {
    std::vector<long long> alive, model;
    std::array<One, num> dead{};
    for (long long i=0;i!=num;++i) dead[i].id = i;
    model.reserve(num);
    for(long long i=0;i!=num;++i) model.template emplace_back(i);

    std::random_device rd;
    std::default_random_engine e {rd()};
    std::uniform_int_distribution<long long> ud;
    long long dev, unlucky;
    for (long long i=0;i!=turns;++i) {
        alive = model;
        dev = 0;
        for (long long j=0;j!=num;++j) {
            ud = *new std::uniform_int_distribution<long long> (0, (num-1-dev)/2);
            unlucky = 2*ud(e);
            dead[alive[unlucky]].turns = i==0? j:(dead[alive[unlucky]].turns*i+j)/(i+1);
            alive.erase(alive.begin()+unlucky);
            ++dev;
        }
    }
    return dead;
}

#endif //DATASTRUCTURE_SHOOTING_HPP
