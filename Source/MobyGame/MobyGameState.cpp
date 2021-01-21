#include "MobyGameState.h"
#include "Net/UnrealNetwork.h"

AMobyGameState::AMobyGameState()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> Character_Table(TEXT("/Game/Table/CharacterTable"));
	CharacterTablePtr = Character_Table.Object;

	static ConstructorHelpers::FObjectFinder<UDataTable> Character_Attribute(TEXT("/Game/Table/CharacterAttribute"));
	CharacterAttributePtr = Character_Attribute.Object;
}

const TArray<FCharacterTable*>* AMobyGameState::GetCharacterTablesTemplate()
{
	if (!CacheCharacterTables.Num())
	{
		if (CharacterTablePtr)
		{
			CharacterTablePtr->GetAllRows(TEXT("Character Table"), CacheCharacterTables);
		}
		else
		{
			//��ӡ
		}
	}

	return &CacheCharacterTables;
}

const TArray<FCharacterAttribute*>* AMobyGameState::GetCharacterAttributesTemplate()
{
	if (!CacheCharacterAttributes.Num())
	{
		if (CharacterAttributePtr)
		{
			CharacterAttributePtr->GetAllRows(TEXT("Character Table"), CacheCharacterAttributes);
		}
		else
		{
			//��ӡ
		}
	}

	return &CacheCharacterAttributes;
}

const FCharacterTable* AMobyGameState::GetCharacterTableTemplate(const int32& InID)
{
	for (auto& Tmp : *GetCharacterTablesTemplate())
	{
		if (Tmp->CharacterID == InID)
		{
			return Tmp;
		}
	}

	return NULL;
}

void AMobyGameState::AddCharacterData(int64 PlayerID, int32 CharacterID)
{
	if (!CharacterAttributes.Contains(PlayerID))
	{
		CharacterAttributes.Add(PlayerID, *GetCharacterAttributeTemplate(CharacterID));
	}
}

const TMap<int64, FCharacterAttribute>* AMobyGameState::GetCharacterAttributes()
{
	return &CharacterAttributes;
}

FCharacterAttribute* AMobyGameState::GetCharacterAttribute(int64 InPlayerID)
{
	for (auto& Tmp : CharacterAttributes)
	{
		if (Tmp.Key == InPlayerID)
		{
			return &Tmp.Value;
		}
	}

	return NULL;
}

const FCharacterAttribute* AMobyGameState::GetCharacterAttributeTemplate(const int32& InID)
{
	for (auto& Tmp : *GetCharacterAttributesTemplate())
	{
		if (Tmp->CharacterID == InID)
		{
			return Tmp;
		}
	}

	return NULL;
}

void AMobyGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMobyGameState, PlayerLocations);
}

void AMobyGameState::UpdateCharacterAILocation(int64 InPlayerID, const FVector& InLocation)
{
	for (auto& Tmp : PlayerLocations)
	{
		if (Tmp.PlayerID == InPlayerID)
		{
			Tmp.Location = InLocation;
			break;
		}
	}
}

void AMobyGameState::AddCharacterAILocation(int64 InPlayerID, const FVector& InLocation)
{
	for (auto& Tmp : PlayerLocations)
	{
		if (Tmp.PlayerID == InPlayerID)
		{
			return;
		}
	}

	PlayerLocations.Add(FPlayerLocation());
	PlayerLocations[PlayerLocations.Num() - 1].PlayerID = InPlayerID;
	PlayerLocations[PlayerLocations.Num() - 1].Location = InLocation;
}

bool AMobyGameState::GetCharacterAILocation(int64 InPlayerID, FVector& InLocation)
{
	for (auto& Tmp : PlayerLocations)
	{
		if (Tmp.PlayerID == InPlayerID)
		{
			InLocation = Tmp.Location;
			return true;
		}
	}

	return false;
}

int32 AMobyGameState::GetCharacterID(int64 InPlayerID)
{
	if (FCharacterAttribute* CA = GetCharacterAttribute(InPlayerID))
	{
		return CA->CharacterID;
	}

	return INDEX_NONE;
}

const TArray<FPlayerLocation>& AMobyGameState::GetPlayerLocations()
{
	return PlayerLocations;
}
