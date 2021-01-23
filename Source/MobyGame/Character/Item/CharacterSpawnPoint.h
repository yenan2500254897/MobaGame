// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "../../MobyGameType.h"
#include "CharacterSpawnPoint.generated.h"

/**
 * 
 */
UCLASS()
class MOBYGAME_API ACharacterSpawnPoint : public ATargetPoint
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterType")
		ETeamType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterType")
		ECharacterType CharacterType;

public:
	ACharacterSpawnPoint();

	FORCEINLINE ETeamType GetType() const { return Type; }
	FORCEINLINE ECharacterType GetCharacterType() const { return CharacterType; }
	
};
