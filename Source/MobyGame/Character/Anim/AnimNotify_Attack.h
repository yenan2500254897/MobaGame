// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_Attack.generated.h"

/**
 * 
 */
class ABullet;
UCLASS()
class MOBYGAME_API UAnimNotify_Attack : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	UAnimNotify_Attack();

	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify", meta = (ExposeOnSpawn = true))
		TSubclassOf<ABullet> BulletClass;

	//Èç¹ûÖ»¹¥»÷Ä¿±ê ÄÇÃ´¾Í¿ªÆôËü Èç¹ûÏ£Íû·¶Î§ÄÚµÐÈË¶¼ÊÜµ½ÉËº¦¾Í±£³ÖÄ¬ÈÏ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify", meta = (ExposeOnSpawn = true))
		bool bCheck;

	//×Óµ¯´æÔÚµÄÉúÃüÖÜÆÚ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify", meta = (ExposeOnSpawn = true))
		float LiftTime;

	//#if WITH_EDITOR
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify", meta = (ExposeOnSpawn = true))
		FName InSocketName;
	//#endif
};
