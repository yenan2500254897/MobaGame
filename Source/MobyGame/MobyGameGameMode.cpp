// Copyright Epic Games, Inc. All Rights Reserved.

#include "MobyGameGameMode.h"
#include "MobyGamePlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "MobyGameState.h"
#include "Character/CharacterInstance/MobyGameCharacter.h"
#include "MobyPawn.h"
#include "MobyGameHUD.h"
#include "MobyGamePlayerState.h"
#include "Character/Item/CharacterSpawnPoint.h"
#include "Kismet/GameplayStatics.h"

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

	/*if (AMobyGameState* InState = GetWorld()->GetGameState<AMobyGameState>())
	{
		InState->AddCharacterAILocation(0, FVector::ZeroVector);
		InState->AddCharacterAILocation(1, FVector::ZeroVector);


	}*/
	GetWorld()->GetTimerManager().SetTimer(InitTimeHandle, this, &AMobyGameGameMode::InitialMode, 3.0f);
}

void AMobyGameGameMode::InitialMode()
{

	AActor* M = UGameplayStatics::GetActorOfClass(GetWorld(), ACharacterSpawnPoint::StaticClass());
	int32 CharacterID = 11110;
	UClass* DefaultPawnClassTmp = NULL;

	if (AMobyGameState* InState = GetWorld()->GetGameState<AMobyGameState>())
	{
		const FCharacterTable* InTable = InState->GetCharacterTableTemplate(CharacterID);
		if (InTable)
		{
			DefaultPawnClassTmp = InTable->CharacterClass;
		}

		if (DefaultPawnClassTmp)
		{
			AMobyGameCharacter* MobyGameCharacter = GetWorld()->SpawnActor<AMobyGameCharacter>(DefaultPawnClassTmp, M->GetActorLocation(), M->GetActorRotation());
			if (MobyGameCharacter)
			{
				int InPlayerID = 123456;
				if (InPlayerID != INDEX_NONE)
				{
					MobyGameCharacter->RegisterCharacter(InPlayerID, CharacterID);
					MobyGameCharacter->SetTeam(ETeamType::TEAM_RED);
					MobyGameCharacter->SetCharacterType(InTable->CharacterType);
				}
			}
		}
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