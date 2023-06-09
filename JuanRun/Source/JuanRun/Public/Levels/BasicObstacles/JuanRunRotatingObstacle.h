// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JuanRunRotatingObstacle.generated.h"

UCLASS()
class JUANRUN_API AJuanRunRotatingObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJuanRunRotatingObstacle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void RotateObstacleInfinite(float DeltaTime);
	void RotateObstacleUntil(float DeltaTime);
public:
	bool InfiniteRotation = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle")
	float ObstacleRotationDirection = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle")
	FRotator ObstacleRotationVelocity = FRotator(0.f, 100.f, 0.f);
};
