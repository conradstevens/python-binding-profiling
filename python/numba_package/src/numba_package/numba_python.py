import numpy as np
from numpy.typing import NDArray
from numba import njit
from numba.experimental import jitclass
from numba import types
from numba.typed import List as NumbaList


@njit(cache=True)
def addition(x: float, y: float) -> float:
    return x + y


@njit(cache=True)
def addition_three_times(x: float, y: float) -> float:
    var = x + y
    var /= 5
    var *= 7
    return var


@njit(cache=True)
def fibonacci(n: int) -> NumbaList:
    fib = NumbaList()
    if n <= 0:
        return fib

    for i in range(n):
        fib.append(float(0))

    if n == 1:
        fib[0] = 1.0
        return fib
    elif n == 2:
        fib[0] = 1.0
        fib[1] = 2.0
        return fib

    fib[0] = 1.0
    fib[1] = 2.0

    for i in range(2, n):
        fib[i] = (fib[i - 1] + fib[i - 2]) / n * i
    return fib


@njit(cache=True)
def fibonacci_numpy(n: int) -> NDArray[np.float64]:
    if n == 0:
        return np.empty(0, dtype=np.float64)
    elif n == 1:
        return np.array([1.0], dtype=np.float64)
    elif n == 2:
        return np.array([1.0, 2.0], dtype=np.float64)

    fib = np.zeros(n, dtype=np.float64)
    fib[0] = 1.0
    fib[1] = 2.0
    for i in range(2, n):
        fib[i] = (fib[i - 1] + fib[i - 2]) / n * i
    return fib


@jitclass([
    ('x', types.float64),
    ('y', types.float64),
    ('n', types.int64),
    ('_fib_l', types.ListType(types.float64)),
    ('_fib_arr', types.float64[:]),
])
class MyClass:
    def __init__(self, x: float, y: float, n: int):
        self.x, self.y, self.n = x, y, n

        self._fib_l = NumbaList.empty_list(types.float64)
        for i in range(n):
            self._fib_l.append(0.0)
        self._fib_arr: NDArray[np.float64] = np.zeros(n, dtype=np.float64)

    def class_addition(self, x: float, y: float) -> float:
        return self.x + self.y + x + y

    def class_addition_three_times(self, x: float, y: float) -> float:
        var = x + y
        var /= 5
        var *= 7
        return var

    def class_fibonacci(self) -> list[float]:
        if self.n <= 0:
            return self._fib_l

        self._fib_l[0] = 1.0

        if self.n > 1:
            self._fib_l[1] = 2.0
            for i in range(2, self.n):
                self._fib_l[i] = (self._fib_l[i - 1] + self._fib_l[i - 2]) / self.n * i

        return self._fib_l

    def class_fibonacci_numpy(self) -> NDArray[np.float64]:
        if self.n <= 0:
            return self._fib_arr

        self._fib_arr[0] = 1.0

        if self.n > 1:
            self._fib_arr[1] = 2.0
            for i in range(2, self.n):
                self._fib_arr[i] = (self._fib_arr[i - 1] + self._fib_arr[i - 2]) / self.n * i

        return self._fib_arr