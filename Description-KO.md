# Description-KO

- [구현](#구현)
  - [1. Simulation Initialization](#1-simulation-initialization)
  - [2. Collision Handling](#2-collision-handling)
  - [3. Rendering Particle](#3-rendering-particle)
- [Particle Renderer](#particle-renderer)
  - [Sprite Renderer Example](#sprite-renderer-example)
  - [Mesh Renderer Example](#mesh-renderer-example)

## 구현

GVDB Library 를 이용해 FLIP 이 구현된 `FluidSystem` 이 있고, 이를 Unreal Engine 과 Linking 하는 `FluidEmulator` 로 구성되어 있다.

`FluidSystem` 은 실제 CUDA Kernel 을 이용해 `FluidSystem` 에서 지정한 Environment 에서 Particle 들을 시뮬레이팅하고, `FluidEmulator` 는 파티클의 Vector 정보들을 받아 이를 Unreal Engine 에 전달한다.

Step by Step 으로 설명하자면,

### 1. Simulation Initialization

![1](https://github.com/W298/gvdb-fluid-unreal/assets/25034289/0e181dc9-49fc-420a-946e-bc02748a525d)
![2](https://github.com/W298/gvdb-fluid-unreal/assets/25034289/6f8dac3c-8ac6-4aee-a13a-34296df51636)

위와 같이 Unreal Engine Editor 에서 `FluidEmulator` 의 Child 로 장애물들을 배치한 뒤 Simulation 을 시작하면,

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

`FluidEmulator` 를 소유한 `GVDBTestActor` 가 Simulation 시작 시 Child 로 배치된 오브젝트들의 Transform 을 읽고, 이를 `FluidSystem` 의 Environment 에 맞게 수정한 뒤 `FluidEmulator` 에게 전달한다.

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

그러면 `FluidEmulator` 는 Parameter 로 받은 Obstacle 들의 Transform 과 Particle 수를 받아 Initalize 를 진행한다.

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

Initialize 단계에서 받은 Obstacle 들의 Transform 들을 Simulation Parameter 로 설정한다.

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

이후 실제 Collision Handling 은 CUDA Kernel 에서 진행되는데, 이때 위에서 설정한 Parameter 값을 이용해 Particle 들의 충돌 처리를 진행한다.

### 3. Rendering Particle

이렇게 Simulating 한 Particle 들의 위치 정보를 Unreal Engine 으로 가져오기 위해 Initialize 의 역순인 `FluidSystem` -> `FluidEmulator` -> `GVDBTestActor` 순으로 리턴하여 가져오고,

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

`GVDBTestActor` 에서 다음과 같이 Niagara 의 Parameter 에 값을 넣어준다.

![3](https://github.com/W298/gvdb-fluid-unreal/assets/25034289/7af48c3f-4cf6-4ee1-9b51-cc625c814f30)
![4](https://github.com/W298/gvdb-fluid-unreal/assets/25034289/c3a18787-3912-4cca-9731-6d0e4f892ac5)

Niagara System 에서 받은 Vector 정보들을 실제로 Rendering 하기 위해서, Niagara Particle 들의 Position 을 받은 Vector 정보로 설정하는 `Update Position` 모듈을 만들었다. Niagara Particle 의 Unique ID 를 Index 를 이용하여 Vector 정보와 일대일 매칭을 시켰다.

## Particle Renderer

`Sprite Renderer`, `Mesh Renderer` 두 가지 Renderer 를 이용해 렌더링을 진행하였다.

![5](https://github.com/W298/gvdb-fluid-unreal/assets/25034289/8f300599-289c-4b5a-961e-27b75135ab1e)

`Sprite Renderer` 의 경우 위와 같은 Sprite Material 을 만들어 액체와 비슷한 느낌을 만들었다. 실제 Mesh 를 사용하여 렌더링 하는 것이 아니므로 성능상 이점이 있으나, 실제 유체의 입자와 같은 모습을 표현하기에는 조금 어색한 부분이 있다.  

### Sprite Renderer Example

https://github.com/W298/gvdb-fluid-unreal/assets/25034289/a8b596cd-d4fc-41c9-b544-915ba2ef7fc4

### Mesh Renderer Example

https://github.com/W298/gvdb-fluid-unreal/assets/25034289/9441a4b6-0c21-417a-8b61-5e5a886428a2
