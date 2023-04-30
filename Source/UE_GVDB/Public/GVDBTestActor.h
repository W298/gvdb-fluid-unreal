// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "gvdb.h"
#include "GameFramework/Actor.h"
#include "GVDBTestActor.generated.h"

UCLASS()
class UE_GVDB_API AGVDBTestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGVDBTestActor();

	bool GVDBTestFunc()
	{
		VolumeGVDB gvdb;
		gvdb.SetDebug(false);
		gvdb.SetVerbose(true);
		gvdb.SetProfile(false, true);
		gvdb.SetCudaDevice(GVDB_DEV_FIRST);
		gvdb.Initialize();
		return false;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
