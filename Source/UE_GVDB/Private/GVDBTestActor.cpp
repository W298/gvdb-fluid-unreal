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
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, GVDBTestFunc() ? "True" : "False");
}

// Called every frame
void AGVDBTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

