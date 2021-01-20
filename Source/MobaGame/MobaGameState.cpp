// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaGameState.h"
#include "Net/UnrealNetwork.h"

AMobaGameState::AMobaGameState()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> Character_Table(TEXT("/Game/Table/CharacterTable"));
	CharacterTablePtr = Character_Table.Object;
}

const TArray<FCharacterTable*>* AMobaGameState::GetCharacterTables()
{
	if (!CacheCharacterTables.Num())
	{
		if (CharacterTablePtr)
		{
			CharacterTablePtr->GetAllRows(TEXT("Character Table"), CacheCharacterTables);
		}
		else
		{
			
		}
	}

	return &CacheCharacterTables;
}

const FCharacterTable* AMobaGameState::GetCharacterTable(const int32& InCharacterID)
{
	for (auto& Tmp : *GetCharacterTables())
	{
		if (Tmp->CharacterID == InCharacterID)
		{
			return Tmp;
		}
	}

	return NULL;
}

void AMobaGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	/*DOREPLIFETIME(AMobaGameState, PlayerLocation);*/
}

//void AMobaGameState::UpdateCharacterAILocation(int64 InPlayerID, const FVector& InLocation)
//{
//	for (auto& Tmp : PlayerLocation)
//	{
//		if (Tmp.CharacterID == InPlayerID)
//		{
//			Tmp.Location = InLocation;
//			break;
//		}
//	}
//}
//
//void AMobaGameState::AddCharacterAILocation(int64 InPlayerID, const FVector& InLocation)
//{
//	for (auto& Tmp : PlayerLocation)
//	{
//		if (Tmp.CharacterID == InPlayerID)
//		{
//			return;
//		}
//	}
//
//	PlayerLocation.Add(FPlayerLocation());
//	PlayerLocation[PlayerLocation.Num() - 1].CharacterID = InPlayerID;
//	PlayerLocation[PlayerLocation.Num() - 1].Location = InLocation;
//}
//
//bool AMobaGameState::GetCharacterAILocation(int64 InPlayerID, FVector& InLocation)
//{
//	for (auto& Tmp : PlayerLocation)
//	{
//		if (Tmp.CharacterID == InPlayerID)
//		{
//			InLocation = Tmp.Location;
//			return true;
//		}
//	}
//
//	return false;
//}
//
//const TArray<FPlayerLocation>& AMobaGameState::GetPlayerLocations()
//{
//	return PlayerLocation;
//}