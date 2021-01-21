#pragma once

#include "CoreMinimal.h"
#include "MisData.generated.h"

USTRUCT(BlueprintType)
struct FPlayerLocation
{
	GENERATED_USTRUCT_BODY()

	FPlayerLocation();

	UPROPERTY()
	int64 PlayerID;

	UPROPERTY()
	FVector Location;
};