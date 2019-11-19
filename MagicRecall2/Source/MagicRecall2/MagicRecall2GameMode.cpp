// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "MagicRecall2GameMode.h"
#include "MagicRecall2Character.h"
#include "UObject/ConstructorHelpers.h"

AMagicRecall2GameMode::AMagicRecall2GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
