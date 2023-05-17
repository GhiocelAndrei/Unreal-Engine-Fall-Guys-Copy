// Fill out your copyright notice in the Description page of Project Settings.


#include "Online/JuanRunRankingSubsystem.h"

#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Misc/CString.h"

void UJuanRunRankingSubsystem::UploadNewRank(const FString& fileName, const FString fileContent) const
{
    if (fileContent.IsEmpty())
    {
        UE_LOG(LogTemp, Error, TEXT("[Ranking Subsystem] File is empty !"));
        return;
    }

    FTCHARToUTF8 data(*fileContent);
    TArray<uint8> fileDataArray((uint8*)data.Get(), data.Length());

    IOnlineSubsystem* subsystem = Online::GetSubsystem(GetWorld());
    if (subsystem == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("[Ranking Subsystem] Get Online Subsystem failed !"));
        return;
    }

    IOnlineIdentityPtr identity = subsystem->GetIdentityInterface();
    if (identity == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("[Ranking Subsystem] Get Identity Interface failed !"));
        return;
    }

    IOnlineUserCloudPtr userCloud = subsystem->GetUserCloudInterface();
    if (userCloud == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("[Ranking Subsystem] Get User Cloud Interface failed !"));
        return;
    }

    userCloud->AddOnWriteUserFileCompleteDelegate_Handle(FOnWriteUserFileComplete::FDelegate::CreateUObject(
        this,
        &UJuanRunRankingSubsystem::HandleWriteUserFileComplete));

    userCloud->WriteUserFile(*identity->GetUniquePlayerId(0), fileName, fileDataArray);
}

void UJuanRunRankingSubsystem::HandleWriteUserFileComplete(bool wasSuccessful, const FUniqueNetId& userId, const FString& fileName) const
{
    if (wasSuccessful)
    {
        UE_LOG(LogTemp, Error, TEXT("[Ranking Subsystem] Write to file %s success !"), *fileName);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("[Ranking Subsystem] Write to file %s failed !"), *fileName);
    }
}

void UJuanRunRankingSubsystem::GetRank(const FString& fileName) const
{
    IOnlineSubsystem* subsystem = Online::GetSubsystem(GetWorld());
    if (subsystem == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("[Ranking Subsystem] Get Online Subsystem failed !"));
        return;
    }

    IOnlineIdentityPtr identity = subsystem->GetIdentityInterface();
    if (identity == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("[Ranking Subsystem] Get Identity Interface failed !"));
        return;
    }

    IOnlineUserCloudPtr userCloud = subsystem->GetUserCloudInterface();
    if (userCloud == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("[Ranking Subsystem] Get User Cloud Interface failed !"));
        return;
    }

    userCloud->AddOnReadUserFileCompleteDelegate_Handle(FOnReadUserFileComplete::FDelegate::CreateUObject(
        this,
        &UJuanRunRankingSubsystem::HandleReadUserFileComplete));

    userCloud->ReadUserFile(*identity->GetUniquePlayerId(0), fileName);
}

void UJuanRunRankingSubsystem::HandleReadUserFileComplete(bool wasSuccessful, const FUniqueNetId& userId, const FString& fileName) const
{
    if (wasSuccessful == false)
    {
        UE_LOG(LogTemp, Error, TEXT("[Ranking Subsystem] Read User file %s failed !"), *fileName);
        RankDelegate.Broadcast(FString("Bronze"));
        return;
    }

    IOnlineSubsystem* subsystem = Online::GetSubsystem(this->GetWorld());
    if (subsystem == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("[Ranking Subsystem] Get Online Subsystem failed !"));
        return;
    }

    IOnlineUserCloudPtr userCloud = subsystem->GetUserCloudInterface();
    if (userCloud == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("[Ranking Subsystem] Get User Cloud Interface failed !"));
        return;
    }

    TArray<uint8> fileContents;
    if (userCloud->GetFileContents(userId, fileName, fileContents))
    {
        FUTF8ToTCHAR data((const ANSICHAR*)fileContents.GetData(), fileContents.Num());
        int rankValue = FCString::Atoi(*FString(data.Length(), data.Get()));
        if (rankValue < 1000) RankDelegate.Broadcast(FString("Bronze"));
        else if(rankValue >= 1000 && rankValue < 2000) RankDelegate.Broadcast(FString("Silver"));
        else if (rankValue >= 2000 && rankValue < 3000) RankDelegate.Broadcast(FString("Gold"));
        else if (rankValue >= 3000 && rankValue < 4000) RankDelegate.Broadcast(FString("Platinum"));
        else if (rankValue >= 4000 && rankValue < 5000) RankDelegate.Broadcast(FString("Diamond"));
        else RankDelegate.Broadcast(FString("Master"));
    }
}

FJuanRunRankingDelegateOneParam& UJuanRunRankingSubsystem::GetRankDelegate()
{
    return RankDelegate;
}