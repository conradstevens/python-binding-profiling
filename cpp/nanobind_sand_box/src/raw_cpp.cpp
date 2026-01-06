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
        return {0};
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


nb::ndarray<nb::numpy, int64_t> fibonacci_numpy(const int n) {
    if (n == 0) {
        return nb::ndarray<nb::numpy, int64_t>(nullptr, {0});
    }
    const auto c_arr = new int64_t[n];
    nb::capsule owner(c_arr, [](void* p) noexcept {
        delete[] static_cast<int64_t*>(p);
    });

    c_arr[0] = 1;
    if (n == 1) {
        return nb::ndarray<nb::numpy, int64_t>(c_arr, {1}, owner);
    }

    c_arr[1] = 2;
    if (n == 2) {
        return nb::ndarray<nb::numpy, int64_t>(c_arr, {2}, owner);
    }

    for (size_t i = 2; i < n; ++i) {
        c_arr[i] = (c_arr[i - 2] + c_arr[i - 1]) / c_arr[i - 2];
    }

    return nb::ndarray<nb::numpy, int64_t>(c_arr, {static_cast<size_t>(n)}, owner);
}


MyClass::MyClass(const float x_, const float y_, const size_t n_) {
    x = x_;
    y = y_;
    n = n_;

    fib_vec = std::vector<unsigned long>(n);
    fib_vec_0 = std::vector<unsigned long>();
    fib_vec_1 = std::vector<unsigned long>{1};
    fib_vec_2 = std::vector<unsigned long>{1, 2};

    fib_arr = new int64_t[n]{1, 2};
    fib = nb::ndarray<nb::numpy, int64_t>(fib_arr, {n});

    fib_sum_arr = new int64_t[n]{1, 2};
    fib = nb::ndarray<nb::numpy, int64_t>(fib_sum_arr, {n});

    fib_0 = nb::ndarray<nb::numpy, int64_t>(fib_0_arr, {});
    fib_1 = nb::ndarray<nb::numpy, int64_t>(fib_1_arr, {1});
    fib_2 = nb::ndarray<nb::numpy, int64_t>(fib_2_arr, {2});
}

MyClass::~MyClass() {
    delete[] fib_arr;
    delete[] fib_sum_arr;
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

nb::ndarray<nb::numpy, int64_t> MyClass::class_fibonacci_numpy() {
    if (n == 0) {
        return fib_0;
    }
    if (n == 1) {
        return fib_1;
    }
    if (n == 2) {
        return fib_2;
    }
    for (int i = 2; i < n; ++i) {
        fib_arr[i] = ((fib_arr[i-1] + fib_arr[i-2]) / fib_arr[i-1]);
    }
    return fib;
}

NB_MODULE(nano_bindings, m) {
    m.doc() = "Nanobind functions and classes for profiling";
    m.def("addition", &addition, "Nanobind, Addition");
    m.def("addition_three_times", &addition_three_times, "Nanobind ,3 opperations addiotion, division subreaction");
    m.def("fibonacci", &fibonacci, "Nanobind, fibonacci sequence to n");
    m.def("fibonacci_numpy", &fibonacci_numpy, "Nanobind, fibonacci sequence to n using numpy");

    nb::class_<MyClass>(m, "MyClass")
        .def(nb::init<const float, const float, const size_t>())
        .def("class_addition", &MyClass::class_addition)
        .def("class_addition_three_times", &MyClass::class_addition_three_times)
        .def("class_fibonacci", &MyClass::class_fibonacci)
        .def("class_fibonacci_numpy", &MyClass::class_fibonacci_numpy);
}