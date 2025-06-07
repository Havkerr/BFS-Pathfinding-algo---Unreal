// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bot/MazeBot.h"
#include "GameFramework/Actor.h"
#include "MazeRunner/Public/Core/MazeTile.h"
#include "MazeManager.generated.h"

UCLASS()
class MAZERUNNER_API AMazeManager : public AActor
{
	GENERATED_BODY()

public:

	//---------VARIABLE-----------
	// Sets default values for this actor's properties
	AMazeManager();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	int32 GridSizeX = 5.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	int32 GridSizeY = 5.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	float TileSpacing = 200.0f;

	UPROPERTY(EditAnywhere)
	AMazeBot* MazeBot;
	// Tile Class to Spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	TSubclassOf<AMazeTile> TileClass;

	//making 2D array to store maze grid;
	TArray<TArray<AMazeTile*>> MazeGrid;

	



	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

	//------Function------
	TArray<AMazeTile*> GetWalkableNeighbors(AMazeTile* Tile);

	void RunBfs(AMazeTile* StartTile, AMazeTile* EndTile);
	

	

};
