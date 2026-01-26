#include <iostream>
#include "profiler.h"


int main() {
    std::cout << "Hello, World!" << std::endl;

    Profiler profiler(
    1000,
    1000,
    100,
    99,
    100,
    1000,
    "Pure CPP"
    );

    profiler.profile_func();

    return 0;
}