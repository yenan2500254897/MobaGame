// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaPawn.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Engine/Engine.h"
#include "MobaGameState.h"
#include "Common/MethodUnit.h"
#include "Character/CharacterInstance/MobaGameCharacter.h"


// Sets default values
AMobaPawn::AMobaPawn()
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

// Called when the game starts or when spawned
void AMobaPawn::BeginPlay()
{
	Super::BeginPlay();

	if (GetLocalRole() == ROLE_Authority)
	{
		if (AMobaGameState* GameState = MethodUnit::GetGameState(GetWorld()))
		{
			FString NumberString;
			FFileHelper::LoadFileToString(NumberString, *(FPaths::ProjectDir() / TEXT("CharacterID.txt")));

			int32 CharacterID = FCString::Atoi64(*NumberString);
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString::Printf(TEXT("id:=%d", CharacterID)));
			if (const FCharacterTable* InTable = GameState->GetCharacterTable(CharacterID))
			{
				DefaultPawnClass = InTable->CharacterClass;
			}

			if (DefaultPawnClass)
			{
				MobaGameCharacter = GetWorld()->SpawnActor<AMobaGameCharacter>(DefaultPawnClass, GetActorLocation(), GetActorRotation());
				if (MobaGameCharacter)
				{
					MobaGameCharacter->InitCharacterID(CharacterID);
				}
			}
		}
	}
	
}

void AMobaPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (GetLocalRole() == ROLE_Authority)
	{
		if (MobaGameCharacter)
		{
			MobaGameCharacter->Destroy();
			MobaGameCharacter = NULL;
		}
	}
}

// Called every frame
void AMobaPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*FString NumberString;
	FFileHelper::LoadFileToString(NumberString, *(FPaths::ProjectDir() / TEXT("CharacterID.txt")));
	int32 CharacterID = FCString::Atoi64(*NumberString);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("CharacterID:=%d"), CharacterID));*/

	if (GetLocalRole() == ROLE_AutonomousProxy)
	{
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
void AMobaPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMobaPawn::CharacterMoveToOnServer_Implementation(const FVector& DirectionLocation)
{
	if (MobaGameCharacter)
	{
		float const Distance = FVector::Dist(DirectionLocation, MobaGameCharacter->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if ((Distance > 120.0f))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(MobaGameCharacter->GetController(), DirectionLocation);
		}
	}
}
