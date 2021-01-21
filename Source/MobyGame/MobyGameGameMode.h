// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MobyGameGameMode.generated.h"

UCLASS(minimalapi)
class AMobyGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMobyGameGameMode();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};



