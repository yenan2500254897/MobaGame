// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaGameAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

AMobaGameAIController::AMobaGameAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> Behavior_Tree(TEXT("/Game/TopDownCPP/AI/ABH"));
	BTAsset = Behavior_Tree.Object;
}

void AMobaGameAIController::NormalAttack(TWeakObjectPtr<AMobaGameCharacter> InTarget)
{
	Target = InTarget;

	if (AMobaGameCharacter* ContorllerPawn = Cast<AMobaGameCharacter>(GetPawn()))
	{
		ContorllerPawn->NormalAttack(InTarget);
	}
}

void AMobaGameAIController::BeginPlay()
{
	Super::BeginPlay();

	if (GetLocalRole() == ENetRole::ROLE_Authority)
	{
		RunBehaviorTree(BTAsset);
	}
}

void AMobaGameAIController::SimpleMoveToLocation(const FVector& InNewLocation)
{
	SetTargetForce(NULL);
	GetBlackboardComponent()->SetValueAsVector("Location", InNewLocation);
}

AMobaGameCharacter* AMobaGameAIController::FindTarget()
{
	return NULL;
}

void AMobaGameAIController::SetTargetForce(AMobaGameCharacter* InTarget)
{
	GetBlackboardComponent()->SetValueAsObject("Target", InTarget);

	Target = InTarget;
}

