// Copyright Epic Games, Inc. All Rights Reserved.

#include "JuanRunGameMode.h"
#include "JuanRunCharacter.h"
#include "UObject/ConstructorHelpers.h"

AJuanRunGameMode::AJuanRunGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
