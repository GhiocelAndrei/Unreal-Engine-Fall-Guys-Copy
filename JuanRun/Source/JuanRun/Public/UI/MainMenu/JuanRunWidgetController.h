// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetSwitcher.h"
#include "JuanRunWidgetController.generated.h"

/**
 * 
 */
UCLASS()
class JUANRUN_API UJuanRunWidgetController : public UUserWidget
{
	GENERATED_BODY()

public:
	void SwitchToWidget(int index);

protected:
	UPROPERTY(meta = (BindWidget))
		TObjectPtr<UWidgetSwitcher> MenuSwitcher = nullptr;
};
