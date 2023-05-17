// Fill out your copyright notice in the Description page of Project Settings.


#include "Levels/BasicObstacles/JuanRunUpDownObstacle.h"

// Sets default values
AJuanRunUpDownObstacle::AJuanRunUpDownObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AJuanRunUpDownObstacle::BeginPlay()
{
	Super::BeginPlay();
	
	initialPosition = GetActorLocation();
}

// Called every frame
void AJuanRunUpDownObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (PlatformWalkedOn)
	{
		if (!wait)
		{
			FVector currLocation = GetActorLocation();

			FVector newLocation = FVector(currLocation.X, currLocation.Y, currLocation.Z - DeltaTime * moveDown_speed);

			SetActorLocation(newLocation);
		}

		if (GetActorLocation().Z < min_Z)
		{
			wait = true;
			FTimerHandle timerHandle;

			GetWorldTimerManager().SetTimer(timerHandle, [this]() {
					wait = false;
					PlatformWalkedOn = false;
					SetActorLocation(initialPosition);
				}, 5.0f, false);
		}
	}
}

void AJuanRunUpDownObstacle::DoInteraction()
{
	PlatformWalkedOn = true;
}
