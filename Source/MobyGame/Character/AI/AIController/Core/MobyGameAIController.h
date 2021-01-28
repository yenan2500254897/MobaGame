// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "../../../../MobyGameType.h"
#include "../../../CharacterInstance/MobyGameCharacter.h"
#include "MobyGameAIController.generated.h"

/**
 * 
 */
UCLASS()
class MOBYGAME_API AMobyGameAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AMobyGameAIController();

	UFUNCTION()
	virtual void InitContorller();

	void NormalAttack(TWeakObjectPtr<AMobyGameCharacter> InTarget);

	void SimpleMoveToLocation(const FVector& InNewLocation);

	virtual AMobyGameCharacter* FindTarget();

	virtual void SetTargetForce(AMobyGameCharacter* InTarget);

	AMobyGameCharacter* GetTarget() { return Target.Get(); }

	void StopAttackRot(bool bAttackRot);

protected:
	virtual void BeginPlay() override;

protected:
	TWeakObjectPtr<AMobyGameCharacter> Target;

protected:
	UPROPERTY()
	class UBehaviorTree* BTAsset;

private:
	FTimerHandle InitTimeHandle;
};
