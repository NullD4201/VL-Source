// Fill out your copyright notice in the Description page of Project Settings.


#include "HostUI.h"
#include "Runtime/Engine/Classes/Engine/UserInterfaceSettings.h"
#include "Runtime/Engine/Classes/Engine/RendererSettings.h"
#include <Blueprint/WidgetLayoutLibrary.h>
#include <Components/CanvasPanelSlot.h>

void UHostUI::NativeConstruct() {
	Super::NativeConstruct();

	selectionImg = Cast<UImage>(GetWidgetFromName(TEXT("pbSelectionImg")));
	if (!selectionImg) {
		UE_LOG(LogTemp, Error, TEXT("Can't find \"pbSelectionImg\" UImage Widget"));
	}
}

void UHostUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);

	switch (CurrentState)
	{
	case HostUIState::HOST_PLAIN:
		break;
	case HostUIState::HOST_GENERATEOBJ:
		OnGenerateObjectMode();
		break;
	default:
		break;
	}
}

void UHostUI::SetHostState(HostUIState newState) {
	CurrentState = newState;
}

void UHostUI::GetMouseToWidgetOffset(float& offsetLeft, float& offsetTop, float& offsetRight, float& offsetBottom) {
	float mouseX, mouseY;
	GetOwningPlayer()->GetMousePosition(mouseX, mouseY);

	const FVector2D viewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	const float viewportScale = GetDefault<UUserInterfaceSettings>(UUserInterfaceSettings::StaticClass())->GetDPIScaleBasedOnSize(FIntPoint(viewportSize.X, viewportSize.Y));

	offsetLeft = mouseX / viewportScale;
	offsetTop = mouseY / viewportScale;
	offsetRight = (viewportSize.X - mouseX) / viewportScale;
	offsetBottom = (viewportSize.Y - mouseY) / viewportScale;
}

void UHostUI::StartObjGeneration() {
	if (selectionImg) {
		SetHostState(HostUIState::HOST_GENERATEOBJ);
		GetOwningPlayer()->GetLocalPlayer()->ViewportClient->GetMousePosition(dragStartPos);

		selectionImg->SetVisibility(ESlateVisibility::Visible);
		UCanvasPanelSlot* slot = UWidgetLayoutLibrary::SlotAsCanvasSlot(selectionImg);
		if (slot) {

			float offsetLeft, offsetTop, offsetRight, offsetBottom;
			GetMouseToWidgetOffset(offsetLeft, offsetTop, offsetRight, offsetBottom);
			slot->SetOffsets(FMargin(offsetLeft, 0.0f, 0.0f, offsetBottom));
		}
	}
}

void UHostUI::EndObjGeneration() {
	if (selectionImg) {
		SetHostState(HostUIState::HOST_PLAIN);
		GetOwningPlayer()->GetLocalPlayer()->ViewportClient->GetMousePosition(dragEndPos);

		selectionImg->SetVisibility(ESlateVisibility::Hidden);

		FVector2D meanDragScreenPos = FVector2D((double)(dragEndPos.X + dragStartPos.X) / 2.0, (double)(dragEndPos.Y + dragStartPos.Y) / 2.0);
		FVector worldPosition, worldDirection;
		GetOwningPlayer()->DeprojectScreenPositionToWorld(meanDragScreenPos.X, meanDragScreenPos.Y, worldPosition, worldDirection);

		FRotator rotator = worldDirection.Rotation();
		UE_LOG(LogTemp, Warning, TEXT("%f"), (dragEndPos.X - dragStartPos.X) / (dragEndPos.Y - dragStartPos.Y));
		FTransform transform = FTransform(rotator, worldPosition + worldDirection * OBJ_GENERATING_DISTANCE, FVector((dragEndPos.X - dragStartPos.X) / (dragEndPos.Y - dragStartPos.Y), 1.0, 1.0));
		GetOwningPlayer()->GetWorld()->SpawnActor<AActor>(spawningActorClass, transform);
	}
}

void UHostUI::OnGenerateObjectMode() {
	if (selectionImg) {
		UCanvasPanelSlot* slot = UWidgetLayoutLibrary::SlotAsCanvasSlot(selectionImg);
		if (slot) {
			float _, offsetTop, offsetRight;
			GetMouseToWidgetOffset(_, offsetTop, offsetRight, _);
			FMargin margin = FMargin(slot->GetOffsets().Left,
				offsetTop,
				offsetRight,
				slot->GetOffsets().Bottom);
			slot->SetOffsets(margin);

		}
	}
}