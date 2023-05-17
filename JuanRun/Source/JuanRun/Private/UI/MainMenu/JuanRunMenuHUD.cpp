// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu/JuanRunMenuHUD.h"
#include "JuanRunGameInstance.h"

void AJuanRunMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	MenuWidgetController = CreateWidget<UJuanRunWidgetController>(GetWorld(), MainWidgetClass);

	UJuanRunGameInstance* gameInstance = Cast<UJuanRunGameInstance>(GetWorld()->GetGameInstance());
	if (gameInstance->bIsLoggedIn)
	{
		TriggerSwitchToWidget(1);
	}

	MenuWidgetController->AddToViewport();

	APlayerController* playerController = GetWorld()->GetFirstPlayerController();
	if (playerController)
	{
		playerController->SetShowMouseCursor(true);
	}
}

void AJuanRunMenuHUD::TriggerSwitchToWidget(int index)
{
	MenuWidgetController->SwitchToWidget(index);
}

void AJuanRunMenuHUD::CreateLobbyWidget()
{
	UJuanRunJoinWidget* WidgetInstance = CreateWidget<UJuanRunJoinWidget>(GetWorld(), LobbyWidgetClass);

	// Add the widget to the viewport
	WidgetInstance->AddToViewport();
}
