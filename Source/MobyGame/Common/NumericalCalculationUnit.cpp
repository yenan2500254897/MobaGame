#include "NumericalCalculationUnit.h"
#include "../Character/CharacterInstance/MobyGameCharacter.h"

namespace NumericalCalculationUnit
{
	float GetArmor(AMobyGameCharacter* InTarget, AMobyGameCharacter* InEnemy)
	{
		if (FCharacterAttribute* InEnemyData = InEnemy->GetCharacterAttribute())
		{
			if (FCharacterAttribute* OriginalData = InTarget->GetCharacterAttribute())
			{
				return OriginalData->Armor * (1.f - InEnemyData->PhysicalPenetration / 100.f);
			}
		}

		return 0;
	}

	float GetMagicDefense(AMobyGameCharacter* InTarget, AMobyGameCharacter* InEnemy)
	{
		if (FCharacterAttribute* InEnemyData = InEnemy->GetCharacterAttribute())
		{
			if (FCharacterAttribute* OriginalData = InTarget->GetCharacterAttribute())
			{
				return OriginalData->MagicDefense * (1.f - InEnemyData->MagicPenetration / 100.f);
			}
		}

		return 0;
	}

	float GetAttack(AMobyGameCharacter* InOriginal)
	{
		if (FCharacterAttribute* OriginalData = InOriginal->GetCharacterAttribute())
		{
			return OriginalData->PhysicalAttack * (1 + OriginalData->CriticalStrike) + OriginalData->Lv;
		}

		return 0;
	}

	float GetPhysicalDamage(AMobyGameCharacter* InTarget, AMobyGameCharacter* InEnemy)
	{
		if (FCharacterAttribute* InEnemyData = InEnemy->GetCharacterAttribute())
		{
			return GetAttack(InEnemy) / ((GetArmor(InTarget, InEnemy) / 100) - InEnemyData->Lv * 2);
		}

		return 0;
	}

	float GetMagicDamage(AMobyGameCharacter* InTarget, AMobyGameCharacter* InEnemy)
	{
		if (FCharacterAttribute* InEnemyData = InEnemy->GetCharacterAttribute())
		{
			if (FCharacterAttribute* OriginalData = InTarget->GetCharacterAttribute())
			{
				return InEnemyData->MagicPenetration / ((GetMagicDefense(InTarget, InEnemy) / 70) - InEnemyData->Lv);
			}
		}

		return 0;
	}

	float GetDamage(AMobyGameCharacter* InTarget, AMobyGameCharacter* InEnemy)
	{
		return GetPhysicalDamage(InTarget, InTarget) + GetMagicDamage(InTarget, InTarget);
	}
}