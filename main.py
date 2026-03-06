from profiler import Profiler
from pathlib import Path

## Python imported by PYTHONPATH
from python.pure_python_package import raw_python as local_raw_python

## Python imported by wheel
import pure_python_package.raw_python as packaged_raw_python

## CPP pybind11 package
# noinspection PyUnresolvedReferences
import cpp.pybind11_sand_box.cmake_build_release.pybind11_bindings as pybind11_bindings

## CPP Nanobind package
# noinspection PyUnresolvedReferences
import cpp.nanobind_sand_box.cmake_build_release.nano_bindings as nano_bindings


## C Library
# noinspection PyUnresolvedReferences
import c.c_lib.cmake_build_debug.c_lib as c_lib

NUM_TRIALS = 10_000
FIBONACCI_NUMBER = 1_000
BURNER_TRIALS = 100


if __name__ == '__main__':

    # print(c_lib.addition(4, 1))
    # print(c_lib.addition_three_times(5, 10))
    # for i in c_lib.fibonacci(n=5):
    #     print(i)
    # print(c_lib.fibonacci(5))
    my_class = c_lib.MyClass(x=1.0, y=2.0, n=100)
    print(my_class.x)
    print(my_class.y)
    print(my_class.n)

    print(my_class.class_addition(4, 5))
    print(my_class.class_addition_three_times(4, 5))
    print(my_class.class_fibonacci())

    # print()
    # print(f'NUM_TRIALS={NUM_TRIALS}')
    # print(f'FIBONACCI_NUMBER={FIBONACCI_NUMBER}')
    #
    # Profiler.set_num_trials(NUM_TRIALS)
    # Profiler.set_fib_num(FIBONACCI_NUMBER)
    # Profiler.set_burner_num(BURNER_TRIALS)
    #
    # Profiler(modulo=local_raw_python, header="RAW PYTHON").profile()
    # Profiler(modulo=packaged_raw_python, header="PACKAGED RAW PYTHON").profile()
    # Profiler(modulo=pybind11_bindings, header="CPP PYBIND11").profile()
    # Profiler(modulo=nano_bindings, header="CPP NANOBIND").profile()
    # Profiler.run_pure_cpp(rel_path=Path("./cpp/pure_cpp/cmake_build_release/pure_cpp"))