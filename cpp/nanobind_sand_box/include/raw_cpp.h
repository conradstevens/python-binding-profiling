#ifndef RAW_CPP_H
#define RAW_CPP_H

#include <vector>
#include <numeric>
#include <nanobind/nanobind.h>
#include <nanobind/stl/vector.h>
#include <nanobind/ndarray.h>

namespace nb = nanobind;

// Function declarations
float addition(float x, float y);

float addition_three_times(float x, float y);

std::vector<unsigned long> fibonacci(int n);

nb::ndarray<nb::numpy, int64_t> fibonacci_numpy(int n);


// Class declaration
//class MyClass {
//    nb::ndarray<nb::numpy, int64_t> fib;
//    nb::ndarray<nb::numpy, int64_t> fib_0;
//    nb::ndarray<nb::numpy, int64_t> fib_1;
//    nb::ndarray<nb::numpy, int64_t> fib_2;
//    nb::ndarray<nb::numpy, int64_t> sum_arr;
//
//public:
//    float x;
//    float y;
//    int n;
//
//    // Constructor
//    MyClass(float x_, float y_, int n_);
//
//    // Member functions
//    [[nodiscard]] float class_addition(float x_, float y_) const;
//
//    [[nodiscard]] float class_addition_three_times(float x_, float y_) const;
//
//    [[nodiscard]] std::vector<unsigned long> class_fibonacci(int n_) const;
//
//    [[nodiscard]] nb::ndarray<nb::numpy, int64_t> class_fibonacci_numpy(int n_);
//
//    [[nodiscard]] int64_t class_sum_range(int n_) const;
//
//    [[nodiscard]] int64_t class_sum_range_numpy(int n_);
//};

#endif // RAW_CPP_H