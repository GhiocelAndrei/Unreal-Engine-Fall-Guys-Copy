// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JuanRunJoinWidget.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class JUANRUN_API UJuanRunSessionsList : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, Category = "ListView Item")
	FString SessionId;
};

/**
 * 
 */
UCLASS()
class JUANRUN_API UJuanRunJoinWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UListView* SessionsListView;
};
