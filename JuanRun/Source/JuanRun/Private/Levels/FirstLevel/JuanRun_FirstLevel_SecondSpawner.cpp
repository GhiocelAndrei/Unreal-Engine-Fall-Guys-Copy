// Fill out your copyright notice in the Description page of Project Settings.


#include "Levels/FirstLevel/JuanRun_FirstLevel_SecondSpawner.h"

// Sets default values
AJuanRun_FirstLevel_SecondSpawner::AJuanRun_FirstLevel_SecondSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AJuanRun_FirstLevel_SecondSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnObstacles();
}

// Called every frame
void AJuanRun_FirstLevel_SecondSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AJuanRun_FirstLevel_SecondSpawner::SpawnObstacles()
{
	// Location of the first obstacle
	// We will generate the locations for the other actors in the for loop below
	FVector initialLocation = FVector(1220.f, 6160.f, 810.f);

	// Create an array of spawn locations
	TArray<FVector> spawnLocations;
	
	float distance = 120.f;

	for (int i = 0; i < NrOfRows; i++)
		for(int j= 0; j < NrOfRows; j++)
		{
			spawnLocations.Add(FVector(initialLocation.X + i * distance, initialLocation.Y + j * distance, initialLocation.Z));
		}

	// Spawn actors at each location in the array

	for (FVector location : spawnLocations)
	{
		AJuanRunUpDownObstacle* newActor = GetWorld()->SpawnActor<AJuanRunUpDownObstacle>(ObstacleClass, location, FRotator::ZeroRotator);
	}
}