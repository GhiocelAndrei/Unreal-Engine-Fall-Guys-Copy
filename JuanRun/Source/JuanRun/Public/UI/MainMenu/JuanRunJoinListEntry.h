// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "JuanRunJoinListEntry.generated.h"

/**
 * 
 */
UCLASS()
class JUANRUN_API UJuanRunJoinListEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
protected:
	// IUserObjectListEntry
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	// IUserObjectListEntry

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SessionIdLabel;
};
