// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MobaGameCharacter.generated.h"

UCLASS(Blueprintable)
class AMobaGameCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMobaGameCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;
};

