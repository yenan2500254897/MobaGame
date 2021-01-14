// Copyright Epic Games, Inc. All Rights Reserved.

#include "MobaGamePlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Character/CharacterInstance/MobaGameCharacter.h"
#include "Engine/World.h"
#include "MobaPawn.h"
#include "Tool/ScreenMoveUnits.h"
AMobaGamePlayerController::AMobaGamePlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AMobaGamePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (GetLocalRole() == ENetRole::ROLE_AutonomousProxy)
	{
		if (bMoveToMouseCursor)
		{
			MoveToMouseCursor();
		}
		FScreenMoveUnits().ListenScreenMove(this, 10.f);
	}
}

void AMobaGamePlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AMobaGamePlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AMobaGamePlayerController::OnSetDestinationReleased);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AMobaGamePlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AMobaGamePlayerController::MoveToTouchLocation);

	InputComponent->BindAction("ResetVR", IE_Pressed, this, &AMobaGamePlayerController::OnResetVR);
}

void AMobaGamePlayerController::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AMobaGamePlayerController::MoveToMouseCursor()
{
	/*if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{
		if (AMobaGameCharacter* MyPawn = Cast<AMobaGameCharacter>(GetPawn()))
		{
			if (MyPawn->GetCursorToWorld())
			{
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MyPawn->GetCursorToWorld()->GetComponentLocation());
			}
		}
	}
	else*/
	if (AMobaPawn* MyPawn = Cast<AMobaPawn>(GetPawn())) {
		// Trace to see what is under the mouse cursor
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if (Hit.bBlockingHit)
		{
			// We hit something, move there
			MyPawn->CharacterMoveToOnServer(Hit.ImpactPoint);
		}
	}
}

void AMobaGamePlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (AMobaPawn* MyPawn = Cast<AMobaPawn>(GetPawn()))
	{
		FVector2D ScreenSpaceLocation(Location);

		// Trace to see what is under the touch location
		FHitResult HitResult;
		GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
		if (HitResult.bBlockingHit)
		{
			// We hit something, move there
			MyPawn->CharacterMoveToOnServer(HitResult.ImpactPoint);
		}
	}
}

void AMobaGamePlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void AMobaGamePlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}
