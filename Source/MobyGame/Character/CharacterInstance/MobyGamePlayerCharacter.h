// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MobyGameCharacter.h"
#include "MobyGamePlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MOBYGAME_API AMobyGamePlayerCharacter : public AMobyGameCharacter
{
	GENERATED_BODY()

public:
	UAnimMontage* GetCurrentSkillMontage(ESkillKeyType SkillKey);

	virtual void InitCharacter();

	void SkillAttack(ESkillKeyType SkillKey, TWeakObjectPtr<AMobyGameCharacter> InTarget);
	
};
