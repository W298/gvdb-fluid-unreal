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
}

bool AGVDBTestActor::InitFluidEmulator()
{
	return fluidEmulator.init(150000);
}

void AGVDBTestActor::FixedUpdate()
{
	stringBuffer.RenderBuffer();
	RenderFluidEmulation();
}

TArray<FVector> AGVDBTestActor::GetRenderBuffer()
{
	return buffer;
}

void AGVDBTestActor::BeginPlay()
{
	Super::BeginPlay();

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
	buffer.Empty();

	const Vector3DF* map = fluidEmulator.display();
	for (int p = 0; p < fluidEmulator.m_numpnts; p++)
	{
		buffer.Add(FVector(map[p].x, map[p].y, map[p].z));
	}
}

void AGVDBTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	elapsedTime += DeltaTime;
	if (elapsedTime - prevTime < tickGap) return;

	FixedUpdate();

	prevTime = elapsedTime;
}
