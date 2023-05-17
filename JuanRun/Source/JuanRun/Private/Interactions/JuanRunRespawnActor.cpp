// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactions/JuanRunRespawnActor.h"
#include "../JuanRunCharacter.h"


// Sets default values
AJuanRunRespawnActor::AJuanRunRespawnActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AJuanRunRespawnActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJuanRunRespawnActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AJuanRunRespawnActor::DoInteraction()
{
    UE_LOG(LogTemp, Error, TEXT("Do Interaction from Respawn Actor"));
    // Retrieve the local player controller
    APlayerController* playerController = GetWorld()->GetFirstPlayerController();

    // Get the character associated with the local player
    AJuanRunCharacter* localCharacter = Cast<AJuanRunCharacter>(playerController->GetCharacter());

    if (localCharacter)
    {
        localCharacter->SetNewSpawnPoint(GetActorLocation());
    }
}