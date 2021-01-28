// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../../MobyGameType.h"
#include "../../Table/CharacterAttribute.h"
#include "MobyGameCharacter.generated.h"

class UWidgetComponent;
class UArrowComponent;
UCLASS(Blueprintable)
class AMobyGameCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttrubute", meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* Widget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttrubute", meta = (AllowPrivateAccess = "true"))
	UArrowComponent* OpenFriePoint;

public:
	AMobyGameCharacter();

	void NormalAttack(TWeakObjectPtr<AMobyGameCharacter> InTarget);

	void RegisterCharacter(const int64& InPlayerID, int32 CharacterID);

	UFUNCTION()
	virtual void InitCharacter();

	UFUNCTION(NetMulticast, unreliable)
	void MultCastPlayerAnimMontage(UAnimMontage *InMontage, float InPlayRate = 1.0f, FName StartSectionName = NAME_None);

	UFUNCTION(NetMulticast, unreliable)
	void MultCastWidgetInfo(float InHPPercentage, float InManaPercentage);

	UFUNCTION(NetMulticast, unreliable)
	void MultCastReborn();

	FCharacterAttribute* GetCharacterAttribute();

	bool IsDie();

	void SetTeam(ETeamType InTeamType);
	void SetCharacterType(ECharacterType InCharacterType);

	void ResetSpeed(float InSpeed);


	FVector GetFireLocation();
	FRotator GetFireRotator();
public:
	FORCEINLINE int64 GetPlayerID() { return PlayerID; }
	FORCEINLINE ETeamType GetTeam() { return TeamType; }
	FORCEINLINE ECharacterType GetCharacterType() { return CharacterType; }
	FORCEINLINE UArrowComponent* GetFirePoint() const { return OpenFriePoint; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:
	bool bAttacking;
	uint8 AttackCount;
	int64 PlayerID;

private:
	FTimerHandle InitTimeHandle;
	ETeamType TeamType;
	ECharacterType CharacterType;
};

