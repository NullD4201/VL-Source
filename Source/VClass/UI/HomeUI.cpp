// Fill out your copyright notice in the Description page of Project Settings.


#include "HomeUI.h"

#include "MyContentWidget.h"
#include "Components/CanvasPanelSlot.h"

void UHomeUI::NativeConstruct()
{
	Super::NativeConstruct();

	ButtonHome = Cast<UButton>(GetWidgetFromName("Home"));
	ButtonLibrary = Cast<UButton>(GetWidgetFromName("Library"));
	ButtonContents = Cast<UButton>(GetWidgetFromName("Contents"));
	ButtonSettings = Cast<UButton>(GetWidgetFromName("Settings"));

	PanelHome = Cast<UCanvasPanel>(GetWidgetFromName("HomePanel"));
	PanelLibrary = Cast<UCanvasPanel>(GetWidgetFromName("LibraryPanel"));
}

void UHomeUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UHomeUI::SetViewToHome()
{
}

void UHomeUI::SetViewToLibrary()
{
}

void UHomeUI::SetViewToContents()
{
}

void UHomeUI::SetViewToSettings()
{
}
