// Fill out your copyright notice in the Description page of Project Settings.


#include "CPanelLiveContents.h"


void UCPanelLiveContents::NativeConstruct()
{
	Super::NativeConstruct();

	ButtonProduct = Cast<UButton>(GetWidgetFromName("Product"));
	ButtonOutside = Cast<UButton>(GetWidgetFromName("Outside"));

	ButtonOutside->OnClicked.AddDynamic(this, &UCPanelLiveContents::ClickOutside);
}

void UCPanelLiveContents::ClickOutside()
{
	UE_LOG(LogTemp, Warning, TEXT("Click"))
	
	this->SetIsEnabled(false);
	this->SetVisibility(ESlateVisibility::Hidden);

}
