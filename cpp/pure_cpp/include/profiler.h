#ifndef PURE_CPP_PROFILER_H
#define PURE_CPP_PROFILER_H

#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include "raw_cpp.h"

class Profiler {
    size_t num_trials;
    size_t fib_num;
    size_t burner_trials;

    float x;
    float y;
    size_t n;

    std::string heading;

    void print_heading();

    template<class ReturnType, class ... Args>
        void profile_function(const std::string& func_name, ReturnType (*func)(Args...), Args... args);

    template<typename ReturnType, typename... Args>
        void profile_function(const std::string &func_name, const MyClass& my_class,
            ReturnType (MyClass::*func)(Args...) const, Args... args);

    template<typename T, typename... Args>
        void profile_function(std::string const& func_name, Args... args);

public:
    Profiler(
        size_t num_trials_,
        size_t fib_num_,
        size_t burner_trials_,
        float x_,
        float y_,
        size_t n_,
        std::string heading_
        );

    void profile_funcs();
};

#endif //PURE_CPP_PROFILER_H