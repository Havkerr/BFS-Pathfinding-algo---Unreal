// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeRunner/Public/Core/MazeTile.h"


// Sets default values
AMazeTile::AMazeTile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMazeTile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMazeTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



