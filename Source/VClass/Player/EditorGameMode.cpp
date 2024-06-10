// Fill out your copyright notice in the Description page of Project Settings.


#include "EditorGameMode.h"

#include "EditorPlayerController.h"


AEditorGameMode::AEditorGameMode()
{
	PlayerControllerClass = AEditorPlayerController::StaticClass();
}
