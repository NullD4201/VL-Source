// Fill out your copyright notice in the Description page of Project Settings.


#include "SlideShowWidget.h"

#include "Components/Button.h"
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
