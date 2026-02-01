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

std::vector<float> fibonacci(size_t n);

py::array_t<float> fibonacci_numpy(size_t n);

// Class declaration
class PYBIND11_EXPORT MyClass {
    std::vector<float> fib_vec;
    std::vector<float> fib_vec_0;
    std::vector<float> fib_vec_1;
    std::vector<float> fib_vec_2;
    py::array_t<float> fib;
    py::array_t<float> fib_0;
    py::array_t<float> fib_1;
    py::array_t<float> fib_2;

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

    [[nodiscard]] py::array_t<float> class_fibonacci_numpy();

};

#endif // RAW_CPP_H