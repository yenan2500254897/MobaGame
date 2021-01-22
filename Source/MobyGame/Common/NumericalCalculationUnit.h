#pragma once

#include "CoreMinimal.h"

class AMobyGameCharacter;

namespace NumericalCalculationUnit
{
	float GetArmor(AMobyGameCharacter* InTarget, AMobyGameCharacter* InEnemy);
	float GetMagicDefense(AMobyGameCharacter* InTarget, AMobyGameCharacter* InEnemy);
	float GetAttack(AMobyGameCharacter* InOriginal);
	float GetPhysicalDamage(AMobyGameCharacter* InTarget, AMobyGameCharacter* InEnemy);
	float GetMagicDamage(AMobyGameCharacter* InTarget, AMobyGameCharacter* InEnemy);

	float GetDamage(AMobyGameCharacter* InTarget, AMobyGameCharacter* InEnemy);
}