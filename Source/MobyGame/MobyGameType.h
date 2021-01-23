#pragma once

#include "CoreMinimal.h"
#include "MobyGameType.generated.h"

enum class ESkillKeyType : uint8
{
	KEY_Q,
	KEY_W,
	KEY_E,
	KEY_R,
	KEY_MAX,
};

UENUM()
enum class ETeamType : uint8
{
	TEAM_RED,
	TEAM_BLUE,
	TEAM_NEUTRAL,
};

UENUM()
enum class ECharacterType : uint8
{
	PLAYER						UMETA(DisplayName = "Player"),

	REMOTE_MINION				UMETA(DisplayName = "Remote Minion"),
	WARRIOR_MINION				UMETA(DisplayName = "Warrior Minion"),
	BIG_MINION					UMETA(DisplayName = "Big Minion"),
	SUPER_MINION				UMETA(DisplayName = "Super Minion"),

	FIRST_CLASS_TURRETS			UMETA(DisplayName = "First Class Tower"),
	SECONDARY_DEFENSE_TOWER		UMETA(DisplayName = "Secondary Defense Tower"),
	HIGHLAND_DEFENSE_TOWER		UMETA(DisplayName = "Highland Defense Tower"),
	BASE_TOWER					UMETA(DisplayName = "Base Tower"),

	WILD_MONSTER				UMETA(DisplayName = "Wild Monster"),
	WILD_BOSS_MONSTER			UMETA(DisplayName = "Wild Boss"),
};