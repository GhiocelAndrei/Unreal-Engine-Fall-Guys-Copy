// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu/JuanRunJoinListEntry.h"
#include "Components/TextBlock.h"
#include "UI/MainMenu/JuanRunJoinWidget.h"

void UJuanRunJoinListEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UJuanRunSessionsList* item = Cast<UJuanRunSessionsList>(ListItemObject);
	SessionIdLabel->SetText(FText::FromString(item->SessionId));
}