// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Online/JuanRunLoginSubsystem.h"
#include "Online/JuanRunSessionSubsystem.h"
#include "Online/JuanRunRankingSubsystem.h"
#include "JuanRunGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class JUANRUN_API UJuanRunGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;

	// Function for getting HUD
	UFUNCTION(BlueprintCallable)
	AHUD* GetHUD();

	// Functions for triggering login process
	UFUNCTION(BlueprintCallable)
	void Login();
	void OnLoginComplete();

	// Functions for creating a session
	UFUNCTION(BlueprintCallable)
	void CreateSession();

	UFUNCTION(BlueprintCallable)
	void FindAllSessions();
	void SwitchToSessionsList();

	UFUNCTION(BlueprintCallable)
	void FindAndJoinSession(FText sessionId);

	void SetRank(FString userRank);
protected:
	UPROPERTY(Transient)
	TObjectPtr<UJuanRunLoginSubsystem> LoginSubsystem = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<UJuanRunSessionSubsystem> SessionSubsystem = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<UJuanRunRankingSubsystem> RankingSubsystem = nullptr;

public:
	bool bIsLoggedIn = false;

private:
	FString Rank;
};
