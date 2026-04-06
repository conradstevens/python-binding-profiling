#ifndef PURE_CPP_PROFILER_H
#define PURE_CPP_PROFILER_H

#include <pybind11/pybind11.h>  // Needed for python
#include <pybind11/stl.h>  // Needed for python
#include <pybind11/numpy.h>

#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <chrono>
#include <type_traits>
#include "raw_cpp.h"

namespace py = pybind11;

class Profiler {
    size_t num_trials;
    size_t fib_num;
    size_t burner_trials;

    double x;
    double y;

    template<class ReturnType, class ... Args>
        double profile_function(const std::string& func_name, ReturnType (*func)(Args...), Args... args);

    template<typename ReturnType, typename... Args>
        double profile_function(const std::string &func_name, const MyClass& my_class,
            ReturnType (MyClass::*func)(Args...) const, Args... args);

    template<typename T, typename... Args>
        double profile_function(std::string const& func_name, Args... args);

    template<typename ReturnType>
        double profile_function(const std::string &func_name, MyClass& my_class,
            ReturnType (MyClass::*func)());

public:
    std::string header;
    py::dict profile_results{};

    Profiler(
        size_t num_trials_,
        size_t fib_num_,
        size_t burner_trials_,
        double x_,
        double y_,
        std::string header_
        );

    void print_heading();

    void profile();
};

#endif //PURE_CPP_PROFILER_H