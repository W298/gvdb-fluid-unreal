# Description-EN

- [Implementation](#implementation)
  - [1. Simulation Initialization](#1-simulation-initialization)
  - [2. Collision Handling](#2-collision-handling)
  - [3. Rendering Particle](#3-rendering-particle)
- [Particle Renderer](#particle-renderer)
  - [Sprite Renderer Example](#sprite-renderer-example)
  - [Mesh Renderer Example](#mesh-renderer-example)

## Implementation

There is a `FluidSystem` that implements FLIP using the GVDB Library, and a `FluidEmulator` that links it to Unreal Engine.

The `FluidSystem` uses the actual CUDA Kernel to simulate particles in the environment specified by the `FluidSystem`, while the `FluidEmulator` receives the particles' vector information and passes it to Unreal Engine.

To explain it step by step,

### 1. Simulation Initialization

![1](https://github.com/W298/gvdb-fluid-unreal/assets/25034289/0e181dc9-49fc-420a-946e-bc02748a525d)
![2](https://github.com/W298/gvdb-fluid-unreal/assets/25034289/6f8dac3c-8ac6-4aee-a13a-34296df51636)

In the Unreal Engine Editor, place the obstacles as Children of the `FluidEmulator` as shown above and start the simulation,

```cpp
bool AGVDBTestActor::InitFluidEmulator()
{
	float3 obsMaxAry[32];
	float3 obsMinAry[32];

	int i = 0;
	for (UStaticMeshComponent* SM : SMs)
	{
		const FVector relativePosition = SM->GetRelativeLocation();
		const FVector relativeScale = SM->GetRelativeScale3D();

		obsMaxAry[i] = make_float3(
			relativePosition.X + relativeScale.X * 125,
			relativePosition.Z + relativeScale.Z * 125 - relativeScale.Z * 125 * 2.35f,
			relativePosition.Y + relativeScale.Y * 125
		);
		obsMinAry[i] = make_float3(
			relativePosition.X - relativeScale.X * 125,
			relativePosition.Z - relativeScale.Z * 125 - relativeScale.Z * 125 * 2.35f,
			relativePosition.Y - relativeScale.Y * 125
		);

		i++;
	}

	return fluidEmulator.init(particleCnt, obsMinAry, obsMaxAry, obsCnt);
}
```

The `GVDBTestActor' that owns the `FluidEmulator' reads the Transforms of the objects placed as children at the start of the simulation, modifies them to match the Environment of the `FluidSystem', and passes them to the `FluidEmulator'.

```cpp
bool FluidEmulator::init(int numpnts, float3* obsMinAry, float3* obsMaxAry, int obsCnt)
{
	...

	// Initialize
	fluid.SetDebug(false);

	gvdb.SetDebug(false);
	gvdb.SetVerbose(false);
	gvdb.SetProfile(false, true);
	gvdb.SetCudaDevice(GVDB_DEV_FIRST);
	gvdb.Initialize();

	...

	// Configure volume
	reconfigure();

	// Initialize Fluid System
	m_numpnts = numpnts;

	fluid.Initialize();
	fluid.AddObstacleInformation(obsMinAry, obsMaxAry, obsCnt);
	fluid.Start(m_numpnts);

	...
}
```

The `FluidEmulator` then takes the Transform and Particle count of the Objects as parameters and proceeds to Initialize them.

### 2. Collision Handling

```cpp
void FluidSystem::AddObstacleInformation(float3* obsMinAry, float3* obsMaxAry, int obsCnt)
{
	m_Param[POBSCNT] = obsCnt;

	for (int i = 0; i < obsCnt; i++)
	{
		m_Ary[POBSMINARY][i] = obsMinAry[i];
		m_Ary[POBSMAXARY][i] = obsMaxAry[i];
	}

	m_Param[PGRAV] = 3.5f;
	m_Param[PVISC] = 1.50f;
}
```

Set the Transforms of the Objects received in the Initialize step to the Simulation Parameters.

```cpp
for (int o = 0; o < fparam.obsCnt; o++)
{
	for (int j = 0; j < 10; j++)
	{
		if (fparam.obsMinAry[o].x <= pos.x && pos.x <= fparam.obsMaxAry[o].x && fparam.obsMinAry[o].y <= pos.y&& pos.y <= fparam.obsMaxAry[o].y && (fparam.obsMaxAry[o].z - 1.0f * (float)j <= pos.z || pos.z <= fparam.obsMinAry[o].z + 1.0f * (float)j))
		{
			diff = fparam.pradius - (fparam.obsMinAry[o].z + 1.0f * (float)j - pos.z) * ss;
			if (diff > 0.001f && pos.z <= fparam.obsMinAry[o].z + 1.0f * (float)j && j == 0)
			{
				norm = make_float3(0, 0, -1);
				adj = fparam.pextstiff * diff - fparam.pdamp * dot(norm, veval);
				norm *= adj; accel += norm;
				break;
			}
			else if (diff > 0.001f && pos.z <= fparam.obsMinAry[o].z + 1.0f * (float)j && j != 0)
			{
				if (vel.z > 0)
					vel.z = -std::abs(vel.z * 0.8);
				break;
			}

			...
		}
	}
}
```

The actual collision handling is then done in the CUDA Kernel, which uses the parameter values set above to handle collision.

### 3. Rendering Particle

To get the position information of these simulated Particles into Unreal Engine, we return the reverse order of Initialize: `FluidSystem` -> `FluidEmulator` -> `GVDBTestActor`,

```cpp
void AGVDBTestActor::RenderFluidEmulation()
{
	const Vector3DF* map = fluidEmulator.display();
	TArray<FVector> buffer;
	for (int p = 0; p < fluidEmulator.m_numpnts; p++)
	{
		buffer.Add(FVector(map[p].x, map[p].y, map[p].z));
	}

	UNiagaraDataInterfaceArrayFunctionLibrary::SetNiagaraArrayVector(NiagaraComponent, "InputPositionArray", buffer);
}
```

In `GVDBTestActor`, insert values into Niagara's parameters as follows.

![3](https://github.com/W298/gvdb-fluid-unreal/assets/25034289/7af48c3f-4cf6-4ee1-9b51-cc625c814f30)
![4](https://github.com/W298/gvdb-fluid-unreal/assets/25034289/c3a18787-3912-4cca-9731-6d0e4f892ac5)

To actually render the Vector information received from the Niagara System, we created an `Update Position` module that sets the position of the Niagara Particles to the received Vector information. The Unique ID of the Niagara Particle was matched one-to-one with the Vector information using Index.

## Particle Renderer

We used two different Renderers for rendering: `Sprite Renderer` and `Mesh Renderer`.

![5](https://github.com/W298/gvdb-fluid-unreal/assets/25034289/8f300599-289c-4b5a-961e-27b75135ab1e)

For the `Sprite Renderer`, we created a Sprite Material like the one above to create a fluid-like look. This method has performance benefits since it is not rendering using an actual Mesh, but it is a bit awkward to achieve the appearance of a real fluid.   

### Sprite Renderer Example

https://github.com/W298/gvdb-fluid-unreal/assets/25034289/a8b596cd-d4fc-41c9-b544-915ba2ef7fc4

### Mesh Renderer Example

https://github.com/W298/gvdb-fluid-unreal/assets/25034289/9441a4b6-0c21-417a-8b61-5e5a886428a2
