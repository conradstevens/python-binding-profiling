#ifndef PURE_CPP_PROFILER_H
#define PURE_CPP_PROFILER_H

#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>

class Profiler {
    size_t num_trials;
    size_t fib_num;
    size_t burner_trials;

    float x;
    float y;
    size_t n;

    std::string heading;

    void print_heading();

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

    void profile_func();
};

#endif //PURE_CPP_PROFILER_H