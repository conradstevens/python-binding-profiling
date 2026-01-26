#ifndef PURE_CPP_PURE_CPP_H
#define PURE_CPP_PURE_CPP_H

#include <vector>

// Function declarations
float addition(float x, float y);

float addition_three_times(float x, float y);

std::vector<unsigned long> fibonacci(int n);

class MyClass {
    std::vector<unsigned long> fib;
    std::vector<unsigned long> fib_0;
    std::vector<unsigned long> fib_1;
    std::vector<unsigned long> fib_2;
    std::vector<unsigned long> sum_arr;

public:
    float x;
    float y;
    int n;

    // Constructor
    MyClass(float x_, float y_, int n_);

    [[nodiscard]] float class_addition( float x_, float y_) const;

    [[nodiscard]] float class_addition_three_times( float x_, float y_) const;

    [[nodiscard]] std::vector<unsigned long> class_fibonacci(int  n_) const;

};


#endif