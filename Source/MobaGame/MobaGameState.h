// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Table/CharacterTable.h"
#include "Data/MisData.h"
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

	//根据characterID拿到character属性
	const FCharacterTable* GetCharacterTable(const int32& InCharacterID);

	//根据玩家ID更新、添加、获取玩家位置
	void UpdateCharacterAILocation(int64 InPlayerID, const FVector& InLocation);
	void AddCharacterAILocation(int64 InPlayerID, const FVector& InLocation);
	UFUNCTION(BlueprintCallable, BlueprintPure)
		bool GetCharacterAILocation(int64 InPlayerID, FVector& InLocation);
	const TArray<FPlayerLocation>& GetPlayerLocations();

protected:
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

protected:
	UPROPERTY()
		UDataTable* CharacterTablePtr;

private:
	TArray<FCharacterTable*> CacheCharacterTables;

	UPROPERTY(Replicated)
		TArray<FPlayerLocation> PlayerLocation;
};
