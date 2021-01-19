// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "../../CharacterInstance/MobaGameCharacter.h"
#include "MobaGameAIController.generated.h"

/**
 * 
 */
UCLASS()
class MOBAGAME_API AMobaGameAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AMobaGameAIController();

	void NormalAttack(TWeakObjectPtr<AMobaGameCharacter> InTarget);

	void SetTargetForce(AMobaGameCharacter* InTarget);

	void SimpleMoveToLocation(const FVector& InNewLocation);

	AMobaGameCharacter* FindTarget();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	TWeakObjectPtr<AMobaGameCharacter> Target;

private:
	UPROPERTY()
		class UBehaviorTree* BTAsset;
};
