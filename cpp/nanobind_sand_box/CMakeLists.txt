cmake_minimum_required(VERSION 3.15)
project(nanobind_sand_box)
set(CMAKE_CXX_STANDARD 20)


if (CMAKE_VERSION VERSION_LESS 3.18)
    set(DEV_MODULE Development)
else()
    set(DEV_MODULE Development.Module)
endif()

find_package(Python 3.9 COMPONENTS Interpreter ${DEV_MODULE} REQUIRED)

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Add libraries
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/nanobind)

# Create Python extension module
nanobind_add_module(nano_bindings NOMINSIZE src/raw_cpp.cpp)

target_include_directories(nano_bindings PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)