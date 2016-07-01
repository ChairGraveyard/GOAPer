// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "GOAPer.h"
#include "GOAPerGameMode.h"
#include "GOAPerPlayerController.h"
#include "GOAPerCharacter.h"

AGOAPerGameMode::AGOAPerGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AGOAPerPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}