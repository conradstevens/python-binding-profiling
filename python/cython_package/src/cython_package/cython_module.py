import cython
import numpy as np
from numpy.typing import NDArray


@cython.ccall
def addition(x: cython.double, y: cython.double) -> cython.double:
    """Return simple addition between x and y"""
    return x + y


@cython.ccall
def addition_three_times(x: cython.double, y: cython.double) -> cython.double:
    """Return simple addition between x and y"""
    var: cython.double = x + y
    var /= 5
    var *= 7
    return var


@cython.ccall
@cython.boundscheck(False)
@cython.wraparound(False)
def fibonacci(n: cython.int) -> list:
    """Generate first n numbers of Fibonacci sequence"""
    if n <= 0:
        return []

    fib: list = list(range(n))
    if n == 1:
        return [1.0]
    elif n == 2:
        return [1.0, 2.0]

    fib[0] = 1.0
    fib[1] = 2.0

    i: cython.int
    for i in range(2, n):
        fib[i] = (fib[i - 1] + fib[i - 2]) / n * i
    return fib


@cython.ccall
@cython.boundscheck(False)
@cython.wraparound(False)
def fibonacci_numpy(n: cython.int) -> NDArray[np.float64]:
    """Generate first n numbers of Fibonacci sequence"""
    if n == 0:
        return np.array([], dtype=np.float64)
    elif n == 1:
        return np.array([1], dtype=np.float64)
    elif n == 2:
        return np.array([1, 2], dtype=np.float64)

    fib: NDArray[np.float64] = np.zeros(n, dtype=np.float64)
    fib_view: cython.double[::1] = fib
    fib_view[0] = 1.0
    fib_view[1] = 2.0

    i: cython.int
    for i in range(2, n):
        fib_view[i] = (fib_view[i - 1] + fib_view[i - 2]) / n * i
    return fib


@cython.cclass
class MyClass:
    x: cython.double
    y: cython.double
    n: cython.int
    _fib_l: list
    _fib_arr: object  # NDArray stored as generic object

    def __init__(self, x: cython.double, y: cython.double, n: cython.int):
        self.x = x
        self.y = y
        self.n = n
        self._fib_l = list(range(n))
        self._fib_arr = np.zeros(n, dtype=np.float64)

    @cython.ccall
    def class_addition(self, x: cython.double, y: cython.double) -> cython.double:
        """Return simple addition between x and y"""
        return self.x + self.y + x + y

    @cython.ccall
    def class_addition_three_times(self, x: cython.double, y: cython.double) -> cython.double:
        """Return simple addition between x and y with some extra steps"""
        var: cython.double = x + y
        var /= 5
        var *= 7
        return var

    @cython.ccall
    @cython.boundscheck(False)
    @cython.wraparound(False)
    def class_fibonacci(self) -> list:
        """Generate first n numbers of Fibonacci sequence"""
        if self.n <= 0:
            return self._fib_l

        self._fib_l[0] = 1.0

        i: cython.int
        if self.n > 1:
            self._fib_l[1] = 2.0
            for i in range(2, self.n):
                self._fib_l[i] = (self._fib_l[i - 1] + self._fib_l[i - 2]) / self.n * i

        return self._fib_l

    @cython.ccall
    @cython.boundscheck(False)
    @cython.wraparound(False)
    def class_fibonacci_numpy(self) -> NDArray[np.float64]:
        """Generate first n numbers of Fibonacci sequence"""
        if self.n <= 0:
            return self._fib_arr

        fib_view: cython.double[::1] = self._fib_arr
        fib_view[0] = 1.0

        i: cython.int
        if self.n > 1:
            fib_view[1] = 2.0
            for i in range(2, self.n):
                fib_view[i] = (fib_view[i - 1] + fib_view[i - 2]) / self.n * i

        return self._fib_arr
