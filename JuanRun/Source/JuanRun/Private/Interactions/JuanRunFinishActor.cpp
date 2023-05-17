// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactions/JuanRunFinishActor.h"
#include "UI/InGame/JuanRunGameHUD.h"

// Sets default values
AJuanRunFinishActor::AJuanRunFinishActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AJuanRunFinishActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJuanRunFinishActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AJuanRunFinishActor::DoInteraction()
{
    UE_LOG(LogTemp, Error, TEXT("Do Interaction from Finish Actor"));
    AJuanRunGameHUD* gameHUD = Cast<AJuanRunGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
    
    if (gameHUD)
    {
        gameHUD->CreateFinishWidget();
    }

    APlayerController* playerController = GetWorld()->GetFirstPlayerController();
    if (playerController)
    {
        playerController->SetShowMouseCursor(true);
    }
}