// Fill out your copyright notice in the Description page of Project Settings.


#include "CPanelLibraryEditAccount.h"


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
}
