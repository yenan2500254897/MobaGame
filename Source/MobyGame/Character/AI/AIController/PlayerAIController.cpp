// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAIController.h"
#include "BehaviorTree/BehaviorTree.h"

APlayerAIController::APlayerAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> PlayerBehavior_Tree(TEXT("/Game/TopDownCPP/AI/Player/PlayerBH"));
	BTAsset = PlayerBehavior_Tree.Object;
}

void APlayerAIController::InitContorller()
{
	Super::InitContorller();
}