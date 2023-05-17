// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactions/JuanRunInteractInterface.h"
#include "JuanRunUpDownObstacle.generated.h"

UCLASS()
class JUANRUN_API AJuanRunUpDownObstacle : public AActor, public IJuanRunInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJuanRunUpDownObstacle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void DoInteraction() override;
private:
	FVector initialPosition;
	bool PlatformWalkedOn = false;
	bool wait = false;

	float min_Z = -1000;

	float moveDown_speed = 250;
};
