// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/MainMenu/JuanRunWidgetController.h"
#include "UI/MainMenu/JuanRunJoinWidget.h"
#include "JuanRunMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class JUANRUN_API AJuanRunMenuHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay();

	UFUNCTION(BlueprintCallable)
	void TriggerSwitchToWidget(int index);

	void CreateLobbyWidget();
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget")
	TObjectPtr<UJuanRunWidgetController> MenuWidgetController = nullptr;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<class UJuanRunWidgetController> MainWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<class UJuanRunJoinWidget> LobbyWidgetClass;
};
