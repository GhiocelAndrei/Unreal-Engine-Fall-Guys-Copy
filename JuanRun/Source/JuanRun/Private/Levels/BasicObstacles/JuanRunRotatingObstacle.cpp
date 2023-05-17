// Fill out your copyright notice in the Description page of Project Settings.


#include "Levels/BasicObstacles/JuanRunRotatingObstacle.h"

// Sets default values
AJuanRunRotatingObstacle::AJuanRunRotatingObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AJuanRunRotatingObstacle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJuanRunRotatingObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (InfiniteRotation)
	{
		RotateObstacleInfinite(DeltaTime);
	}
	else
	{
		RotateObstacleUntil(DeltaTime);
	}
	
}

void AJuanRunRotatingObstacle::RotateObstacleInfinite(float DeltaTime)
{
	AddActorLocalRotation(ObstacleRotationDirection * ObstacleRotationVelocity * DeltaTime);
}

void AJuanRunRotatingObstacle::RotateObstacleUntil(float DeltaTime)
{
	FRotator actorRotation = GetActorRotation();
	if (actorRotation.Pitch < 180.f || actorRotation.Pitch > 0.f)
	{
		ObstacleRotationDirection *= -1;
	}

	AddActorLocalRotation(ObstacleRotationDirection * ObstacleRotationVelocity * DeltaTime);
}