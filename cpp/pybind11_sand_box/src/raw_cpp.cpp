#include "raw_cpp.h"


float addition(const float x, const float y) {
    /** Addition function in cpp */
    return x + y;
}


float addition_three_times(const float x, const float y) {
    /** Addition function in cpp */
    float var = x + y;
    var /= x + 5;
    var *= y + 7;
    return var;
}


std::vector<unsigned long> fibonacci(const int n) {
    /** Return std::move fibonacci sequence n long as vector
     * (deviding by index - 1 to limit number size) */
    if (n <= 0) {
        return {};
    }
    if (n == 1) {
        return {1};
    }
    if (n == 2) {
        return {1, 2};
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
    /** Return std::move fibonacci sequence n long as nanobind
     * numpy array type (deviding by index - 1 to limit number
     * size) */
    if (n == 0) {
        return py::array_t<int64_t>(0);
    }

    auto fib = py::array_t<int64_t>(n);
    if (n == 1) {
        fib.mutable_at(0) = 1;
        return fib;
    }

    if (n == 2) {
        fib.mutable_at(0) = 1;
        fib.mutable_at(1) = 2;
        return fib;
    }

    auto buf = fib.mutable_unchecked<1>();
    buf(0) = 1;
    buf(1) = 2;
    for (int i = 2; i < n; ++i) {
        buf(i) = (buf(i - 1) + buf(i - 2)) / buf(i - 2);
    }

    return fib;
}


MyClass::MyClass(const float x_, const float y_, const size_t n_) {
    /** Initialization of addition variables */
    x = x_;
    y = y_;
    n = n_;

    /** Allocate memory and fixed balues for fibonacci arrays */
    fib_vec = std::vector<unsigned long>(n);
    fib_vec_0 = std::vector<unsigned long>();
    fib_vec_1 = std::vector<unsigned long>{1};
    fib_vec_2 = std::vector<unsigned long>{1, 2};
    fib = py::array_t<int64_t>(n);
    fib_0 = py::array_t<int64_t>(0);
    fib_1 = py::array_t<int64_t>(1);
    fib_2 = py::array_t<int64_t>(2);
    fib_1.mutable_at(0) = 1;
    fib_2.mutable_at(0) = 1;
    fib_2.mutable_at(0) = 2;
}

[[nodiscard]] float MyClass::class_addition(const float x_, const float y_) const {
    return x + y + x_ + y_;
}

[[nodiscard]] float MyClass::class_addition_three_times(const float x_, const float y_) const {
    /** Addition function in cpp */
    float var = x_ + y_;
    var /= x_ + 5;
    var *= y_ + 7;
    return var;
}

[[nodiscard]] std::vector<unsigned long> MyClass::class_fibonacci() {
    if (n == 0) {
        return fib_vec_0;
    }
    if (n == 1) {
        return fib_vec_1;
    }
    if (n == 2) {
        return fib_vec_2;
    }
    fib_vec[0] = 1;
    fib_vec[1] = 2;
    for (int i = 2; i < n; ++i) {
        fib_vec[i] = (fib_vec[i - 2] + fib_vec[i - 1]) / fib_vec[i - 2];
    }
    return fib_vec;
}

[[nodiscard]] py::array_t<int64_t> MyClass::class_fibonacci_numpy() {
    if (n == 0) {
        return fib_0;
    }
    if (n == 1) {
        return fib_1;
    }
    if (n == 2) {
        return fib_2;
    }

    auto buf = fib.mutable_unchecked<1>();

    buf(0) = 1;
    buf(1) = 2;
    for (int i = 2; i < n; ++i) {
        buf(i) = (buf(i - 1) + buf(i - 2)) / buf(i - 2);
    }
    return fib;
}


PYBIND11_MODULE(pybind11_bindings, m) {
    m.doc() = "pybind11 functions and classes for profiling";
    m.def("addition", &addition, "Pybind11 function that adds two floats");
    m.def("addition_three_times", &addition_three_times, "Pybind11 function that adds, divides and multiplies two floats");
    m.def("fibonacci", &fibonacci, "Pybind11 function that returns list of fibonacci numbers");
    m.def("fibonacci_numpy", &fibonacci_numpy, "Returns list of fibonacci numbers");

    py::class_<MyClass>(m, "MyClass")
        .def(py::init<const float &, const float &, const int &>())
        .def("class_addition", &MyClass::class_addition)
        .def("class_addition_three_times", &MyClass::class_addition_three_times)
        .def("class_fibonacci", &MyClass::class_fibonacci)
        .def("class_fibonacci_numpy", &MyClass::class_fibonacci_numpy);
}