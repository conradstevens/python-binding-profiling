import argparse
import sys
from pathlib import Path

import python_pacakge.raw_python as packaged_raw_python

sys.path.insert(0, "../../src")
# noinspection PyUnresolvedReferences
from python_binding_profiling.profiler import Profiler


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument("--num-trials", type=int, default=1_000)
    parser.add_argument("--fibonacci-number", type=int, default=10_000)
    parser.add_argument("--burner-trials", type=int, default=200)
    args = parser.parse_args()

    NUM_TRIALS: int = args.num_trials
    FIBONACCI_NUMBER: int = args.fibonacci_number
    BURNER_TRIALS: int = args.burner_trials

    print()
    print(f'PYPY - NUM_TRIALS={NUM_TRIALS}')
    print(f'PYPY - FIBONACCI_NUMBER={FIBONACCI_NUMBER}')
    print(f'PYPY - BURNER_TRIALS={FIBONACCI_NUMBER}')

    Profiler.set_num_trials(NUM_TRIALS)
    Profiler.set_fib_num(FIBONACCI_NUMBER)
    Profiler.set_burner_num(BURNER_TRIALS)

    pypy_profiler = Profiler(modulo=packaged_raw_python, header="PYPY")
    pypy_profiler.profile()
    pypy_profiler.save_results_to_json(Path("outputs"))