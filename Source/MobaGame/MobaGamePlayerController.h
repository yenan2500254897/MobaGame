// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MobaGamePlayerController.generated.h"

UCLASS()
class AMobaGamePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMobaGamePlayerController();

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

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

	UFUNCTION(server, reliable)
		void OnSetQPressed();
		void OnSetQReleased();

	UFUNCTION(server, reliable)
		void OnSetWPressed();
		void OnSetWReleased();

	UFUNCTION(server, reliable)
		void OnSetEPressed();
		void OnSetEReleased();

	UFUNCTION(server, reliable)
		void OnSetRPressed();
		void OnSetRReleased();

	//UFUNCTION(server, reliable)
		void OnSetDPressed();
		void OnSetDReleased();

	//UFUNCTION(server, reliable)
		void OnSetFPressed();
		void OnSetFReleased();

protected:
	UFUNCTION(Server, reliable, WithValidation)
		void VerifyMouseWorldPostionClickOnServer(const FVector& WorldOrigin, const FVector& WorldDirection);
};


