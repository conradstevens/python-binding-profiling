#ifndef RAW_CPP_H
#define RAW_CPP_H

#include <vector>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>

namespace nb = nanobind;

// Function declarations
float addition(float x, float y);

float addition_three_times(float x, float y);

std::vector<unsigned long> fibonacci(int n);

nb::ndarray<nb::numpy, int64_t> fibonacci_numpy(int n);


class MyClass {

    std::vector<unsigned long> fib_vec;
    std::vector<unsigned long> fib_vec_0;
    std::vector<unsigned long> fib_vec_1;
    std::vector<unsigned long> fib_vec_2;

    int64_t* fib_arr;
    int64_t fib_0_arr[0] = {};
    int64_t fib_1_arr[1] = {1};
    int64_t fib_2_arr[2] = {1, 2};
    int64_t* fib_sum_arr;
    nb::ndarray<nb::numpy, int64_t> fib;
    nb::ndarray<nb::numpy, int64_t> sum_arr;
    nb::ndarray<nb::numpy, int64_t> fib_0;
    nb::ndarray<nb::numpy, int64_t> fib_1;
    nb::ndarray<nb::numpy, int64_t> fib_2;

public:
    float x;
    float y;
    size_t n;

    // Constructor
    MyClass(float x_, float y_, size_t n_);

    // Member functions
    [[nodiscard]] float class_addition(float x_, float y_) const;

    [[nodiscard]] float class_addition_three_times(float x_, float y_) const;

    [[nodiscard]] std::vector<unsigned long> class_fibonacci();

    [[nodiscard]] nb::ndarray<nb::numpy, int64_t> class_fibonacci_numpy();

    // [[nodiscard]] int64_t class_sum_range_numpy(int n_);

    ~MyClass();
};

#endif // RAW_CPP_H