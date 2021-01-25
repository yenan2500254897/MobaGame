// Fill out your copyright notice in the Description page of Project Settings.


#include "MobyGameTurretsCharacter.h"
#include "Net/UnrealNetwork.h"

AMobyGameTurretsCharacter::AMobyGameTurretsCharacter()
{
	TowersRotator = FVector2D::ZeroVector;
}

void AMobyGameTurretsCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMobyGameTurretsCharacter, TowersRotator);
}
