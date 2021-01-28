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
	GetWorld()->GetTimerManager().SetTimer(InitTimeHandle, this, &AMobyGameGameMode::InitialMode, 2.0f);
}

void AMobyGameGameMode::InitialMode()
{

	int64 InPlayerID = 1231451;
	if (AMobyGameState* InGameState = GetWorld()->GetGameState<AMobyGameState>())
	{
		TArray<AActor*> SpawnPointArrays;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACharacterSpawnPoint::StaticClass(), SpawnPointArrays);
		for (auto& Tmp : SpawnPointArrays)
		{
			if (ACharacterSpawnPoint* M = Cast<ACharacterSpawnPoint>(Tmp))
			{
				int32 CharacterID = INDEX_NONE;
				if (M->GetCharacterType() == ECharacterType::FIRST_CLASS_TURRETS)
				{
					CharacterID = 22220;
				}
				else if (M->GetCharacterType() == ECharacterType::WARRIOR_MINION)
				{
					CharacterID = 11110;
				}
				else if (M->GetCharacterType() == ECharacterType::WILD_MONSTER)
				{
					CharacterID = 33330;
				}

				UClass* DefaultPawnClassTmp = NULL;
				const FCharacterTable* InTable = InGameState->GetCharacterTableTemplate(CharacterID);
				if (InTable)
				{
					DefaultPawnClassTmp = InTable->CharacterClass;
				}
				else
				{
					return;
				}

				if (DefaultPawnClassTmp)
				{
					AMobyGameCharacter* MobyGameCharacter = GetWorld()->SpawnActor<AMobyGameCharacter>(DefaultPawnClassTmp, M->GetActorLocation(), M->GetActorRotation());
					if (MobyGameCharacter)
					{
						InPlayerID++;
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