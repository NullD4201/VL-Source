// Fill out your copyright notice in the Description page of Project Settings.


#include "SlideShowWidget.h"	

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "VClass/Actor/ScreenActor.h"

void USlideShowWidget::NativeConstruct()
{
	Super::NativeConstruct();

	TestButton = Cast<UButton>(GetWidgetFromName("Test"));
	if (TestButton)
	{
		TestButton->OnClicked.AddDynamic(this, &USlideShowWidget::OnTestButtonClick);
	}
	TestButton2 = Cast<UButton>(GetWidgetFromName("Test2"));
	if (TestButton2)
	{
		TestButton2->OnClicked.AddDynamic(this, &USlideShowWidget::OnTestButtonClick2);
	}

	ScreenActor1 = UGameplayStatics::GetActorOfClass(GetWorld(), AScreenActor::StaticClass());

	DraggedImage = nullptr;
	bIsDragging = false;
}

void USlideShowWidget::OnTestButtonClick()
{
	if (ScreenActor1)
	{
		AScreenActor* ScreenActor = Cast<AScreenActor>(ScreenActor1);
		if (ScreenActor)
		{
			ScreenActor->StartSlideTransition();
		}
	}
}

void USlideShowWidget::OnTestButtonClick2()
{
	if (ScreenActor1)
	{
		AScreenActor* ScreenActor = Cast<AScreenActor>(ScreenActor1);
		if (ScreenActor)
		{
			ScreenActor->StartSlideTransitionReverse();
		}
	}
}

FVector2D GetImageSlotIndex(UUniformGridPanel* UniformGridPanel, UImage* Image)
{
	int IndexX = 0, IndexY = 0;
	for (UWidget* WidgetComponent : UniformGridPanel->GetAllChildren())
	{
		UImage* ImageComponent = Cast<UImage>(WidgetComponent);

		if (ImageComponent->GetName() == Image->GetName())
		{
			IndexX = Cast<UUniformGridSlot>(WidgetComponent->Slot)->GetRow();
			IndexY = Cast<UUniformGridSlot>(WidgetComponent->Slot)->GetColumn();
		}
	}
	return FVector2D(IndexX, IndexY);
}

FReply USlideShowWidget::NativeOnMouseButtonDown(const FGeometry& Geometry, const FPointerEvent& MouseEvent)
{
    if (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
    {
        if (TestSlide1 && Geometry.IsUnderLocation(MouseEvent.GetScreenSpacePosition()))
        {
            bIsDragging = true;

            DraggedImage = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass(), TEXT("DraggedImage"));
            DraggedImage->SetBrush(TestSlide1->Brush);
            DraggedImage->SetRenderOpacity(0.5f);

            if (RootCanvasPanel)
            {
                RootCanvasPanel->AddChild(DraggedImage);
                UCanvasPanelSlot* DraggedImageSlot = Cast<UCanvasPanelSlot>(DraggedImage->Slot);
                if (DraggedImageSlot)
                {
                	DragOffset = Geometry.AbsoluteToLocal(MouseEvent.GetScreenSpacePosition()) - DraggedImageSlot->GetPosition();

                	UUniformGridPanel* GridPanel = Cast<UUniformGridPanel>(TestSlide1->GetParent());
                	if (GridPanel)
                	{
                		UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(GridPanel->Slot);
                		if (CanvasSlot)
                		{
                			int PosX = CanvasSlot->GetPosition().X + 30 * (GetImageSlotIndex(GridPanel, TestSlide1).Y);
                			int PosY = CanvasSlot->GetPosition().Y + 45 * (GetImageSlotIndex(GridPanel, TestSlide1).X);
                			DraggedImageSlot->SetPosition(FVector2D(PosX, PosY));

                			double SizeX = (CanvasSlot->GetSize().X - 90) / 3;
                			double SizeY = (CanvasSlot->GetSize().Y - 135) / 3;
                			DraggedImageSlot->SetSize(FVector2D(SizeX, SizeY));
                		}
                	}
                }
            }

            TestSlide1->SetRenderOpacity(0.5f);

            FEventReply Reply;
            return UWidgetBlueprintLibrary::CaptureMouse(Reply, this).NativeReply;
        }
    }
	return Super::NativeOnMouseButtonDown(Geometry, MouseEvent);
}

FReply USlideShowWidget::NativeOnMouseMove(const FGeometry& Geometry, const FPointerEvent& MouseEvent)
{
	if (bIsDragging && DraggedImage)
	{
		FVector2D NewPosition = Geometry.AbsoluteToLocal(MouseEvent.GetScreenSpacePosition()) - DragOffset;
		UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(DraggedImage->Slot);
		if (CanvasSlot)
		{
			CanvasSlot->SetPosition(NewPosition);
		}
		return FReply::Handled();
	}
	return Super::NativeOnMouseMove(Geometry, MouseEvent);
}

FReply USlideShowWidget::NativeOnMouseButtonUp(const FGeometry& Geometry, const FPointerEvent& MouseEvent)
{
	if (bIsDragging)
	{
		bIsDragging = false;
		if (DraggedImage)
		{
			DraggedImage->SetRenderOpacity(1.0f);
			TestSlide1->SetRenderOpacity(0.5f);
			DraggedImage = nullptr;
		}
		
		FEventReply Reply;
		return UWidgetBlueprintLibrary::ReleaseMouseCapture(Reply).NativeReply;
	}
	return Super::NativeOnMouseButtonUp(Geometry, MouseEvent);
}