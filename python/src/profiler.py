import logging
import shutil
import types
from time import time
from typing import Callable, Type, Protocol


logger = logging.Logger(__name__)


class ModuleProtocol(Protocol):
    __all__: list[str]

    @staticmethod
    def addition(x: float, y: float) -> float: pass

    @staticmethod
    def addition_three_times(x: float, y: float) -> float: pass

    @staticmethod
    def fibonacci(n: int) -> list[float]: pass

    @staticmethod
    def fibonacci_numpy(n: int) -> int: pass

    MyClass: Type


class Profiler:
    ## Number of trials repeated to profile
    _NUM_TRIALS: int = None

    ## Number of fibonacci sequence to go to
    _FIB_NUM: int = None

    ## Number of trials to run before profiling
    _BURNER_TRIALS: int = 100

    def __init__(
            self,
            modulo: ModuleProtocol | types.ModuleType,
            header: str,
    ) -> None:
        ## Module used to call functions
        self._m: ModuleProtocol = modulo

        ## Header used to describe what is being profiled
        self._header: str = header

        ## Make class to call functions for
        self._m_class = self._m.MyClass(99, 100, self._FIB_NUM)

    def profile(self):
        """Profile all elements being tested and prints their results"""
        self.print_heading()
        self.profile_func(self._m.addition, 99, 100)
        self.profile_func(self._m.addition_three_times, 99, 100)
        self.profile_func(self._m.fibonacci, self._FIB_NUM)
        self.profile_func(self._m.fibonacci_numpy, self._FIB_NUM)
        self.profile_func(self._m.MyClass, 99, 100, self._FIB_NUM)
        self.profile_func(self._m_class.class_addition, 99, 100)
        self.profile_func(self._m_class.class_addition_three_times, 99, 100)
        self.profile_func(self._m_class.class_fibonacci)
        self.profile_func(self._m_class.class_fibonacci_numpy)

    @classmethod
    def profile_func(cls, obj: Callable, *args, **kwargs):
        # Setting cache
        for i in range(cls._BURNER_TRIALS):
            _ = obj(*args, **kwargs)

        lapsed_time = 0
        for i in range(cls._NUM_TRIALS):
            start_time = time()
            _ = obj(*args, **kwargs)
            end_time = time()
            lapsed_time += (end_time - start_time)
        print(f"{obj.__name__}: {round(lapsed_time, 4)}")

    @classmethod
    def set_num_trials(cls, num_trials: int):
        if cls._NUM_TRIALS is None:
            if isinstance(num_trials, int) and num_trials > 0:
                cls._NUM_TRIALS = num_trials
            else:
                logger.warning(f"Invalid value for Profiler._NUM_TRIALS: {num_trials}\n"
                               f"Value not set.")
        else:
            logger.warning(f"Profiler._NUM_TRIALS can only be set once, is still: {cls._NUM_TRIALS}")

    @classmethod
    def set_fib_num(cls, fib_num: int):
        if cls._FIB_NUM is None:
            if isinstance(fib_num, int) and fib_num > 0:
                cls._FIB_NUM = fib_num
            else:
                logger.warning(f"Invalid value for Profiler._FIB_NUM: {fib_num}\n"
                               f"Value not set.")
        else:
            logger.warning(f"Profiler._FIB_NUM can only be set once, is still: {cls._FIB_NUM}")

    def print_heading(self):
        """Print start heading"""
        # Get terminal width, default to 80 if unable to determine
        try:
            width = shutil.get_terminal_size().columns
        except (AttributeError, OSError):
            width = 80

        # Print top border
        print()
        print('#' * width)

        # Calculate padding for centered heading
        if len(self._header) < width - 4:  # -4 for "- " and " -"
            padding = (width - len(self._header) - 4) // 2
            line = '-' * padding + f' {self._header} ' + '-' * padding
            # Add extra dash if width is odd
            if len(line) < width:
                line += '-'
        else:
            # Message too long, truncate
            line = f' {self._header[:width - 4]} '

        print(line)

        # Print bottom border
        print('#' * width)
        print()