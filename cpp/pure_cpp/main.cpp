#include <iostream>
#include "profiler.h"


int main() {
    Profiler profiler(
    1000,
    1000,
    100,
    99.0,
    100.0,
    1000,
    "Pure CPP"
    );

    profiler.profile_funcs();

    return 0;
}