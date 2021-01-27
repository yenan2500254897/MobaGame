// Copyright Epic Games, Inc. All Rights Reserved.
#include "MobyGameCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
//#include "GameFramework/SpringArmComponent.h"
#include "Engine/World.h"
#include "Components/CapsuleComponent.h"
#include "../../Common/MethodUnit.h"
#include "Components/WidgetComponent.h"
#include "../../UI/Game/Character/UI_InformationBar.h"
#include "Components/ArrowComponent.h"

AMobyGameCharacter::AMobyGameCharacter()
	:bAttacking(false)
	,AttackCount(0)
	,PlayerID(INDEX_NONE)
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	OpenFriePoint = CreateDefaultSubobject<UArrowComponent>(TEXT("OpenFilePoint"));
	Widget->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	OpenFriePoint->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AMobyGameCharacter::NormalAttack(TWeakObjectPtr<AMobyGameCharacter> InTarget)
{
	if (InTarget.IsValid())
	{
		int32 CharacterID = MethodUnit::GetCharacterID(GetWorld(), PlayerID);
		if (CharacterID != INDEX_NONE)
		{
			if (const FCharacterTable* CharacterTable = MethodUnit::GetCharacterTable(GetWorld(), CharacterID))
			{
				if (AttackCount < CharacterTable->NormalAttack.Num())
				{
					if (UAnimMontage* MontageInstance = CharacterTable->NormalAttack[AttackCount])
					{
						if (AttackCount == CharacterTable->NormalAttack.Num() - 1)
						{
							AttackCount = 0;
						}
						else
						{
							AttackCount++;
						}

						//���Ŷ���
						MultCastPlayerAnimMontage(MontageInstance);
					}
				}
			}
		}
	}
}

void AMobyGameCharacter::MultCastWidgetInfo_Implementation(float InHPPercentage, float InManaPercentage)
{
	if (GetLocalRole() != ROLE_Authority)
	{
		if (UUI_InformationBar* InformationBar = Cast<UUI_InformationBar>(Widget->GetUserWidgetObject()))
		{
			InformationBar->SetHealth(InHPPercentage);
			InformationBar->SetMana(InManaPercentage);
		}
		else if (UUI_HealthBar* InHealthBar = Cast<UUI_HealthBar>(Widget->GetUserWidgetObject()))
		{
			InHealthBar->SetHealth(InHPPercentage);
		}
	}
}

void AMobyGameCharacter::MultCastPlayerAnimMontage_Implementation(UAnimMontage* InMontage, float InPlayRate, FName StartSectionName)
{
	if (InMontage)
	{
		PlayAnimMontage(InMontage, InPlayRate, StartSectionName);
	}
}

void AMobyGameCharacter::MultCastReborn_Implementation()
{

	if (GetLocalRole() == ENetRole::ROLE_Authority)
	{
		GetCharacterAttribute()->Reset();

		MultCastWidgetInfo(
			GetCharacterAttribute()->GetHealthPercentage(),
			GetCharacterAttribute()->GetManaPercentage());
	}

	StopAnimMontage();
}

bool AMobyGameCharacter::IsDie()
{
	if (GetCharacterAttribute()->Health <= 0.f)
	{
		return true;
	}

	return false;
}

FCharacterAttribute* AMobyGameCharacter::GetCharacterAttribute()
{
	if (AMobyGameState* InState = MethodUnit::GetGameState(GetWorld()))
	{
		return InState->GetCharacterAttribute(PlayerID);
	}

	return NULL;
}

void AMobyGameCharacter::RegisterCharacter(const int64& InPlayerID, int32 CharacterID)
{
	PlayerID = InPlayerID;

	if (AMobyGameState* InState = MethodUnit::GetGameState(GetWorld()))
	{
		InState->AddCharacterData(PlayerID, CharacterID);
		InState->AddCharacterAILocation(PlayerID, GetActorLocation());

		GetWorld()->GetTimerManager().SetTimer(InitTimeHandle, this, &AMobyGameCharacter::InitCharacter, 0.1f);
	}
}

void AMobyGameCharacter::InitCharacter()
{
	if (InitTimeHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(InitTimeHandle);
	}

	if (AMobyGameState* InState = MethodUnit::GetGameState(GetWorld()))
	{
		if (FCharacterAttribute* Data = InState->GetCharacterAttribute(PlayerID))
		{
			GetCharacterMovement()->MaxWalkSpeed = Data->WalkSpeed;
			MultCastWidgetInfo(Data->GetHealthPercentage(), Data->GetManaPercentage());
		}
	}
}

void AMobyGameCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (GetLocalRole() == ROLE_Authority)
	{
		if (AMobyGameState* InState = MethodUnit::GetGameState(GetWorld()))
		{
			InState->UpdateCharacterAILocation(GetPlayerID(), GetActorLocation());
		}
	}
}

void AMobyGameCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (GetLocalRole() == ROLE_Authority)
	{
		SpawnDefaultController();
	}
}

float AMobyGameCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (GetLocalRole() == ROLE_Authority)//if (GetWord()->IsServer())
	{
		if (AMobyGameState* InState = MethodUnit::GetGameState(GetWorld()))
		{
			GetCharacterAttribute()->Health += Damage;

			MultCastWidgetInfo(
				GetCharacterAttribute()->GetHealthPercentage(),
				GetCharacterAttribute()->GetManaPercentage());
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "GameCharacter");

			if (IsDie())
			{
				int32 CharacterID = InState->GetCharacterID(PlayerID);
				if (const FCharacterTable* InTable = InState->GetCharacterTableTemplate(CharacterID))
				{
					int32 Index = FMath::RandRange(0, InTable->Death.Num() - 1);
					MultCastPlayerAnimMontage(InTable->Death[Index]);

					if (InitTimeHandle.IsValid())
					{
						GetWorld()->GetTimerManager().ClearTimer(InitTimeHandle);
					}

					GetWorld()->GetTimerManager().SetTimer(InitTimeHandle, this, &AMobyGameCharacter::MultCastReborn, 3.0f);
					//GThread::Get()->GetCoroutines().BindUObject(5.f, this, &AMobyGameCharacter::MultCastReborn);
				}
			}

		}
	}

	return 0;
}

void AMobyGameCharacter::SetTeam(ETeamType InTeamType)
{
	TeamType = InTeamType;
}

void AMobyGameCharacter::SetCharacterType(ECharacterType InCharacterType)
{
	CharacterType = InCharacterType;
}