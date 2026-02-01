#include "profiler.h"
#include <chrono>


Profiler::Profiler(
    const size_t num_trials_,
    const size_t fib_num_,
    const size_t burner_trials_,
    const float x_,
    const float y_,
    const size_t n_,
    std::string heading_
    ) {
    num_trials = num_trials_;
    fib_num = fib_num_;
    burner_trials = burner_trials_;

    x = x_;
    y = y_;
    n = n_;

    heading = heading_;
}

void Profiler::print_heading() {

    // Print starting hashes
    winsize w{};
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    size_t width = w.ws_col > 0 ? w.ws_col : 80;


    std::cout << std:: endl;
    auto print_hashes = [width]() -> void {
        std::cout << std::string(width, '#') << std::endl;
    };

    print_hashes();

    // Print middle line
    size_t hash_len_pad = width - heading.length();  // deducting word length
    hash_len_pad = hash_len_pad - 2;         // adding padding
    hash_len_pad = hash_len_pad / 2;

    std::cout << std::string(hash_len_pad, '-') << ' ' << heading << ' ';

    if (hash_len_pad * 2 + heading.length() + 2 < width) {
         std::cout << std::string(hash_len_pad + 1, '-') << std::endl;
    } else {
        std::cout << std::string(hash_len_pad, '-') << std::endl;
    }

    print_hashes();
}

void Profiler::profile_funcs() {
    print_heading();
    MyClass my_class(x, y, n);
    profile_function("addition", addition, x, y);
    profile_function("addition_three_times", addition_three_times, x, y);
    profile_function("fibonacci", fibonacci, n);
    profile_function<MyClass>("MyClass", x, y, n);
    profile_function("class_addition", my_class, &MyClass::class_addition, x, y);
    profile_function("class_addition_three_times", my_class, &MyClass::class_addition_three_times, x, y);
    profile_function("class_addition_three_times", my_class, &MyClass::class_fibonacci, n);
}

template<typename ReturnType, typename... Args>
void Profiler::profile_function(std::string const& func_name, ReturnType (*func)(Args...), Args... args) {
    volatile ReturnType* dummy_var_p = nullptr;

    for (size_t i = 0; i < burner_trials; i++) {
        ReturnType dummy_var = func(args...);
        dummy_var_p = &dummy_var;
    }

    auto duration = std::chrono::nanoseconds(0);

    for (size_t i = 0; i < num_trials; i++) {
        auto start = std::chrono::high_resolution_clock::now();
        ReturnType dummy_var = std::move(func(args...));
        auto end = std::chrono::high_resolution_clock::now();
        dummy_var_p = &dummy_var;
        duration += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    }

    std::cout << std::fixed << std::setprecision(5) << func_name << ": " << duration.count() * 1e-9 << std::endl;
}

template<typename ReturnType, typename... Args>
void Profiler::profile_function(const std::string &func_name, const MyClass& my_class,
    ReturnType (MyClass::*func)(Args...) const, Args... args) {
    volatile ReturnType* dummy_var_p = nullptr;

    for (size_t i = 0; i < burner_trials; i++) {
        ReturnType dummy_var = (my_class.*func)(args...);
        dummy_var_p = &dummy_var;
    }

    auto duration = std::chrono::nanoseconds(0);

    for (size_t i = 0; i < num_trials; i++) {
        auto start = std::chrono::high_resolution_clock::now();
        ReturnType dummy_var = std::move((my_class.*func)(args...));
        auto end = std::chrono::high_resolution_clock::now();
        dummy_var_p = &dummy_var;
        duration += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    }

    std::cout << std::fixed << std::setprecision(5) << func_name << ": " << duration.count() * 1e-9 << std::endl;
}

template<typename T, typename... Args>
void Profiler::profile_function(std::string const& func_name, Args... args) {
    volatile T* dummy_var_p = nullptr;
    for (size_t i = 0; i < burner_trials; i++) {
        T dummy_var = T(args...);
        dummy_var_p = &dummy_var;
    }

    auto duration = std::chrono::nanoseconds(0);

    for (size_t i = 0; i < num_trials; i++) {
        auto start = std::chrono::high_resolution_clock::now();
        T dummy_var = std::move(T(args...));
        auto end = std::chrono::high_resolution_clock::now();
        dummy_var_p = &dummy_var;
        duration += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    }

    std::cout << std::fixed << std::setprecision(5) << func_name << ": " << duration.count() * 1e-9 << std::endl;
}