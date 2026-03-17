#ifndef RAW_CPP_H
#define RAW_CPP_H

#include <vector>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/stl/vector.h>

namespace nb = nanobind;

// Function declarations
double addition(double x, double y);

double addition_three_times(double x, double y);

std::vector<double> fibonacci(size_t n);

nb::ndarray<nb::numpy, double> fibonacci_numpy(size_t n);


class MyClass {
public:
    double x;
    double y;
    size_t n;

    nb::list _fib_l;
    nb::ndarray<nb::numpy, double> _fib_arr;

    // Constructor
    MyClass(double x_, double y_, size_t n_);

    // Member functions
    [[nodiscard]] double class_addition(double x_, double y_) const;

    [[nodiscard]] double class_addition_three_times(double x_, double y_) const;

    [[nodiscard]] nb::list& class_fibonacci();

    [[nodiscard]] nb::ndarray<nb::numpy, double>& class_fibonacci_numpy();
};

#endif // RAW_CPP_H