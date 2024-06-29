// Fill out your copyright notice in the Description page of Project Settings.


#include "CPanelContents.h"

#include "Components/WidgetSwitcher.h"


void UCPanelContents::NativeConstruct()
{
	Super::NativeConstruct();

	ButtonHome = Cast<UButton>(GetWidgetFromName("Home"));
	ButtonLibrary = Cast<UButton>(GetWidgetFromName("Library"));
	ButtonBrowse = Cast<UButton>(GetWidgetFromName("Browse"));

	ButtonOpenLiveContents = Cast<UButton>(GetWidgetFromName("OpenLiveContents"));
	ButtonMakerSpace = Cast<UButton>(GetWidgetFromName("MakerSpace"));

	WidgetLiveContents = Cast<UUserWidget>(GetWidgetFromName("LiveContentsPanel"));

	WidgetLiveContents->SetVisibility(ESlateVisibility::Hidden);
	WidgetLiveContents->SetIsEnabled(false);

	ButtonHome->OnClicked.AddDynamic(this, &UCPanelContents::SetViewToHome);
	ButtonLibrary->OnClicked.AddDynamic(this, &UCPanelContents::SetViewToLibrary);
	ButtonBrowse->OnClicked.AddDynamic(this, &UCPanelContents::SetViewToBrowse);

	ButtonOpenLiveContents->OnClicked.AddDynamic(this, &UCPanelContents::OpenLiveContents);
	ButtonMakerSpace->OnClicked.AddDynamic(this, &UCPanelContents::OpenMakerSpace);
}

void UCPanelContents::SetViewToHome()
{
	UWidgetSwitcher* ParentWidget = Cast<UWidgetSwitcher>(GetParent());
	if (ParentWidget)
	{
		ParentWidget->SetActiveWidgetIndex(0);
	}
}

void UCPanelContents::SetViewToLibrary()
{
	UWidgetSwitcher* ParentWidget = Cast<UWidgetSwitcher>(GetParent());
	if (ParentWidget)
	{
		ParentWidget->SetActiveWidgetIndex(1);
	}
}

void UCPanelContents::SetViewToBrowse()
{
	UWidgetSwitcher* ParentWidget = Cast<UWidgetSwitcher>(GetParent());
	if (ParentWidget)
	{
		ParentWidget->SetActiveWidgetIndex(4);
	}
}

void UCPanelContents::OpenLiveContents()
{
	WidgetLiveContents->SetVisibility(ESlateVisibility::Visible);
	WidgetLiveContents->SetIsEnabled(true);
}

void UCPanelContents::OpenMakerSpace()
{
	UWidgetSwitcher* ParentWidget = Cast<UWidgetSwitcher>(GetParent());
	if (ParentWidget)
	{
		ParentWidget->SetActiveWidgetIndex(5);
	}
}
