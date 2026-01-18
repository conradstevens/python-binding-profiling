#include <iostream>

float loc_add(float x, float y) {
    return x + y;
}

class Profiler {
    unsigned int num_trials;
    int fib_num;
    float x;
    float y;

    public:
    Profiler(const unsigned int num_trials_, const int fib_num_, const float x_, const float y_) {
        num_trials = num_trials_;
        fib_num = fib_num_;
        x = x_;
        y = y_;
    }

    void profile_func() {

    }

};


int main() {
    std::cout << "Hello, World!" << std::endl;




    return 0;
}