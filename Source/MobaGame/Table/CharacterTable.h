// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CharacterTable.generated.h"

USTRUCT(BlueprintType)
struct FCharacterTable :public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

		FCharacterTable();

	UPROPERTY(EditDefaultsOnly, Category = "Character Class")
		int64 CharacterID;

	UPROPERTY(EditDefaultsOnly, Category = "Character Class")
		TSubclassOf<APawn> CharacterClass;

	UPROPERTY(EditDefaultsOnly, Category = "Character Class")
		TArray<UAnimMontage*> NormalAttack;

	UPROPERTY(EditDefaultsOnly, Category = "Character Skill Montage")
		UAnimMontage* QSkillAttack;

	UPROPERTY(EditDefaultsOnly, Category = "Character Skill Montage")
		UAnimMontage* WSkillAttack;

	UPROPERTY(EditDefaultsOnly, Category = "Character Skill Montage")
		UAnimMontage* ESkillAttack;

	UPROPERTY(EditDefaultsOnly, Category = "Character Skill Montage")
		UAnimMontage* RSkillAttack;
};