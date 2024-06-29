// Fill out your copyright notice in the Description page of Project Settings.


#include "CPanelLibrary.h"

#include "Components/WidgetSwitcher.h"


void UCPanelLibrary::NativeConstruct()
{
	Super::NativeConstruct();

	ButtonHome = Cast<UButton>(GetWidgetFromName("Home"));
	ButtonContents = Cast<UButton>(GetWidgetFromName("Contents"));
	ButtonBrowse = Cast<UButton>(GetWidgetFromName("Browse"));

	Image3DPreview = Cast<UImage>(GetWidgetFromName("3DPreviewImage"));

	ButtonNotification1 = Cast<UButton>(GetWidgetFromName("Notification1"));
	ButtonNotification2 = Cast<UButton>(GetWidgetFromName("Notification2"));
	ButtonMyContents = Cast<UButton>(GetWidgetFromName("MyContents"));

	PanelCurrent = Cast<UUserWidget>(GetWidgetFromName("CurrentAccountLibraryPanel"));
	PanelEdit = Cast<UUserWidget>(GetWidgetFromName("EditAccountLibraryPanel"));

	AccountBackgroundImage = Cast<UImage>(GetWidgetFromName("AccountBackground"));

	ButtonHome->OnClicked.AddDynamic(this, &UCPanelLibrary::SetViewToHome);
	ButtonContents->OnClicked.AddDynamic(this, &UCPanelLibrary::SetViewToContents);
	ButtonBrowse->OnClicked.AddDynamic(this, &UCPanelLibrary::SetViewToBrowse);

	ButtonMyContents->OnClicked.AddDynamic(this, &UCPanelLibrary::SetViewToMyContents);
}

void UCPanelLibrary::SetViewToHome()
{
	UWidgetSwitcher* ParentWidget = Cast<UWidgetSwitcher>(GetParent());
	if (ParentWidget)
	{
		ParentWidget->SetActiveWidgetIndex(0);
	}
}

void UCPanelLibrary::SetViewToMyContents()
{
	UWidgetSwitcher* ParentWidget = Cast<UWidgetSwitcher>(GetParent());
	if (ParentWidget)
	{
		ParentWidget->SetActiveWidgetIndex(2);
	}
}

void UCPanelLibrary::SetViewToContents()
{
	UWidgetSwitcher* ParentWidget = Cast<UWidgetSwitcher>(GetParent());
	if (ParentWidget)
	{
		ParentWidget->SetActiveWidgetIndex(3);
	}
}

void UCPanelLibrary::SetViewToBrowse()
{
	UWidgetSwitcher* ParentWidget = Cast<UWidgetSwitcher>(GetParent());
	if (ParentWidget)
	{
		ParentWidget->SetActiveWidgetIndex(4);
	}
}
