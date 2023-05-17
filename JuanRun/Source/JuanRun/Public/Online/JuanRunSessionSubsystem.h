// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "JuanRunSessionSubsystem.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE(FJuanRunSessionsDelegate);
DECLARE_MULTICAST_DELEGATE_OneParam(FJuanRunSessionsDelegateOneParam, const FString);

UCLASS()
class JUANRUN_API UJuanRunSessionSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	void CreateSession();
	void FindAllSessions();
	void FindSessionById(const FString& sessionID);
	void JoinSession(const FOnlineSessionSearchResult& sessionSearchResult);

	FJuanRunSessionsDelegateOneParam& GetCreateOrJoinSessionsDelegate();
	FJuanRunSessionsDelegate& GetFindSessionsDelegate();

	TArray<FString>& GetCurrentSessionsId();
private:
	void HandleCreateSessionComplete(FName sessionName, bool bWasSuccessful);
	void HandleFindAllSessions(bool bWasSuccessful);
	void HandleFindSessionByIdComplete(int32 localUserIndex, bool bWasSuccessful, const FOnlineSessionSearchResult& sessionSearchResult);
	void HandleJoinSessionComplete(FName sessionName, EOnJoinSessionCompleteResult::Type joinResult);

private:
	FDelegateHandle CreateSessionCompleteDelegateHandle;
	FDelegateHandle JoinSessionCompleteDelegateHandle;

	FJuanRunSessionsDelegateOneParam CreateOrJoinSessionsDelegate;
	FJuanRunSessionsDelegate FindSessionsDelegate;

	TArray<FString> CurrentSessionsId;
	TSharedPtr<FOnlineSessionSearch> SearchSettings;
};
