// Fill out your copyright notice in the Description page of Project Settings.


#include "CDisplayImageSocketSelectorPanel.h"

#include "VClass/Actor/ImageDisplayManager.h"
#include "VClass/Data/VClassSaveGame.h"

void UCDisplayImageSocketSelectorPanel::NativeConstruct()
{
	Super::NativeConstruct();

	if(UWidget* foundWidget = GetWidgetFromName("Index_0"))
	{
		Index_0 = Cast<UButton>(foundWidget);
		Index_0->OnClicked.AddDynamic(this,&UCDisplayImageSocketSelectorPanel::ImageToIndex0);
	}
	if(UWidget* foundWidget = GetWidgetFromName("Index_1"))
	{
		Index_1 = Cast<UButton>(foundWidget);
		Index_1->OnClicked.AddDynamic(this,&UCDisplayImageSocketSelectorPanel::ImageToIndex1);
	}
	if(UWidget* foundWidget = GetWidgetFromName("Index_2"))
	{
		Index_2 = Cast<UButton>(foundWidget);
		Index_2->OnClicked.AddDynamic(this,&UCDisplayImageSocketSelectorPanel::ImageToIndex2);
	}
}

void UCDisplayImageSocketSelectorPanel::ImageToIndex0()
{
	UVClassSaveGame* SaveGame = Cast<UVClassSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Main"),0));
	TActorIterator<AImageDisplayManager> Actor(GetWorld());
	if(*Actor)
	{
		AImageDisplayManager* DisplayManager = *Actor;
		if(DisplayManager)
		{
			DisplayManager->ServerDisplayImage(SaveGame->ImageMode,0,MediaNameToDisplay);
		}
	}
	OnSocketDefinite.Broadcast();
}

void UCDisplayImageSocketSelectorPanel::ImageToIndex1()
{
	UVClassSaveGame* SaveGame = Cast<UVClassSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Main"),0));
	TActorIterator<AImageDisplayManager> Actor(GetWorld());
	if(*Actor)
	{
		AImageDisplayManager* DisplayManager = *Actor;
		if(DisplayManager)
		{
			DisplayManager->ServerDisplayImage(SaveGame->ImageMode,1,MediaNameToDisplay);
		}
	}
	OnSocketDefinite.Broadcast();
}

void UCDisplayImageSocketSelectorPanel::ImageToIndex2()
{
	UVClassSaveGame* SaveGame = Cast<UVClassSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Main"),0));
	TActorIterator<AImageDisplayManager> Actor(GetWorld());
	if(*Actor)
	{
		AImageDisplayManager* DisplayManager = *Actor;
		if(DisplayManager)
		{
			DisplayManager->ServerDisplayImage(SaveGame->ImageMode,2,MediaNameToDisplay);
		}
	}
	OnSocketDefinite.Broadcast();
}