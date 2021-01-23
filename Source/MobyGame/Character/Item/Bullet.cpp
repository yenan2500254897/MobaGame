// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "../CharacterInstance/MobyGameCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "../AI/AIController/Core/MobyGameAIController.h"
#include "../../Common/NumericalCalculationUnit.h"

// Sets default values
ABullet::ABullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootBullet = CreateDefaultSubobject<USceneComponent>(TEXT("BulletRootBullet"));
	BoxDamage = CreateDefaultSubobject<UBoxComponent>(TEXT("BulletBoxDamage"));
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("BulletProjectileMovement"));

	RootComponent = RootBullet;
	BoxDamage->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ProjectileMovement->MaxSpeed = 2000.f;
	ProjectileMovement->InitialSpeed = 1600.f;
	ProjectileMovement->ProjectileGravityScale = 0.f;
	ProjectileMovement->UpdatedComponent = BoxDamage;

	InitialLifeSpan = 4.0f;

	bCheck = false;
	SetReplicates(true);

}

void ABullet::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AMobyGameCharacter* InstigatorCharacter = Cast<AMobyGameCharacter>(GetInstigator()))
	{
		if (AMobyGameCharacter* TargetCharacter = Cast<AMobyGameCharacter>(OtherActor))
		{
			if (InstigatorCharacter != TargetCharacter)
			{
				if (1)
				{
					if (GetWorld()->IsServer())
					{
						if (bCheck)
						{
							if (AMobyGameAIController* InstigCharacterController = Cast<AMobyGameAIController>(InstigatorCharacter->GetController()))
							{
								if (InstigCharacterController->GetTarget() != TargetCharacter)
								{
									return;
								}
							}
						}

						float DamageValue = NumericalCalculationUnit::GetDamage(TargetCharacter, InstigatorCharacter);
						GEngine->AddOnScreenDebugMessage(-1, 0.5, FColor::Black, FString::Printf(TEXT("take damage value:%f"), DamageValue));
						UGameplayStatics::ApplyDamage(
							TargetCharacter,
							DamageValue,
							InstigatorCharacter->GetController(),
							InstigatorCharacter,
							UDamageType::StaticClass());
					}

					Destroy();
				}
			}
		}
	}
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	BoxDamage->OnComponentBeginOverlap.AddUniqueDynamic(this, &ABullet::BeginOverlap);
	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

