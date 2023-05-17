// Fill out your copyright notice in the Description page of Project Settings.


#include "Levels/FirstLevel/JuanRun_FirstLevel_FirstSpawner.h"

// Sets default values
AJuanRun_FirstLevel_FirstSpawner::AJuanRun_FirstLevel_FirstSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AJuanRun_FirstLevel_FirstSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnObstacles();
}

// Called every frame
void AJuanRun_FirstLevel_FirstSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AJuanRun_FirstLevel_FirstSpawner::SpawnObstacles()
{
	// Location of the first obstacle
	// We will generate the locations for the other actors in the for loop below
	FVector initialSpinnerLocation = FVector(1860.f, 2880.f, 830.f);
	FVector initialHammerLocation = FVector(1850.f, 3420.f, 1830.f);

	// Create an array of spawn locations
	TArray<FVector> spinnerSpawnLocations;
	TArray<FVector> hammerSpawnLocations;
	float y_distance = 1060.f;
	
	for (int i = 0; i < NrOfSpinners; i++)
	{
		spinnerSpawnLocations.Add(FVector(initialSpinnerLocation.X, initialSpinnerLocation.Y + i * y_distance, initialSpinnerLocation.Z));
	}

	for (int i = 0; i < NrOfHammers; i++)
	{
		hammerSpawnLocations.Add(FVector(initialHammerLocation.X, initialHammerLocation.Y + i * y_distance, initialHammerLocation.Z));
	}

	// Spawn actors at each location in the array
	int i = 0;
	for (FVector location : spinnerSpawnLocations)
	{
		AJuanRunRotatingObstacle* newActor = GetWorld()->SpawnActor<AJuanRunRotatingObstacle>(SpinnerObstacleClass, location, FRotator::ZeroRotator);
		if (i % 2 != 0) newActor->ObstacleRotationDirection = -1;
		i++;
	}

	for (FVector location : hammerSpawnLocations)
	{
		AJuanRunRotatingObstacle* newActor = GetWorld()->SpawnActor<AJuanRunRotatingObstacle>(HammerObstacleClass, location, FRotator::ZeroRotator);
		newActor->ObstacleRotationVelocity = FRotator(90.f, 0.f, 0.f);
	}
}