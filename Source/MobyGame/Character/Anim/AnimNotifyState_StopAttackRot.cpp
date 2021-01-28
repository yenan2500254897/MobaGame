// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState_StopAttackRot.h"
#include "../AI/AIController/Core/MobyGameAIController.h"

void UAnimNotifyState_StopAttackRot::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (ACharacter* Character = Cast<ACharacter>(MeshComp->GetOuter()))
	{
		if (Character->GetWorld()->IsServer())
		{
			if (AMobyGameAIController* AIContorller = Cast<AMobyGameAIController>(Character->GetController()))
			{
				AIContorller->StopAttackRot(true);
			}
		}
	}
}

void UAnimNotifyState_StopAttackRot::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	if (ACharacter* Character = Cast<ACharacter>(MeshComp->GetOuter()))
	{
		if (Character->GetWorld()->IsServer())
		{
			if (AMobyGameAIController* AIContorller = Cast<AMobyGameAIController>(Character->GetController()))
			{
				AIContorller->StopAttackRot(false);
			}
		}
	}
}
