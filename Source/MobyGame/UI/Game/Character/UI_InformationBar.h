// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../../UI/Core/UI_Base.h"
#include "UI_InformationBar.generated.h"

class UProgressBar;
class UTextBlock;
/**
 *
 */
UCLASS()
class MOBYGAME_API UUI_InformationBar : public UUI_Base
{
	GENERATED_BODY()

		UPROPERTY(meta = (BindWidget))
		UTextBlock* Title;

	UPROPERTY(meta = (BindWidget))
		UProgressBar* Health;

	UPROPERTY(meta = (BindWidget))
		UProgressBar* Mana;

public:

	virtual void NativeConstruct() override;

	void SetTitle(const FString& Msg);
	void SetHealth(float InPercentage);
	void SetMana(float InPercentage);
};

