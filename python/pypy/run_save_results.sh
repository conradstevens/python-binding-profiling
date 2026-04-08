#!/bin/bash

mkdir "outputs"
uv venv --python pypy3.10 pypy_venv
source pypy_venv/bin/activate

# uv sync --active  # Installs and builds the wrong binaries of numpy
pip install "numpy>=1.24.4"
pip install ../pure_python/dist/pure_python_package-0.1.0-py3-none-any.whl

python save_results.py

deactivate