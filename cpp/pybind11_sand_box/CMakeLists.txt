cmake_minimum_required(VERSION 3.15)
project(binding_sand_box)
set(CMAKE_CXX_STANDARD 20)

find_package(Python 3.12 COMPONENTS Interpreter Development REQUIRED)

# Add Libraries
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/pybind11)

# Create Python extension module
pybind11_add_module(pybind11_bindings src/bindings_11.cpp)

target_include_directories(pybind11_bindings PRIVATE ${CMAKE_SOURCE_DIR}/include)