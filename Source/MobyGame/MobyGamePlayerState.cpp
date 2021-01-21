#include "MobyGamePlayerState.h"
#include "PlayerComponent/PlayerDataComponent.h"

AMobyGamePlayerState::AMobyGamePlayerState()
{
	PlayerData = CreateDefaultSubobject<UPlayerDataComponent>(TEXT("Data"));
	//RootComponent = PlayerData;
}