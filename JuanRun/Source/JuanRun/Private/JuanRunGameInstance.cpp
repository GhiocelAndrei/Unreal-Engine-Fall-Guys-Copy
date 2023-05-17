// Fill out your copyright notice in the Description page of Project Settings.


#include "JuanRunGameInstance.h"
#include "UI/MainMenu/JuanRunMenuHUD.h"
#include "Kismet/GameplayStatics.h"

void UJuanRunGameInstance::Init()
{
	Super::Init();

	LoginSubsystem = GetSubsystem<UJuanRunLoginSubsystem>();
	if (LoginSubsystem)
	{
		LoginSubsystem->GetLoginDelegate().AddUObject(this, &UJuanRunGameInstance::OnLoginComplete);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[Juan Run Game Instance] Login Subsystem Unavailable !"));
	}

	SessionSubsystem = GetSubsystem<UJuanRunSessionSubsystem>();
	if (SessionSubsystem)
	{
		SessionSubsystem->GetFindSessionsDelegate().AddUObject(this, &UJuanRunGameInstance::SwitchToSessionsList);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[Juan Run Game Instance] Session Subsystem Unavailable !"));
	}

	RankingSubsystem = GetSubsystem<UJuanRunRankingSubsystem>();
	if (RankingSubsystem)
	{
		RankingSubsystem->GetRankDelegate().AddUObject(this, &UJuanRunGameInstance::SetRank);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[Juan Run Game Instance] Ranking Subsystem Unavailable !"));
	}
}

void UJuanRunGameInstance::Login()
{
	if (LoginSubsystem)
	{
		LoginSubsystem->Login();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[Juan Run Game Instance] Login Subsystem Unavailable !"));
	}
}

void UJuanRunGameInstance::OnLoginComplete()
{
	AJuanRunMenuHUD* startMenuHUD = Cast<AJuanRunMenuHUD>(GetHUD());
	startMenuHUD->TriggerSwitchToWidget(1);
	bIsLoggedIn = true;
}

void UJuanRunGameInstance::CreateSession()
{
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddWeakLambda(this, [this](UWorld* loadedWorld)
	{
		if (SessionSubsystem)
		{
			SessionSubsystem->CreateSession();
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("[Juan Run Game Instance] Session Subsystem Unavailable !"));
		}
		FCoreUObjectDelegates::PostLoadMapWithWorld.RemoveAll(this);
	});


	UKismetSystemLibrary::ExecuteConsoleCommand(this, TEXT("open JuanRun_FirstLevel?listen?NetMode=ForceP2P"));
}

void UJuanRunGameInstance::FindAndJoinSession(FText sessionId)
{
	if (SessionSubsystem)
	{
		SessionSubsystem->FindSessionById(sessionId.ToString());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[Juan Run Game Instance] Session Subsystem Unavailable !"));
	}
}

void UJuanRunGameInstance::FindAllSessions()
{
	if (SessionSubsystem)
	{
		SessionSubsystem->FindAllSessions();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[Juan Run Game Instance] Session Subsystem Unavailable !"));
	}
}

void UJuanRunGameInstance::SwitchToSessionsList()
{
	AJuanRunMenuHUD* startMenuHUD = Cast<AJuanRunMenuHUD>(GetHUD());
	startMenuHUD->CreateLobbyWidget();
}

AHUD* UJuanRunGameInstance::GetHUD()
{
	AHUD* currentHUD = GetWorld()->GetFirstPlayerController()->GetHUD();
	return currentHUD;
}

void UJuanRunGameInstance::SetRank(FString userRank)
{
	Rank = userRank;
}