// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu/JuanRunJoinWidget.h"
#include "Components/ListView.h"
#include "Online/JuanRunSessionSubsystem.h"

void UJuanRunJoinWidget::NativeConstruct()
{
	Super::NativeConstruct();
	UJuanRunSessionSubsystem* sessionSubsystem = GetGameInstance()->GetSubsystem<UJuanRunSessionSubsystem>();

	TArray<UJuanRunSessionsList*> sessionsList;

	TArray<FString> sessionsListString = sessionSubsystem->GetCurrentSessionsId();
	for (auto session : sessionsListString)
	{
		UJuanRunSessionsList* newSession = NewObject<UJuanRunSessionsList>();
		newSession->SessionId = session;
		sessionsList.Add(newSession);
	}
	
	SessionsListView->SetListItems(sessionsList);
}
