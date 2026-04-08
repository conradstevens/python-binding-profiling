from pathlib import Path

from python_binding_profiling.profiler import Profiler
from python_binding_profiling.profiler import ProfilerJson
from python_binding_profiling.plotter import ProfilePlotter

## Python raw
import pure_python.raw_python as packaged_raw_python

## Python with numba
import numba_package.numba_python as numba_python

## Cython package
import cython_package.cython_module as cython_module

## CPP pybind11 package
# noinspection PyUnresolvedReferences
import cpp.pybind11_package.cmake_build_release.pybind11_bindings as pybind11_bindings

## CPP Nanobind package
# noinspection PyUnresolvedReferences
import cpp.nanobind_package.cmake_build_release.nano_bindings as nano_bindings

## C Library
# noinspection PyUnresolvedReferences
import c.c_package.cmake_build_release.c_package as c_package

## CPP Profiler
# noinspection PyUnresolvedReferences
import cpp.pure_cpp.cmake_build_release.python_cpp_profiler as cpp_profiler


NUM_TRIALS: int = 1_000
FIBONACCI_NUMBER: int = 10_000
BURNER_TRIALS: int = 200

if __name__ == '__main__':
    print()
    print(f'NUM_TRIALS={NUM_TRIALS}')
    print(f'FIBONACCI_NUMBER={FIBONACCI_NUMBER}')

    Profiler.set_num_trials(NUM_TRIALS)
    Profiler.set_fib_num(FIBONACCI_NUMBER)
    Profiler.set_burner_num(BURNER_TRIALS)

    profile_plotter = ProfilePlotter([
        Profiler(header="PYTHON", modulo=packaged_raw_python),
        Profiler(header="PYTHON-NUMBA", modulo=numba_python),
        Profiler(header="CYTHON", modulo=cython_module),
        ProfilerJson(header="PYPY", json_path=Path("python/pypy/outputs/PYPY_results.json")),
        Profiler(header="PYBIND11-PACKAGE", modulo=pybind11_bindings),
        Profiler(header="NANOBIND-PACKAGE", modulo=nano_bindings),
        Profiler(header="C-PACKAGE", modulo=c_package),
        cpp_profiler.CppProfiler(NUM_TRIALS, FIBONACCI_NUMBER, BURNER_TRIALS, 99, 100, "CPP"),
    ])

    profile_plotter.profile_all()
    profile_plotter.plot_time_averages("addition")
    profile_plotter.plot_time_averages("addition_three_times")
    profile_plotter.plot_time_averages("fibonacci")
    profile_plotter.plot_time_averages("fibonacci_numpy")
    profile_plotter.plot_time_averages("MyClass")
    profile_plotter.plot_time_averages("class_addition")
    profile_plotter.plot_time_averages("class_addition_three_times")
    profile_plotter.plot_time_averages("class_fibonacci")
    profile_plotter.plot_time_averages("class_fibonacci_numpy")