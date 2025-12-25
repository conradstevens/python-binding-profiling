# include<iostream>
#include "profile.h"


void print_header() {
    for(int i = 0; i < 80; i++) {
        std::cout << "#";
    }
    std::cout << std::endl;

    for(int i = 0; i < (80 - 20) / 2; i++) {
        std::cout << "-";
    }
    std::cout << " RAW CPP ";
    for(int i = 0; i < (80 - 20) / 2; i++) {
        std::cout << "-";
    }
    std::cout << std::endl;

    for(int i = 0; i < 80; i++) {
        std::cout << "#";
    }
    std::cout << std::endl;
}