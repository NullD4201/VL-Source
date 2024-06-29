// Fill out your copyright notice in the Description page of Project Settings.


#include "CPanelHome.h"

#include "HomeUI.h"


void UCPanelHome::NativeConstruct()
{
	Super::NativeConstruct();

	ButtonHome = Cast<UButton>(GetWidgetFromName("Home"));
	ButtonLibrary = Cast<UButton>(GetWidgetFromName("Library"));
	ButtonContents = Cast<UButton>(GetWidgetFromName("Contents"));
	ButtonBrowse = Cast<UButton>(GetWidgetFromName("BrowseButton"));

	ButtonPrev = Cast<UButton>(GetWidgetFromName("PrevButton"));
	ButtonLeft = Cast<UButton>(GetWidgetFromName("LeftButton"));
	ButtonRight = Cast<UButton>(GetWidgetFromName("RightButton"));
	ButtonNext = Cast<UButton>(GetWidgetFromName("NextButton"));

	PanelLibraryMyContents = Cast<UCanvasPanel>(GetWidgetFromName("MyContentsLibraryPanel"));

	ButtonHome->OnClicked.AddDynamic(this, &UCPanelHome::SetViewToHome);
	ButtonLibrary->OnClicked.AddDynamic(this, &UCPanelHome::SetViewToLibrary);
	ButtonContents->OnClicked.AddDynamic(this, &UCPanelHome::SetViewToContents);
	ButtonBrowse->OnClicked.AddDynamic(this, &UCPanelHome::SetViewToBrowse);
}

void UCPanelHome::PrevClick()
{
}

void UCPanelHome::LeftClick()
{
}

void UCPanelHome::RightClick()
{
}

void UCPanelHome::NextClick()
{
}

void UCPanelHome::SetViewToHome()
{
	UWidgetSwitcher* ParentWidget = Cast<UWidgetSwitcher>(GetParent());
	if (ParentWidget)
	{
		ParentWidget->SetActiveWidgetIndex(0);
	}
}

void UCPanelHome::SetViewToLibrary()
{
	UWidgetSwitcher* ParentWidget = Cast<UWidgetSwitcher>(GetParent());
	if (ParentWidget)
	{
		ParentWidget->SetActiveWidgetIndex(1);
	}
}

void UCPanelHome::SetViewToContents()
{
	UWidgetSwitcher* ParentWidget = Cast<UWidgetSwitcher>(GetParent());
	if (ParentWidget)
	{
		ParentWidget->SetActiveWidgetIndex(3);
	}
}

void UCPanelHome::SetViewToBrowse()
{
	UWidgetSwitcher* ParentWidget = Cast<UWidgetSwitcher>(GetParent());
	if (ParentWidget)
	{
		ParentWidget->SetActiveWidgetIndex(4);
	}
}
