#include "GVDBTestActor.h"

void StringBuffer::PrintMsg(FString msg, FColor color)
{
	GEngine->AddOnScreenDebugMessage(-1, 0, color, msg);
}

int StringBuffer::AddToBuffer(FString msg, FColor color)
{
	logBuffer[logCursor] = msg;
	logColor[logCursor++] = color;
	return logCursor - 1;
}

void StringBuffer::UpdateBuffer(int index, FString msg, FColor color)
{
	logBuffer[index] = msg;
	logColor[index] = color;
}

void StringBuffer::RenderBuffer()
{
	for (int i = logCursor - 1; i >= 0; i--)
	{
		PrintMsg(logBuffer[i], logColor[i]);
	}
}

AGVDBTestActor::AGVDBTestActor()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));

	SM0 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM-0"));
	SM1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM-1"));
	SM2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM-2"));

	SMs.Add(SM0);
	SMs.Add(SM1);
	SMs.Add(SM2);
}

bool AGVDBTestActor::InitFluidEmulator()
{
	float3 obsMaxAry[32];
	float3 obsMinAry[32];

	int i = 0;
	for (UStaticMeshComponent* SM : SMs)
	{
		const FVector relativePosition = SM->GetRelativeLocation();
		const FVector relativeScale = SM->GetRelativeScale3D();

		obsMaxAry[i] = make_float3(relativePosition.X + relativeScale.X * 125, relativePosition.Z + relativeScale.Z * 125 - relativeScale.Z * 125 * 2.35f, relativePosition.Y + relativeScale.Y * 125);
		obsMinAry[i] = make_float3(relativePosition.X - relativeScale.X * 125, relativePosition.Z - relativeScale.Z * 125 - relativeScale.Z * 125 * 2.35f, relativePosition.Y - relativeScale.Y * 125);

		i++;
	}

	return fluidEmulator.init(particleCnt, obsMinAry, obsMaxAry, obsCnt);
}

void AGVDBTestActor::FixedUpdate()
{
	stringBuffer.RenderBuffer();
	RenderFluidEmulation();
}

void AGVDBTestActor::BeginPlay()
{
	Super::BeginPlay();

	NiagaraComponent->SetNiagaraVariableInt("ParticleNum", particleCnt);

	if (!InitFluidEmulator())
	{
		stringBuffer.lastErrorMsg = "Emulation Init Failed";
		stringBuffer.AddToBuffer(stringBuffer.lastErrorMsg, FColor::Red);
	}
	else
	{
		stringBuffer.AddToBuffer("Start Emulation", FColor::Green);
		stringBuffer.AddToBuffer("", FColor::Cyan);
		stringBuffer.debugLogIndex = stringBuffer.AddToBuffer(FString::Printf(TEXT("")), FColor::Cyan);
	}

	RenderFluidEmulation();
}

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

void AGVDBTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	elapsedTime += DeltaTime;
	if (elapsedTime - prevTime < tickGap) return;

	FixedUpdate();

	prevTime = elapsedTime;
}
