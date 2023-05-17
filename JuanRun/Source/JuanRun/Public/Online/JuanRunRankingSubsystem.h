// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "JuanRunRankingSubsystem.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE_OneParam(FJuanRunRankingDelegateOneParam, const FString);

UCLASS()
class JUANRUN_API UJuanRunRankingSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
    void UploadNewRank(const FString& fileName, const FString fileContent) const;
    void GetRank(const FString& fileName) const;

    FJuanRunRankingDelegateOneParam& GetRankDelegate();

private:
    void HandleWriteUserFileComplete(bool wasSuccessful, const FUniqueNetId& userId, const FString& fileName) const;
    void HandleReadUserFileComplete(bool wasSuccessful, const FUniqueNetId& userId, const FString& fileName) const;

private:
    FJuanRunRankingDelegateOneParam RankDelegate;


};
