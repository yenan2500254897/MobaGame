// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MobyGamePlayerController.generated.h"

UCLASS()
class AMobyGamePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMobyGamePlayerController();

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Navigate player to the current mouse cursor location. */
	void MoveToMouseCursor();

	/** Navigate player to the current touch location. */
	void MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location);
	
	///** Navigate player to the given world location. */
	//void SetNewMoveDestination(const FVector DestLocation);

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

	/** Input handlers for SetDestination action. */
	UFUNCTION(server, reliable)
	void OnSetQPressed();
	void OnSetQReleased();

	/** Input handlers for SetDestination action. */
	UFUNCTION(server, reliable)
	void OnSetWPressed();
	void OnSetWReleased();

	/** Input handlers for SetDestination action. */
	UFUNCTION(server, reliable)
	void OnSetEPressed();
	void OnSetEReleased();

	/** Input handlers for SetDestination action. */
	UFUNCTION(server, reliable)
	void OnSetRPressed();
	void OnSetRReleased();

	/** Input handlers for SetDestination action. */
	UFUNCTION(server, reliable)
	void OnSetDPressed();
	void OnSetDReleased();

	/** Input handlers for SetDestination action. */
	UFUNCTION(server, reliable)
	void OnSetFPressed();
	void OnSetFReleased();

protected:
	UFUNCTION(server, reliable, WithValidation)
	void VerifyMouseWorldPositionOnServer(const FVector& WorldOrigin, const FVector& WorldDirection);
};


