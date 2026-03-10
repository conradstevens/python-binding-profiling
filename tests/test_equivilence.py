import types
import numpy as np
from numpy.typing import NDArray

from profiler import ModuleProtocol

### Modules

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
import c.c_lib.cmake_build_release.c_lib as c_lib


EQUIVALENCE_TOLERANCE: float = 1e-6

class TestEquivalence:
    def setup_method(self):
        self._x_y_val_test_pairs = ((1, 2), (3, 4), (5, 10), (100, 1000))
        self._n_test_values = (1, 2, 3, 4, 5, 10, 100, 1000)

        self._py_addition_results: tuple[float, ...] = tuple(
            packaged_raw_python.addition(*pair) for pair in self._x_y_val_test_pairs
        )
        self._py_addition_three_times_results: tuple[float, ...] = tuple(
            packaged_raw_python.addition_three_times(*pair) for pair in self._x_y_val_test_pairs
        )
        self._py_fibonacci_results: tuple[list[float], ...] = tuple(
            packaged_raw_python.fibonacci(n) for n in self._n_test_values
        )
        self._py_fibonacci_numpy_results: tuple[NDArray[np.float64], ...] = tuple(
            packaged_raw_python.fibonacci_numpy(n) for n in self._n_test_values
        )

    def test_equivalence(self):
        for m in (packaged_raw_python,):
            self._test_module(m)

    def _test_module(self, m: ModuleProtocol | types.ModuleType):

        ### Test functions
        module_addition_results: tuple[float, ...] = tuple(
            m.addition(*pair) for pair in self._x_y_val_test_pairs
        )
        assert self._py_addition_results == module_addition_results

        module_addition_three_times_results: tuple[float, ...] = tuple(
            m.addition_three_times(*pair) for pair in self._x_y_val_test_pairs
        )
        assert self._py_addition_three_times_results == module_addition_three_times_results

        module_fibonacci_results: tuple[list[float], ...] = tuple(
            m.fibonacci(n) for n in self._n_test_values
        )
        assert self._py_fibonacci_results == module_fibonacci_results

        module_fibonacci_numpy_results: tuple[NDArray[np.float64], ...] = tuple(
            m.fibonacci_numpy(n) for n in self._n_test_values
        )

        assert all(np.allclose(a, b, atol=EQUIVALENCE_TOLERANCE)
                   for a, b in zip(self._py_fibonacci_numpy_results, module_fibonacci_numpy_results))

        ### Test Classes
        # TODO my_class = m.MyClass(...)
