# GVDB Unreal

NVDIA GVDB Library Implementation to UE5

## REQUIREMENTS

- NVIDIA Kepler generation or later GPU
- **CUDA Toolkit 6.5 or higher (Toolkit 10.2 recommended)**
- **Optix 6.5.0**
- CMake 3.10 or later

## INSTALLATION

1. Move to `GVDB_Library/src`
2. Modify macro of `env.h` to below

```cpp
// GVDB_Library/src/env.h
#ifndef CUDA_GVDB_COPYDATA_PTX_PATH
	#define	CUDA_GVDB_COPYDATA_PTX_PATH     "{PATH_TO_PTX_FOLDER}/cuda_gvdb_copydata.ptx"
#endif

#ifndef CUDA_GVDB_MODULE_PTX_PATH
	#define	CUDA_GVDB_MODULE_PTX_PATH       "{PATH_TO_PTX_FOLDER}/cuda_gvdb_module.ptx"
#endif

#ifndef CUDA_FLUID_PTX_PATH
	#define CUDA_FLUID_PTX_PATH             "{PATH_TO_PTX_FOLDER}/fluid_system_cuda.ptx"
#endif
```

> `{PATH_TO_PTX_FOLDER}` is located at `GVDB_Library/ptx`, but you should use absolute path

3. Modify Include Path & Library Path of CUDA / Optix SDK in `Source/UE_GVDBUE_GVDB.Build.cs`

```cpp
// Source/UE_GVDBUE_GVDB.Build.cs
...
// const string CUDAPath = "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v10.2";
const string CUDAPath = "{PATH_TO_CUDA_TOOLKIT_INSTALL_LOCATION}";
...
// const string OptixPath = "C:/ProgramData/NVIDIA Corporation/OptiX SDK 6.5.0";
const string OptixPath = "{PATH_TO_OPTIX_SDK_INSTALL_LOCATION}";
```

4. Generate Visual Studio project files (using `UE_GVDB.uproject`)
5. Open `UE_GVDB.sln`
6. Build and Launch

## [OPTIONAL] GVDB LIBRARY BUILD

1. Generate project files using CMake (`GVDB_Library/CMakeLists.txt`)
2. Open `gvdb.sln`
3. Set Output Directory of gvdb project as `GVDB_Library/lib` path _(ex. $`(SolutionDir)..\lib`)_
4. Set Target Extension of gvdb proejct as `Static Library (*.lib)`
5. Set Target File Extension of gvdb project as `.lib`
6. Build gvdb project (It will generate `gvdb.lib` at `GVDB_Library/lib`)
