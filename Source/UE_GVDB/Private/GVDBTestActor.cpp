// Fill out your copyright notice in the Description page of Project Settings.


#include "GVDBTestActor.h"

// Sets default values
AGVDBTestActor::AGVDBTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGVDBTestActor::BeginPlay()
{
	Super::BeginPlay();
	if (!GVDBInit())
	{
		AddToBuffer(lastErrorMsg, FColor::Red);
	}
	else
	{
		AddToBuffer("GVDB Volume Init Success!", FColor::Green);
		AddToBuffer("", FColor::Cyan);
		updateIndex = AddToBuffer(FString::Printf(TEXT("Render volume. %6.3f ms"), 0.0f), FColor::Cyan);
	}
}

// Called every frame
void AGVDBTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GVDBRender();

	for (int i = logCursor - 1; i >= 0; i--)
	{
		PrintMsg(logBuffer[i], logColor[i]);
	}
}

