// Fill out your copyright notice in the Description page of Project Settings.


#include "EditorPlayerController.h"


AEditorPlayerController::AEditorPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	bShowMouseCursor = true;

	SetReplicates(true);
}

void AEditorPlayerController::BeginPlay()
{
	const FInputModeGameAndUI InputModeGameAndUI;
	SetInputMode(InputModeGameAndUI);
}
