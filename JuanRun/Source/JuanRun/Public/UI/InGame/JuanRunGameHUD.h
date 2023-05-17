// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "JuanRunGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class JUANRUN_API AJuanRunGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	void CreateFinishWidget();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<class UUserWidget> FinishWidgetClass;
};
