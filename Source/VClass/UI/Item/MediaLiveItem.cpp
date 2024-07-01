// Fill out your copyright notice in the Description page of Project Settings.


#include "MediaLiveItem.h"

#include "VClass/UI/Panels/CPanelLiveHost.h"

void UMediaLiveItem::NativeConstruct()
{
	Super::NativeConstruct();

	Display = Cast<UButton>(GetWidgetFromName("Display"));
	
	Display->OnClicked.AddDynamic(this,&UMediaLiveItem::OnClickDisplayButton);
}

void UMediaLiveItem::OnClickDisplayButton()
{
	ClickedCallback.Broadcast(MediaName);
}
