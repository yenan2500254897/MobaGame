#pragma once

#include "CoreMinimal.h"
#include "MobyGameCharacter.h"
#include "MobyGameMonsterCharacter.generated.h"

/**
 *
 */
UCLASS()
class MOBYGAME_API AMobyGameMonsterCharacter : public AMobyGameCharacter
{
	GENERATED_BODY()

public:
	virtual void InitCharacter();


protected:
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};