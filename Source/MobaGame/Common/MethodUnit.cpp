#include "MethodUnit.h"

namespace MethodUnit
{
	AMobaGameState* GetGameState(UWorld* NewWorld)
	{
		if (NewWorld)
		{
			return NewWorld->GetGameState<AMobaGameState>();
		}

		return NULL;
	}

	const FCharacterTable* GetCharacterTable(UWorld* NewWorld, int64 InID)
	{
		if (AMobaGameState* InGameStatre = GetGameState(NewWorld))
		{
			return InGameStatre->GetCharacterTable(InID);
		}

		return NULL;
	}
}

