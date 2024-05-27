// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "UI/EntryUI.h"
#include "EntryPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class VCLASS_API AEntryPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AEntryPlayerController();

	virtual void BeginPlay() override;

	TSubclassOf<UEntryUI> entryUIClass;
	
	void EntryServer(const FString& address, const FString& port, const bool isHost, const FString& seatNum);
};
