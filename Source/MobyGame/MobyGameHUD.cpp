#include "MobyGameHUD.h"
#include "UI/Game/UI_MainScreen.h"
#include "Blueprint/UserWidget.h"

AMobyGameHUD::AMobyGameHUD()
{
	static ConstructorHelpers::FClassFinder<UUI_MainScreen> HallMain_BPClass(TEXT("/Game/UI/Game/MainScreen_BP"));
	MainScreenClass = HallMain_BPClass.Class;

	static ConstructorHelpers::FObjectFinder<UDataTable> GlobalClientConfiguration_Table(TEXT("/Game/Table/GlobalClientConfiguration"));
	GlobalClientConfigurationPtr = GlobalClientConfiguration_Table.Object;
}

void AMobyGameHUD::BeginPlay()
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

const FGlobalClientConfiguration& AMobyGameHUD::GetGlobalClientConfig()
{
	// TODO: insert return statement here
	return GlobalClientConfiguration;
}
