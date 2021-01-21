// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_MiniMap.h"
#include "MobaGame/MobaGameState.h"
#include "../../../Common/RenderingUtils.h"
#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/CanvasPanel.h"
#include "Engine/SceneCapture2D.h"

void UUI_MiniMap::NativeConstruct()
{
	Super::NativeConstruct();

	if (ASceneCapture2D* SceneCapture2D = RenderingUtils::SpawnSceneCapture2D(GetWorld(), CaptureClass, MapSize, 0.03f))
	{
		MiniMapImage->SetBrushFromMaterial(Cast<UMaterialInterface>(MiniMapMat.GetObject()));
	}

	if (MiniMapImage)
	{
		if (UCanvasPanelSlot* ImagePanelSlot = Cast<UCanvasPanelSlot>(MiniMapImage->Slot))
		{
			ImagePanelSlot->SetSize(FVector2D(GetHUD()->GetGlobalClientConfig().MaxMiniMapSize));
		}
	}
}

void UUI_MiniMap::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (AMobaGameState* InState = GetWorld()->GetGameState<AMobaGameState>())
	{
		const TArray<FPlayerLocation>& Locations = InState->GetPlayerLocations();

		if (UCanvasPanelSlot* ImagePanelSlot = Cast<UCanvasPanelSlot>(MiniMapImage->Slot))
		{
			const float MaxMiniMapSize = GetHUD()->GetGlobalClientConfig().MaxMiniMapSize;
			const float MaxTargetArmLength = GetHUD()->GetGlobalClientConfig().MaxTargetArmLength;

			FVector2D LocalSize2D = MyGeometry.GetDrawSize();

			FVector2D ZoomSize;
			{
				float TargetArmLength = 800.f;//Cast<ATowerDefenceGameCamera>(GetWorld()->GetFirstPlayerController()->GetPawn())->GetTargetArmLength();
				ZoomSize = FVector2D((MaxMiniMapSize / MaxTargetArmLength) * TargetArmLength);

				ImagePanelSlot->SetSize(ZoomSize);
			}

			FVector2D MinImageMapOffset;
			{
				//先将小地图固定在右下角
				FVector Location = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
				/*MinImageMapOffset.Y = -(ZoomSize.X - (ZoomSize.X / MapSize.X) * Location.X);
				MinImageMapOffset.X = -(ZoomSize.Y / MapSize.Y) * Location.Y;*/
				MinImageMapOffset.Y = -20;
				MinImageMapOffset.X = -20;

				ImagePanelSlot->SetPosition(MinImageMapOffset);
			}

			for (auto& Tmp : Locations)
			{
				if (!IsExistence(Tmp.PlayerID))
				{
					if (UImage* Point = NewObject<UImage>(GetWorld(), UImage::StaticClass()))
					{
						if (UCanvasPanelSlot* PanelSlot = MiniMap->AddChildToCanvas(Point))
						{
							PanelSlot->SetZOrder(1.0f);
							PanelSlot->SetAnchors(0.5f);
							//Point->SetBrushFromTexture(Tmp.Value.Icon.LoadSynchronous());
							PanelSlot->SetSize(FVector2D(32.f));
							PanelSlot->SetAlignment(FVector2D(.5f));
							CharacterIcons.Add(Tmp.PlayerID, PanelSlot);
						}
					}
				}
				else
				{
					if (UCanvasPanelSlot* PanelSlot = CharacterIcons[Tmp.PlayerID].Get())
					{
						FVector2D MinMapPos;
						MinMapPos.Y = ZoomSize.X - (ZoomSize.X / MapSize.X) * Tmp.Location.X + MinImageMapOffset.Y;
						MinMapPos.X = (ZoomSize.Y / MapSize.Y) * Tmp.Location.Y + MinImageMapOffset.X;

						ResetLocation(PanelSlot, MinMapPos, LocalSize2D);
					}
				}

			}

			TArray<int64> RemoveGuid;
			for (auto& Tmp : CharacterIcons)
			{
				bool bContains = false;
				for (auto& L : Locations)
				{
					if (L.PlayerID == Tmp.Key)
					{
						bContains = true;
						break;
					}
				}

				if (!bContains)
				{
					if (UCanvasPanelSlot* PanelSlot = CharacterIcons[Tmp.Key].Get())
					{
						MiniMap->RemoveChild(PanelSlot->Content);
						RemoveGuid.Add(Tmp.Key);
					}
				}
			}

			for (auto& Tmp : RemoveGuid)
			{
				CharacterIcons.Remove(Tmp);
			}
		}

	}
}

bool UUI_MiniMap::IsExistence(const int64 InID)
{
	for (auto& Tmp : CharacterIcons)
	{
		if (Tmp.Key == InID)
		{
			return true;
		}
	}

	return false;
}

void UUI_MiniMap::ResetLocation(UCanvasPanelSlot* PanelSlot, const FVector2D& MinMapPos, const FVector2D& LocalSize2D)
{
	FVector2D IconSize = PanelSlot->GetSize() / 2;

	auto IsRange = [&](const float& CompareValue, const float& Value)->bool
	{
		return Value > -CompareValue && Value < CompareValue;
	};

	FVector2D NewPos = MinMapPos;
	if (MinMapPos.X <= LocalSize2D.X &&
		MinMapPos.Y <= LocalSize2D.Y &&
		MinMapPos.X >= -LocalSize2D.X &&
		MinMapPos.Y >= -LocalSize2D.Y)
	{

	}
	else if (MinMapPos.Y < -LocalSize2D.Y && IsRange(LocalSize2D.X, MinMapPos.X))
	{
		NewPos = FVector2D(MinMapPos.X, -LocalSize2D.Y + IconSize.Y);
	}
	else if (MinMapPos.X < -LocalSize2D.X && IsRange(LocalSize2D.Y, MinMapPos.Y))
	{
		NewPos = FVector2D(-LocalSize2D.X + IconSize.Y, MinMapPos.Y);
	}
	else if (MinMapPos.Y > LocalSize2D.Y && IsRange(LocalSize2D.X, MinMapPos.X))
	{
		NewPos = FVector2D(MinMapPos.X, LocalSize2D.Y - IconSize.Y);
	}
	else if (MinMapPos.X > LocalSize2D.X && IsRange(LocalSize2D.Y, MinMapPos.Y))
	{
		NewPos = FVector2D(LocalSize2D.X - IconSize.X, MinMapPos.Y);
	}
	else if (MinMapPos.X < -LocalSize2D.X && MinMapPos.Y < -LocalSize2D.Y)
	{
		NewPos = -LocalSize2D + IconSize;
	}
	else if (MinMapPos.X < -LocalSize2D.X && MinMapPos.Y > LocalSize2D.Y)
	{
		NewPos = FVector2D(-LocalSize2D.X + IconSize.X, LocalSize2D.Y - IconSize.Y);
	}
	else if (MinMapPos.X > LocalSize2D.X && MinMapPos.Y > LocalSize2D.Y)
	{
		NewPos = LocalSize2D - IconSize;
	}
	else if (MinMapPos.X > LocalSize2D.X && MinMapPos.Y < -LocalSize2D.Y)
	{
		NewPos = FVector2D(LocalSize2D.X - IconSize.X, -LocalSize2D.Y + IconSize.Y);
	}

	PanelSlot->SetPosition(NewPos);
}
