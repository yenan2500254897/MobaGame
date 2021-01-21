// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "../MobyGameState.h"
#include "../PlayerComponent/PlayerDataComponent.h"

namespace MethodUnit
{
	enum EServerCallType :uint8
	{
		INPROGRESS,
		PROGRESS_COMPLETE
	};

	AMobyGameState* GetGameState(UWorld* NewWorld);
	
	const FCharacterTable* GetCharacterTable(UWorld* NewWorld, int32& InID);
	
	int32 GetCharacterID(UWorld* NewWorld, int64 InPlayerID);

	bool IsPlayer(UWorld* NewWorld, int64 InPlayerID);

	template<class T>
	void ServerCallAllPlayerController(UWorld* NewWorld, TFunction<EServerCallType(T*)> InImplement);

	template<class T>
	void ServerCallAllPlayerState(UWorld* NewWorld, TFunction<EServerCallType(T*)> InImplement);

	void ServerCallAllPlayerData(UWorld* NewWorld, TFunction<EServerCallType(const UPlayerDataComponent*)> InImplement);

	template<class T>
	void ServerCallAllPlayer(UWorld* NewWorld, TFunction<EServerCallType(T*)> InImplement);

	template<class T>
	void ServerCallAllCharacterAI(UWorld* NewWorld, TFunction<EServerCallType(T*)> InImplement);
}