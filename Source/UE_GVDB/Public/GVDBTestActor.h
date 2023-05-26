#pragma once

#include "CoreMinimal.h"
#include "fluid_emulator.h"
#include "GameFramework/Actor.h"
#include "GVDBTestActor.generated.h"

class StringBuffer
{
public:
	FString logBuffer[1024];
	FColor logColor[1024];
	FString lastErrorMsg;
	int logCursor = 0;
	int debugLogIndex = 0;

	static void PrintMsg(FString msg, FColor color);
	int AddToBuffer(FString msg, FColor color);
	void UpdateBuffer(int index, FString msg, FColor color);
	void RenderBuffer();
};

UCLASS()
class UE_GVDB_API AGVDBTestActor : public AActor
{
	GENERATED_BODY()
	
public:
	StringBuffer stringBuffer;
	FluidEmulator fluidEmulator;

	TArray<FVector> buffer;

	float prevTime;
	float elapsedTime;
	float tickGap = 0.02f;

	AGVDBTestActor();

	bool InitFluidEmulator();
	void FixedUpdate();

	UFUNCTION(BlueprintCallable, Category = "FluidEmulation")
	TArray<FVector> GetRenderBuffer();

protected:
	virtual void BeginPlay() override;
	void RenderFluidEmulation();

public:	
	virtual void Tick(float DeltaTime) override;
	
};
