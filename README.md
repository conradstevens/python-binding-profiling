# Profiling Python C / C++ Extensions

This repo profiles tools used to improve the performance of python, determining which is the best for different use cases. 
The approaches profiled are:
1. Pure python
2. Pure CPP
3. Pybind11
4. Nanobind
5. C Python Package
5. Cython _TODO_
6. Nanobind _TODO_

_Pull requests profiling others are allways welcome :)_

## Building and Running
### Cloning
Clone the repo recursively getting the extension libraries from respective repos.

```commandline
git clone --recurse-submodules https://github.com/conradstevens/python-binding-profiling.git
cd python-binding-profiling
```

### Building Compiled Packages
C / CPP is compiled with optimization flags to profile release performance. 
Run the build script to build all compiled repos.
```commandline
./build.sh  # potentially requires: chmod +x build.sh 
```

### Run Profiler!
```commandline
uv run main.py
```
