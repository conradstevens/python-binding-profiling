from python_binding_profiling.profiler import Profiler
from pathlib import Path

## Python imported by wheel
import pure_python.raw_python as packaged_raw_python

## CPP pybind11 package
# noinspection PyUnresolvedReferences
import cpp.pybind11_package.cmake_build_release.pybind11_bindings as pybind11_bindings

## CPP Nanobind package
# noinspection PyUnresolvedReferences
import cpp.nanobind_package.cmake_build_release.nano_bindings as nano_bindings

## C Library
# noinspection PyUnresolvedReferences
import c.c_package.cmake_build_release.c_package as c_package

NUM_TRIALS = 10_000
FIBONACCI_NUMBER = 1_000
BURNER_TRIALS = 100


if __name__ == '__main__':
    print()
    print(f'NUM_TRIALS={NUM_TRIALS}')
    print(f'FIBONACCI_NUMBER={FIBONACCI_NUMBER}')

    Profiler.set_num_trials(NUM_TRIALS)
    Profiler.set_fib_num(FIBONACCI_NUMBER)
    Profiler.set_burner_num(BURNER_TRIALS)

    # Profiler(modulo=packaged_raw_python, header="PYTHON").profile()
    # Profiler(modulo=pybind11_bindings, header="PYBIND11 PACKAGE").profile()
    # Profiler(modulo=nano_bindings, header="NANOBIND PACKAGE").profile()
    Profiler(modulo=c_package, header="C PACKAGE").profile()
    Profiler.run_pure_cpp(rel_path=Path("./cpp/pure_cpp/cmake_build_release/pure_cpp"))