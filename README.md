![header](https://github.com/W298/gvdb-fluid-unreal/assets/25034289/b1602e50-394c-4a1b-af73-fcec15ba99a9)

# gvdb-fluid-unreal

## About this repository

Implement Fluid Simulation (FLIP) on Unreal Engine 5 with NVIDIA GVDB Library.  
The particles are simulated with a Niagara system.

> Reference Paper
> - [Fast Fluid Simulations with Sparse Volumes on the GPU](https://www.researchgate.net/publication/325488464_Fast_Fluid_Simulations_with_Sparse_Volumes_on_the_GPU)
> - https://people.csail.mit.edu/kuiwu/gvdb_sim.html

## Requirements

- NVIDIA Kepler generation or later GPU
- **CUDA Toolkit 6.5 or later (Toolkit 10.2 recommended)**
- **Visual Studio 16 2019 or later**
- CMake 3.10 or later

Tested on CUDA Toolkit 10.2 & Visual Studio 16 2019 only. Other versions may not work properly.

## Installation Guide

### 1. BUILD

1. Move to `GVDB_Library` Directory
2. Generate files using CMake (Put your CUDA Path at argument)

```bash
cmake -B ./build -G "Visual Studio 16 2019" -DCUDA_PATH_BUILD="YOUR_CUDA_PATH"
```

```bash
# Example
cmake -B ./build -G "Visual Studio 16 2019" -DCUDA_PATH_BUILD="C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v10.2"
```

3. Open `build/gvdb.sln`
4. Set Output Directory of gvdb project as `GVDB_Library/lib` path _(ex. $`(SolutionDir)..\lib`)_
5. Set Target Extension of gvdb proejct as `Static Library (*.lib)`
6. Set Target File Extension of gvdb project as `.lib`
7. Build gvdb project with 'Release' (It will generate `gvdb.lib` at `GVDB_Library/lib`)

### 2. LAUNCH

1. Generate Visual Studio project files (using `UE_GVDB.uproject`)
2. Open `UE_GVDB.sln`
3. Build and Launch
