# Profiling Python C / C++ Extensions

This repo profiles a number of C and CPP python extensions determining which is the best for different use cases. 
The approaches profiled are:
1. Pure python
2. Pure CPP
3. Pybind11
4. Nanobind 

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

### Build Python Environment
```commandline
uv sync
```

### Run Profiler!
```commandline
uv run main.py
```