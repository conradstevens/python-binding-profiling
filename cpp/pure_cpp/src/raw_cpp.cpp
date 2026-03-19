#include <raw_cpp.h>

double addition(const double x, const double y) {
    return x + y;
}

double addition_three_times(const double x, const double y) {
    double var = x + y;
    var /= 5;
    var *= 7;
    return var;
}

std::vector<size_t> fibonacci(const size_t n) {
    if (n == 0) {
        return {};
    }
    auto fib = std::vector<size_t>(n);
    fib[0] = 1;

    if (n > 1) {
        fib[1] = 2;
        if (n > 2) {
            for (int i = 2; i < n; i++) {
                fib[i] = (fib[i-1] + fib[i - 2]) / n * i;
            }
        }
    }
    return fib;
}

MyClass::MyClass(const double x_, const double y_, const size_t n_) {
    x = x_;
    y = y_;
    n = n_;

    _fib_arr = std::vector<size_t>(n);
}

double MyClass::class_addition(const double x_, const double y_) const {
    return x + y + x_ + y_;
}

double MyClass::class_addition_three_times(const double x_, const double y_) const {
    /** Addition function in cpp */
    double var = x_ + y_;
    var /= 5;
    var *= 7;
    return var;
}

std::vector<size_t>* MyClass::class_fibonacci() {
    if (n == 0) {
        return &_fib_arr;
    }
    _fib_arr[0] = 1;

    if (n > 1) {
        _fib_arr[1] = 2;
        if (n > 2) {
            for (int i = 2; i < n; i++) {
                _fib_arr[i] = (_fib_arr[i-1] + _fib_arr[i - 2]) / n * i;
            }
        }
    }
    return &_fib_arr;
}
