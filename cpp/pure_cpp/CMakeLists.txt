cmake_minimum_required(VERSION 3.15)
project(pure_cpp)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(pure_cpp
        main.cpp
        src/raw_cpp.cpp
        src/profiler.cpp
        include/raw_cpp.h
        include/profiler.h
)
