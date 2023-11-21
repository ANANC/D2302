// Copyright Epic Games, Inc. All Rights Reserved.

#include "D2302GameMode.h"
#include "D2302Character.h"
#include "UObject/ConstructorHelpers.h"

AD2302GameMode::AD2302GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
