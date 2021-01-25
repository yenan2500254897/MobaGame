 //Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/MobyGameAIController.h"
#include "TurretsAIController.generated.h"

/**
 * 
 */
class AMobyGameCharacter;

UCLASS()
class MOBYGAME_API ATurretsAIController : public AMobyGameAIController
{
	GENERATED_BODY()

public:
	ATurretsAIController();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void InitContorller();

	virtual AMobyGameCharacter* FindTarget();

	virtual void SetTargetForce(AMobyGameCharacter* InTarget);

protected:
	bool bIntruder;
	
};
