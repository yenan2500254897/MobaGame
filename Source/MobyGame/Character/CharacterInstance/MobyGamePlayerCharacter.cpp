// Fill out your copyright notice in the Description page of Project Settings.


#include "MobyGamePlayerCharacter.h"
#include "../../Common/MethodUnit.h"
#include "../../Table/CharacterTable.h"
#include "../../MobyPawn.h"
#include "../../MobyGamePlayerState.h"
#include "../../UI/Game/Character/UI_InformationBar.h"
#include "Components/WidgetComponent.h"

UAnimMontage* AMobyGamePlayerCharacter::GetCurrentSkillMontage(ESkillKeyType SkillKey)
{
	int32 CharacterID = MethodUnit::GetCharacterID(GetWorld(), GetPlayerID());
	if (CharacterID != INDEX_NONE)
	{
		if (const FCharacterTable* CharacterTable = MethodUnit::GetCharacterTable(GetWorld(), CharacterID))
		{
			switch (SkillKey)
			{
			case ESkillKeyType::KEY_Q:return CharacterTable->QSkillAttack;
			case ESkillKeyType::KEY_W:return CharacterTable->WSkillAttack;
			case ESkillKeyType::KEY_E:return CharacterTable->ESkillAttack;
			case ESkillKeyType::KEY_R:return CharacterTable->RSkillAttack;
			}
		}
	}

	return NULL;
}

void AMobyGamePlayerCharacter::InitCharacter()
{
	Super::InitCharacter();

	//if (AMobyGameState* InState = MethodUnit::GetGameState(GetWorld()))
	//{
	//	if (FCharacterAttribute* Data = InState->GetCharacterAttribute(GetPlayerID()))
	//	{
	//		MethodUnit::ServerCallAllPlayer<AMobyPawn>(GetWorld(), [&](AMobyPawn* InPawn)->MethodUnit::EServerCallType
	//		{
	//			if (InPawn->GetPlayerID() == GetPlayerID())
	//			{
	//				if (AMobyGamePlayerState* InPlayerState = InPawn->GetController()->GetPlayerState<AMobyGamePlayerState>())
	//				{
	//					//MultCastWidgetInfo_PlayerName(InPlayerState->GetPlayerData()->PlayerName.ToString());
	//				}

	//				return MethodUnit::EServerCallType::PROGRESS_COMPLETE;
	//			}

	//			return MethodUnit::EServerCallType::INPROGRESS;
	//		});

	//		//MultCastWidgetInfo_Lv(Data->Lv);
	//	}
	//}
}

void AMobyGamePlayerCharacter::SkillAttack(ESkillKeyType SkillKey, TWeakObjectPtr<AMobyGameCharacter> InTarget)
{
	int32 CharacterID = MethodUnit::GetCharacterID(GetWorld(), GetPlayerID());
	if (CharacterID != INDEX_NONE)
	{
		if (const FCharacterTable* CharacterTable = MethodUnit::GetCharacterTable(GetWorld(), CharacterID))
		{
			if (UAnimMontage* MontageInstance = GetCurrentSkillMontage(SkillKey))
			{

				MultCastPlayerAnimMontage(MontageInstance);
			}
		}
	}
}