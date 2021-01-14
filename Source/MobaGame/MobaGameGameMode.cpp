// Copyright Epic Games, Inc. All Rights Reserved.

#include "MobaGameGameMode.h"
#include "MobaGamePlayerController.h"
#include "Character/CharacterInstance/MobaGameCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "MobaGameState.h"

AMobaGameGameMode::AMobaGameGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AMobaGamePlayerController::StaticClass();

	GameStateClass = AMobaGameState::StaticClass();
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/MobaPlayer"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}