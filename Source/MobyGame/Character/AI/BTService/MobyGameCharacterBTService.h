// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "MobyGameCharacterBTService.generated.h"

/**
 * 
 */
UCLASS()
class MOBYGAME_API UMobyGameCharacterBTService : public UBTService
{
	GENERATED_BODY()

public:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	
	UPROPERTY(EditAnyWhere, Category = "BlackBoard")
	struct FBlackboardKeySelector BlackboardKey_Target;

	UPROPERTY(EditAnyWhere, Category = "BlackBoard")
	struct FBlackboardKeySelector BlackboardKey_Distance;

	UPROPERTY(EditAnyWhere, Category = "BlackBoard")
	struct FBlackboardKeySelector BlackboardKey_Location;

	UPROPERTY(EditAnywhere, Category = "BlackBoard")
	struct FBlackboardKeySelector BlackBoardKey_Death;

	/** Notify called after GameplayTask finishes initialization (not active yet) */
	virtual void OnGameplayTaskInitialized(UGameplayTask& Task) {}

	/** Notify called after GameplayTask changes state to Active (initial activation or resuming) */
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) {}

	/** Notify called after GameplayTask changes state from Active (finishing or pausing) */
	virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) {}
};
