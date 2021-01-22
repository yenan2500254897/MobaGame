#pragma once

#include "CoreMinimal.h"
#include "Core/MobyGameTableBase.h"
#include "CharacterAttribute.generated.h"

USTRUCT(BlueprintType)
struct FCharacterAttribute : public FMobyGameTableBase
{
	GENERATED_USTRUCT_BODY()

	FCharacterAttribute();

	UPROPERTY()
	int32 Lv;

	//最大蓝量
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	float MaxMana;

	//当前蓝量
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	float Mana;

	//最大怒值
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	float MaxAnger;

	//当前怒值
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	float Anger;

	//最大生命值
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	float MaxHealth;

	//生命值
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	float Health;

	//物理攻击
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	float PhysicalAttack;

	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	float CriticalStrike;

	//护甲
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	float Armor;

	//魔法攻击
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	float MagicAttack;

	//魔法防御
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	float MagicDefense;

	//物理穿透
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	float PhysicalPenetration;

	//魔法穿透
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	float MagicPenetration;

	//移动速度
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	float WalkSpeed;

	//攻击速度
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	float AttackSpeed;

	//最大经验值
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	float MaxEmpircalValue;

	//当前经验值
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	float EmpircalValue;

	//范围攻击
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	float RangeAttack;

	void Init();

	float GetHealthPercentage();
	float GetManaPercentage();
	float GetEmpircalPercentage();
	float GetAngerPercentage();
};