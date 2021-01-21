// Copyright Epic Games, Inc. All Rights Reserved.

#include "MobyGameGameMode.h"
#include "MobyGamePlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "MobyGameState.h"
#include "Character/CharacterInstance/MobyGameCharacter.h"
#include "MobyPawn.h"
#include "MobyGameHUD.h"
#include "MobyGamePlayerState.h"

AMobyGameGameMode::AMobyGameGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	// use our custom PlayerController class
	PlayerControllerClass = AMobyGamePlayerController::StaticClass();
	PlayerStateClass = AMobyGamePlayerState::StaticClass();

	GameStateClass = AMobyGameState::StaticClass();
	HUDClass = AMobyGameHUD::StaticClass();
	
	// set default pawn class to our Blueprinted character
	//�滻Ϊ�Լ���pawn
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/MobyPlayer"));
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AMobyGameGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (AMobyGameState* InState = GetWorld()->GetGameState<AMobyGameState>())
	{
		InState->AddCharacterAILocation(0, FVector::ZeroVector);
		InState->AddCharacterAILocation(1, FVector::ZeroVector);
	}
}

void AMobyGameGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*if (AMobyGameState* InState = GetWorld()->GetGameState<AMobyGameState>())
	{
		ServerCallAllCharacterAI<AMobyGameCharacter>([&](AMobyGameCharacter *InCharacter)
		{
			InState->UpdateCharacterAILocation(InCharacter->GePlayerID(), InCharacter->GetActorLocation());
		});
	}*/
}