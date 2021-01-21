// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaGameHUD.h"
#include "UI/Game/UI_MainScreen.h"

AMobaGameHUD::AMobaGameHUD()
{
	static ConstructorHelpers::FClassFinder<UUI_MainScreen> HallMain_BPClass(TEXT("/Game/UI/UI_MainScreen_BP"));
	MainScreenClass = HallMain_BPClass.Class;

	static ConstructorHelpers::FObjectFinder<UDataTable> GlobalClientConfiguration_Table(TEXT("/Game/Table/GlobalClientConfiguration"));
	GlobalClientConfigurationPtr = GlobalClientConfiguration_Table.Object;
}

const FGlobalClientConfiguration& AMobaGameHUD::GetGlobalClientConfig()
{
	return GlobalClientConfiguration;
}

void AMobaGameHUD::BeginPlay()
{
	Super::BeginPlay();

	if (MainScreenClass)
	{
		MainScreen = CreateWidget<UUI_MainScreen>(GetWorld(), MainScreenClass);
		MainScreen->AddToPlayerScreen(2);
	}

	if (GlobalClientConfigurationPtr)
	{
		TArray<FGlobalClientConfiguration*> GlobalClientConfigurations;
		GlobalClientConfigurationPtr->GetAllRows(TEXT("Global Client Configuration"), GlobalClientConfigurations);

		if (GlobalClientConfigurations.Num())
		{
			GlobalClientConfiguration = *GlobalClientConfigurations[0];
		}
	}
}

