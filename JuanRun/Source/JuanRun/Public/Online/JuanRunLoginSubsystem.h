// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "OnlineSubsystem.h"
#include "JuanRunLoginSubsystem.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE(FJuanRunLoginDelegate);

UCLASS()
class JUANRUN_API UJuanRunLoginSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void Login();

	FJuanRunLoginDelegate& GetLoginDelegate();

private:
	void OnLoginCompleted(int localUserNum, bool bWasSuccessful, const FUniqueNetId& userId, const FString& error);

private:
	FDelegateHandle LoginCompletedDelegateHandle;
	FJuanRunLoginDelegate LoginDelegate;
};
