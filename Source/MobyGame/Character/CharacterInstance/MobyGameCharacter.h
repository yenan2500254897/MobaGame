// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../../MobyGameType.h"
#include "../../Table/CharacterAttribute.h"
#include "MobyGameCharacter.generated.h"

class UWidgetComponent;
UCLASS(Blueprintable)
class AMobyGameCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttrubute", meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* Widget;

public:
	AMobyGameCharacter();

	void NormalAttack(TWeakObjectPtr<AMobyGameCharacter> InTarget);

	void SkillAttack(ESkillKeyType SkillType, TWeakObjectPtr<AMobyGameCharacter> InTarget);

	void RegisterCharacter(const int64& InPlayerID, int32 CharacterID);

	void InitCharacter();

	UFUNCTION(NetMulticast, unreliable)
	void MultCastPlayerAnimMontage(UAnimMontage *InMontage, float InPlayRate = 1.0f, FName StartSectionName = NAME_None);

	UFUNCTION(NetMulticast, unreliable)
	void MultCastWidgetInfo(float InHPPercentage, float InManaPercentage);

	UAnimMontage* GetCurrentSkillMontage(ESkillKeyType SkillType);

	FCharacterAttribute* GetCharacterAttribute();

	bool IsDie();

	void SetTeam(ETeamType InTeamType);

public:
	FORCEINLINE int64 GePlayerID() { return PlayerID; }
	FORCEINLINE ETeamType GeTeam() { return TeamType; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

private:
	bool bAttacking;
	uint8 AttackCount;
	int64 PlayerID;

private:
	FTimerHandle InitTimeHandle;
	ETeamType TeamType;
};
