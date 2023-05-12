#pragma once

#include "CoreMinimal.h"
#include "fluid_emulator.h"
#include "GameFramework/Actor.h"
#include "GVDBTestActor.generated.h"

UCLASS()
class UE_GVDB_API AGVDBTestActor : public AActor
{
	GENERATED_BODY()
	
public:
	FString logBuffer[1024];
	FColor logColor[1024];
	FString lastErrorMsg;
	int logCursor = 0;
	int debugLogIndex = 0;

	FluidEmulator fluidEmulator;

	AGVDBTestActor();

	static void PrintMsg(FString msg, FColor color);
	int AddToBuffer(FString msg, FColor color);
	void UpdateBuffer(int index, FString msg, FColor color);
	bool InitFluidEmulator();
	void RenderFluidEmulation();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
};
