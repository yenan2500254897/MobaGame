// Fill out your copyright notice in the Description page of Project Settings.


#include "MobyGameAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
AMobyGameAIController::AMobyGameAIController()
{
	/*static ConstructorHelpers::FObjectFinder<UBehaviorTree> Behavior_Tree(TEXT("/Game/TopDownCPP/AI/ABH"));
	BTAsset = Behavior_Tree.Object;*/
}

void AMobyGameAIController::NormalAttack(TWeakObjectPtr<AMobyGameCharacter> InTarget)
{
	Target = InTarget;

	if (AMobyGameCharacter* ControllerPawn = Cast<AMobyGameCharacter>(GetPawn()))
	{
		ControllerPawn->NormalAttack(InTarget);
	}
}


void AMobyGameAIController::SimpleMoveToLocation(const FVector& InNewLocation)
{
	if (GetBlackboardComponent())
	{
		SetTargetForce(NULL);
		GetBlackboardComponent()->SetValueAsVector("Location", InNewLocation);

	}
}

AMobyGameCharacter* AMobyGameAIController::FindTarget()
{
	return NULL;
}

void AMobyGameAIController::SetTargetForce(AMobyGameCharacter* InTarget)
{
	if (GetBlackboardComponent())
	{
		GetBlackboardComponent()->SetValueAsObject("Target", InTarget);
		Target = InTarget;
	}

}

void AMobyGameAIController::BeginPlay()
{
	Super::BeginPlay();
	if (GetLocalRole() == ENetRole::ROLE_Authority)
	{
		GetWorld()->GetTimerManager().SetTimer(InitTimeHandle, this, &AMobyGameAIController::InitContorller, 0.1f);
	}
}

void AMobyGameAIController::InitContorller()
{
	if (InitTimeHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(InitTimeHandle);
	}

	RunBehaviorTree(BTAsset);
}