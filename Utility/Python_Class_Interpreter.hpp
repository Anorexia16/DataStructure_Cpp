#ifndef DATASTRUCTURE_PYTHON_CLASS_INTERPRETER_HPP
#define DATASTRUCTURE_PYTHON_CLASS_INTERPRETER_HPP

#include <map>
#include <string>
#include <functional>

struct standard_class_lib {
    std::map<std::string, void*> built_in{};

    void *operator[](std::string const &) {
        return nullptr;
    }
};

template<class sub_class>
struct Py_Class {
    template<typename I, typename ...args>
    void def(std::string const &name, I(*func)(args...)) {
        class_method.built_in[name] = static_cast<void*>(func);
    }

    Py_Class &operator=(Py_Class const &) noexcept = default;
    Py_Class &operator=(Py_Class &&) noexcept = default;
    Py_Class(Py_Class const &) noexcept = default;
    Py_Class(Py_Class &&) noexcept = default;
    explicit Py_Class(sub_class const &sc):heap{}, dev{}, cs{sc} {}
    explicit Py_Class(sub_class &&sc): heap{}, dev{}, cs{std::move(sc)} {}

private:
    Py_Class() = default;
    std::map<std::string, void*> heap;
    std::map<std::string, short> dev;
    static standard_class_lib class_method;
    sub_class cs{};
};

#endif //DATASTRUCTURE_PYTHON_CLASS_INTERPRETER_HPP
