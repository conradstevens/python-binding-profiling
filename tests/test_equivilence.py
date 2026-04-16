import types
import numpy as np
import pytest
from numpy.typing import NDArray

from python_binding_profiling.profiler import ModuleProtocol
from pure_python.raw_python import MyClass

### Modules

## Python imported by wheel
import pure_python.raw_python as packaged_raw_python

## Python pacakge optimized with numba
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
import c.c_package.cmake_build_release.c_package as c_lib


EQUIVALENCE_TOLERANCE: float = 1e-6
TEST_VAL: int = -999

MODULES_TO_TEST: list[ModuleProtocol] = [
    packaged_raw_python,
    pybind11_bindings,
    nano_bindings,
    numba_python,
    cython_module,
]

X_Y_PAIRS = ((1, 2), (3, 4), (5, 10), (100, 1000))
N_VALUES = (1, 2, 3, 4, 10, 100, 1000)
CLASS_INIT_ARGS = ((1, 2, 1), (3, 4, 2), (5, 6, 3), (7, 8, 100))


@pytest.fixture
def ref():
    return packaged_raw_python


@pytest.fixture
def ref_classes(ref):
    return tuple(ref.MyClass(*args) for args in CLASS_INIT_ARGS)


def _make_classes(m):
    return tuple(m.MyClass(*args) for args in CLASS_INIT_ARGS)


@pytest.mark.parametrize("m", MODULES_TO_TEST)
def test_addition(m, ref):
    expected = tuple(ref.addition(*p) for p in X_Y_PAIRS)
    results = tuple(m.addition(*p) for p in X_Y_PAIRS)
    assert results == pytest.approx(expected, abs=EQUIVALENCE_TOLERANCE, rel=0)


@pytest.mark.parametrize("m", MODULES_TO_TEST)
def test_addition_three_times(m, ref):
    expected = tuple(ref.addition_three_times(*p) for p in X_Y_PAIRS)
    results = tuple(m.addition_three_times(*p) for p in X_Y_PAIRS)
    assert results == pytest.approx(expected, abs=EQUIVALENCE_TOLERANCE, rel=0)


@pytest.mark.parametrize("m", MODULES_TO_TEST)
def test_fibonacci(m, ref):
    expected = tuple(ref.fibonacci(n) for n in N_VALUES)
    results = tuple(list(m.fibonacci(n)) for n in N_VALUES)
    assert results == pytest.approx(expected, abs=EQUIVALENCE_TOLERANCE, rel=0)


@pytest.mark.parametrize("m", MODULES_TO_TEST)
def test_fibonacci_numpy(m, ref):
    expected = tuple(ref.fibonacci_numpy(n) for n in N_VALUES)
    results = tuple(m.fibonacci_numpy(n) for n in N_VALUES)
    assert all(np.allclose(a, b, atol=EQUIVALENCE_TOLERANCE) for a, b in zip(results, expected))


@pytest.mark.parametrize("m", MODULES_TO_TEST)
def test_class_addition(m, ref_classes):
    classes = _make_classes(m)
    for c, ref_c in zip(classes, ref_classes):
        results = tuple(c.class_addition(*p) for p in X_Y_PAIRS)
        expected = tuple(ref_c.class_addition(*p) for p in X_Y_PAIRS)
        assert results == pytest.approx(expected, abs=EQUIVALENCE_TOLERANCE, rel=0)


@pytest.mark.parametrize("m", MODULES_TO_TEST)
def test_class_addition_three_times(m, ref_classes):
    classes = _make_classes(m)
    for c, ref_c in zip(classes, ref_classes):
        results = tuple(c.class_addition_three_times(*p) for p in X_Y_PAIRS)
        expected = tuple(ref_c.class_addition_three_times(*p) for p in X_Y_PAIRS)
        assert results == pytest.approx(expected, abs=EQUIVALENCE_TOLERANCE, rel=0)


@pytest.mark.parametrize("m", MODULES_TO_TEST)
def test_class_fibonacci(m, ref_classes):
    classes = _make_classes(m)
    for c, ref_c in zip(classes, ref_classes):
        results = list(c.class_fibonacci())
        expected = list(ref_c.class_fibonacci())
        assert results == pytest.approx(expected, abs=EQUIVALENCE_TOLERANCE, rel=0)


@pytest.mark.parametrize("m", MODULES_TO_TEST)
def test_class_fibonacci_numpy(m, ref_classes):
    classes = _make_classes(m)
    for c, ref_c in zip(classes, ref_classes):
        assert np.allclose(c.class_fibonacci_numpy(), ref_c.class_fibonacci_numpy(), atol=EQUIVALENCE_TOLERANCE)


@pytest.mark.parametrize("m", MODULES_TO_TEST)
def test_mutability_of_my_class_members(m):
    my_class = m.MyClass(*CLASS_INIT_ARGS[0])

    fib_l_ref = my_class.class_fibonacci()
    fib_l_ref[0] = TEST_VAL
    assert fib_l_ref == my_class._fib_l

    fib_arr_ref = my_class.class_fibonacci_numpy()
    fib_arr_ref[0] = TEST_VAL
    assert all(fib_arr_ref == my_class._fib_arr)