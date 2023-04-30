# GVDB Unreal

NVDIA GVDB Library Implementation to UE5

## REQUIREMENTS (gdvb-voxel library)

- NVIDIA Kepler generation or later GPU
- **CUDA Toolkit 6.5 or higher (Toolkit 10.2 recommended)**
- **Optix 6.5.0**
- CMake 3.10 or later

## INSTALLATION

1. Move to `GVDB_Library\src`
2. Modify macro of `gvdb_allocator.h`, `gvdb_volume_gvdb.h` to below

```cpp
// GVDB_Library/src/gvdb_allocator.h

// PTX module path
#define	CUDA_GVDB_COPYDATA_PTX_CUSTOM		"{PATH_TO_PTX_FOLDER}/cuda_gvdb_copydata.ptx"
```

```cpp
// GVDB_Library/src/gvdb_volume_gvdb.h

// PTX module path
#define	CUDA_GVDB_COPYDATA_PTX_CUSTOM		"{PATH_TO_PTX_FOLDER}/cuda_gvdb_module.ptx"
```

> `{PATH_TO_PTX_FOLDER}` is located at `GVDB_Library/ptx`, but you should use absolute path

3. Generate Visual Studio project files (using `UE_GVDB.uproject`)
4. Open `UE_GVDB.sln`
5. Build and Launch

## [Optional] GVDB LIBRARY BUILD

1. Generate project files using CMake (`GVDB_Library/CMakeLists.txt`)
2. Open `gvdb.sln`
3. Set Output Directory of gvdb project as `GVDB_Library/lib` path _(ex. $`(SolutionDir)..\lib`)_
4. Set Target Extension of gvdb proejct as `Static Library (*.lib)`
5. Set Target File Extension of gvdb project as `.lib`
6. Build gvdb project (It will generate `gvdb.lib` at `GVDB_Library/lib`)
