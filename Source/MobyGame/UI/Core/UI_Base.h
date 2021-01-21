#pragma once

#include "CoreMinimal.h"
#include "../../MobyGameHUD.h"
#include "Blueprint/UserWidget.h"
#include "UI_Base.generated.h"

/**
 *
 */
UCLASS()
class MOBYGAME_API UUI_Base : public UUserWidget
{
	GENERATED_BODY()

public:
	AMobyGameHUD* GetHUD();
};