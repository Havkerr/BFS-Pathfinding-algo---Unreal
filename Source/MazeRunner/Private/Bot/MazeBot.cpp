// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeRunner/Public/Bot/MazeBot.h"
#include "TimerManager.h"
#include "Engine/World.h"

// Sets default values
AMazeBot::AMazeBot()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = StaticMesh;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BotMesh"));
	RootComponent = StaticMesh;

	// Try loading a built-in cube mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));

	if (MeshAsset.Succeeded())
	{
		StaticMesh->SetStaticMesh(MeshAsset.Object);
		StaticMesh->SetWorldScale3D(FVector(0.5f)); // Smaller size to fit on tile
	}
}

void AMazeBot::BeginPlay()
{
	Super::BeginPlay();

	CurrentIndex = 0;

	if (PathToFollow.Num() > 0)
	{
		MovetoNextTile();
	}
}

void AMazeBot::PathRecieved(TArray<AMazeTile*>& InPath)
{
	PathToFollow = InPath;
	CurrentIndex = 0;

	if (PathToFollow.Num() > 0)
	{
		MovetoNextTile();
	}
}

void AMazeBot::MovetoNextTile()
{
	if (CurrentIndex >= PathToFollow.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("Bot has finished the path"));
		return;
	}

	if (PathToFollow[CurrentIndex])
	{
		FVector TargetLocation = PathToFollow[CurrentIndex]->GetActorLocation();
		TargetLocation.Z += 50.0f;
		SetActorLocation(TargetLocation);

		UE_LOG(LogTemp, Warning, TEXT("Moving to next tile"));
		
	}
	CurrentIndex++;

	GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
	{
		GetWorld()->GetTimerManager().SetTimer(MovementTimerHandle, this, &AMazeBot::MovetoNextTile, MovementDelay, false);
	}
	);
}

// Called when the game starts or when spawned


// Called every frame


