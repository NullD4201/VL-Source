// Fill out your copyright notice in the Description page of Project Settings.


#include "CPanelMakerSpace.h"

#include "Components/WidgetSwitcher.h"
#include "VClass/Player/MainMenuPlayerController.h"


void UCPanelMakerSpace::NativeConstruct()
{
	Super::NativeConstruct();

	ButtonOpenLiveContents = Cast<UButton>(GetWidgetFromName("OpenLiveContents"));
	ButtonContentsHUB = Cast<UButton>(GetWidgetFromName("ContentsHub"));
	ButtonNewContents = Cast<UButton>(GetWidgetFromName("NewContent"));

	ButtonContentsHUB->OnClicked.AddDynamic(this, &UCPanelMakerSpace::OpenContentsHUB);
	ButtonOpenLiveContents->OnClicked.AddDynamic(this, &UCPanelMakerSpace::OpenLiveContents);
	ButtonNewContents->OnClicked.AddDynamic(this, &UCPanelMakerSpace::OpenEditorHome);
}

void UCPanelMakerSpace::OpenContentsHUB()
{
	UWidgetSwitcher* ParentWidget = Cast<UWidgetSwitcher>(GetParent());
	if (ParentWidget)
	{
		ParentWidget->SetActiveWidgetIndex(3);
	}
}

void UCPanelMakerSpace::OpenLiveContents()
{
}

void UCPanelMakerSpace::OpenEditorHome()
{
	AMainMenuPlayerController* PlayerController = Cast<AMainMenuPlayerController>(GetOwningPlayer());
	if(PlayerController)
	{
		PlayerController->OpenEditorModeUI();
	}
}


