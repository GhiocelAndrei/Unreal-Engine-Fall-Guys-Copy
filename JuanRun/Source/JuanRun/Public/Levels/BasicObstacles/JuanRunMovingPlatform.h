// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactions/JuanRunInteractInterface.h"
#include "JuanRunMovingPlatform.generated.h"

UCLASS()
class JUANRUN_API AJuanRunMovingPlatform : public AActor, public IJuanRunInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJuanRunMovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void DoInteraction() override;
	void MovePlatform(float DeltaTime);
public:
	bool bStartMoving = false;
	float Move_Direction = 1;
	float Move_Speed = 300;
	float MaxY = 16225;
	float MinY = 12545;
};
