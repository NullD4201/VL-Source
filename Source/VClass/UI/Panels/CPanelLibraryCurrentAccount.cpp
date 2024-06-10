// Fill out your copyright notice in the Description page of Project Settings.


#include "CPanelLibraryCurrentAccount.h"

#include "../CPanelLibrary.h"
#include "Components/CanvasPanel.h"


void UCPanelLibraryCurrentAccount::NativeConstruct()
{
	Super::NativeConstruct();
	
	ImageProfileBackground = Cast<UImage>(GetWidgetFromName("ProfileBackground"));
	ImageProfileForeground = Cast<UImage>(GetWidgetFromName("ProfileForeground"));
	
	ButtonEditProfile = Cast<UButton>(GetWidgetFromName("EditProfile"));

	TextBlockProfileName = Cast<UTextBlock>(GetWidgetFromName("ProfileName"));
	TextBlockProfileEmail = Cast<UTextBlock>(GetWidgetFromName("ProfileEmail"));
	TextBlockAboutMe = Cast<UTextBlock>(GetWidgetFromName("AboutMe"));
	TextBlockAboutDescription = Cast<UTextBlock>(GetWidgetFromName("AboutDescription"));
	TextBlockPersonerCode = Cast<UTextBlock>(GetWidgetFromName("PersonerCodeText"));

	ButtonEditProfile->OnClicked.AddDynamic(this, &UCPanelLibraryCurrentAccount::EditProfile);
}

void UCPanelLibraryCurrentAccount::EditProfile()
{
	this->SetVisibility(ESlateVisibility::Hidden);
	Cast<UCPanelLibrary>(this->GetParent())->PanelEdit->SetVisibility(ESlateVisibility::Visible);
}
