// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretsAIController.h"
#include "../../CharacterInstance/MobyGameTurretsCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"


ATurretsAIController::ATurretsAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> TurretsBehavior_Tree(TEXT("/Game/TopDownCPP/AI/Turret/TurretBH"));
	BTAsset = TurretsBehavior_Tree.Object;
}

void ATurretsAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Target.IsValid())
	{
		if (AMobyGameTurretsCharacter* OnwerCharacter = GetPawn<AMobyGameTurretsCharacter>())
		{
			FRotator R = FRotationMatrix::MakeFromX(Target->GetActorLocation() - GetPawn()->GetActorLocation()).Rotator();
			OnwerCharacter->TowersRotator = FVector2D(R.Pitch, (float)R.Yaw-90.0f);
			if (GetPawn()->GetActorRotation() != FRotator::ZeroRotator)
			{
				FVector2D NewRot = FVector2D(GetPawn()->GetActorRotation().Pitch, GetPawn()->GetActorRotation().Yaw);
				OnwerCharacter->TowersRotator -= NewRot;
			}
		}
	}
}

void ATurretsAIController::InitContorller()
{
	Super::InitContorller();

}

void ATurretsAIController::SetTargetForce(AMobyGameCharacter* InTarget)
{
	Super::SetTargetForce(InTarget);

	if (!InTarget)
	{
		bIntruder = false;
	}
}

AMobyGameCharacter* ATurretsAIController::FindTarget()
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMobyGameCharacter::StaticClass(), OutActors);

	if (AMobyGameCharacter* InOwnerCharacter = Cast<AMobyGameCharacter>(GetPawn()))
	{
		if (!bIntruder)
		{
			float OwnerDistance = 999999.f;
			AMobyGameCharacter* TargetActor = NULL;

			for (auto& Tmp : OutActors)
			{
				if (Tmp != InOwnerCharacter)
				{
					if (AMobyGameCharacter* InTargetCharacter = Cast<AMobyGameCharacter>(Tmp))
					{
						if (1)
						{
							float Distance = FVector::Dist(Tmp->GetActorLocation(), InOwnerCharacter->GetActorLocation());
							float RangeAttack = InOwnerCharacter->GetCharacterAttribute()->RangeAttack;
							if (Distance <= RangeAttack)
							{
								if (Distance < OwnerDistance)
								{
									OwnerDistance = Distance;
									TargetActor = InTargetCharacter;

									bIntruder = true;
								}
							}
						}
					}
				}
			}

			return TargetActor;
		}

		struct FAICharacterTarget
		{
			FAICharacterTarget()
				:Player(NULL)
				, Minion(NULL)
				, Monster(NULL)
				, PlayerReferenceDistance(999999.f)
				, MinionReferenceDistance(999999.f)
				, MonsterReferenceDistance(999999.f)
			{}

			AMobyGameCharacter* Player;
			AMobyGameCharacter* Minion;
			AMobyGameCharacter* Monster;
			float PlayerReferenceDistance;
			float MinionReferenceDistance;
			float MonsterReferenceDistance;
		}Targets;

		for (auto& Tmp : OutActors)
		{
			if (Tmp != InOwnerCharacter)
			{
				if (AMobyGameCharacter* InTargetCharacter = Cast<AMobyGameCharacter>(Tmp))
				{
					if (1)
					{
						float Distance = FVector::Dist(Tmp->GetActorLocation(), InOwnerCharacter->GetActorLocation());
						float RangeAttack = InOwnerCharacter->GetCharacterAttribute()->RangeAttack;
						if (Distance <= RangeAttack)
						{
							if (InTargetCharacter->GetCharacterType() >= ECharacterType::REMOTE_MINION &&
								InTargetCharacter->GetCharacterType() <= ECharacterType::SUPER_MINION)
							{
								if (Distance < Targets.MinionReferenceDistance)
								{
									Targets.MinionReferenceDistance = Distance;
									Targets.Minion = InTargetCharacter;
								}
							}
							else if (InTargetCharacter->GetCharacterType() == ECharacterType::PLAYER)
							{
								if (Distance < Targets.PlayerReferenceDistance)
								{
									Targets.PlayerReferenceDistance = Distance;
									Targets.Player = InTargetCharacter;
								}
							}
							else if (InTargetCharacter->GetCharacterType() >= ECharacterType::WILD_MONSTER)
							{
								if (Distance < Targets.MonsterReferenceDistance)
								{
									Targets.MonsterReferenceDistance = Distance;
									Targets.Monster = InTargetCharacter;
								}
							}
						}
					}
				}
			}
		}

		if (Targets.Monster)
		{
			return Targets.Monster;
		}
		else if (Targets.Minion)
		{
			return Targets.Minion;
		}
		else if (Targets.Player)
		{
			return Targets.Player;
		}
	}

	return NULL;
}

