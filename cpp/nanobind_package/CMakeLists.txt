cmake_minimum_required(VERSION 3.15)
project(nanobind_package)
set(CMAKE_CXX_STANDARD 20)

set(Python3_ROOT_DIR "../../.venv")

if (CMAKE_VERSION VERSION_LESS 3.18)
    set(DEV_MODULE Development)
else()
    set(DEV_MODULE Development.Module)
endif()

find_package(Python 3.12 COMPONENTS Interpreter ${DEV_MODULE} REQUIRED)

# Add libraries
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/nanobind)

# Create Python extension module
nanobind_add_module(nanobind_package NOMINSIZE src/bindings_nano.cpp)

target_include_directories(nanobind_package PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)