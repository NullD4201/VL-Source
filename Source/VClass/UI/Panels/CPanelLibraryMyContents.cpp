// Fill out your copyright notice in the Description page of Project Settings.


#include "CPanelLibraryMyContents.h"

#include "Components/WidgetSwitcher.h"


void UCPanelLibraryMyContents::NativeConstruct()
{
	Super::NativeConstruct();

	ButtonHome = Cast<UButton>(GetWidgetFromName("Home"));
	ButtonContents = Cast<UButton>(GetWidgetFromName("Contents"));
	ButtonBrowse = Cast<UButton>(GetWidgetFromName("Browse"));

	Image3DPreview = Cast<UImage>(GetWidgetFromName("3DPreviewImage"));
	ImageProfileBackground = Cast<UImage>(GetWidgetFromName("ProfileBackground"));
	ImageProfileForeground = Cast<UImage>(GetWidgetFromName("ProfileForeground"));
	
	ButtonMyAccount = Cast<UButton>(GetWidgetFromName("MyAccount"));

	ButtonHome->OnClicked.AddDynamic(this, &UCPanelLibraryMyContents::SetViewToHome);
	ButtonMyAccount->OnClicked.AddDynamic(this, &UCPanelLibraryMyContents::SetViewToMyAccount);
}

void UCPanelLibraryMyContents::SetViewToHome()
{
	UWidgetSwitcher* ParentWidget = Cast<UWidgetSwitcher>(GetParent());
	if (ParentWidget)
	{
		ParentWidget->SetActiveWidgetIndex(0);
	}
}

void UCPanelLibraryMyContents::SetViewToMyAccount()
{
	UWidgetSwitcher* ParentWidget = Cast<UWidgetSwitcher>(GetParent());
	if (ParentWidget)
	{
		ParentWidget->SetActiveWidgetIndex(1);
	}
}

void UCPanelLibraryMyContents::SetViewToContents()
{
	UWidgetSwitcher* ParentWidget = Cast<UWidgetSwitcher>(GetParent());
	if (ParentWidget)
	{
		ParentWidget->SetActiveWidgetIndex(3);
	}
}

void UCPanelLibraryMyContents::SetViewToBrowse()
{
	UWidgetSwitcher* ParentWidget = Cast<UWidgetSwitcher>(GetParent());
	if (ParentWidget)
	{
		ParentWidget->SetActiveWidgetIndex(4);
	}
}
