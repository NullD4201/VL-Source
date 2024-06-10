// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameMode.h"

#include "MainMenuPlayerController.h"


AMainMenuGameMode::AMainMenuGameMode()
{
	DefaultPawnClass = nullptr;
	HUDClass = nullptr;
	PlayerControllerClass = AMainMenuPlayerController::StaticClass();
	GameStateClass = nullptr;
	PlayerStateClass = nullptr;
	SpectatorClass = nullptr;
}
