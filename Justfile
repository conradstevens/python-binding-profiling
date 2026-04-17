# justfile

########################################################################################################################
#################################################     RUN SCRIPTS     ##################################################
########################################################################################################################


NUM_TRIALS := "1000"
FIBONACCI_NUMBER := "1000"
BURNER_TRIALS := "200"

profile-all: profile-pypy
    #!/usr/bin/env bash
    uv run main.py \
        --num-trials {{NUM_TRIALS}} \
        --fibonacci-number {{FIBONACCI_NUMBER}} \
        --burner-trials {{BURNER_TRIALS}}

profile-pypy:
    #!/usr/bin/env bash
    cd python/pypy_package
    source pypy_venv/bin/activate
    python save_results.py \
        --num-trials {{NUM_TRIALS}} \
        --fibonacci-number {{FIBONACCI_NUMBER}} \
        --burner-trials {{BURNER_TRIALS}}
    deactivate


########################################################################################################################
################################################     BUILD SCRIPTS     #################################################
########################################################################################################################


build-python-package:
    #!/usr/bin/env bash
    echo -e "\n ### Building Pure Python Package ### \n"
    uv build --wheel --project python/python_package/

build-numba-python:
    #!/usr/bin/env bash
    echo -e "\n ### Building Numba Python Package ### \n"
    uv build --wheel --project python/numba_package/

build-cython:
    #!/usr/bin/env bash
    echo -e "\n ### Building Cython Package ### \n"
    uv build --wheel --project python/cython_package/

build-main-venv:
    #!/usr/bin/env bash
    echo -e "\n ### Making Virtual Environment ### \n"
    # Supress error of removing if it is not there
    uv remove cython-package 2>/dev/null || true
    # Wheel name will change depending on system
    uv add "python/cython_package/dist/"$(ls python/cython_package/dist/)
    uv sync

build-pypy-venv:
    #!/usr/bin/env bash
    echo -e "\n ### Making PYPY Virtual Environment ### \n"
    cd python/pypy_package
    mkdir -p "outputs"
    uv venv --python pypy3.10 --clear pypy_venv
    pypy_venv/bin/pypy -m ensurepip
    pypy_venv/bin/pip3 install "numpy>=1.24.4"
    pypy_venv/bin/pip3 install ../python_package/dist/python_package-0.1.0-py3-none-any.whl
    cd ../..

build-pure-cpp:
    #!/usr/bin/env bash
    echo -e "\n ### Building Pure CPP Executable ### \n"
    mkdir -p cpp/pure_cpp/cmake_build_release
    cmake -DCMAKE_BUILD_TYPE=Release \
          -DCMAKE_CXX_FLAGS_RELEASE="-O3 -march=native -DNDEBUG" \
          -DCMAKE_C_FLAGS_RELEASE="-O3 -march=native -DNDEBUG" \
          -S cpp/pure_cpp/ \
          -B cpp/pure_cpp/cmake_build_release/
    cmake --build cpp/pure_cpp/cmake_build_release/

build-pybind11-package:
    #!/usr/bin/env bash
    echo -e "\n ### Building Pybind11 Package ### \n"
    mkdir -p cpp/pybind11_package/cmake_build_release
    cmake -DCMAKE_BUILD_TYPE=Release \
          -DCMAKE_CXX_FLAGS_RELEASE="-O3 -march=native -DNDEBUG" \
          -DCMAKE_C_FLAGS_RELEASE="-O3 -march=native -DNDEBUG" \
          -S cpp/pybind11_package/ \
          -B cpp/pybind11_package/cmake_build_release/
    cmake --build cpp/pybind11_package/cmake_build_release/

build-nanobind-package:
    #!/usr/bin/env bash
    echo -e "\n ### Building Nanobind Package ### \n"
    mkdir -p cpp/nanobind_package/cmake_build_release
    cmake -DCMAKE_BUILD_TYPE=Release \
          -DCMAKE_CXX_FLAGS_RELEASE="-O3 -march=native -DNDEBUG" \
          -DCMAKE_C_FLAGS_RELEASE="-O3 -march=native -DNDEBUG" \
          -S cpp/nanobind_package/ \
          -B cpp/nanobind_package/cmake_build_release/
    cmake --build cpp/nanobind_package/cmake_build_release/

build-c-package:
    #!/usr/bin/env bash
    echo -e "\n ### C Package ### \n"
    mkdir -p c/c_package/cmake_build_release
    cmake -DCMAKE_BUILD_TYPE=Release \
          -DCMAKE_C_FLAGS_RELEASE="-O3 -march=native -DNDEBUG" \
          -S c/c_package/ \
          -B c/c_package/cmake_build_release
    cmake --build c/c_package/cmake_build_release

# Build all
build: \
    build-python-package \
    build-numba-python \
    build-cython \
    build-main-venv \
    build-pypy-venv \
    build-pure-cpp \
    build-pybind11-package \
    build-nanobind-package \
    build-c-package \


########################################################################################################################
########################################################################################################################
########################################################################################################################