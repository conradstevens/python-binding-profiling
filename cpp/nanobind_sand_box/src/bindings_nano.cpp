#include "bindings_nano.h"


double addition(const double x, const double y) {
    /** Addition function in cpp */
    return x + y;
}


double addition_three_times(const double x, const double y) {
    /** Addition function in cpp */
    double var = x + y;
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


nb::ndarray<nb::numpy, double> fibonacci_numpy(const size_t n) {
    /** Return std::move fibonacci sequence n long as nanobind
     * numpy array type (deviding by index - 1 to limit number
     * size) */
    if (n == 0) {
        return nb::ndarray<nb::numpy, double>(nullptr, {0});
    }
    const auto c_arr = new double[n];
    const nb::capsule owner(c_arr, [](void* p) noexcept {
        delete[] static_cast<double*>(p);
    });

    c_arr[0] = 1;
    if (n == 1) {
        return nb::ndarray<nb::numpy, double>(c_arr, {1}, owner);
    }

    c_arr[1] = 2;
    if (n == 2) {
        return nb::ndarray<nb::numpy, double>(c_arr, {2}, owner);
    }

    for (size_t i = 2; i < n; ++i) {
        c_arr[i] = (c_arr[i - 1] + c_arr[i - 2]) / static_cast<double>(n) * static_cast<double>(i);
    }

    return nb::ndarray<nb::numpy, double>(c_arr, {n}, owner);
}


MyClass::MyClass(const double x_, const double y_, const size_t n_) {
    /** Initialization of addition variables */
    x = x_;
    y = y_;
    n = n_;

    _fib_l = nb::list();
    for (size_t i = 0; i < n; ++i) _fib_l.append(0.0);

    if (n > 0) {
        auto* data = new double[n]();
        nb::capsule owner(data, [](void* p) noexcept {
            delete[] static_cast<double*>(p);
        });
        _fib_arr = nb::ndarray<nb::numpy, double>(data, {n}, owner);
    } else {
        _fib_arr = nb::ndarray<nb::numpy, double>(nullptr, {0});
    }
}

[[nodiscard]] double MyClass::class_addition(const double x_, const double y_) const {
    return x + y + x_ + y_;
}

[[nodiscard]] double MyClass::class_addition_three_times(const double x_, const double y_) const {
    /** Addition function in cpp */
    double var = x_ + y_;
    var /= 5;
    var *= 7;
    return var;
}

[[nodiscard]] nb::list& MyClass::class_fibonacci() {

    if (n <= 0) {
        return _fib_l;
    }

    _fib_l[0] = nb::float_(1.0);

    if (n > 1) {
        _fib_l[1] = nb::float_(2.0);
        for (size_t i = 2; i < n; ++i) {
            _fib_l[i] = nb::float_(
                (nb::cast<double>(_fib_l[i - 1]) + nb::cast<double>(_fib_l[i - 2]))
                / static_cast<double>(n) * static_cast<double>(i));
        }
    }

    return _fib_l;
}

nb::ndarray<nb::numpy, double>& MyClass::class_fibonacci_numpy() {
    if (n <= 0) {
        return _fib_arr;
    }

    double* data = _fib_arr.data();
    data[0] = 1.0;

    if (n > 1) {
        data[1] = 2.0;
        for (size_t i = 2; i < n; ++i) {
            data[i] = (data[i - 1] + data[i - 2]) /
                static_cast<double>(n) * static_cast<double>(i);
        }
    }

    return _fib_arr;
}

NB_MODULE(nano_bindings, m) {
    m.doc() = "Nanobind functions and classes for profiling";
    m.def("addition", &addition, "Nanobind, Addition");
    m.def("addition_three_times", &addition_three_times, "Nanobind function that adds, divides and multiplies two floats");
    m.def("fibonacci", &fibonacci, "Pybind11 function that returns list of fibonacci numbers");
    m.def("fibonacci_numpy", &fibonacci_numpy, "Nanobind, returns list of fibonacci numbers");

    nb::class_<MyClass>(m, "MyClass")
        .def(nb::init<const double, const double, const size_t>())
        .def_rw("x", &MyClass::x)
        .def_rw("y", &MyClass::y)
        .def_rw("n", &MyClass::n)

        .def_rw("_fib_l", &MyClass::_fib_l)
        .def_prop_ro("_fib_arr", [](MyClass& self) {
            return nb::ndarray<nb::numpy, double>(
                self._fib_arr.data(), {self._fib_arr.shape(0)},
                nb::find(self));
        })

        .def("class_addition", &MyClass::class_addition)
        .def("class_addition_three_times", &MyClass::class_addition_three_times)
        .def("class_fibonacci", &MyClass::class_fibonacci)
        .def("class_fibonacci_numpy", &MyClass::class_fibonacci_numpy);
}