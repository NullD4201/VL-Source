// Fill out your copyright notice in the Description page of Project Settings.


#include "SlideShowWidget.h"	

void USlideShowWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (bIsDragging)
	{
		if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
		{
			float MouseX, MouseY;
			PlayerController->GetMousePosition(MouseX, MouseY);

			FVector2D ScreenPosition(MouseX, MouseY);
			FVector2D WidgetPosition = MyGeometry.AbsoluteToLocal(ScreenPosition);

			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, WidgetPosition.ToString());

			if (_ImageSlideTemp)
			{
				_ImageSlideTemp->SetRenderTranslation(WidgetPosition);
			}
		}
	}
}

void USlideShowWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ButtonTestSlide1)
	{
		ButtonTestSlide1->OnPressed.AddDynamic(this, &USlideShowWidget::OnButtonPressed);
		ButtonTestSlide1->OnReleased.AddDynamic(this, &USlideShowWidget::OnButtonReleased);
	}

	bIsDragging = false;

	// 입력 매핑 설정
	if (UWorld* World = GetWorld())
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			PlayerController->InputComponent->BindAction("MouseLeftClick", IE_Released, this, &USlideShowWidget::OnMouseLeftClick);
		}
	}
}

void USlideShowWidget::OnButtonPressed()
{
	bIsDragging = true;
}

void USlideShowWidget::OnButtonReleased()
{
	bIsDragging = false;
}

void USlideShowWidget::OnMouseLeftClick()
{
	bIsDragging = false;
}
