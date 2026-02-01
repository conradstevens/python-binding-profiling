#include <raw_cpp.h>

float addition(const float x, const float y) {
    return x + y;
}

float addition_three_times(const float x, const float y) {
    float var = x + y;
    var /= 5;
    var *= 7;
    return var;
}

std::vector<unsigned long> fibonacci(const size_t n) {
    if (n == 0) {
        return {};
    }
    if (n == 1) {
        return {1};
    }
    auto fib = std::vector<unsigned long>(n);
    fib[0] = 1;
    fib[1] = 2;
    for (int i = 2; i < n; i++) {
        fib[i] = fib[i-2] + fib[i - 1] / fib[i - 2];
    }
    return fib;
}

MyClass::MyClass(const float x_, const float y_, const size_t n_) {
    x = x_;
    y = y_;
    n = n_;

    fib = std::vector<unsigned long>(n);
    fib_0 = std::vector<unsigned long>(0);
    fib_1 = std::vector<unsigned long>{1};
    fib_2 = std::vector<unsigned long>{1, 2};

    sum_arr = std::vector<unsigned long>(n);
}

float MyClass::class_addition(const float x_, const float y_) const {
    return x + y + x_ + y_;
}

float MyClass::class_addition_three_times(const float x_, const float y_) const {
    /** Addition function in cpp */
    float var = x_ + y_;
    var /= 5;
    var *= 7;
    return var;
}

std::vector<unsigned long> MyClass::class_fibonacci(const size_t n_) const {
    const int n_var = n;
    if (n_var == 0) {
        return {};
    }
    if (n_var == 1) {
        return {0};
    }
    auto fib = std::vector<unsigned long>(n_var);
    fib[0] = 1;
    fib[1] = 2;
    for (int i = 2; i < n_var; ++i) {
        fib[i] = (fib[i - 2] + fib[i - 1]) / fib[i - 2];
    }
    return fib;
}
