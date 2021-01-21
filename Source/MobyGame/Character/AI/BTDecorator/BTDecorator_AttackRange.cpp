// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_AttackRange.h"
#include "../AIController/MobyGameAIController.h"
#include "../../CharacterInstance/MobyGameCharacter.h"

void UBTDecorator_AttackRange::InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const
{
	Super::InitializeMemory(OwnerComp, NodeMemory, InitType);

	if (AMobyGameAIController* OwnerController = Cast<AMobyGameAIController>(OwnerComp.GetOwner()))
	{
		if (AMobyGameCharacter* OwnerCharacter = Cast<AMobyGameCharacter>(OwnerController->GetPawn()))
		{
			float* fv = const_cast<float*>(&FloatValue);//ȥconst
			*fv = OwnerCharacter->GetCharacterAttribute()->RangeAttack;
			//*fv = 500.f;
		}
	}
}