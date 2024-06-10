// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ProjectInfo.h"
#include "GameFramework/PlayerController.h"
#include "EditorPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class VCLASS_API AEditorPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AEditorPlayerController();

	virtual void BeginPlay() override;
};
