// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Levels/BasicObstacles/JuanRunRotatingObstacle.h"
#include "JuanRun_FirstLevel_FirstSpawner.generated.h"

UCLASS()
class JUANRUN_API AJuanRun_FirstLevel_FirstSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJuanRun_FirstLevel_FirstSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void SpawnObstacles();

private:
	int NrOfSpinners = 3; // number of spinner objects that will be spawned
	int NrOfHammers = 2; // number of hammer objects that will be spawned

	UPROPERTY(EditDefaultsOnly, Category = "FirstLevel")
	TSubclassOf<AJuanRunRotatingObstacle> SpinnerObstacleClass;

	UPROPERTY(EditDefaultsOnly, Category = "FirstLevel")
	TSubclassOf<AJuanRunRotatingObstacle> HammerObstacleClass;
};
