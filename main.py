import argparse
from pathlib import Path

from python_binding_profiling.profiler import Profiler
from python_binding_profiling.profiler import ProfilerJson
from python_binding_profiling.plotter import ProfilePlotter

## Python raw
import python_pacakge.raw_python as python_pacakge

## Python with numba
import numba_package.numba_python as numba_package

## Cython package
import cython_package.cython_module as cython_package

## CPP pybind11 package
# noinspection PyUnresolvedReferences
import cpp.pybind11_package.cmake_build_release.pybind11_bindings as pybind11_package

## CPP Nanobind package
# noinspection PyUnresolvedReferences
import cpp.nanobind_package.cmake_build_release.nano_bindings as nanobind_package

## C Library
# noinspection PyUnresolvedReferences
import c.c_package.cmake_build_release.c_package as c_package

## CPP Profiler
# noinspection PyUnresolvedReferences
import cpp.pure_cpp.cmake_build_release.python_cpp_profiler as cpp_profiler


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument("--num-trials", type=int, default=1_000)
    parser.add_argument("--fibonacci-number", type=int, default=1_000)
    parser.add_argument("--burner-trials", type=int, default=200)
    args = parser.parse_args()

    NUM_TRIALS: int = args.num_trials
    FIBONACCI_NUMBER: int = args.fibonacci_number
    BURNER_TRIALS: int = args.burner_trials

    print()
    print(f'NUM_TRIALS={NUM_TRIALS}')
    print(f'FIBONACCI_NUMBER={FIBONACCI_NUMBER}')
    print(f'BURNER_TRIALS={FIBONACCI_NUMBER}')

    Profiler.set_num_trials(NUM_TRIALS)
    Profiler.set_fib_num(FIBONACCI_NUMBER)
    Profiler.set_burner_num(BURNER_TRIALS)

    profile_plotter = ProfilePlotter([
        Profiler(header="PYTHON", modulo=python_pacakge),
        ProfilerJson(header="PYPY", json_path=Path("python/pypy/outputs/PYPY_results.json")),
        Profiler(header="NUMBA", modulo=numba_package),
        Profiler(header="CYTHON", modulo=cython_package),
        Profiler(header="NANOBIND", modulo=nanobind_package),
        Profiler(header="PYBIND11", modulo=pybind11_package),
        Profiler(header="C", modulo=c_package),
        cpp_profiler.CppProfiler(NUM_TRIALS, FIBONACCI_NUMBER, BURNER_TRIALS, 99, 100, "CPP"),
    ])

    profile_plotter.profile_all()
    profile_plotter.plot("addition")
    profile_plotter.plot("addition_three_times")
    profile_plotter.plot("fibonacci")
    profile_plotter.plot("fibonacci_numpy")
    profile_plotter.plot("MyClass")
    profile_plotter.plot("class_addition")
    profile_plotter.plot("class_addition_three_times")
    profile_plotter.plot("class_fibonacci")
    profile_plotter.plot("class_fibonacci_numpy")