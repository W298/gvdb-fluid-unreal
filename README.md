# GVDB Fluid Unreal

NVDIA GVDB Library + Fluid Simulation Implementation to UE5

## REQUIREMENTS

- NVIDIA Kepler generation or later GPU
- **CUDA Toolkit 6.5 or higher (Toolkit 10.2 recommended)**
- **Optix 6.5.0**
- CMake 3.10 or later

## INSTALLATION

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
