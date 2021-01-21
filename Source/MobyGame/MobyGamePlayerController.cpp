// Copyright Epic Games, Inc. All Rights Reserved.

#include "MobyGamePlayerController.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Engine/World.h"
#include "MobyPawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Tool/ScreenMoveUnits.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "GameFramework/HUD.h"
#include "MobyGameType.h"

AMobyGamePlayerController::AMobyGamePlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AMobyGamePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	
	if (GetLocalRole() == ROLE_AutonomousProxy) {
		// keep updating the destination every tick while desired
		if (bMoveToMouseCursor)
		{
			MoveToMouseCursor();
		}
	}

	FScreenMoveUnits().ListenScreenMove(this, 10.0f);
	
}

void AMobyGamePlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AMobyGamePlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AMobyGamePlayerController::OnSetDestinationReleased);

	InputComponent->BindAction("Q", IE_Pressed, this, &AMobyGamePlayerController::OnSetQPressed);
	InputComponent->BindAction("Q", IE_Released, this, &AMobyGamePlayerController::OnSetQReleased);

	InputComponent->BindAction("W", IE_Pressed, this, &AMobyGamePlayerController::OnSetWPressed);
	InputComponent->BindAction("W", IE_Released, this, &AMobyGamePlayerController::OnSetWReleased);

	InputComponent->BindAction("E", IE_Pressed, this, &AMobyGamePlayerController::OnSetEPressed);
	InputComponent->BindAction("E", IE_Released, this, &AMobyGamePlayerController::OnSetEReleased);

	InputComponent->BindAction("R", IE_Pressed, this, &AMobyGamePlayerController::OnSetRPressed);
	InputComponent->BindAction("R", IE_Released, this, &AMobyGamePlayerController::OnSetRReleased);

	InputComponent->BindAction("D", IE_Pressed, this, &AMobyGamePlayerController::OnSetDPressed);
	InputComponent->BindAction("D", IE_Released, this, &AMobyGamePlayerController::OnSetDReleased);

	InputComponent->BindAction("F", IE_Pressed, this, &AMobyGamePlayerController::OnSetFPressed);
	InputComponent->BindAction("F", IE_Released, this, &AMobyGamePlayerController::OnSetFReleased);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AMobyGamePlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AMobyGamePlayerController::MoveToTouchLocation);

	InputComponent->BindAction("ResetVR", IE_Pressed, this, &AMobyGamePlayerController::OnResetVR);
}

void AMobyGamePlayerController::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AMobyGamePlayerController::MoveToMouseCursor()
{
	if(AMobyPawn * MyPawn = Cast<AMobyPawn>(GetPawn()))
	{

		ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
		bool bHit = false;
		
		if (LocalPlayer && LocalPlayer->ViewportClient)
		{
			FVector2D MousePosition;
			if (LocalPlayer->ViewportClient->GetMousePosition(MousePosition))
			{
				// Early out if we clicked on a HUD hitbox
				
				if (GetHUD() != NULL && GetHUD()->GetHitBoxAtCoordinates(MousePosition, true))
				{
					return ;
				}

				FVector WorldOrigin;
				FVector WorldDirection;
				if (UGameplayStatics::DeprojectScreenToWorld(this, MousePosition, WorldOrigin, WorldDirection) == true)
				{
					VerifyMouseWorldPositionOnServer(WorldOrigin, WorldDirection);
				}
			}
		}
	}
}

void AMobyGamePlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (AMobyPawn* MyPawn = Cast<AMobyPawn>(GetPawn()))
	{
		FVector2D ScreenSpaceLocation(Location);

		// Trace to see what is under the touch location
		FHitResult HitResult;
		GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
		if (HitResult.bBlockingHit)
		{
			MyPawn->CharacterMoveToOnServer(HitResult.ImpactPoint);
		}
	}
	
}

void AMobyGamePlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void AMobyGamePlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}

void AMobyGamePlayerController::OnSetQPressed_Implementation()
{
	if (AMobyPawn *MyPawn = Cast<AMobyPawn>(GetPawn()))
	{
		MyPawn->SkillAttack(ESkillKeyType::KEY_Q, NULL);
	}
}

void AMobyGamePlayerController::OnSetQReleased()
{
}

void AMobyGamePlayerController::OnSetWPressed_Implementation()
{
	if (AMobyPawn* MyPawn = Cast<AMobyPawn>(GetPawn()))
	{
		MyPawn->SkillAttack(ESkillKeyType::KEY_W, NULL);
	}
}

void AMobyGamePlayerController::OnSetWReleased()
{
}

void AMobyGamePlayerController::OnSetEPressed_Implementation()
{
	if (AMobyPawn* MyPawn = Cast<AMobyPawn>(GetPawn()))
	{
		MyPawn->SkillAttack(ESkillKeyType::KEY_E, NULL);
	}
}

void AMobyGamePlayerController::OnSetEReleased()
{
}

void AMobyGamePlayerController::OnSetRPressed_Implementation()
{
	if (AMobyPawn* MyPawn = Cast<AMobyPawn>(GetPawn()))
	{
		MyPawn->SkillAttack(ESkillKeyType::KEY_R, NULL);
	}
}

void AMobyGamePlayerController::OnSetRReleased()
{
}

void AMobyGamePlayerController::OnSetDPressed_Implementation()
{
	
}

void AMobyGamePlayerController::OnSetDReleased()
{
}

void AMobyGamePlayerController::OnSetFPressed_Implementation()
{
	
}

void AMobyGamePlayerController::OnSetFReleased()
{
}

//发生在服务器上
void AMobyGamePlayerController::VerifyMouseWorldPositionOnServer_Implementation(const FVector& WorldOrigin, const FVector& WorldDirection)
{
	if (AMobyPawn* MyPawn = Cast<AMobyPawn>(GetPawn()))
	{
		FHitResult HitResult;
		FCollisionQueryParams CollisionQueryParams(SCENE_QUERY_STAT(ClickableTrace), false);
		// Trace to see what is under the mouse cursor
		auto TracePos = [&](ECollisionChannel InChannel)->bool
		{
			return GetWorld()->LineTraceSingleByChannel(HitResult, WorldOrigin, WorldOrigin + WorldDirection * HitResultTraceDistance, InChannel, CollisionQueryParams);
		};

		if (TracePos(ECC_GameTraceChannel1))//检测到对象
		{
			if (HitResult.bBlockingHit)//检测到就移动攻击
			{
				//移动攻击
				MyPawn->CharacterMoveToTargetAttackOnServer(HitResult.ImpactPoint, Cast<APawn>(HitResult.Actor));
				return;
			}

		}
		if (TracePos(ECC_Visibility)) {
			if (HitResult.bBlockingHit)//检测移动攻击
			{
				MyPawn->CharacterMoveToOnServer(HitResult.ImpactPoint);
			}
		}
	}
}

bool AMobyGamePlayerController::VerifyMouseWorldPositionOnServer_Validate(const FVector& WorldOrigin, const FVector& WorldDirection)
{
	return true;
}
