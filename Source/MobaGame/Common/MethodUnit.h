// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "../MobaGameState.h"

namespace MethodUnit
{
	AMobaGameState* GetGameState(UWorld *NewWorld);

	const FCharacterTable* GetCharacterTable(UWorld* NewWorld,int64 InID);
}