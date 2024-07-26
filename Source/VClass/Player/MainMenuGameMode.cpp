// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameMode.h"

#include "MainMenuPlayerController.h"
#include "VClass/Data/VClassSaveGame.h"


AMainMenuGameMode::AMainMenuGameMode()
{
	DefaultPawnClass = nullptr;
	HUDClass = nullptr;
	//PlayerControllerClass = AMainMenuPlayerController::StaticClass();
	SpectatorClass = nullptr;
}

void AMainMenuGameMode::BeginPlay()
{
	UVClassSaveGame* SaveGame = Cast<UVClassSaveGame>(UGameplayStatics::CreateSaveGameObject(UVClassSaveGame::StaticClass()));
	if(SaveGame)
	{
		if(UGameplayStatics::SaveGameToSlot(SaveGame,TEXT("Main"),0))
		{
			UE_LOG(LogTemp,Warning,TEXT("Save Game Successfully!"));
		}
	}
}

