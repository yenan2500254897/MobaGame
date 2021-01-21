#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../MobyGameType.h"
#include "PlayerDataComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MOBYGAME_API UPlayerDataComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPlayerDataComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

protected:
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(Replicated, EditDefaultsOnly, Category = "Player data")
		FName PlayerName;

	UPROPERTY(Replicated, EditDefaultsOnly, Category = "Player data")
		ETeamType Team;

	UPROPERTY(Replicated, EditDefaultsOnly, Category = "Player data")
		int64 PlayerID;
};