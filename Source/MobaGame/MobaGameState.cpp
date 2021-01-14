// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaGameState.h"

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

const FCharacterTable* AMobaGameState::GetCharacterTable(const int64& InID)
{
	for (auto& Tmp : *GetCharacterTables())
	{
		if (Tmp->CharacterID == InID)
		{
			return Tmp;
		}
	}

	return NULL;
}