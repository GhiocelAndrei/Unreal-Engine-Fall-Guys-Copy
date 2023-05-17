// Fill out your copyright notice in the Description page of Project Settings.


#include "Online/JuanRunSessionSubsystem.h"


#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "Interfaces/OnlineSessionInterface.h"

void UJuanRunSessionSubsystem::CreateSession()
{
    const IOnlineSubsystem* subsystem = Online::GetSubsystem(this->GetWorld());
    if (!subsystem)
    {
        UE_LOG(LogTemp, Error, TEXT("[Session Subsystem] Get Online Subsystem Failed!"));
        return;
    }

    const IOnlineSessionPtr session = subsystem->GetSessionInterface();
    if (!session.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("[Session Subsystem] Get Session Interface Failed!"));
        return;
    }

    const TSharedRef<FOnlineSessionSettings> sessionSettings = MakeShared<FOnlineSessionSettings>();
    sessionSettings->NumPublicConnections = 4; // The number of players.
    sessionSettings->bShouldAdvertise = true;
    sessionSettings->bUsesPresence = true;
    sessionSettings->bIsDedicated = false;
    sessionSettings->bAllowJoinInProgress = true;

    sessionSettings->Set(SEARCH_KEYWORDS, FString("JuanRunSession"), EOnlineDataAdvertisementType::ViaOnlineService);
    /*sessionSettings->Settings.Add(FName(TEXT("SessionSetting")),
        FOnlineSessionSetting(FString(TEXT("SettingValue")), EOnlineDataAdvertisementType::ViaOnlineService));*/

    CreateSessionCompleteDelegateHandle = session->AddOnCreateSessionCompleteDelegate_Handle(
        FOnCreateSessionCompleteDelegate::CreateUObject(this, &UJuanRunSessionSubsystem::HandleCreateSessionComplete));

    if (!session->CreateSession(0, FName(TEXT("MyLocalSessionName")), *sessionSettings))
    {
        // Call didn't start, return error.
        UE_LOG(LogTemp, Error, TEXT("[Session Subsystem] Create Session Call failed !"))
    }
}

void UJuanRunSessionSubsystem::HandleCreateSessionComplete(FName sessionName, bool bWasSuccessful)
{
    if (bWasSuccessful)
    {
        UE_LOG(LogTemp, Error, TEXT("[Session Subsystem] Create Session Successful !"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("[Session Subsystem] Create Session Failed !"));
    }

    const IOnlineSubsystem* subsystem = Online::GetSubsystem(this->GetWorld());
    if (!subsystem)
    {
        UE_LOG(LogTemp, Error, TEXT("[Session Subsystem] Get Online Subsystem Failed!"));
        return;
    }

    const IOnlineSessionPtr session = subsystem->GetSessionInterface();
    if (!session.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("[Session Subsystem] Get Session Interface Failed!"));
        return;
    }

    if (bWasSuccessful)
    {
        const FNamedOnlineSession* currentSession = session->GetNamedSession(sessionName);
        check(currentSession);

        FString sessionIdString = currentSession->SessionInfo->GetSessionId().ToString();

        UE_LOG(LogTemp, Error, TEXT("[Session Subsystem] Created session success ! Session ID : %s"), *sessionIdString);

        //GetWorld()->ServerTravel("/Game/Level/JuanRun_Lobby_Level?listen");
    }
    session->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegateHandle);

    const IOnlineIdentityPtr identity = subsystem->GetIdentityInterface();
    if (!identity.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("[Session Subsystem] Get Identity Interface Failed!"));
        return;
    }

    CreateOrJoinSessionsDelegate.Broadcast(identity->GetPlayerNickname(0));
}

void UJuanRunSessionSubsystem::FindAllSessions()
{
    const IOnlineSubsystem* subsystem = Online::GetSubsystem(this->GetWorld());
    if (!subsystem)
    {
        UE_LOG(LogTemp, Error, TEXT("[Session Subsystem] Get Online Subsystem Failed!"));
        return;
    }

    const IOnlineSessionPtr session = subsystem->GetSessionInterface();
    if (!session.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("[Session Subsystem] Get Session Interface Failed!"));
        return;
    }


    const IOnlineIdentityPtr identity = subsystem->GetIdentityInterface();
    if (!identity.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("[Session Subsystem] Get Identity Interface Failed!"));
        return;
    }

    SearchSettings = MakeShareable(new FOnlineSessionSearch());
    SearchSettings->QuerySettings.Set(SEARCH_KEYWORDS, FString("JuanRunSession"), EOnlineComparisonOp::Equals);
    SearchSettings->QuerySettings.Set(SEARCH_KEYWORDS, FString("JuanRunSession"), EOnlineComparisonOp::Equals);

    session->OnFindSessionsCompleteDelegates.AddUObject(this, &UJuanRunSessionSubsystem::HandleFindAllSessions);
    session->FindSessions(*identity->GetUniquePlayerId(0), SearchSettings.ToSharedRef());
}

void UJuanRunSessionSubsystem::HandleFindAllSessions(bool bWasSuccessful)
{
    if (bWasSuccessful)
    {
        for (auto result : SearchSettings->SearchResults)
        {
            UE_LOG(LogTemp, Error, TEXT("[Session Subsystem] Session Id : %s"), *(result.GetSessionIdStr()));
            
            CurrentSessionsId.Add(result.GetSessionIdStr());
        }

        FindSessionsDelegate.Broadcast();
    }
}

