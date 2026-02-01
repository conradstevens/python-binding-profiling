#include <iostream>
#include "profiler.h"


int main(int argc, char* argv[]) {

    size_t NUM_TRIALS;
    size_t FIBONACCI_NUMBER;
    size_t BURNER_TRIALS;

    if (argc < 4) {
        std::cerr << "[ERROR] " << "Requires arguments of type `size_t`: "
                                     "\n --num-trials\n --fibonacci-number\n --burner-trials \n";
        exit(1);
    }

    for (size_t i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "--num-trials") {
            NUM_TRIALS = std::stoi(argv[i + 1]);
        } else if (std::string(argv[i]) == "--fibonacci-number") {
            FIBONACCI_NUMBER = std::stoi(argv[i + 1]);
        } else if (std::string(argv[i]) == "--burner-trials") {
            BURNER_TRIALS = std::stoi(argv[i + 1]);
        }
    }

    Profiler profiler(
    NUM_TRIALS,
    FIBONACCI_NUMBER,
    BURNER_TRIALS,
    99.0,
    100.0,
    1000,
    "Pure CPP"
    );

    profiler.profile_funcs();

    return 0;
}