#include "CPanelLibraryCurrentAccount.h"

#include "CPanelLibraryEditAccount.h"
#include "../CPanelLibrary.h"
#include "Blueprint/UserWidget.h"
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
	UCanvasPanel* CanvasPanel = Cast<UCanvasPanel>(this->GetParent());
	if (CanvasPanel)
	{
		UCPanelLibrary* CPanelLibrary = CanvasPanel->GetTypedOuter<UCPanelLibrary>();
		if (CPanelLibrary)
		{
			CPanelLibrary->PanelEdit->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void UCPanelLibraryCurrentAccount::SetProfileName(const FString& NewName, const FString& NewEmail, const FString& message)
{
	TextBlockProfileName->SetText(FText::FromString(NewName));
	TextBlockProfileEmail->SetText(FText::FromString(NewEmail));
	TextBlockAboutMe->SetText(FText::FromString(message));
}

