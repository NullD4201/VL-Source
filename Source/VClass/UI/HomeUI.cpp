// Fill out your copyright notice in the Description page of Project Settings.


#include "HomeUI.h"

#include "MyContentWidget.h"
#include "Components/CanvasPanelSlot.h"

void UHomeUI::NativeConstruct()
{
	Super::NativeConstruct();

	PanelHome = Cast<UCanvasPanel>(GetWidgetFromName("HomePanel"));
	PanelLibrary = Cast<UCanvasPanel>(GetWidgetFromName("LibraryPanel"));
	PanelContents = Cast<UCanvasPanel>(GetWidgetFromName("MyContentsLibraryPanel"));

	WidgetSwitcherMain = Cast<UWidgetSwitcher>(GetWidgetFromName("MainWidgetSwitcher"));

	ButtonWindowMin = Cast<UButton>(GetWidgetFromName("WindowMin"));
	ButtonWindowMax = Cast<UButton>(GetWidgetFromName("WindowMax"));
	ButtonWindowClose = Cast<UButton>(GetWidgetFromName("Close"));


	ButtonWindowMin->OnClicked.AddDynamic(this, &UHomeUI::MinimizeWindow);
	ButtonWindowMax->OnClicked.AddDynamic(this, &UHomeUI::MaximizeWindow);
	ButtonWindowClose->OnClicked.AddDynamic(this, &UHomeUI::CloseWindow);
}

void UHomeUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UHomeUI::MinimizeWindow()
{
}

void UHomeUI::MaximizeWindow()
{
}

void UHomeUI::CloseWindow()
{
	
}
