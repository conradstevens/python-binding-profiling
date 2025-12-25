#ifndef RAW_CPP_H
#define RAW_CPP_H

#include <vector>
#include <pybind11/pybind11.h>  // Needed for python
#include <pybind11/stl.h>  // Needed for python
#include <pybind11/numpy.h>

namespace py = pybind11;

// Function declarations
float addition(float x, float y);

float addition_three_times(float x, float y);

std::vector<unsigned long> fibonacci(int n);

py::array_t<int64_t> fibonacci_numpy(int n);

// Class declaration
class MyClass {
    py::array_t<int64_t> fib;
    py::array_t<int64_t> fib_0;
    py::array_t<int64_t> fib_1;
    py::array_t<int64_t> fib_2;

public:
    float x;
    float y;
    int n;

    // Constructor
    MyClass(float x_, float y_, int n_);

    // Member functions
    [[nodiscard]] float class_addition(float x_, float y_) const;

    [[nodiscard]] float class_addition_three_times(float x_, float y_) const;

    [[nodiscard]] std::vector<unsigned long> class_fibonacci(int n_) const;

    [[nodiscard]] py::array_t<int64_t> class_fibonacci_numpy(int n_);
};

#endif // RAW_CPP_H