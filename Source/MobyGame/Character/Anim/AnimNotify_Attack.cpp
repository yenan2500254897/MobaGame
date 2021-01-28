// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_Attack.h"
#include "../Item/Bullet.h"
#include "../CharacterInstance/MobyGameCharacter.h"
#include "../AI/AIController/Core/MobyGameAIController.h"

UAnimNotify_Attack::UAnimNotify_Attack()
{
	InSocketName = TEXT("OpenFire");
	bCheck = false;

	LiftTime = 4.f;

#if WITH_EDITORONLY_DATA
	NotifyColor = FColor(196, 142, 255, 255);
#endif // WITH_EDITORONLY_DATA
}

FString UAnimNotify_Attack::GetNotifyName_Implementation() const
{
	if (BulletClass)
	{
		return BulletClass->GetName();
	}

	return Super::GetNotifyName_Implementation();
}

void UAnimNotify_Attack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!BulletClass)
	{
		return;
	}

	if (AActor* Character = Cast<AActor>(MeshComp->GetOuter()))
	{
		FVector ComponentLocation = MeshComp->GetSocketLocation(InSocketName);
		FRotator ComponentRotation = MeshComp->GetSocketRotation(InSocketName);

		if (Character->GetWorld()->IsServer())
		{
			if (AMobyGameCharacter* NewCharacter = Cast<AMobyGameCharacter>(MeshComp->GetOuter()))
			{
				if (AMobyGameAIController* OwnerController = Cast<AMobyGameAIController>(NewCharacter->GetController()))
				{
					if (OwnerController->GetTarget())
					{
						ComponentRotation = FRotationMatrix::MakeFromX(OwnerController->GetTarget()->GetActorLocation() - ComponentLocation).Rotator();
						if (NewCharacter->GetCharacterType() >= ECharacterType::FIRST_CLASS_TURRETS &&
							NewCharacter->GetCharacterType() <= ECharacterType::BASE_TOWER)
						{
							
							//GEngine->AddOnScreenDebugMessage(-1, 0.5, FColor::Black, FString::Printf(TEXT("Rotator:%d  %d  %d"), NewCharacter->GetActorRotation().Pitch, NewCharacter->GetActorRotation().Yaw, NewCharacter->GetActorRotation().Roll));
							if (NewCharacter->GetActorRotation() != FRotator::ZeroRotator)
							{
								ComponentRotation -= NewCharacter->GetActorRotation();
							}
						}
					}
				}
			}

			//Character->GetLocalRole() == ENetRole::ROLE_Authority
			FActorSpawnParameters ActorSpawnParameters;
			ActorSpawnParameters.Instigator = Cast<APawn>(Character);
			//GEngine->AddOnScreenDebugMessage(-1, 0.5, FColor::Red, FString::Printf(TEXT("generate bullet at:x=:%d  y=:%d  z:=%d"), ComponentLocation.X, ComponentLocation.Y, ComponentLocation.Z));

			if (ABullet* Bullet = Character->GetWorld()->SpawnActor<ABullet>(BulletClass, ComponentLocation, ComponentRotation, ActorSpawnParameters))
			{
				Bullet->SetCheck(bCheck);
				Bullet->SetLifeSpan(LiftTime);
			}
		}
	}
}
