#include "GVDBTestActor.h"

AGVDBTestActor::AGVDBTestActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGVDBTestActor::PrintMsg(FString msg, FColor color)
{
	GEngine->AddOnScreenDebugMessage(-1, 0, color, msg);
}

int AGVDBTestActor::AddToBuffer(FString msg, FColor color)
{
	logBuffer[logCursor] = msg;
	logColor[logCursor++] = color;
	return logCursor - 1;
}

void AGVDBTestActor::UpdateBuffer(int index, FString msg, FColor color)
{
	logBuffer[index] = msg;
	logColor[index] = color;
}

bool AGVDBTestActor::InitFluidEmulator()
{
	return fluidEmulator.init(1000000);
}

void AGVDBTestActor::RenderFluidEmulation()
{
	const char* info = fluidEmulator.display(25);
	UpdateBuffer(debugLogIndex, FString::Printf(TEXT("Particle %d %hs"), 25, info), FColor::Cyan);
}

void AGVDBTestActor::BeginPlay()
{
	Super::BeginPlay();
	if (!InitFluidEmulator())
	{
		lastErrorMsg = "Emulation Init Failed";
		AddToBuffer(lastErrorMsg, FColor::Red);
	}
	else
	{
		AddToBuffer("Start Emulation", FColor::Green);
		AddToBuffer("", FColor::Cyan);
		debugLogIndex = AddToBuffer(FString::Printf(TEXT("")), FColor::Cyan);
	}
}

void AGVDBTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RenderFluidEmulation();

	for (int i = logCursor - 1; i >= 0; i--)
	{
		PrintMsg(logBuffer[i], logColor[i]);
	}
}
