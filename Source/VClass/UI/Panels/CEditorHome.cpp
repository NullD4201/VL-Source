// Fill out your copyright notice in the Description page of Project Settings.


#include "CEditorHome.h"

#include <string>

#include "VClass/ImportFiles.h"
#include "VClass/Data/VClassSaveGame.h"
#include "VClass/Player/MainMenuGameMode.h"
#include "VClass/UI/Item/MediaListItem.h"


void UCEditorHome::NativeConstruct()
{
	Super::NativeConstruct();

	PanelNewMedia = Cast<UCanvasPanel>(GetWidgetFromName("NewMediaPanel"));
	ButtonAddMedia = Cast<UButton>(GetWidgetFromName("AddMedia"));
	MediaListScrollBox = Cast<UScrollBox>(GetWidgetFromName("MediaListScrollBox"));

	PanelMediaAdd = Cast<UCanvasPanel>(GetWidgetFromName("MediaUploadPopup"));
	EditableTextMediaName = Cast<UEditableText>(GetWidgetFromName("MediaNameEditableText"));
	ButtonMediaUpload = Cast<UButton>(GetWidgetFromName("MediaUpload"));

	PanelAlignObject = Cast<UCanvasPanel>(GetWidgetFromName("AlignObjectPanel"));
	PanelShadowSetting = Cast<UCanvasPanel>(GetWidgetFromName("ShadowSettingPanel"));

	ButtonNewMedia = Cast<UButton>(GetWidgetFromName("NewMedia"));
	ButtonShape = Cast<UButton>(GetWidgetFromName("Shape"));
	ButtonAlignObjects = Cast<UButton>(GetWidgetFromName("AlignObjects"));
	ButtonSetShadow = Cast<UButton>(GetWidgetFromName("SetShadow"));
	ButtonInteraction = Cast<UButton>(GetWidgetFromName("Interaction"));
	ButtonStageSetting = Cast<UButton>(GetWidgetFromName("StageSetting"));

	ButtonShadowON = Cast<UButton>(GetWidgetFromName("ShadowON"));
	ButtonShadowOFF = Cast<UButton>(GetWidgetFromName("ShadowOFF"));
	ButtonShadowDetail = Cast<UButton>(GetWidgetFromName("ShadowDetail"));

	ButtonAlign1 = Cast<UButton>(GetWidgetFromName("Align_1"));
	ButtonAlign2 = Cast<UButton>(GetWidgetFromName("Align_2"));
	ButtonAlign3 = Cast<UButton>(GetWidgetFromName("Align_3"));
	ButtonAlign4 = Cast<UButton>(GetWidgetFromName("Align_4"));
	ButtonAlign5 = Cast<UButton>(GetWidgetFromName("Align_5"));
	ButtonAlign6 = Cast<UButton>(GetWidgetFromName("Align_6"));


	ButtonNewMedia->OnClicked.AddDynamic(this, &UCEditorHome::SetPanelToNewMedia);
	ButtonAlignObjects->OnClicked.AddDynamic(this, &UCEditorHome::SetPanelToAlignObject);
	ButtonSetShadow->OnClicked.AddDynamic(this, &UCEditorHome::SetPanelToShadowSetting);

	ButtonAlign1->OnClicked.AddDynamic(this, &UCEditorHome::SetImageAppearModeToTwoSided);
	ButtonAlign2->OnClicked.AddDynamic(this, &UCEditorHome::SetImageAppearModeToOneSided);
	ButtonAlign3->OnClicked.AddDynamic(this, &UCEditorHome::SetImageAppearModeToTriple);
	ButtonAlign4->OnClicked.AddDynamic(this, &UCEditorHome::SetImageAppearModeToOneSidedLong);
	ButtonAlign5->OnClicked.AddDynamic(this, &UCEditorHome::SetImageAppearModeToFrontWide);
	ButtonAlign6->OnClicked.AddDynamic(this, &UCEditorHome::SetImageAppearModeToBackwardFull);
	
	ButtonAddMedia->OnClicked.AddDynamic(this, &UCEditorHome::PopMediaUploadPanel);

	ButtonMediaUpload->OnClicked.AddDynamic(this, &UCEditorHome::UploadMedia);
}

