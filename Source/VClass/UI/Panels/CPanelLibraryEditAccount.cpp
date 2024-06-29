// Fill out your copyright notice in the Description page of Project Settings.


#include "CPanelLibraryEditAccount.h"

#include "Components/CanvasPanel.h"
#include "VClass/UI/CPanelLibrary.h"


void UCPanelLibraryEditAccount::NativeConstruct()
{
	Super::NativeConstruct();

	ImageProfileBackground = Cast<UImage>(GetWidgetFromName("ProfileBackground"));
	ImageProfileForeground = Cast<UImage>(GetWidgetFromName("ProfileForeground"));

	TextBoxFirstName = Cast<UEditableTextBox>(GetWidgetFromName("FirstName"));
	TextBoxLastName = Cast<UEditableTextBox>(GetWidgetFromName("LastName"));
	TextBoxEmail = Cast<UEditableTextBox>(GetWidgetFromName("Email"));
	TextBoxMessage = Cast<UEditableTextBox>(GetWidgetFromName("Message"));

	ButtonSubmit = Cast<UButton>(GetWidgetFromName("SubmitButton"));

	ButtonSubmit->OnClicked.AddDynamic(this, &UCPanelLibraryEditAccount::Sumbit);
}

void UCPanelLibraryEditAccount::Sumbit()
{
	this->SetVisibility(ESlateVisibility::Hidden);
	UCanvasPanel* CanvasPanel = Cast<UCanvasPanel>(this->GetParent());
	if (CanvasPanel)
	{
		UCPanelLibrary* CPanelLibrary = CanvasPanel->GetTypedOuter<UCPanelLibrary>();
		if (CPanelLibrary)
		{
			CPanelLibrary->PanelCurrent->SetVisibility(ESlateVisibility::Visible);
		}
	}
}
