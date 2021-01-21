#include "UI_Base.h"

AMobyGameHUD* UUI_Base::GetHUD()
{
	return Cast<AMobyGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
}