void UCEditorHome::SetPanelToNewMedia()
{
	PanelNewMedia->SetVisibility(ESlateVisibility::Visible);
	PanelAlignObject->SetVisibility(ESlateVisibility::Hidden);
	PanelShadowSetting->SetVisibility(ESlateVisibility::Hidden);
}

void UCEditorHome::SetPanelToAlignObject()
{
	PanelNewMedia->SetVisibility(ESlateVisibility::Hidden);
	PanelAlignObject->SetVisibility(ESlateVisibility::Visible);
	PanelShadowSetting->SetVisibility(ESlateVisibility::Hidden);
}

void UCEditorHome::SetPanelToShadowSetting()
{
	PanelNewMedia->SetVisibility(ESlateVisibility::Hidden);
	PanelAlignObject->SetVisibility(ESlateVisibility::Hidden);
	PanelShadowSetting->SetVisibility(ESlateVisibility::Visible);
}

void UCEditorHome::PopMediaUploadPanel()
{
	PanelMediaAdd->SetVisibility(ESlateVisibility::Visible);
}

void UCEditorHome::UploadMedia()
{
	FText MediaName = EditableTextMediaName->GetText();

	UVClassSaveGame* SaveGame = Cast<UVClassSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Main"),0));
	
	if(!MediaName.IsEmpty() /*&& !SaveGame->UploadMediaList.Contains(MediaName.ToString())*/)
	{
		AMainMenuGameMode* gamemode = Cast<AMainMenuGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		UImportFiles::OpenFileDialogueAndUploadImage(MediaName.ToString(), "http://"+gamemode->ImageServerIPAddress+":"+FString::FromInt(gamemode->ImageServerPort));
		UMediaListItem* NewItem = CreateWidget<UMediaListItem>(this, MediaBlockClass.Get());
		if(NewItem)
		{
			NewItem->SetName(MediaName.ToString());
			MediaListScrollBox->AddChild(NewItem);
		}
		PanelMediaAdd->SetVisibility(ESlateVisibility::Hidden);
		/*SaveGame->UploadMediaList.Add(MediaName.ToString());
		for(FString s : SaveGame->UploadMediaList)
		{
			UE_LOG(VClass, Warning, TEXT("%s"), *s);
		}
		UE_LOG(VClass, Warning, TEXT("%d"), SaveGame->UploadMediaList.Num());*/
		UGameplayStatics::SaveGameToSlot(SaveGame, TEXT("Main"),0);
	}
}

