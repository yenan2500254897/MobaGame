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