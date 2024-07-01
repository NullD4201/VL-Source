// Fill out your copyright notice in the Description page of Project Settings.


#include "CPanelLiveHost.h"

#include "VClass/Data/VClassSaveGame.h"
#include <VClass/UI/Item/MediaLiveItem.h>

void UCPanelLiveHost::NativeConstruct(){
	RootPanel = Cast<UCanvasPanel>(GetWidgetFromName("RootPanel"));
	
	MotionPanel = Cast<UCanvasPanel>(GetWidgetFromName("MotionPanel"));
	SetSlide = Cast<UButton>(GetWidgetFromName("SetSlide"));
	SlideList = Cast<UScrollBox>(GetWidgetFromName("SlideList"));

	SlidePanel = Cast<UCanvasPanel>(GetWidgetFromName("SlidePanel"));

	SetSlide->OnClicked.AddDynamic(this,&UCPanelLiveHost::OpenSlideSettingPanel);
}

void UCPanelLiveHost::Init()
{
	UVClassSaveGame* SaveGame = Cast<UVClassSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Main"),0));
	if(SaveGame)
	{
		
		for(FString s : SaveGame->UploadMediaList)
		{
			UMediaLiveItem* item = CreateWidget<UMediaLiveItem>(this,MediaListItem.Get());
			if(item)
			{
				item->SetMediaName(s);
				item->ClickedCallback.AddDynamic(this,&UCPanelLiveHost::OpenDisplaySocketSelector);
				SlideList->AddChild(item);
			}
		}
		UUserWidget* socket;
		switch(SaveGame->ImageMode)
		{
		case ImageAppearMode::IAM_ONESIDED:
			socket = CreateWidget<UUserWidget>(this,MediaSocketSelector_OneSided.Get());
			RootPanel->AddChildToCanvas(socket);
			MediaSocketSelector = Cast<UCDisplayImageSocketSelectorPanel>(socket);
			MediaSocketSelector->OnSocketDefinite.AddDynamic(this,&UCPanelLiveHost::ReturnToMainMenu);
			socket->SetVisibility(ESlateVisibility::Hidden);
			break;
		case ImageAppearMode::IAM_TWOSIDED:
			socket = CreateWidget<UUserWidget>(this,MediaSocketSelector_TwoSided.Get());
			RootPanel->AddChildToCanvas(socket);
			MediaSocketSelector = Cast<UCDisplayImageSocketSelectorPanel>(socket);
			MediaSocketSelector->OnSocketDefinite.AddDynamic(this,&UCPanelLiveHost::ReturnToMainMenu);
			socket->SetVisibility(ESlateVisibility::Hidden);
			break;
		case ImageAppearMode::IAM_TRIPLE:
			socket = CreateWidget<UUserWidget>(this,MediaSocketSelector_Triple.Get());
			RootPanel->AddChildToCanvas(socket);
			MediaSocketSelector = Cast<UCDisplayImageSocketSelectorPanel>(socket);
			MediaSocketSelector->OnSocketDefinite.AddDynamic(this,&UCPanelLiveHost::ReturnToMainMenu);
			socket->SetVisibility(ESlateVisibility::Hidden);
			break;
		case ImageAppearMode::IAM_ONESIDED_LONG:
			socket = CreateWidget<UUserWidget>(this,MediaSocketSelector_OneSided_Long.Get());
			RootPanel->AddChildToCanvas(socket);
			MediaSocketSelector = Cast<UCDisplayImageSocketSelectorPanel>(socket);
			MediaSocketSelector->OnSocketDefinite.AddDynamic(this,&UCPanelLiveHost::ReturnToMainMenu);
			socket->SetVisibility(ESlateVisibility::Hidden);
			break;
		case ImageAppearMode::IAM_FRONT_WIDE:
			socket = CreateWidget<UUserWidget>(this,MediaSocketSelector_Front_Wide.Get());
			RootPanel->AddChildToCanvas(socket);
			MediaSocketSelector = Cast<UCDisplayImageSocketSelectorPanel>(socket);
			MediaSocketSelector->OnSocketDefinite.AddDynamic(this,&UCPanelLiveHost::ReturnToMainMenu);
			socket->SetVisibility(ESlateVisibility::Hidden);
			break;
		case ImageAppearMode::IAM_BACKWARD_FULL:
			socket = CreateWidget<UUserWidget>(this,MediaSocketSelector_Backward_Full.Get());
			RootPanel->AddChildToCanvas(socket);
			MediaSocketSelector = Cast<UCDisplayImageSocketSelectorPanel>(socket);
			MediaSocketSelector->OnSocketDefinite.AddDynamic(this,&UCPanelLiveHost::ReturnToMainMenu);
			socket->SetVisibility(ESlateVisibility::Hidden);
			break;
		default:
				break;
		}
	}
}

void UCPanelLiveHost::SetMotionPanelVisibility(bool bIsVisible)
{
	if(bIsVisible)
	{
		MotionPanel->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		MotionPanel->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UCPanelLiveHost::OpenSlideSettingPanel()
{
	SetMotionPanelVisibility(false);
	SlidePanel->SetVisibility(ESlateVisibility::Visible);
}

void UCPanelLiveHost::OpenDisplaySocketSelector(const FString& MediaNameToDisplay)
{
	if(MediaSocketSelector)
	{
		MediaSocketSelector->SetVisibility(ESlateVisibility::Visible);
		MediaSocketSelector->MediaNameToDisplay = MediaNameToDisplay;
	}
}

void UCPanelLiveHost::ReturnToMainMenu()
{
	MotionPanel->SetVisibility(ESlateVisibility::Hidden);
	SlidePanel->SetVisibility(ESlateVisibility::Hidden);
	MediaSocketSelector->SetVisibility(ESlateVisibility::Hidden);
}