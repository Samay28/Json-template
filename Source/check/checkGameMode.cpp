// Copyright Epic Games, Inc. All Rights Reserved.

#include "checkGameMode.h"
#include "checkCharacter.h"
#include "UObject/ConstructorHelpers.h"

AcheckGameMode::AcheckGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
