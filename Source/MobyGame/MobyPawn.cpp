// Fill out your copyright notice in the Description page of Project Settings.


#include "MobyPawn.h"
#include "Character/CharacterInstance/MobyGameCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
//#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Common/MethodUnit.h"
#include "Character/AI/AIController/Core/MobyGameAIController.h"
#include "MobyGamePlayerState.h"
#include "PlayerComponent/PlayerDataComponent.h"

void AMobyPawn::SkillAttack(ESkillKeyType SkillType, TWeakObjectPtr<AMobyGameCharacter> InTarget)
{
	if (MobyGameCharacter)
	{
		MobyGameCharacter->SkillAttack(SkillType, InTarget);
	}
}

// Sets default values
AMobyPawn::AMobyPawn()
{

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	RootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RootBox"));
	RootComponent = RootBox;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/TopDownCPP/Blueprints/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AMobyPawn::InitPlayer()
{
	if (InitTimeHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(InitTimeHandle);
	}

	if (AMobyGameState* GameState = MethodUnit::GetGameState(GetWorld()))
	{
		FString NumberString;
		FFileHelper::LoadFileToString(NumberString, *(FPaths::ProjectDir() / TEXT("CharacterID.txt")));

		int32 CharacterID = FCString::Atoi(*NumberString);
		if (const FCharacterTable* InTable = GameState->GetCharacterTableTemplate(CharacterID))
		{
			DefaultPawnClass = InTable->CharacterClass;
		}

		if (DefaultPawnClass)
		{
			MobyGameCharacter = GetWorld()->SpawnActor<AMobyGameCharacter>(DefaultPawnClass, GetActorLocation(), GetActorRotation());
			if (MobyGameCharacter)
			{
				int64 InPlayerID = GetPlayerID();
				if (InPlayerID != INDEX_NONE)
				{
					MobyGameCharacter->RegisterCharacter(InPlayerID, CharacterID);
					MobyGameCharacter->SetTeam(GetPlayerData()->Team);
				}
			}
		}
	}
}

void AMobyPawn::BeginPlay()
{
	Super::BeginPlay();

	if (GetLocalRole() == ROLE_Authority) 
	{
		//InitPlayer();
		GetWorld()->GetTimerManager().SetTimer(InitTimeHandle, this, &AMobyPawn::InitPlayer, 0.5f);
	}
}

int64 AMobyPawn::GetPlayerID()
{
	return GetPlayerData()->PlayerID;
}

const UPlayerDataComponent* AMobyPawn::GetPlayerData()
{
	return GetPlayerState()->GetPlayerData();
}

AMobyGamePlayerState* AMobyPawn::GetPlayerState()
{
	
	return GetController()->GetPlayerState<AMobyGamePlayerState>();
}


// Called every frame
void AMobyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetLocalRole() == ROLE_AutonomousProxy) {
		if (CursorToWorld != nullptr)
		{
			if (APlayerController* PC = Cast<APlayerController>(GetController()))
			{
				FHitResult TraceHitResult;
				PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
				FVector CursorFV = TraceHitResult.ImpactNormal;
				FRotator CursorR = CursorFV.Rotation();
				CursorToWorld->SetWorldLocation(TraceHitResult.Location);
				CursorToWorld->SetWorldRotation(CursorR);
			}
		}
	}
	

}

// Called to bind functionality to input
void AMobyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMobyPawn::CharacterMoveToTargetAttackOnServer_Implementation(const FVector& DirectionLocation, const APawn* InPawn)
{
	if (MobyGameCharacter)
	{
		//UAIBlueprintHelperLibrary::SimpleMoveToLocation(MobyGameCharacter->GetController(), DirectionLocation);
		if (AMobyGameAIController* AGAIController = Cast<AMobyGameAIController>(MobyGameCharacter->GetController()))
		{
			AGAIController->SetTargetForce(Cast<AMobyGameCharacter>(const_cast<APawn*>(InPawn)));
		}
		
	}
}

//bool AMobyPawn::CharacterMoveToTargetAttackOnServer_Validate(const FVector& DirectionLocation, const APawn* InPawn)
//{
//	return InPawn != NULL && InPawn != MobyGameCharacter;
//}

void AMobyPawn::CharacterMoveToOnServer_Implementation(const FVector& DirectionLocation)
{
	if (MobyGameCharacter)
	{
		float const Distance = FVector::Dist(DirectionLocation, MobyGameCharacter->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if ((Distance > 120.0f))
		{
			//UAIBlueprintHelperLibrary::SimpleMoveToLocation(MobyGameCharacter->GetController(), DirectionLocation);
			if (AMobyGameAIController* AGAIController = Cast<AMobyGameAIController>(MobyGameCharacter->GetController()))
			{
				AGAIController->SimpleMoveToLocation(DirectionLocation);
			}
		}
	}
}

void AMobyPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (GetLocalRole() == ROLE_Authority)
	{
		if (MobyGameCharacter)
		{
			MobyGameCharacter->Destroy();
			MobyGameCharacter = NULL;
		}
	}
}