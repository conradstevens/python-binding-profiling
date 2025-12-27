cmake_minimum_required(VERSION 3.15)
project(binding_sand_box)
set(CMAKE_CXX_STANDARD 20)

find_package(Python 3.12 COMPONENTS Interpreter Development REQUIRED)
# Add Libraries
add_subdirectory(lib/pybind11)
include_directories(${pybind11_INCLUDE_DIRS})

include_directories(${CMAKE_SOURCE_DIR}/include)

pybind11_add_module(pybind11_bindings src/raw_cpp.cpp)

# Add Executable
add_executable(binding_sand_box main.cpp src/profile.cpp src/raw_cpp.cpp)

target_link_libraries(binding_sand_box PRIVATE pybind11::embed)