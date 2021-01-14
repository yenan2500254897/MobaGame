// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../../MobaGameType.h"
#include "MobaGameCharacter.generated.h"

UCLASS(Blueprintable)
class AMobaGameCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMobaGameCharacter();

	void NormalAttack(TWeakObjectPtr<AMobaGameCharacter> InTarget);

	void SkillAttack(ESkillKeyType SillKey, TWeakObjectPtr<AMobaGameCharacter> InTarget);

	void InitCharacterID(const int64& InID);

	UFUNCTION(NetMulticast, unreliable)
		void MultCastPlayerAnimMontage(UAnimMontage* InAnimMontage, float InPlayRate = 1.0f, FName StartSectionName = NAME_None);

	UAnimMontage* GetCurrentSkillMontage(ESkillKeyType SillKey);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

private:

	bool bAttacking;
	uint8 AttackCount;
	int64 CharacterID;
};

