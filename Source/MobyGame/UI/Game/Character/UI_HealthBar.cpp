// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_HealthBar.h"
#include "Components/ProgressBar.h"

void UUI_HealthBar::SetHealth(float InPercentage)
{
	Health->SetPercent(InPercentage);
}
