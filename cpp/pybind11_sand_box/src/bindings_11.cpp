#include "bindings_11.h"


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


std::vector<double> fibonacci(const size_t n) {
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
    auto fib = std::vector<double>(n);
    fib[0] = 1;
    fib[1] = 2;
    for (size_t i = 2; i < n; ++i) {
        fib[i] = (fib[i - 1] + fib[i - 2]) / static_cast<double>(n) * static_cast<double>(i);
    }
    return fib;
}


py::array_t<double> fibonacci_numpy(const size_t n) {
    /** Return std::move fibonacci sequence n long as nanobind
     * numpy array type (deviding by index - 1 to limit number
     * size) */
    if (n == 0) {
        return py::array_t<double>(0);
    }

    auto fib = py::array_t<double>(n);
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
    for (ssize_t i = 2; i < n; ++i) {
        buf[i] = (buf[i - 1] + buf[i - 2]) / static_cast<double>(n) * static_cast<double>(i);
    }

    return fib;
}


MyClass::MyClass(const float x_, const float y_, const size_t n_) {
    /** Initialization of addition variables */
    x = x_;
    y = y_;
    n = n_;

    /** Allocate memory and fixed values for fibonacci arrays */
    _fib_l = py::list(n);
    _fib_arr = py::array_t<double>(n);
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

[[nodiscard]] py::list& MyClass::class_fibonacci() {
    if (n <= 0) {
        return _fib_l;
    }

    _fib_l[0] = 1.0;

    if (n > 1) {
        _fib_l[1] = 2.0;
        for (ssize_t i = 2; i < n; ++i) {
            _fib_l[i] = (py::cast<double>(_fib_l[i - 1]) + py::cast<double>(_fib_l[i - 2])) /
                static_cast<double>(n) * static_cast<double>(i);
        }
    }

    return _fib_l;
}

[[nodiscard]] py::array_t<double>& MyClass::class_fibonacci_numpy() {
    if (n <= 0) {
        return _fib_arr;
    }

    auto buf = _fib_arr.mutable_unchecked<1>();
    buf(0) = 1;

    if (n > 1) {
        buf(1) = 2;
        for (ssize_t i = 2; i < n; ++i) {
            buf[i] = (buf[i - 1] + buf[i - 2]) / static_cast<double>(n) * static_cast<double>(i);
        }
    }
    return _fib_arr;
}


PYBIND11_MODULE(pybind11_bindings, m) {
    m.doc() = "pybind11 functions and classes for profiling";
    m.def("addition", &addition, "Pybind11 function that adds two floats");
    m.def("addition_three_times", &addition_three_times, "Pybind11 function that adds, divides and multiplies two floats");
    m.def("fibonacci", &fibonacci, "Pybind11 function that returns list of fibonacci numbers function that returns list of fibonacci numbers");
    m.def("fibonacci_numpy", &fibonacci_numpy, "Pybind11, returns list of fibonacci numbers");

    py::class_<MyClass>(m, "MyClass")
        .def(py::init<const float &, const float &, const size_t &>())
        .def_readwrite("x", &MyClass::x)
        .def_readwrite("y", &MyClass::y)
        .def_readwrite("_fib_l", &MyClass::_fib_l)
        .def_readwrite("_fib_arr", &MyClass::_fib_arr)
        .def("class_addition", &MyClass::class_addition)
        .def("class_addition_three_times", &MyClass::class_addition_three_times)
        .def("class_fibonacci", &MyClass::class_fibonacci, py::return_value_policy::reference_internal)
        .def("class_fibonacci_numpy", &MyClass::class_fibonacci_numpy, py::return_value_policy::reference_internal);
}