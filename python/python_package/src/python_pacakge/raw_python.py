import numpy as np
from numpy.typing import NDArray


def addition(x: float, y: float) -> float:
    """Return simple addition between x and y"""
    return x + y


def addition_three_times(x: float, y: float) -> float:
    """Return simple operations between x and y"""
    var = x + y
    var /= 5
    var *= 7
    return var


def fibonacci(n: int) -> list[float]:
    """Generate first n numbers of Fibonacci like sequence using list"""
    if n <= 0:
        return []

    fib: list[float] = list(range(n))
    if n == 1:
        return [1.0]
    elif n == 2:
        return [1.0, 2.0]

    fib[0] = 1.0
    fib[1] = 2.0

    for i in range(2, n):
        fib[i] = (fib[i - 1] + fib[i - 2]) / n * i
    return fib


def fibonacci_numpy(n: int) -> NDArray[np.float64]:
    """Generate first n numbers of Fibonacci like sequence using numpy list"""
    if n == 0:
        return np.array([], dtype=np.float64)
    elif n == 1:
        return np.array([1], dtype=np.float64)
    elif n == 2:
        return np.array([1, 2], dtype=np.float64)

    fib: NDArray[np.float64] = np.zeros(n, dtype=float)
    fib[0] = 1.0
    fib[1] = 2.0
    for i in range(2, n):
        fib[i] = (fib[i - 1] + fib[i - 2]) / n * i
    return fib


class MyClass:
    def __init__(self, x: float, y: float, n: int):
        """Class used for profiling. Initialize data members allocating memory"""
        self.x, self.y, self.n = x, y, n

        self._fib_l: list[float] = list(range(n))
        self._fib_arr: NDArray[np.float64] = np.zeros(n, dtype=np.float64)

    def class_addition(self, x: float, y: float) -> float:
        """Return simple addition between x and y and data members"""
        return self.x + self.y + x + y

    def class_addition_three_times(self, x: float, y: float) -> float:
        """Return simple operation between x and y and data members"""
        var = x + y
        var /= 5
        var *= 7
        return var

    def class_fibonacci(self) -> list[float]:
        """Generate first n numbers of Fibonacci like sequence with memory already allocated"""
        if self.n <= 0:
            return self._fib_l

        self._fib_l[0] = 1.0

        if self.n > 1:
            self._fib_l[1] = 2.0
            for i in range(2, self.n):
                self._fib_l[i] = (self._fib_l[i - 1] + self._fib_l[i - 2]) / self.n * i

        return self._fib_l

    def class_fibonacci_numpy(self) -> NDArray[np.float64]:
        """Generate first n numbers of Fibonacci like sequence using numpy with memory already allocated"""
        if self.n <= 0:
            return self._fib_arr

        self._fib_arr[0] = 1.0

        if self.n > 1:
            self._fib_arr[1] = 2.0
            for i in range(2, self.n):
                self._fib_arr[i] = (self._fib_arr[i - 1] + self._fib_arr[i - 2]) / self.n * i

        return self._fib_arr