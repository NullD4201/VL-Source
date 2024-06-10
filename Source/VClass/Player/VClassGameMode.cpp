// Fill out your copyright notice in the Description page of Project Settings.


#include "../Player/VClassGameMode.h"

#include "VClassPlayerController.h"

AVClassGameMode::AVClassGameMode()
{
	PlayerControllerClass = AVClassPlayerController::StaticClass();
}
