// Fill out your copyright notice in the Description page of Project Settings.


#include "CPanelLibraryEditAccount.h"

#include "CPanelLibraryCurrentAccount.h"
#include "Components/CanvasPanel.h"
#include "VClass/Data/VClassSaveGame.h"
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
			UCPanelLibraryCurrentAccount* CurrentAccount = Cast<UCPanelLibraryCurrentAccount>(CPanelLibrary->PanelCurrent);
			if(CurrentAccount)
			{
				FString name = FText::Format(FText::FromString("{0} {1}"), TextBoxFirstName->GetText(), TextBoxLastName->GetText()).ToString();
				FString email = TextBoxEmail->GetText().ToString();
				FString message = TextBoxMessage->GetText().ToString();
				UVClassSaveGame* SaveGame = Cast<UVClassSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Main"),0));
				if(SaveGame)
				{
					SaveGame->PlayerName = name;
					UGameplayStatics::SaveGameToSlot(SaveGame,TEXT("Main"),0);
				}
				CurrentAccount->SetProfileName(name,email,message);
			}
			CPanelLibrary->PanelCurrent->SetVisibility(ESlateVisibility::Visible);
		}
	}
}
