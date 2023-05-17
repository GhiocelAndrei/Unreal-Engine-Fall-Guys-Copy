// Fill out your copyright notice in the Description page of Project Settings.


#include "Online/JuanRunLoginSubsystem.h"

#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "Interfaces/OnlineIdentityInterface.h"

void UJuanRunLoginSubsystem::Login()
{
	const IOnlineSubsystem* onlineSubsystem = Online::GetSubsystem(GetWorld());
	if (!onlineSubsystem)
	{
		UE_LOG(LogTemp, Error, TEXT("[Login Subsystem] Get Online Subsystem Failed !"));
		return;
	}

	const IOnlineIdentityPtr identityInterface = onlineSubsystem->GetIdentityInterface();
	if (!identityInterface.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("[Login Subsystem] Get Identity Interface Failed"));
		return;
	}

	FOnlineAccountCredentials credentials;
	credentials.Id = FString();
	credentials.Token = FString();
	credentials.Type = FString("accountportal");

	LoginCompletedDelegateHandle = identityInterface->AddOnLoginCompleteDelegate_Handle(
		0,
		FOnLoginCompleteDelegate::CreateUObject(this, &UJuanRunLoginSubsystem::OnLoginCompleted));

	identityInterface->Login(0, credentials);
}

void UJuanRunLoginSubsystem::OnLoginCompleted(int localUserNum, bool bWasSuccessful, const FUniqueNetId& userId, const FString& error)
{
	const IOnlineSubsystem* onlineSubsystem = Online::GetSubsystem(GetWorld());
	if (!onlineSubsystem)
	{
		UE_LOG(LogTemp, Error, TEXT("[Login Subsystem] Get Online Subsystem Failed !"));
		return;
	}

	const IOnlineIdentityPtr identityInterface = onlineSubsystem->GetIdentityInterface();
	if (identityInterface.IsValid())
	{
		identityInterface->ClearOnLoginCompleteDelegate_Handle(0, LoginCompletedDelegateHandle);
	}

	if (bWasSuccessful)
	{
		LoginDelegate.Broadcast();
		UE_LOG(LogTemp, Error, TEXT("[Login Subsystem] Logged in user with id : %s!"), *userId.ToString());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[Login Subsystem] Login Failed %s!"), *error);
	}

}

FJuanRunLoginDelegate& UJuanRunLoginSubsystem::GetLoginDelegate()
{
	return LoginDelegate;
}