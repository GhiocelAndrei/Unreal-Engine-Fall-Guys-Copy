// Fill out your copyright notice in the Description page of Project Settings.


#include "Levels/BasicObstacles/JuanRunMovingPlatform.h"

// Sets default values
AJuanRunMovingPlatform::AJuanRunMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AJuanRunMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	MinY = GetActorLocation().Y;
	MaxY = MinY + 3700;
}

// Called every frame
void AJuanRunMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bStartMoving)
	{
		MovePlatform(DeltaTime);
	}
}

void AJuanRunMovingPlatform::MovePlatform(float DeltaTime)
{
	FVector currLocation = GetActorLocation();

	if (currLocation.Y < MinY || currLocation.Y > MaxY)
	{
		Move_Direction *= -1;
	}

	FVector newLocation = FVector(currLocation.X, currLocation.Y + Move_Direction * Move_Speed * DeltaTime, currLocation.Z);

	SetActorLocation(newLocation);

}

void AJuanRunMovingPlatform::DoInteraction()
{
	bStartMoving = true;
}