// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/MobyGameAIController.h"
#include "MinionsAIController.generated.h"

/**
 * 
 */
UCLASS()
class MOBYGAME_API AMinionsAIController : public AMobyGameAIController
{
	GENERATED_BODY()

public:
	AMinionsAIController();

	virtual void InitContorller();

	virtual AMobyGameCharacter* FindTarget();
	
};
