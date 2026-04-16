import matplotlib.pyplot as plt
import numpy as np
from python_binding_profiling.profiler import Profiler


DARK_THEME = {
        'figure.facecolor': '#0d1117',
        'axes.facecolor': '#0d1117',
        'axes.edgecolor': '#30363d',
        'axes.labelcolor': '#8b949e',
        'axes.titlecolor': '#79c0ff',
        'xtick.color': '#8b949e',
        'ytick.color': '#8b949e',
        'grid.color': '#417A68',
        'text.color': '#c9d1d9',
        'figure.titlesize': 13,
        'axes.titlesize': 11,
    }

BAR_COLOR = '#238636'


class ProfilePlotter:

    def __init__(self, profilers: list[Profiler]):
        self._profilers: list[Profiler] = profilers
        self._headers: list[str] = [p.header for p in self._profilers]

    def profile_all(self) -> None:
        """Profile all the profilers"""
        for profiler in self._profilers:
            profiler.profile()

    def plot_time_averages(self, func_name: str, ax: plt.Axes = None):
        """Plot average time spent on `func_name` for each profiler"""
        if ax is None:
            with plt.rc_context(DARK_THEME):
                fig, ax = plt.subplots(figsize=(15, 3), layout='constrained')

        avg_func_profile_time: list[float] = [
            p.profile_results[func_name] * 1e6  # micro seconds
            for p in self._profilers
        ]

        ax.set_title('Absolute')
        ax.set_ylabel('Function time (μs)')
        ax.grid(True, alpha=0.2, axis='y')
        ax.bar(self._headers, avg_func_profile_time, color=BAR_COLOR)
        # ax.set_ylim([0, 250])

        if ax is None:
            plt.show()

    def plot_time_averages_rel(self, func_name: str, ax: plt.Axes = None):
        """Plot average time spent on `func_name` for each profiler, relative to the first profiler"""
        if ax is None:
            with plt.rc_context(DARK_THEME):
                fig, ax = plt.subplots(figsize=(15, 3), layout='constrained')

        avg_func_profile_time: list[float] = [
            p.profile_results[func_name]
            for p in self._profilers
        ]

        baseline = avg_func_profile_time[0]
        relative_times = [t / baseline for t in avg_func_profile_time]

        ax.set_title('Relative')
        ax.set_ylabel('Relative time (baseline = 1)')
        ax.grid(True, alpha=0.2, axis='y')
        ax.axhline(y=1, color='#f78166', linestyle='--', linewidth=0.8, alpha=0.7)
        ax.bar(self._headers, relative_times, color=BAR_COLOR)

        if ax is None:
            plt.show()

    def plot(self, func_name: str):
        """Plot both absolute and relative time averages for `func_name` in a single figure"""
        with plt.rc_context(DARK_THEME):
            fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(15, 7))
            fig.suptitle(func_name, fontsize=16, fontweight='bold')
            fig.subplots_adjust(top=0.90, hspace=0.35)

            self.plot_time_averages(func_name, ax=ax1)
            self.plot_time_averages_rel(func_name, ax=ax2)
            fig.savefig(f"plot_outputs/{func_name}.png", bbox_inches="tight")
            plt.show()