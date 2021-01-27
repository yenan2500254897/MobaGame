// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAIController.h"
#include "BehaviorTree/BehaviorTree.h"

AMonsterAIController::AMonsterAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> MonsterBehavior_Tree(TEXT("/Game/TopDownCPP/AI/Monster/MonsterBH"));
	BTAsset = MonsterBehavior_Tree.Object;

	HomePoint = FVector::ZeroVector;
}

AMobyGameCharacter* AMonsterAIController::FindTarget()
{
	return nullptr;
}
