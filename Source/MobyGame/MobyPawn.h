// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MobyGameType.h"
#include "MobyPawn.generated.h"

class AMobyGamePlayerCharacter;
class UPlayerDataComponent;
class AMobyGamePlayerState;
UCLASS()
class MOBYGAME_API AMobyPawn : public APawn
{
	GENERATED_BODY()
public:
	//ΪMobyPawn���ÿ��ƽ�ɫ,ʵ��������ƶ�ʱ�����ǲ�Ӱ���ɫ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Classes)
	TSubclassOf<APawn> DefaultPawnClass;
public:
	void SkillAttack(ESkillKeyType SkillType, TWeakObjectPtr<AMobyGamePlayerCharacter> InTarget);

public:
	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UDecalComponent* CursorToWorld;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* RootBox;

public:
	UFUNCTION(server,reliable)
		void CharacterMoveToOnServer(const FVector &DirectionLocation);

	UFUNCTION(server, reliable/*, WithValidation*/)
		void CharacterMoveToTargetAttackOnServer(const FVector& DirectionLocation, const APawn *InPawn);

public:
	// Sets default values for this pawn's properties
	AMobyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called when the game end
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void InitPlayer();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE AMobyGamePlayerCharacter* GetControllerCharacter() { return MobyGameCharacter; }

public:
	int64 GetPlayerID();

	const UPlayerDataComponent* GetPlayerData();

	AMobyGamePlayerState* GetPlayerState();

protected:
	UPROPERTY()
		AMobyGamePlayerCharacter* MobyGameCharacter;

private:
	FTimerHandle InitTimeHandle;

};
