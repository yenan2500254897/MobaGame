// Fill out your copyright notice in the Description page of Project Settings.


#include "MinionsAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"

AMinionsAIController::AMinionsAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> MinionsBehavior_Tree(TEXT("/Game/TopDownCPP/AI/Minions/MinionsBH"));
	BTAsset = MinionsBehavior_Tree.Object;
}

void AMinionsAIController::InitContorller()
{
	Super::InitContorller();
}

AMobyGameCharacter* AMinionsAIController::FindTarget()
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMobyGameCharacter::StaticClass(), OutActors);

	if (AMobyGameCharacter* InOwnerCharacter = Cast<AMobyGameCharacter>(GetPawn()))
	{
		struct FAICharacterTarget
		{
			FAICharacterTarget()
				:Player(NULL)
				, Tower(NULL)
				, Minion(NULL)
				, Monster(NULL)
				, PlayerReferenceDistance(999999.f)
				, TowerReferenceDistance(999999.f)
				, MinionReferenceDistance(999999.f)
				, MonsterReferenceDistance(999999.f)
			{}

			AMobyGameCharacter* Player;
			AMobyGameCharacter* Tower;
			AMobyGameCharacter* Minion;
			AMobyGameCharacter* Monster;

			float PlayerReferenceDistance;
			float TowerReferenceDistance;
			float MinionReferenceDistance;
			float MonsterReferenceDistance;
		};

		FAICharacterTarget Targets;
		for (auto& Tmp : OutActors)
		{
			if (Tmp != InOwnerCharacter)
			{

				float Distance = FVector::Dist(Tmp->GetActorLocation(), InOwnerCharacter->GetActorLocation());
				if (Distance <= 2000.f)
				{
					if (AMobyGameCharacter* InCharacter = Cast<AMobyGameCharacter>(Tmp))
					{
						if (InCharacter->GetCharacterType() >= ECharacterType::REMOTE_MINION &&
							InCharacter->GetCharacterType() <= ECharacterType::SUPER_MINION)//ÅÐ¶ÏÐ¡±ø
						{
							if (Distance < Targets.MinionReferenceDistance)
							{
								Targets.MinionReferenceDistance = Distance;
								Targets.Minion = InCharacter;
							}
						}
						else if (InCharacter->GetCharacterType() >= ECharacterType::FIRST_CLASS_TURRETS &&
							InCharacter->GetCharacterType() <= ECharacterType::BASE_TOWER)//ÅÐ¶ÏËþ
						{
							if (Distance < Targets.TowerReferenceDistance)
							{
								Targets.TowerReferenceDistance = Distance;
								Targets.Tower = InCharacter;
							}
						}
						else if (InCharacter->GetCharacterType() == ECharacterType::PLAYER)//ÅÐ¶ÏÍæ¼Ò
						{
							if (Distance < Targets.PlayerReferenceDistance)
							{
								Targets.PlayerReferenceDistance = Distance;
								Targets.Player = InCharacter;
							}
						}
						else if (InCharacter->GetCharacterType() >= ECharacterType::WILD_MONSTER)//ÅÐ¶ÏÍæ¼Ò
						{
							if (Distance < Targets.MonsterReferenceDistance)
							{
								Targets.MonsterReferenceDistance = Distance;
								Targets.Monster = InCharacter;
							}
						}
					}
				}
			}
		}

		if (Targets.Minion)
		{
			return Targets.Minion;
		}
		else if (Targets.Tower)
		{
			return Targets.Tower;
		}
		else if (Targets.Player)
		{
			return Targets.Player;
		}
		else if (Targets.Monster)
		{
			return Targets.Monster;
		}
	}

	return NULL;
}
