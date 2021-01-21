// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SimpleMoveTo.h"

EBTNodeResult::Type UBTTask_SimpleMoveTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AcceptableRadius = 950.0f;

	return Super::ExecuteTask(OwnerComp, NodeMemory);
}