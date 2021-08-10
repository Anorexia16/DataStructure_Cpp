#ifndef DATASTRUCTURE_CONCURRENT_HPP
#define DATASTRUCTURE_CONCURRENT_HPP
#include <functional>
#include <atomic>

template<typename I, class...args>
class synchronized_joint: std::function<I(args...)> {
public:
    explicit synchronized_joint(I(*)(args...));

    I operator()(args const &...) override;

    decltype(auto) func_getter();
private:
    I (*func)(args...);
    std::atomic_flag mutex;
};

template<typename I, class... args>
synchronized_joint<I, args...>::synchronized_joint(I (*func)(args...))
:func{func}, mutex{} {}

template<typename I, class... args>
decltype(auto) synchronized_joint<I, args...>::func_getter() {
    return func;
}

template<typename I, class... args>
I synchronized_joint<I, args...>::operator()(const args &...vars) {
    while(mutex.test_and_set());
    I _ans = func(vars...);
    mutex.clear();
    return _ans;
}

template<typename I, class...args>
std::function<I(args...)> *synchronized(std::function<I(args...)> *func) {
    auto *ptr = new synchronized_joint<I, args...> {*func};
    return dynamic_cast<std::function<I(args...)>>(ptr);
}

#endif //DATASTRUCTURE_CONCURRENT_HPP
