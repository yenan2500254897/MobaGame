// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../../UI/Core/UI_Base.h"
#include "UI_HealthBar.generated.h"

class UProgressBar;

/**
 * 
 */
UCLASS()
class MOBYGAME_API UUI_HealthBar : public UUI_Base
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UProgressBar* Health;

public:

	void SetHealth(float InPercentage);
	
};
