// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaGameCharacterBTService.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Float.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "../AIController/MobaGameAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UMobaGameCharacterBTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (BlackBoardKey_Target.SelectedKeyType == UBlackboardKeyType_Object::StaticClass() &&
		BlackBoardKey_Distance.SelectedKeyType == UBlackboardKeyType_Float::StaticClass() &&
		BlackBoardKey_Location.SelectedKeyType == UBlackboardKeyType_Vector::StaticClass())
	{
		if (AMobaGameAIController* OwnerCharacter = Cast<AMobaGameAIController>(OwnerComp.GetOwner()))
		{
			if (UBlackboardComponent* MyBlackBoard = OwnerComp.GetBlackboardComponent())
			{
				AMobaGameCharacter* InTarget = Cast<AMobaGameCharacter>(MyBlackBoard->GetValueAsObject(BlackBoardKey_Target.SelectedKeyName));
				if (!InTarget)
				{
					InTarget = OwnerCharacter->FindTarget();
				}

				float Distance = 999999.0f;
				if (InTarget)
				{
					Distance = FVector::Dist(InTarget->GetActorLocation(), OwnerCharacter->GetPawn()->GetActorLocation());

					MyBlackBoard->SetValueAsVector(BlackBoardKey_Location.SelectedKeyName, InTarget->GetActorLocation());
				}

				MyBlackBoard->SetValueAsFloat(BlackBoardKey_Distance.SelectedKeyName, Distance);
			}
		}
	}
}

void UMobaGameCharacterBTService::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	if (UBlackboardData* BBAsset = GetBlackboardAsset())
	{
		BlackBoardKey_Target.ResolveSelectedKey(*BBAsset);
		BlackBoardKey_Distance.ResolveSelectedKey(*BBAsset);
		BlackBoardKey_Location.ResolveSelectedKey(*BBAsset);
	}
}

