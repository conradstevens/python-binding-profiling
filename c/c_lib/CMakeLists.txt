cmake_minimum_required(VERSION 3.18)
set(CMAKE_C_STANDARD 11)
project(c_lib C)


find_package(Python3 3.12 COMPONENTS Interpreter Development REQUIRED)

Python3_add_library(c_lib MODULE library.c)
