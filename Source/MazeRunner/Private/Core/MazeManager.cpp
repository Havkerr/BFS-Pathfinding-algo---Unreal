// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/MazeManager.h"
#include "MazeRunner/Public/Core/MazeTile.h"             // ✅ Needed for AMazeTile class
#include "Engine/World.h"
#include "Bot/MazeBot.h"
#include "GameFramework/Actor.h"


// Sets default values
AMazeManager::AMazeManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AMazeManager::BeginPlay()
{
	Super::BeginPlay();
	if (!TileClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("TileClass is not set in MazeManager"));
		return;
	}

	
	MazeGrid.SetNum(GridSizeX);;
	for (int32 X =0; X<GridSizeX; X++)
	{
		MazeGrid[X].SetNum(GridSizeY);
		for (int32 Y=0; Y<GridSizeY; Y++)
		{
			//Calculate the world position where the tiles should spawn
			FVector SpawnLocation = FVector(X*TileSpacing, Y*TileSpacing, 0.f);

			//Setting no Rotation
			FRotator SpawnRotation = FRotator::ZeroRotator;

			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;

			//Spawn this tile in the world location using MazeTile class
			AMazeTile* SpawnTile = GetWorld()->SpawnActor<AMazeTile>(TileClass, SpawnLocation, SpawnRotation, SpawnParams);

			if (SpawnTile)
			{
				MazeGrid[X][Y] = SpawnTile;
				SpawnTile->GridX = X;
				SpawnTile->GridY = Y;
			}
		}
	}

	UE_LOG(LogTemp, Log, TEXT("MazeGrid generated"));

	AMazeTile* StartTile = MazeGrid[0][0];
	AMazeTile* EndTile = MazeGrid[4][4];
	RunBfs(StartTile, EndTile);
}

TArray<AMazeTile*> AMazeManager::GetWalkableNeighbors(AMazeTile* Tile)
{
	TArray<AMazeTile*> Neighbors;

	int32 X = Tile->GridX;
	int32 Y = Tile->GridY;

	//const TArray<FIntPoint> Direction;
	int Dx[4] = {0,0,1,-1};
	int Dy[4] = {1,-1,0,0};

	for (int i =0; i<4; i++)
	{
		int NewX = X + Dx[i];
		int NewY = Y + Dy[i];

		if (NewX >= 0 && NewX < GridSizeX && NewY >= 0 && NewY < GridSizeY)
		{
			AMazeTile* Neighbor = MazeGrid[NewX][NewY];
			
			if (Neighbor && !Neighbor->bIsWall)
			Neighbors.Add(Neighbor);
		}	
	}
	return Neighbors;
}

void AMazeManager::RunBfs(AMazeTile* StartTile, AMazeTile* EndTile)
{
	if (!StartTile || !EndTile || StartTile == EndTile)
	{
		return;
	}

	TQueue<AMazeTile*>Queue;
	TSet<AMazeTile*> Visited;
	TMap<AMazeTile*, AMazeTile*> ParentMap;

	Queue.Enqueue(StartTile);
	Visited.Add(StartTile);

	bool bIsPathFound = false;

	while (!Queue.IsEmpty())
	{
		AMazeTile* CurrentTile;
		
		Queue.Dequeue(CurrentTile);
		CurrentTile->SetVisitedVisual();
		
		if (CurrentTile == EndTile)
		{
			bIsPathFound = true;
			break;
		}

		TArray<AMazeTile*> Neighbors = GetWalkableNeighbors(CurrentTile);
		for (AMazeTile* Neighbor : Neighbors)
		{
			if (!Visited.Contains(Neighbor))
			{
				Queue.Enqueue(Neighbor);
				Visited.Add(Neighbor);
				ParentMap.Add(Neighbor, CurrentTile);
			}
		}
	}

	if (bIsPathFound)
	{
		TArray<AMazeTile*> Path;
		AMazeTile* Tile = EndTile;

		while (Tile && Tile != StartTile)
		{
			Path.Insert(Tile, 0);
			Tile = ParentMap.FindRef(Tile);
		}

		Path.Insert(StartTile, 0);

		for (AMazeTile* PathTile : Path)
		{
			PathTile->SetPathVisual();
			UE_LOG(LogTemp, Warning, TEXT("Path Tile: %d, %d"), PathTile->GridX, PathTile->GridY);

		}

		if (MazeBot)
		{
			MazeBot->PathRecieved(Path);
		}
	}
}