void UJuanRunSessionSubsystem::FindSessionById(const FString& sessionIdString)
{
    const IOnlineSubsystem* subsystem = Online::GetSubsystem(this->GetWorld());
    if (!subsystem)
    {
        UE_LOG(LogTemp, Error, TEXT("[Session Subsystem] Get Online Subsystem Failed!"));
        return;
    }

    const IOnlineSessionPtr session = subsystem->GetSessionInterface();
    if (!session.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("[Session Subsystem] Get Session Interface Failed!"));
        return;
    }


    const IOnlineIdentityPtr identity = subsystem->GetIdentityInterface();
    if (!identity.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("[Session Subsystem] Get Identity Interface Failed!"));
        return;
    }

    const FUniqueNetIdPtr sessionId = session->CreateSessionIdFromString(sessionIdString);
    const FUniqueNetIdRef friendId = FUniqueNetIdString::EmptyId(); // Optional id


    if (!session->FindSessionById(*identity->GetUniquePlayerId(0),
        *sessionId,
        *friendId,
        FOnSingleSessionResultCompleteDelegate::CreateUObject(this, &UJuanRunSessionSubsystem::HandleFindSessionByIdComplete)))
    {
        UE_LOG(LogTemp, Error, TEXT("[Session Subsystem] Find Session by ID Failed!"));
    }
}

void UJuanRunSessionSubsystem::HandleFindSessionByIdComplete(int32 localUserIndex, bool bWasSuccessful, const FOnlineSessionSearchResult& sessionSearchResult)
{
    if (bWasSuccessful)
    {
        JoinSession(sessionSearchResult);
    }
}

void UJuanRunSessionSubsystem::JoinSession(const FOnlineSessionSearchResult& sessionSearchResult)
{
    const IOnlineSubsystem* subsystem = Online::GetSubsystem(this->GetWorld());
    if (!subsystem)
    {
        UE_LOG(LogTemp, Error, TEXT("[Session Subsystem] Get Online Subsystem Failed!"));
        return;
    }

    const IOnlineSessionPtr session = subsystem->GetSessionInterface();
    if (!session.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("[Session Subsystem] Get Session Interface Failed!"));
        return;
    }

    JoinSessionCompleteDelegateHandle = session->AddOnJoinSessionCompleteDelegate_Handle(
        FOnJoinSessionCompleteDelegate::CreateUObject(this, &UJuanRunSessionSubsystem::HandleJoinSessionComplete));

    if (!session->JoinSession(0, FName(TEXT("MyLocalSessionName")), sessionSearchResult))
    {
        UE_LOG(LogTemp, Error, TEXT("[Session Subsystem] Join Session Failed!"));
    }
}

void UJuanRunSessionSubsystem::HandleJoinSessionComplete(FName sessionName, EOnJoinSessionCompleteResult::Type joinResult)
{
    if (joinResult == EOnJoinSessionCompleteResult::Success || joinResult == EOnJoinSessionCompleteResult::AlreadyInSession)
    {
        UE_LOG(LogTemp, Error, TEXT("[Session Subsystem] Join Session Success !"));

        const IOnlineSubsystem* subsystem = Online::GetSubsystem(this->GetWorld());
        if (!subsystem)
        {
            UE_LOG(LogTemp, Error, TEXT("[Session Subsystem] Get Online Subsystem Failed!"));
            return;
        }

        const IOnlineSessionPtr session = subsystem->GetSessionInterface();
        if (!session.IsValid())
        {
            UE_LOG(LogTemp, Error, TEXT("[Session Subsystem] Get Session Interface Failed!"));
            return;
        }

        session->ClearOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegateHandle);

        FString connectInfo;
        if (session->GetResolvedConnectString(sessionName, connectInfo))
        {
            UE_LOG(LogTemp, Error, TEXT("[Session Subsystem] Get Resolved connect string succes : %s !"), *connectInfo);
            check(GEngine);

            GEngine->NetworkFailureEvent.AddWeakLambda(this,
                [this](
                    UWorld* world,
                    UNetDriver* netDriver,
                    ENetworkFailure::Type failureType,
                    const FString& errorString)
                {
                    // destroy session
                    GEngine->NetworkFailureEvent.RemoveAll(this);
                });

            FString connectErrorString;
            APlayerController* playerController = GetWorld()->GetFirstPlayerController();
            check(playerController);
            playerController->ClientTravel(connectInfo, ETravelType::TRAVEL_Absolute);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("[Session Subsystem] Get Resolved Connect String Failed!"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("[Session Subsystem] Join Session Failed!"));
    }
}

TArray<FString>& UJuanRunSessionSubsystem::GetCurrentSessionsId()
{
    return CurrentSessionsId;
}

FJuanRunSessionsDelegateOneParam& UJuanRunSessionSubsystem::GetCreateOrJoinSessionsDelegate()
{
    return CreateOrJoinSessionsDelegate;
}

FJuanRunSessionsDelegate& UJuanRunSessionSubsystem::GetFindSessionsDelegate()
{
    return FindSessionsDelegate;
}