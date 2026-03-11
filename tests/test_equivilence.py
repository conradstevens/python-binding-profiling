import types
import numpy as np
import pytest
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

MODULES_TO_TEST: list[ModuleProtocol | types.ModuleType] = [packaged_raw_python]

class TestEquivalence:
    def setup_method(self):
        self._x_y_val_test_pairs: tuple[tuple[int, int], ...] = ((1, 2), (3, 4), (5, 10), (100, 1000))
        self._n_test_values: tuple[int, ...] = (1, 2, 3, 4, 10, 100, 1000)
        self._my_class_test_init_args: tuple[tuple[float, float, int], ...] = (
            (1, 2, 1), (3, 4, 2), (5, 6, 3), (7, 8, 100)
        )

        ref_module = packaged_raw_python
        ref_my_class: tuple[MyClass, ...] = self._get_classes_module(ref_module)

        self._py_addition_results: tuple[float, ...] = tuple(
            ref_module.addition(*p) for p in self._x_y_val_test_pairs
        )
        self._py_addition_three_times_results: tuple[float, ...] = tuple(
            ref_module.addition_three_times(*p) for p in self._x_y_val_test_pairs
        )
        self._py_fibonacci_results: tuple[list[float], ...] = tuple(
            ref_module.fibonacci(n) for n in self._n_test_values
        )
        self._py_fibonacci_numpy_results: tuple[NDArray[np.float64], ...] = tuple(
            ref_module.fibonacci_numpy(n) for n in self._n_test_values
        )

        self._my_class_py_addition_results: tuple[tuple[float, ...], ...] = tuple(
            tuple(c.class_addition(*p) for p in self._x_y_val_test_pairs) for c in ref_my_class
        )
        self._my_class_py_addition_three_times_results: tuple[tuple[float, ...], ...] = tuple(
            tuple(c.class_addition_three_times(*p) for p in self._x_y_val_test_pairs) for c in ref_my_class
        )
        self._my_class_py_fibonacci_results: tuple[tuple[list[float], ...], ...] = tuple(
            tuple(c.class_fibonacci() for _ in self._n_test_values) for c in ref_my_class
        )
        self._my_class_py_fibonacci_numpy_results: tuple[tuple[NDArray[np.float64], ...], ...] = tuple(
            tuple(c.class_fibonacci_numpy() for _ in self._n_test_values) for c in ref_my_class
        )

    @pytest.mark.parametrize("m", MODULES_TO_TEST)
    def test_addition(self, m):
        results: tuple[float, ...] = tuple(m.addition(*p) for p in self._x_y_val_test_pairs)
        assert results == self._py_addition_results

    @pytest.mark.parametrize("m", MODULES_TO_TEST)
    def test_addition_three_times(self, m):
        results: tuple[float, ...] = tuple(m.addition_three_times(*p) for p in self._x_y_val_test_pairs)
        assert results == self._py_addition_three_times_results

    @pytest.mark.parametrize("m", MODULES_TO_TEST)
    def test_fibonacci(self, m):
        results: tuple[list[float], ...] = tuple(m.fibonacci(n) for n in self._n_test_values)
        assert results == self._py_fibonacci_results

    @pytest.mark.parametrize("m", MODULES_TO_TEST)
    def test_fibonacci_numpy(self, m):
        results: tuple[NDArray[np.float64], ...] = tuple(m.fibonacci_numpy(n) for n in self._n_test_values)
        assert all(
            np.allclose(a, b, atol=EQUIVALENCE_TOLERANCE)
            for a, b in zip(results, self._py_fibonacci_numpy_results)
        )

    @pytest.mark.parametrize("m", MODULES_TO_TEST)
    def test_class_addition(self, m):
        classes: tuple[MyClass, ...] = self._get_classes_module(m)
        results: tuple[tuple[float, ...], ...] = tuple(
            tuple(c.class_addition(*p) for p in self._x_y_val_test_pairs) for c in classes
        )
        assert results == self._my_class_py_addition_results

    @pytest.mark.parametrize("m", MODULES_TO_TEST)
    def test_class_addition_three_times(self, m):
        classes: tuple[MyClass, ...] = self._get_classes_module(m)
        results: tuple[tuple[float, ...], ...] = tuple(
            tuple(c.class_addition_three_times(*p) for p in self._x_y_val_test_pairs) for c in classes
        )
        assert results == self._my_class_py_addition_three_times_results

    @pytest.mark.parametrize("m", MODULES_TO_TEST)
    def test_class_fibonacci(self, m):
        classes: tuple[MyClass, ...] = self._get_classes_module(m)
        results: tuple[tuple[list[float], ...], ...] = tuple(
            tuple(c.class_fibonacci() for _ in self._n_test_values) for c in classes
        )
        assert results == self._my_class_py_fibonacci_results

    @pytest.mark.parametrize("m", MODULES_TO_TEST)
    def test_class_fibonacci_numpy(self, m):
        classes: tuple[MyClass, ...] = self._get_classes_module(m)
        results: tuple[tuple[NDArray[np.float64], ...], ...] = tuple(
            tuple(c.class_fibonacci_numpy() for _ in self._n_test_values) for c in classes
        )
        assert all(
            np.allclose(a, b, atol=EQUIVALENCE_TOLERANCE)
            for a, b in zip(results, self._my_class_py_fibonacci_numpy_results)
        )

    def _get_classes_module(self, m: ModuleProtocol | types.ModuleType) -> tuple:
        return tuple(m.MyClass(*args) for args in self._my_class_test_init_args)