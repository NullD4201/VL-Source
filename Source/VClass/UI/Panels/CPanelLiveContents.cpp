// Fill out your copyright notice in the Description page of Project Settings.


#include "CPanelLiveContents.h"

#include "VClass/Player/MainMenuGameMode.h"
#include "VClass/Player/MainMenuPlayerController.h"


void UCPanelLiveContents::NativeConstruct()
{
	Super::NativeConstruct();

	ButtonProduct = Cast<UButton>(GetWidgetFromName("Product"));
	ButtonOutside = Cast<UButton>(GetWidgetFromName("Outside"));

	ButtonOutside->OnClicked.AddDynamic(this, &UCPanelLiveContents::ClickOutside);
	ButtonProduct->OnClicked.AddDynamic(this, &UCPanelLiveContents::ClickButtonProduct);
}

void UCPanelLiveContents::ClickOutside()
{
	UE_LOG(LogTemp, Warning, TEXT("Click"))
	
	this->SetIsEnabled(false);
	this->SetVisibility(ESlateVisibility::Hidden);

}

void UCPanelLiveContents::ClickButtonProduct()
{
	AMainMenuGameMode* GameMode = Cast<AMainMenuGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	AMainMenuPlayerController* PlayerController = Cast<AMainMenuPlayerController>(GetOwningPlayer());
	if(GameMode && PlayerController)
	{
		PlayerController->SetPlayer(GameMode->StageServerIPAddress,FString::FromInt(GameMode->StageServerPort),GameMode->IsHost,GameMode->Key);
	}
}

