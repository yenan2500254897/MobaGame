// Copyright Epic Games, Inc. All Rights Reserved.

#include "MobaGameCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Components/CapsuleComponent.h"
#include "../../Common/MethodUnit.h"

AMobaGameCharacter::AMobaGameCharacter()
	:bAttacking(false)
	, AttackCount(0)
	, CharacterID(INDEX_NONE)
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AMobaGameCharacter::NormalAttack(TWeakObjectPtr<AMobaGameCharacter> InTarget)
{
	if (InTarget.IsValid())
	{
		if (const FCharacterTable* CharacterTable = MethodUnit::GetCharacterTable(GetWorld(), CharacterID))
		{
			if (AttackCount < CharacterTable->NormalAttack.Num())
			{
				if (UAnimMontage* MontageInstance = CharacterTable->NormalAttack[AttackCount])
				{
					if (AttackCount == CharacterTable->NormalAttack.Num() - 1)
					{
						AttackCount = 0;
					}
					else
					{
						AttackCount++;
					}

					MultCastPlayerAnimMontage(MontageInstance);
				}
			}
		}
	}
}

UAnimMontage* AMobaGameCharacter::GetCurrentSkillMontage(ESkillKeyType SkillKey)
{
	if (const FCharacterTable* CharacterTable = MethodUnit::GetCharacterTable(GetWorld(), CharacterID))
	{
		switch (SkillKey)
		{
		case ESkillKeyType::KEY_Q:return CharacterTable->QSkillAttack;
		case ESkillKeyType::KEY_W:return CharacterTable->WSkillAttack;
		case ESkillKeyType::KEY_E:return CharacterTable->ESkillAttack;
		case ESkillKeyType::KEY_R:return CharacterTable->RSkillAttack;
		}
	}

	return NULL;
}

void AMobaGameCharacter::SkillAttack(ESkillKeyType SkillKey, TWeakObjectPtr<AMobaGameCharacter> InTarget)
{
	if (const FCharacterTable* CharacterTable = MethodUnit::GetCharacterTable(GetWorld(), CharacterID))
	{
		if (UAnimMontage* MontageInstance = GetCurrentSkillMontage(SkillKey))
		{
			MultCastPlayerAnimMontage(MontageInstance);
		}
	}
}

void AMobaGameCharacter::InitCharacterID(const int32& InCharacterID)
{
	CharacterID = InCharacterID;
}

void AMobaGameCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (GetLocalRole() == ROLE_Authority)
	{
		SpawnDefaultController();
	}
}

void AMobaGameCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AMobaGameCharacter::MultCastPlayerAnimMontage_Implementation(UAnimMontage* InAnimMontage, float InPlayRate /*= 1.0f*/, FName StartSectionName /*= NAME_None*/)
{
	if (InAnimMontage)
	{
		PlayAnimMontage(InAnimMontage, InPlayRate, StartSectionName);
	}
}