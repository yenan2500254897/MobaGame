#include "MethodUnit.h"
#include "../MobyGamePlayerState.h"
#include "../PlayerComponent/PlayerDataComponent.h"

namespace MethodUnit
{
	AMobyGameState* GetGameState(UWorld* NewWorld)
	{
		if (NewWorld)
		{
			return NewWorld->GetGameState<AMobyGameState>();
		}
		return NULL;
	}

	const FCharacterTable* GetCharacterTable(UWorld* NewWorld, int32& InID)
	{
		if (AMobyGameState* InGameState = MethodUnit::GetGameState(NewWorld))
		{
			return InGameState->GetCharacterTableTemplate(InID);
		}
		return NULL;
	}

	int32 GetCharacterID(UWorld* NewWorld, int64 InPlayerID)
	{
		if (AMobyGameState* InState = GetGameState(NewWorld))
		{
			return InState->GetCharacterID(InPlayerID);
		}

		return INDEX_NONE;
	}

	bool IsPlayer(UWorld* NewWorld, int64 InPlayerID)
	{
		bool bPlayer = false;
		ServerCallAllPlayerData(NewWorld, [&](const UPlayerDataComponent* InPlayerData)->EServerCallType
		{
			if (InPlayerData->PlayerID == InPlayerID)
			{
				bPlayer = true;
				return EServerCallType::PROGRESS_COMPLETE;
			}

			return EServerCallType::INPROGRESS;
		});

		return bPlayer;
	}

	void ServerCallAllPlayerData(UWorld* NewWorld, TFunction<EServerCallType(const UPlayerDataComponent*)> InImplement)
	{
		ServerCallAllPlayerState<AMobyGamePlayerState>(NewWorld, [&](AMobyGamePlayerState* InPlayerState)->EServerCallType
		{
			if (InPlayerState->GetPlayerData())
			{
				return InImplement(InPlayerState->GetPlayerData());
			}

			return EServerCallType::PROGRESS_COMPLETE;
		});
	}

	template<class T>
	void ServerCallAllPlayerState(UWorld* NewWorld, TFunction<EServerCallType(T*)> InImplement)
	{
		ServerCallAllPlayerController<APlayerController>(NewWorld, [&](APlayerController* InPlayerContoroller)->EServerCallType
		{
			if (T* InState = InPlayerContoroller->GetPlayerState<T>())
			{
				return InImplement(InState);
			}

			return EServerCallType::PROGRESS_COMPLETE;
		});
	}

	template<class T>
	void ServerCallAllPlayerController(UWorld* NewWorld, TFunction<EServerCallType(T*)> InImplement)
	{
		for (FConstPlayerControllerIterator It = NewWorld->GetPlayerControllerIterator(); It; ++It)
		{
			if (T* InPlayerController = Cast<T>(It->Get()))
			{
				if (InImplement(InPlayerController) == EServerCallType::PROGRESS_COMPLETE)
				{
					break;
				}
			}
		}
	}


	template<class T>
	void ServerCallAllPlayer(UWorld* NewWorld, TFunction<EServerCallType(T*)> InImplement)
	{
		ServerCallAllPlayerController<APlayerController>(NewWorld, [&](APlayerController* InPlayerContoroller)->EServerCallType
		{
			if (T* InPawn = Cast<T>(InPlayerContoroller->GetPawn()))
			{
				return InImplement(InPawn);
			}

			return EServerCallType::PROGRESS_COMPLETE;
		});
	}

	template<class T>
	void ServerCallAllCharacterAI(UWorld* NewWorld, TFunction<EServerCallType(T*)> InImplement)
	{
		ServerCallAllPlayer<AMobyPawn>(NewWorld, [&](AMobyPawn* InPawn)->EServerCallType
		{
			return InImplement(InPawn->GetControllerCharacter());
		});
	}

}