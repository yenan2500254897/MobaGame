#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MobaGameTableBase.generated.h"

USTRUCT(BlueprintType)
struct FMobaGameTableBase :public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	FMobaGameTableBase();

	//角色ID
	UPROPERTY(EditDefaultsOnly, Category = "Moby Game Table")
		int32 CharacterID;
};