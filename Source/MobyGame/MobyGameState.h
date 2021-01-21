// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Table/CharacterTable.h"
#include "Table/CharacterAttribute.h"
#include "Data/MisData.h"
#include "MobyGameState.generated.h"
/**
 * 
 */
UCLASS()
class MOBYGAME_API AMobyGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	AMobyGameState();

	const TArray<FCharacterTable*>* GetCharacterTablesTemplate();
	const TArray<FCharacterAttribute*>* GetCharacterAttributesTemplate();
	const TMap<int64, FCharacterAttribute>* GetCharacterAttributes();
	const FCharacterTable* GetCharacterTableTemplate(const int32& InID);
	const FCharacterAttribute* GetCharacterAttributeTemplate(const int32& InID);
	FCharacterAttribute* GetCharacterAttribute(int64 InPlayerID);

	void AddCharacterData(int64 PlayerID, int32 CharacterID);

	void UpdateCharacterAILocation(int64 InPlayerID, const FVector& InLocation);
	void AddCharacterAILocation(int64 InPlayerID, const FVector& InLocation);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		bool GetCharacterAILocation(int64 InPlayerID, FVector& InLocation);

	int32 GetCharacterID(int64 InPlayerID);
	const TArray<FPlayerLocation>& GetPlayerLocations();

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UPROPERTY()
		UDataTable* CharacterTablePtr;

	UPROPERTY()
		UDataTable* CharacterAttributePtr;

private:
	TArray<FCharacterTable*> CacheCharacterTables;
	TArray<FCharacterAttribute*> CacheCharacterAttributes;

	UPROPERTY(Replicated)
	TArray<FPlayerLocation> PlayerLocations;

	UPROPERTY()
	TMap<int64, FCharacterAttribute> CharacterAttributes;
	
};

