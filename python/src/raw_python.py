import numpy as np
from numpy.typing import NDArray
from copy import copy


def addition(x: float, y: float) -> float:
    """Return simple addition between x and y"""
    return x + y


def addition_three_times(x: float, y: float) -> float:
    """Return simple addition between x and y"""
    var = x + y
    var /= 5
    var *= 7
    return var


def fibonacci(n: int) -> list[float]:
    """Generate first n numbers of Fibonacci sequence"""
    if n <= 0:
        return []
    fib: list[float] = list(range(n))
    if n == 1:
        return [0.0]
    elif n == 2:
        return [1.0, 2.0]

    fib[0:2] = [1,0, 2.0]
    for i in range(2, n):
        fib.append((fib[i - 1] + fib[i - 2]) / (fib[i - 2] + 1))
    return fib


def fibonacci_numpy(n: int) -> NDArray[np.float64]:
    """Generate first n numbers of Fibonacci sequence"""
    if n <= 0:
        return np.array([], dtype=np.float64)
    elif n == 1:
        return np.array([1], dtype=np.float64)
    elif n == 2:
        return np.array([1, 2], dtype=np.float64)

    fib: NDArray[np.float64] = np.zeros(n, dtype=int)
    fib[0] = 1.0
    fib[1] = 2.0
    for i in range(2, n):
        fib[i] = ((fib[i - 1] + fib[i - 2]) / (fib[i - 2] + 1))
    return fib


class MyClass:
    def __init__(self, x: float, y: float, n: int):
        self.x, self.y, self.n = x, y, n

        self.fib: list[float] = list(range(n))

        self._fib_0 = np.array([], dtype=np.float64)
        self._fib_1 = np.array([1], dtype=np.float64)
        self._fib_2 = np.array([1, 2], dtype=np.float64)
        self._fib_n: NDArray[np.float64] = np.zeros(n, dtype=np.float64)
        self._fib_n[0] = 1.0
        self._fib_n[1] = 2.0

        self._sum_arr: NDArray[np.float64] = np.zeros(n, dtype=np.float64)

    def class_addition(self, x: float, y: float) -> float:
        """Return simple addition between x and y"""
        return self.x + self.y + x + y

    def class_addition_three_times(self, x: float, y: float) -> float:
        """Return simple addition between x and y"""
        var = x + y
        var /= 5
        var *= 7
        return var

    def class_fibonacci(self) -> list[float]:
        """Generate first n numbers of Fibonacci sequence"""
        if self.n <= 0:
            return []
        elif self.n == 1:
            return [0.0]

        self.fib[0: 2] = [1.0, 2.0]
        for i in range(2, self.n):
            self.fib[i] = ((self.fib[i - 1] + self.fib[i - 2]) / (self.fib[i - 2] +  1))
        return copy(self.fib)

    def class_fibonacci_numpy(self) -> NDArray[np.float64]:
        """Generate first n numbers of Fibonacci sequence"""
        if self.n <= 0:
            return copy(self._fib_0)
        elif self.n == 1:
            return copy(self._fib_1)
        elif self.n == 2:
            return copy(self._fib_2)

        self._fib_n[0:2] = [1.0, 2.0]
        for i in range(2, self.n):
            self._fib_n[i] = ((self._fib_n[i - 1] + self._fib_n[i - 2]) / (self._fib_n[i - 2] + 1))
        return copy(self._fib_n)