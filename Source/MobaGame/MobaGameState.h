// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Table/CharacterTable.h"
#include "MobaGameState.generated.h"

/**
 * 
 */
UCLASS()
class MOBAGAME_API AMobaGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	AMobaGameState();

	const TArray<FCharacterTable*>* GetCharacterTables();

	const FCharacterTable* GetCharacterTable(const int64& InID);

protected:
	UPROPERTY()
		UDataTable* CharacterTablePtr;

private:
	TArray<FCharacterTable*> CacheCharacterTables;
};
