// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu/JuanRunWidgetController.h"

void UJuanRunWidgetController::SwitchToWidget(int index)
{
	UE_LOG(LogTemp, Error, TEXT("Switch To Widget"));
	if (MenuSwitcher == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Widge Switcher is null"));
	}
	MenuSwitcher->SetActiveWidgetIndex(index);
}