#pragma once

#include "CoreMinimal.h"
#include "fluid_emulator.h"
#include "GameFramework/Actor.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraDataInterfaceArrayFunctionLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
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

	float prevTime;
	float elapsedTime;
	float tickGap = 0.02f;

	int particleCnt = 500000;
	int obsCnt = 3;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FluidEmulation")
	UStaticMeshComponent* SM0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FluidEmulation")
	UStaticMeshComponent* SM1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FluidEmulation")
	UStaticMeshComponent* SM2;

	TArray<UStaticMeshComponent*> SMs;

	AGVDBTestActor();

	bool InitFluidEmulator();
	void FixedUpdate();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FluidEmulation")
	UNiagaraComponent* NiagaraComponent;

protected:
	virtual void BeginPlay() override;
	void RenderFluidEmulation();

public:	
	virtual void Tick(float DeltaTime) override;
	
};
