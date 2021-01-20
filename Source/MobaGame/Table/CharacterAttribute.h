// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Core/MobaGameTableBase.h"
#include "CharacterAttribute.generated.h"

USTRUCT(BlueprintType)
struct FCharacterAttribute :public FMobaGameTableBase
{
	GENERATED_USTRUCT_BODY()

	FCharacterAttribute();

	//等级
	UPROPERTY()
		int32 Lv;

	//最大蓝量
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
		float MaxMana;

	//蓝量
	UPROPERTY()
		float Mana;

	//最大怒值
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
		float MaxAnger;

	//怒值
	UPROPERTY()
		float Anger;

	//最大生命值
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
		float MaxHealth;

	//生命值
	UPROPERTY()
		float Health;

	//物理攻击
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
		float PhysicalAttack;

	//护甲
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
		float Armor;

	//魔法攻击
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
		float MagicAttack;

	//魔抗
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
		float MagicDefense;

	//物理穿透
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
		float PhysicalPenetration;

	//物理穿透
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

	//经验值
	UPROPERTY()
		float EmpircalValue;

	//攻击范围
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
		float RangeAttack;


	void Init();

	float GetHealthPercentage();
	float GetManaPercentage();
	float GetEmpircalPercentage();
	float GetAngerPercentage();
};