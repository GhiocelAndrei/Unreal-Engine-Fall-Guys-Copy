// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Levels/BasicObstacles/JuanRunUpDownObstacle.h"
#include "JuanRun_FirstLevel_SecondSpawner.generated.h"

UCLASS()
class JUANRUN_API AJuanRun_FirstLevel_SecondSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJuanRun_FirstLevel_SecondSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void SpawnObstacles();

private:
	int NrOfRows = 12; // we will have nrOfRows * nrOfRows objects

	UPROPERTY(EditDefaultsOnly, Category = "FirstLevel")
	TSubclassOf<AJuanRunUpDownObstacle> ObstacleClass;

};
