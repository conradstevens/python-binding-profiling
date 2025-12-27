from src.profiler import Profiler
from src import raw_python

# noinspection PyUnresolvedReferences
import sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent.parent))
# import cpp.pybind11_sand_box.build.pybind11_bindings as pybind11_bindings
# import cpp.pybind11_sand_box.cmake_build_debug.pybind11_bindings as pybind11_bindings
import cpp.pybind11_sand_box.cmake_build_release.pybind11_bindings as pybind11_bindings

NUM_TRIALS = 100_000
FIBONACCI_NUMBER = 1000


if __name__ == '__main__':
    print()
    print(f'NUM_TRIALS={NUM_TRIALS}')
    print(f'FIBONACCI_NUMBER={FIBONACCI_NUMBER}')

    Profiler.set_num_trials(NUM_TRIALS)
    Profiler.set_fib_num(FIBONACCI_NUMBER)

    # Profiler(modulo=raw_python, header="RAW PYTHON").profile()
    Profiler(modulo=pybind11_bindings, header="CPP PYBIND11").profile()