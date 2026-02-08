#!/bin/bash


echo -e "\n ### Building Pure CPP ### \n"
mkdir -p cpp/pure_cpp/cmake_build_release
cmake -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_CXX_FLAGS_RELEASE="-O3 -march=native -DNDEBUG" \
      -DCMAKE_C_FLAGS_RELEASE="-O3 -march=native -DNDEBUG" \
      -S cpp/pure_cpp/ \
      -B cpp/pure_cpp/cmake_build_release/
cmake --build cpp/pure_cpp/cmake_build_release/

echo -e "\n ### Building Pybind11 library ### \n"
mkdir -p cpp/pybind11_sand_box/cmake_build_release
cmake -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_CXX_FLAGS_RELEASE="-O3 -march=native -DNDEBUG" \
      -DCMAKE_C_FLAGS_RELEASE="-O3 -march=native -DNDEBUG" \
      -S cpp/pybind11_sand_box/ \
      -B cpp/pybind11_sand_box/cmake_build_release/
cmake --build cpp/pybind11_sand_box/cmake_build_release/

echo -e "\n ### Building nanobind library ### \n"
mkdir -p cpp/nanobind_sand_box/cmake_build_release
cmake -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_CXX_FLAGS_RELEASE="-O3 -march=native -DNDEBUG" \
      -DCMAKE_C_FLAGS_RELEASE="-O3 -march=native -DNDEBUG" \
      -S cpp/nanobind_sand_box/ \
      -B cpp/nanobind_sand_box/cmake_build_release/
cmake --build cpp/nanobind_sand_box/cmake_build_release/

