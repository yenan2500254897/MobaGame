// Fill out your copyright notice in the Description page of Project Settings.

#include "MobyGameMonsterCharacter.h"
#include "../AI/AIController/MonsterAIController.h"

float AMobyGameMonsterCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (GetLocalRole() == ROLE_Authority)//if (GetWord()->IsServer())
	{
		if (AMobyGameCharacter* DamageCauserCharacter = Cast<AMobyGameCharacter>(DamageCauser))
		{
			if (AMonsterAIController* MonsterController = Cast<AMonsterAIController>(GetController()))
			{
				MonsterController->SetTargetForce(DamageCauserCharacter);
			}
		}
	}

	return Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
}

void AMobyGameMonsterCharacter::InitCharacter()
{
	Super::InitCharacter();

	if (AMonsterAIController* MonsterController = Cast<AMonsterAIController>(GetController()))
	{
		MonsterController->HomePoint = GetActorLocation();
	}
}