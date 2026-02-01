from src.profiler import Profiler
from src import raw_python
from pathlib import Path

# noinspection PyUnresolvedReferences
import cpp.pybind11_sand_box.cmake_build_release.pybind11_bindings as pybind11_bindings
# noinspection PyUnresolvedReferences
import cpp.nanobind_sand_box.cmake_build_release.nano_bindings as nano_bindings

NUM_TRIALS = 1_000
FIBONACCI_NUMBER = 1_000
BURNER_TRIALS = 100


if __name__ == '__main__':
    print()
    print(f'NUM_TRIALS={NUM_TRIALS}')
    print(f'FIBONACCI_NUMBER={FIBONACCI_NUMBER}')

    Profiler.set_num_trials(NUM_TRIALS)
    Profiler.set_fib_num(FIBONACCI_NUMBER)
    Profiler.set_burner_num(BURNER_TRIALS)

    Profiler(modulo=raw_python, header="RAW PYTHON").profile()
    Profiler(modulo=pybind11_bindings, header="CPP PYBIND11").profile()
    Profiler(modulo=nano_bindings, header="CPP NANOBIND").profile()
    Profiler.run_pure_cpp(rel_path=Path("./cpp/pure_cpp/cmake_build_release/pure_cpp"))