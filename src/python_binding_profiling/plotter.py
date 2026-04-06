import matplotlib.pyplot as plt
import numpy as np
from python_binding_profiling.profiler import Profiler


class ProfilePlotter:

    def __init__(self, profilers: list[Profiler]):
        self._profilers: list[Profiler] = profilers
        self._headers: list[str] = [p.header for p in self._profilers]

    def profile_all(self) -> None:
        """Profile all the profilers"""
        for profiler in self._profilers:
            profiler.profile()

    def plot_time_averages(self, func_name: str):
        """Plot average time spent on `func_name` for each profiler"""
        fig, ax = plt.subplots(figsize=(10, 3), layout='constrained')

        avg_func_profile_time: list[float] = [
            p.profile_results[func_name] * 1e9  # nano seconds
            for p in self._profilers
        ]

        ax.set_title(func_name)
        ax.set_ylabel('Function time (ns)')
        ax.grid(True, alpha=0.2, axis='y')
        ax.bar(self._headers, avg_func_profile_time)

        plt.show()