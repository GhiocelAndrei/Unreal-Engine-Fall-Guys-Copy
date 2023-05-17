// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/JuanRunGameHUD.h"
#include "Blueprint/UserWidget.h"

void AJuanRunGameHUD::CreateFinishWidget()
{
	UUserWidget* widgetInstance = CreateWidget<UUserWidget>(GetWorld(), FinishWidgetClass);

	// Add the widget to the viewport
	widgetInstance->AddToViewport();
}