import argparse
import sys
from pathlib import Path

import pure_python.raw_python as packaged_raw_python

sys.path.insert(0, "../../src")
# noinspection PyUnresolvedReferences
from python_binding_profiling.profiler import Profiler

if __name__ == '__main__':
    NUM_TRIALS = 1_000
    FIBONACCI_NUMBER = 1_000
    BURNER_TRIALS = 200

    Profiler.set_num_trials(NUM_TRIALS)
    Profiler.set_fib_num(FIBONACCI_NUMBER)
    Profiler.set_burner_num(BURNER_TRIALS)

    pypy_profiler = Profiler(modulo=packaged_raw_python, header="PYPY")
    pypy_profiler.profile()
    pypy_profiler.save_results_to_json(Path("outputs"))