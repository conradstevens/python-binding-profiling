from profiler import Profiler

import raw_python
# noinspection PyUnresolvedReferences
import cpp.binding_sand_box.build.pybind11_bindings as pybind11_bindings

NUM_TIRALS = 100
FIBONACCI_NUMBER = 500
LOUP_NUMBER = 1


if __name__ == '__main__':
    print()
    print(f'NUM_TIRALS={NUM_TIRALS}')
    print(f'FIBONACCI_NUMBER={FIBONACCI_NUMBER}')

    Profiler.set_num_trials(NUM_TIRALS)
    Profiler.set_fib_num(FIBONACCI_NUMBER)

    Profiler(modulo=raw_python, header="RAW PYTHON").profile()
    Profiler(modulo=pybind11_bindings, header="CPP PYBIND11").profile()