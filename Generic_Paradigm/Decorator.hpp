#ifndef DATASTRUCTURE_DECORATOR_HPP
#define DATASTRUCTURE_DECORATOR_HPP

#include <functional>
#include <ctime>
#include <future>

enum class Decorator_Method {
    Operator_Class,
    Member_Map_Class,
    Signal_Conversion,
    Void_None_Functional,
    Conversion_Type_Function,
};

template<size_t ...>
struct Sequence {
};

template<size_t N, size_t ...S>
struct Index_Builder : Index_Builder<N - 1, N - 1, S...> {};

template<size_t ...S>
struct Index_Builder<0, S...>
{
    typedef Sequence<S...> type;
};

template<size_t N> using Index_Builder = typename Index_Builder<N>::type;

namespace Decorator_Builder
{
    template<typename dec_type, typename var_type, typename ...Args>
    class Decorator_TC_Active
    {
    public:
        Decorator_TC_Active(std::function<dec_type(var_type, Args...)> const &, std::tuple<Args...> const &);

        dec_type at(var_type const &);

    private:
        Decorator_Method const property = Decorator_Method::Signal_Conversion;

        template<size_t ...N>
        dec_type operator()(var_type const &, Sequence<N...> const &);

        std::function<dec_type(var_type, Args...)> const Func;

        std::tuple<Args...> Vars;
    };

    template<typename dec_type, typename var_type, typename... Args>
    Decorator_TC_Active<dec_type, var_type, Args...>::Decorator_TC_Active(
            std::function<dec_type(var_type, Args...)> const &func,
            const std::tuple<Args...> &tuple)
            :Func{func}, Vars{tuple} {}

    template<typename dec_type, typename var_type, typename... Args>
    dec_type Decorator_TC_Active<dec_type, var_type, Args...>::at(const var_type &Conversed_Parameters)
    {
        return this->operator()(Conversed_Parameters, Index_Builder<sizeof...(Args)>());
    }

    template<typename dec_type, typename var_type, typename... Args>
    template<size_t ...N>
    dec_type
    Decorator_TC_Active<dec_type, var_type, Args...>::operator()(const var_type &op, Sequence<N...> const &)
    {
        return this->Func(op, std::get<N>(this->Vars)...);
    }

    template<typename dec_type, typename var_type, typename ...Args>
    class Decorator_TC_Native
    {
    public:
        explicit Decorator_TC_Native(std::function<dec_type(var_type, Args...)>);

        Decorator_TC_Native &at(var_type const &);

        dec_type when(Args...);

    private:
        Decorator_Method const Property = Decorator_Method::Signal_Conversion;

        template<size_t ...N, typename...inner_args>
        dec_type operator()(std::tuple<inner_args...> const &, Sequence<N...> const &);

        std::function<dec_type(var_type, Args...)> const Func;

        var_type Value;
    };

    template<typename dec_type, typename var_type, typename... Args>
    Decorator_TC_Native<dec_type, var_type, Args...>::Decorator_TC_Native(
            std::function<dec_type(var_type, Args...)> func) :
            Func{func}, Value{var_type{}} {}

    template<typename dec_type, typename var_type, typename... Args>
    Decorator_TC_Native<dec_type, var_type, Args...> &
    Decorator_TC_Native<dec_type, var_type, Args...>::at(var_type const &Conversed_Parameters)
    {
        this->Value = Conversed_Parameters;
        return *this;
    }

    template<typename dec_type, typename var_type, typename... Args>
    dec_type Decorator_TC_Native<dec_type, var_type, Args...>::when(Args ...args)
    {
        return this->template operator()(std::make_tuple(args...), Index_Builder<sizeof...(Args)>());
    }

    template<typename dec_type, typename var_type, typename... Args>
    template<size_t... N, typename... inner_args>
    dec_type Decorator_TC_Native<dec_type, var_type, Args...>::operator()(const std::tuple<inner_args...> &tuple,
                                                                          const Sequence<N...> &)
    {
        return this->Func(this->Value, std::get<N>(tuple)...);
    }
}

template<typename dec_type, typename var_type, typename ...Args>
Decorator_Builder::Decorator_TC_Active<dec_type, var_type, Args...>
Decorate(std::function<dec_type(var_type const &, Args const &...)> const &func, Args...args)
{
    auto params = std::make_tuple(args...);
    return Decorator_Builder::Decorator_TC_Active<dec_type, var_type, Args...>(func, params);
}

template<typename dec_type, typename var_type, typename ...Args>
Decorator_Builder::Decorator_TC_Active<dec_type, var_type, Args...>
Decorate(dec_type (*func_ptr)(var_type const &, Args const &...), Args...args)
{
    auto params = std::make_tuple(args...);
    return Decorator_Builder::Decorator_TC_Active<dec_type, var_type, Args...>(
            std::function<dec_type(var_type, Args...)>{func_ptr}, params);
}

template<typename dec_type, typename var_type, typename ...Args>
Decorator_Builder::Decorator_TC_Native<dec_type, var_type, Args...>
Decorate(std::function<dec_type(var_type const &, Args const &...)> const &func)
{
    return Decorator_Builder::Decorator_TC_Native<dec_type const &, var_type, Args...>(func);
}

template<typename dec_type, typename var_type, typename ...Args>
Decorator_Builder::Decorator_TC_Native<dec_type, var_type, Args...>
Decorate(dec_type (*func_ptr)(var_type const &, Args const &...))
{
    return Decorator_Builder::Decorator_TC_Native<dec_type, var_type, Args...>
            {std::function<dec_type(var_type const &, Args...)>{func_ptr}};
}

template<typename func_return, typename ...Args>
double record_v(std::function<func_return(Args const &...)> const &func, Args ...args)
{
    clock_t start, end;
    start = clock();
    func(args...);
    end = clock();
    return static_cast<double>(end - start) / (CLOCKS_PER_SEC);
}

template<typename func_return, typename ...Args>
double record_v(func_return (*func)(Args const &...), Args ...args)
{
    clock_t start, end;
    start = clock();
    func(args...);
    end = clock();
    return static_cast<double>(end - start) / (CLOCKS_PER_SEC);
}


#endif //DATASTRUCTURE_DECORATOR_HPP
