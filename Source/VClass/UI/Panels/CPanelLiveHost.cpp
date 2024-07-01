// Fill out your copyright notice in the Description page of Project Settings.


#include "CPanelLiveHost.h"

#include "VClass/Data/VClassSaveGame.h"
#include <VClass/UI/Item/MediaLiveItem.h>

void UCPanelLiveHost::NativeConstruct(){
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
			UE_LOG(VClass, Warning, TEXT("%s"), *s);
			if(item)
			{
				item->SetMediaName(s);
				SlideList->AddChild(item);
			}
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




