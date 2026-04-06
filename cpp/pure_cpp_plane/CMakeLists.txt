cmake_minimum_required(VERSION 3.15)
project(python_cpp_profiler)
set(CMAKE_CXX_STANDARD 20)

set(Python3_ROOT_DIR "../../.venv")
find_package(Python 3.12 EXACT COMPONENTS Interpreter Development REQUIRED)

# Add Libraries
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/pybind11)

# Create Python extension module
pybind11_add_module(python_cpp_profiler
        src/profiler.cpp
        src/raw_cpp.cpp
)

target_include_directories(python_cpp_profiler PRIVATE ${CMAKE_SOURCE_DIR}/include)