// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Base.h"

AMobaGameHUD* UUI_Base::GetHUD()
{
	return Cast<AMobaGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
}