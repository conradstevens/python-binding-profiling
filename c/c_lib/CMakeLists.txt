cmake_minimum_required(VERSION 3.18)
set(CMAKE_C_STANDARD 11)
project(c_lib C)

set(Python3_ROOT_DIR "../../.venv")
find_package(Python3 3.12 COMPONENTS Interpreter Development NumPy REQUIRED)

Python3_add_library(c_lib MODULE
        src/c_lib.c
        src/my_class.c
)

target_include_directories(c_lib PRIVATE
        include/
        ${Python3_NumPy_INCLUDE_DIRS}
)
