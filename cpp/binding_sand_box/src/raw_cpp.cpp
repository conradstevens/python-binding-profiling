#include "raw_cpp.h"
#include <numeric>


float addition(const float x, const float y) {
    /** Addition function in cpp */
    return x + y;
}

float addition_three_times(const float x, const float y) {
    /** Addition function in cpp */
    float var = x + y;
    var /= 5;
    var *= 7;
    return var;
}

std::vector<unsigned long> fibonacci(const int n) {
    if (n <= 0) {
        return {};
    }
    if (n == 1) {
        return {0};
    }
    auto fib = std::vector<unsigned long>(n);
    fib[0] = 1;
    fib[1] = 2;
    for (int i = 2; i < n; ++i) {  // Changed <= to
        fib[i] = (fib[i - 2] + fib[i - 1]) / fib[i - 2];
    }
    return fib;
}

py::array_t<int64_t> fibonacci_numpy(const int n) {
    if (n == 0) {
        return py::array_t<int64_t>(0);
    }
    if (n == 1) {
        auto arr = py::array_t<int64_t>(1);
        arr.mutable_at(0) = 1;
        return arr;
    }

    auto fib = py::array_t<int64_t>(n);
    auto buf = fib.mutable_unchecked<1>();

    buf(0) = 1;
    buf(1) = 2;
    for (int i = 2; i < n; ++i) {
        buf(i) = (buf(i - 1) + buf(i - 2)) / buf(i - 2);
    }

    return fib;
}

MyClass::MyClass(const float x_, const float y_, const int n_) {
    x = x_;
    y = y_;
    n = n_;

    fib = py::array_t<int64_t>(n);
    fib_0 = py::array_t<int64_t>(0);
    fib_1 = py::array_t<int64_t>(1);
    fib_2 = py::array_t<int64_t>(2);
    fib_1.mutable_at(0) = 1;
    fib_2.mutable_at(0) = 1;
    fib_2.mutable_at(0) = 2;

    sum_arr = py::array_t<int64_t>(n);
}

[[nodiscard]] float MyClass::class_addition(const float x_, const float y_) const {
    return x + y + x_ + y_;
}

[[nodiscard]] float MyClass::class_addition_three_times(const float x_, const float y_) const {
    /** Addition function in cpp */
    float var = x_ + y_;
    var /= 5;
    var *= 7;
    return var;
}

[[nodiscard]] std::vector<unsigned long> MyClass::class_fibonacci(const int n_) const {
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

[[nodiscard]] py::array_t<int64_t> MyClass::class_fibonacci_numpy(const int n_) {
    if (n == 0) {
        return fib_0;
    }
    if (n == 1) {
        return fib_1;
    }

    auto buf = fib.mutable_unchecked<1>();

    buf(0) = 1;
    buf(1) = 2;
    for (int i = 2; i < n; ++i) {
        buf(i) = (buf(i - 1) + buf(i - 2)) / buf(i - 2);
    }
    return fib;
}

[[nodiscard]] int64_t MyClass::class_sum_range(const int n_) const {
    if (n_ <= 0) {
        return 0;
    }
    int64_t total = 0;
    for (int i = 1; i <= n_; ++i) {
        total += i;
    }
    return total;
}

[[nodiscard]] int64_t MyClass::class_sum_range_numpy(const int n_) const {
    if (n <= 0) {
        return 0;
    }
    auto* data = sum_arr.mutable_data();

    // Efficiently fill array with values 1 to n using std::iota
    std::iota(data, data + n, int64_t{1});

    // Sum using std::accumulate
    return std::accumulate(data, data + n, int64_t{0});
}

PYBIND11_MODULE(pybind11_bindings, m) {
    m.doc() = "pybind11 functions and classes for profiling";
    m.def("addition", &addition, "Pybind11 function that adds two floats");
    m.def("addition_three_times", &addition_three_times, "Pybind11 function that adds, divides and multiplies two floats");
    m.def("fibonacci", &fibonacci, "Pybind11 function that returns list of fibonacci numbers");
    m.def("fibonacci_numpy", &fibonacci_numpy, py::call_guard<py::gil_scoped_release>(), "Returns list of fibonacci numbers");

    py::class_<MyClass>(m, "MyClass")
        .def(py::init<const float &, const float &, const int &>())
        .def("class_addition", &MyClass::class_addition)
        .def("class_addition_three_times", &MyClass::class_addition_three_times)
        .def("class_fibonacci", &MyClass::class_fibonacci)
        .def("class_fibonacci_numpy", &MyClass::class_fibonacci_numpy)
        .def("class_sum_range", &MyClass::class_sum_range)
        .def("class_sum_range_numpy", &MyClass::class_sum_range_numpy);
}