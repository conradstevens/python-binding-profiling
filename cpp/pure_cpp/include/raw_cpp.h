#ifndef PURE_CPP_PURE_CPP_H
#define PURE_CPP_PURE_CPP_H

#include <vector>

// Function declarations
[[nodiscard]] double addition(double x, double y);

[[nodiscard]] double addition_three_times(double x, double y);

[[nodiscard]] std::vector<size_t> fibonacci(size_t n);

class MyClass {
public:
    double x;
    double y;
    size_t n;
    std::vector<size_t> _fib_arr;

    // Constructor
    MyClass(double x_, double y_, size_t n_);

    [[nodiscard]] double class_addition( double x_, double y_) const;

    [[nodiscard]] double class_addition_three_times( double x_, double y_) const;

    [[nodiscard]] std::vector<size_t>* class_fibonacci();

};


#endif