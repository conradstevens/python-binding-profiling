#!/bin/bash

echo -e "\n ### Building Pure Python Package ### \n"
uv build --wheel --project python/pure_python/

echo -e "\n ### Building Numba Python Package ### \n"
uv build --wheel --project python/numba_package/

echo -e "\n ### Building Cython Package ### \n"
uv build --wheel --project python/cython_package/

echo -e "\n ### Making Virtual Environment ### \n"
# Supress error of removing if it is not there
uv remove cython-package 2>/dev/null || true
# Wheel name will change depending on system
uv add "python/cython_package/dist/"$(ls python/cython_package/dist/)
uv sync

echo -e "\n ### Building Pure CPP Executable ### \n"
mkdir -p cpp/pure_cpp/cmake_build_release
cmake -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_CXX_FLAGS_RELEASE="-O3 -march=native -DNDEBUG" \
      -DCMAKE_C_FLAGS_RELEASE="-O3 -march=native -DNDEBUG" \
      -S cpp/pure_cpp/ \
      -B cpp/pure_cpp/cmake_build_release/
cmake --build cpp/pure_cpp/cmake_build_release/

echo -e "\n ### Building Pybind11 Package ### \n"
mkdir -p cpp/pybind11_package/cmake_build_release
cmake -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_CXX_FLAGS_RELEASE="-O3 -march=native -DNDEBUG" \
      -DCMAKE_C_FLAGS_RELEASE="-O3 -march=native -DNDEBUG" \
      -S cpp/pybind11_package/ \
      -B cpp/pybind11_package/cmake_build_release/
cmake --build cpp/pybind11_package/cmake_build_release/

echo -e "\n ### Building Nanobind Package ### \n"
mkdir -p cpp/nanobind_package/cmake_build_release
cmake -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_CXX_FLAGS_RELEASE="-O3 -march=native -DNDEBUG" \
      -DCMAKE_C_FLAGS_RELEASE="-O3 -march=native -DNDEBUG" \
      -S cpp/nanobind_package/ \
      -B cpp/nanobind_package/cmake_build_release/
cmake --build cpp/nanobind_package/cmake_build_release/

echo -e "\n ### C Package ### \n"
mkdir -p c/c_package/cmake_build_release
cmake -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_C_FLAGS_RELEASE="-O3 -march=native -DNDEBUG" \
      -S c/c_package/ \
      -B c/c_package/cmake_build_release
cmake --build c/c_package/cmake_build_release