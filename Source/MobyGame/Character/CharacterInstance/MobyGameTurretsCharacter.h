// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MobyGameCharacter.h"
#include "MobyGameTurretsCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MOBYGAME_API AMobyGameTurretsCharacter : public AMobyGameCharacter
{
	GENERATED_BODY()

public:
	AMobyGameTurretsCharacter();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

public:
	UPROPERTY(Replicated, BlueprintReadOnly)
		FVector2D TowersRotator;
	
};