void UCEditorHome::SetImageAppearModeToTwoSided()
{
	UVClassSaveGame* SaveGame = Cast<UVClassSaveGame>(UGameplayStatics::LoadGameFromSlot("Main",0));
	if(SaveGame)
	{
		SaveGame->ImageMode = ImageAppearMode::IAM_TWOSIDED;

		FButtonStyle style = ButtonAlign1->GetStyle();
		style.Normal = style.Hovered;
		ButtonAlign1->SetStyle(style);
		
		if(ActivatedImageButtonMode)
		{
			style = ActivatedImageButtonMode->GetStyle();
			style.Normal = style.Disabled;
			ActivatedImageButtonMode->SetStyle(style);
		}
		ActivatedImageButtonMode = ButtonAlign1;
	}
	UGameplayStatics::SaveGameToSlot(SaveGame, TEXT("Main"), 0);
}
void UCEditorHome::SetImageAppearModeToOneSided()
{
	UVClassSaveGame* SaveGame = Cast<UVClassSaveGame>(UGameplayStatics::LoadGameFromSlot("Main",0));
	if(SaveGame)
	{
		SaveGame->ImageMode = ImageAppearMode::IAM_ONESIDED;
		
		FButtonStyle style = ButtonAlign2->GetStyle();
		style.Normal = style.Hovered;
		ButtonAlign2->SetStyle(style);

		if(ActivatedImageButtonMode)
		{
			style = ActivatedImageButtonMode->GetStyle();
			style.Normal = style.Disabled;
			ActivatedImageButtonMode->SetStyle(style);
		}
		ActivatedImageButtonMode = ButtonAlign2;
	}
	UGameplayStatics::SaveGameToSlot(SaveGame, TEXT("Main"), 0);
}
void UCEditorHome::SetImageAppearModeToTriple()
{
	UVClassSaveGame* SaveGame = Cast<UVClassSaveGame>(UGameplayStatics::LoadGameFromSlot("Main",0));
	if(SaveGame)
	{
		SaveGame->ImageMode = ImageAppearMode::IAM_TRIPLE;

		FButtonStyle style = ButtonAlign3->GetStyle();
		style.Normal = style.Hovered;
		ButtonAlign3->SetStyle(style);

		if(ActivatedImageButtonMode)
		{
			style = ActivatedImageButtonMode->GetStyle();
			style.Normal = style.Disabled;
			ActivatedImageButtonMode->SetStyle(style);
		}
		ActivatedImageButtonMode = ButtonAlign3;
	}
	UGameplayStatics::SaveGameToSlot(SaveGame, TEXT("Main"), 0);
}
void UCEditorHome::SetImageAppearModeToOneSidedLong()
{
	UVClassSaveGame* SaveGame = Cast<UVClassSaveGame>(UGameplayStatics::LoadGameFromSlot("Main",0));
	if(SaveGame)
	{
		SaveGame->ImageMode = ImageAppearMode::IAM_ONESIDED_LONG;
		
		FButtonStyle style = ButtonAlign4->GetStyle();
		style.Normal = style.Hovered;
		ButtonAlign4->SetStyle(style);

		if(ActivatedImageButtonMode)
		{
			style = ActivatedImageButtonMode->GetStyle();
			style.Normal = style.Disabled;
			ActivatedImageButtonMode->SetStyle(style);
		}
		ActivatedImageButtonMode = ButtonAlign4;
	}
	UGameplayStatics::SaveGameToSlot(SaveGame, TEXT("Main"), 0);
}
void UCEditorHome::SetImageAppearModeToFrontWide()
{
	UVClassSaveGame* SaveGame = Cast<UVClassSaveGame>(UGameplayStatics::LoadGameFromSlot("Main",0));
	if(SaveGame)
	{
		SaveGame->ImageMode = ImageAppearMode::IAM_FRONT_WIDE;
		
		FButtonStyle style = ButtonAlign5->GetStyle();
		style.Normal = style.Hovered;
		ButtonAlign5->SetStyle(style);

		if(ActivatedImageButtonMode)
		{
			style = ActivatedImageButtonMode->GetStyle();
			style.Normal = style.Disabled;
			ActivatedImageButtonMode->SetStyle(style);
		}
		ActivatedImageButtonMode = ButtonAlign5;
	}
	UGameplayStatics::SaveGameToSlot(SaveGame, TEXT("Main"), 0);
}
void UCEditorHome::SetImageAppearModeToBackwardFull()
{
	UVClassSaveGame* SaveGame = Cast<UVClassSaveGame>(UGameplayStatics::LoadGameFromSlot("Main",0));
	if(SaveGame)
	{
		SaveGame->ImageMode = ImageAppearMode::IAM_BACKWARD_FULL;

		FButtonStyle style = ButtonAlign6->GetStyle();
		style.Normal = style.Hovered;
		ButtonAlign6->SetStyle(style);

		if(ActivatedImageButtonMode)
		{
			style = ActivatedImageButtonMode->GetStyle();
			style.Normal = style.Disabled;
			ActivatedImageButtonMode->SetStyle(style);
		}
		ActivatedImageButtonMode = ButtonAlign6;
	}
	UGameplayStatics::SaveGameToSlot(SaveGame, TEXT("Main"), 0);
}

