// Fill out your copyright notice in the Description page of Project Settings.


#include "CEditorHome.h"

#include "VClass/ImportFiles.h"
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
	if(!MediaName.IsEmpty())
	{
		UImportFiles::OpenFIleDialogueAndUploadImage(MediaName.ToString());
		UMediaListItem* NewItem = CreateWidget<UMediaListItem>(this, MediaBlockClass.Get());
		if(NewItem)
		{
			NewItem->SetName(MediaName.ToString());
			MediaListScrollBox->AddChild(NewItem);
		}
		PanelMediaAdd->SetVisibility(ESlateVisibility::Hidden);
	}
}
