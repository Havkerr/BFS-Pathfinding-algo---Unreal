// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeTile.generated.h"

UCLASS()
class MAZERUNNER_API AMazeTile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMazeTile();
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bIsWall;
	int32 GridX;
	int32 GridY;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void SetVisitedVisual();

	UFUNCTION(BlueprintImplementableEvent)
	void SetPathVisual();

};
