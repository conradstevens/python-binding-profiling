#ifndef RAW_CPP_H
#define RAW_CPP_H

#include <vector>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/stl/vector.h>

namespace nb = nanobind;

// Function declarations
float addition(float x, float y);

float addition_three_times(float x, float y);

std::vector<float> fibonacci(size_t n);

nb::ndarray<nb::numpy, float> fibonacci_numpy(size_t n);


class MyClass {

    std::vector<float> fib_vec;
    std::vector<float> fib_vec_0;
    std::vector<float> fib_vec_1;
    std::vector<float> fib_vec_2;

    float* fib_arr;
    float fib_0_arr[0] = {};
    float fib_1_arr[1] = {1};
    float fib_2_arr[2] = {1, 2};
    nb::ndarray<nb::numpy, float> fib;
    nb::ndarray<nb::numpy, float> fib_0;
    nb::ndarray<nb::numpy, float> fib_1;
    nb::ndarray<nb::numpy, float> fib_2;

public:
    float x;
    float y;
    size_t n;

    // Constructor
    MyClass(float x_, float y_, size_t n_);

    // Member functions
    [[nodiscard]] float class_addition(float x_, float y_) const;

    [[nodiscard]] float class_addition_three_times(float x_, float y_) const;

    [[nodiscard]] std::vector<float> class_fibonacci();

    [[nodiscard]] nb::ndarray<nb::numpy, float> class_fibonacci_numpy();

    ~MyClass();
};

#endif // RAW_CPP_H