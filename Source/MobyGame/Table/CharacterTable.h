// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Core/MobyGameTableBase.h"
#include "../MobyGameType.h"
#include "CharacterTable.generated.h"

USTRUCT(BlueprintType)
struct FCharacterTable : public FMobyGameTableBase 
{
	GENERATED_USTRUCT_BODY()

	FCharacterTable();

	UPROPERTY(EditDefaultsOnly, Category = "Character Class")
	TSubclassOf<APawn> CharacterClass;

	UPROPERTY(EditDefaultsOnly, Category = "Character Class")
	ECharacterType CharacterType;

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

	UPROPERTY(EditDefaultsOnly, Category = "Character")
	TArray<UAnimMontage*> Death;
};
