// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class UE_GVDB : ModuleRules
{
	private string ProjectRootPath => Path.Combine(ModuleDirectory, "../..");

	public UE_GVDB(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "OpenGL" });
		PrivateDependencyModuleNames.AddRange(new string[] {  });

		const string GVDBIncludePath = "GVDB_Library/src";
		const string GVDBLibraryPath = "GVDB_Library/lib";

		PublicIncludePaths.Add(Path.Combine(ProjectRootPath, GVDBIncludePath));
		PublicAdditionalLibraries.Add(Path.Combine(ProjectRootPath, GVDBLibraryPath, "gvdb.lib"));

		const string GLEWIncludePath = "GVDB_Library/glew/include";
		const string GLEWLibraryPath = "GVDB_Library/lib";

		PublicIncludePaths.Add(Path.Combine(ProjectRootPath, GLEWIncludePath));
		PublicAdditionalLibraries.Add(Path.Combine(ProjectRootPath, GLEWLibraryPath, "glew32.lib"));

		const string CUDAPath = "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v10.2";
		const string CUDAIncludePath = "include";
		const string CUDALibraryPath = "lib/x64";

		PublicIncludePaths.Add(Path.Combine(CUDAPath, CUDAIncludePath));
		PublicAdditionalLibraries.Add(Path.Combine(CUDAPath, CUDALibraryPath, "cuda.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(CUDAPath, CUDALibraryPath, "cudadevrt.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(CUDAPath, CUDALibraryPath, "cudart.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(CUDAPath, CUDALibraryPath, "cudart_static.lib"));

		const string OptixPath = "C:/ProgramData/NVIDIA Corporation/OptiX SDK 6.5.0";
		const string OptixIncludePath = "include";
		const string OptixLibraryPath = "lib64";

		PublicIncludePaths.Add(Path.Combine(OptixPath, OptixIncludePath));
		PublicAdditionalLibraries.Add(Path.Combine(OptixPath, OptixLibraryPath, "optix.6.5.0.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(OptixPath, OptixLibraryPath, "optixu.6.5.0.lib"));
	}
}
