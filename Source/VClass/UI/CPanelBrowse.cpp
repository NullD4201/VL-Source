// Fill out your copyright notice in the Description page of Project Settings.


#include "CPanelBrowse.h"

#include "Components/WidgetSwitcher.h"


void UCPanelBrowse::NativeConstruct()
{
	Super::NativeConstruct();

	ButtonHome = Cast<UButton>(GetWidgetFromName("Home"));
	ButtonLibrary = Cast<UButton>(GetWidgetFromName("Library"));
	ButtonContents = Cast<UButton>(GetWidgetFromName("Contents"));

	PanelGraphicsBrowser = Cast<UCanvasPanel>(GetWidgetFromName("GraphicsBrowser"));
	PanelVolumeBrowser = Cast<UCanvasPanel>(GetWidgetFromName("VolumeBrowser"));

	ButtonBrowseGraphics = Cast<UButton>(GetWidgetFromName("BrowseGraphics"));
	ButtonBrowseVolume = Cast<UButton>(GetWidgetFromName("BrowseVolume"));

	ButtonHome->OnClicked.AddDynamic(this, &UCPanelBrowse::SetViewToHome);
	ButtonLibrary->OnClicked.AddDynamic(this, &UCPanelBrowse::SetViewToLibrary);
	ButtonContents->OnClicked.AddDynamic(this, &UCPanelBrowse::SetViewToContents);

	ButtonBrowseGraphics->OnClicked.AddDynamic(this, &UCPanelBrowse::BrowseGraphics);
	ButtonBrowseVolume->OnClicked.AddDynamic(this, &UCPanelBrowse::BrowseVolume);
}

void UCPanelBrowse::SetViewToHome()
{
	UWidgetSwitcher* ParentWidget = Cast<UWidgetSwitcher>(GetParent());
	if (ParentWidget)
	{
		ParentWidget->SetActiveWidgetIndex(0);
	}
}

void UCPanelBrowse::SetViewToLibrary()
{
	UWidgetSwitcher* ParentWidget = Cast<UWidgetSwitcher>(GetParent());
	if (ParentWidget)
	{
		ParentWidget->SetActiveWidgetIndex(1);
	}
}

void UCPanelBrowse::SetViewToContents()
{
	UWidgetSwitcher* ParentWidget = Cast<UWidgetSwitcher>(GetParent());
	if (ParentWidget)
	{
		ParentWidget->SetActiveWidgetIndex(3);
	}
}

void UCPanelBrowse::BrowseVolume()
{
	PanelVolumeBrowser->SetVisibility(ESlateVisibility::Visible);
	PanelGraphicsBrowser->SetVisibility(ESlateVisibility::Hidden);
}

void UCPanelBrowse::BrowseGraphics()
{
	PanelVolumeBrowser->SetVisibility(ESlateVisibility::Hidden);
	PanelGraphicsBrowser->SetVisibility(ESlateVisibility::Visible);
}
