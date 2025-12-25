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


def fibonacci(n: int) -> int:
    """Generate first n numbers of Fibonacci sequence"""
    if n <= 0:
        return []
    elif n == 1:
        return [0]
    elif n == 2:
        return [1, 2]

    fib = [1, 2]
    for i in range(2, n):
        fib.append((fib[i - 1] + fib[i - 2]) / fib[i - 2])
    return fib


def fibonacci_numpy(n: int) -> int:
    """Generate first n numbers of Fibonacci sequence"""
    if n <= 0:
        return np.array([], dtype=int)
    elif n == 1:
        return np.array([1], dtype=int)
    elif n == 2:
        return np.array([1, 2], dtype=int)

    fib: NDArray[int] = np.zeros(n, dtype=int)
    fib[0] = 1
    fib[1] = 2
    for i in range(2, n):
        fib[i] = ((fib[i - 1] + fib[i - 2]) / fib[i - 2])
    return fib


class MyClass:
    def __init__(self, x: float, y: float, n: int):
        self.x, self.y, self.n = x, y, n

        self._fib_0 = np.array([], dtype=int)
        self._fib_1 = np.array([1], dtype=int)
        self._fib_2 = np.array([1, 2], dtype=int)
        self._fib_n: NDArray[int] = np.zeros(n, dtype=int)
        self._fib_n[0] = 1
        self._fib_n[1] = 2

    def class_addition(self, x: float, y: float) -> float:
        """Return simple addition between x and y"""
        return self.x + self.y + x + y

    def class_addition_three_times(self, x: float, y: float) -> float:
        """Return simple addition between x and y"""
        var = x + y
        var /= 5
        var *= 7
        return var

    def class_fibonacci(self, n: int) -> int:
        """Generate first n numbers of Fibonacci sequence"""
        if n <= 0:
            return []
        elif n == 1:
            return [0]

        fib = [1, 2]
        for i in range(2, n):
            fib.append((fib[i - 1] + fib[i - 2]) / fib[i - 2])
        return fib

    def class_fibonacci_numpy(self, n: int) -> int:
        """Generate first n numbers of Fibonacci sequence"""
        if n <= 0:
            return copy(self._fib_0)
        elif n == 1:
            return copy(self._fib_1)
        elif n == 2:
            return copy(self._fib_2)

        fib = copy(self._fib_n)
        fib[0] = 1
        fib[1] = 2
        for i in range(2, n):
            fib[i] = ((fib[i - 1] + fib[i - 2]) / fib[i - 2])
        return fib