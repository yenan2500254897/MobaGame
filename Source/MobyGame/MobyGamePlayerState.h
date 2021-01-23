#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MobyGamePlayerState.generated.h"

class UPlayerDataComponent;
/**
 *
 */
UCLASS()
class MOBYGAME_API AMobyGamePlayerState : public APlayerState
{
	GENERATED_BODY()

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttrubute", meta = (AllowPrivateAccess = "true"))
		UPlayerDataComponent* PlayerData;

public:

	AMobyGamePlayerState();

	FORCEINLINE const UPlayerDataComponent* GetPlayerData() { return PlayerData; }
};