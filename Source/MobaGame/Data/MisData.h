// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MisData.generated.h"

USTRUCT(BlueprintType)
struct FPlayerLocation 
{
	GENERATED_USTRUCT_BODY()

	FPlayerLocation();

	//玩家ID
	UPROPERTY()
	int64 PlayerID;

	UPROPERTY()
	FVector Location;
};