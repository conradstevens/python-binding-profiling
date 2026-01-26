#include "profiler.h"

#include <utility>


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

void Profiler::profile_func() {
    print_heading();
}
