// Fill out your copyright notice in the Description page of Project Settings.


#include "EditorModeWidget.h"

#include "VClass/Player/MainMenuPlayerController.h"


void UEditorModeWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ButtonFile = Cast<UButton>(GetWidgetFromName("File"));
	ButtonHome = Cast<UButton>(GetWidgetFromName("Home"));
	ButtonAnimation = Cast<UButton>(GetWidgetFromName("Animation"));
	ButtonRecord = Cast<UButton>(GetWidgetFromName("Record"));
	ButtonPeople = Cast<UButton>(GetWidgetFromName("People"));
	ButtonReturnToHomeScreen = Cast<UButton>(GetWidgetFromName("ReturnHomeScreen"));

	ButtonReturnToHomeScreen->OnClicked.AddDynamic(this,&UEditorModeWidget::ReturntoHomeScreen);
	
}

void UEditorModeWidget::ReturntoHomeScreen()
{
	AMainMenuPlayerController* PlayerController = Cast<AMainMenuPlayerController>(GetOwningPlayer());
	if(PlayerController)
	{
		PlayerController->OpenHomeScreenUI();
	}
}

