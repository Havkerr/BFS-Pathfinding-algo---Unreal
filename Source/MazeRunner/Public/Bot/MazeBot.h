// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeRunner/Public/Core/MazeTile.h"
#include "MazeBot.generated.h"

UCLASS()
class MAZERUNNER_API AMazeBot : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMazeBot();

	//---------VARIABLE-----------

	//-------FUNCTION---------
	
		//Function to Recieve path from MazeManager
		void PathRecieved(TArray<AMazeTile*>& InPath);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//-------FUNCTION---------
	void MovetoNextTile();

	FTimerHandle MovementTimerHandle;


private:

	//---------VARIABLE-----------

	//Path Assigned to the bot.
	TArray<AMazeTile*> PathToFollow;

	int32 CurrentIndex = 0;

	UPROPERTY(EditAnywhere, Category = "MazeBot")
	float MovementDelay = 0.5f;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMesh;


};
