// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "../Actor/ImageDisplayManager.h"
#include "VClassSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class VCLASS_API UVClassSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TArray<FString> UploadMediaList = TArray<FString>();

	UPROPERTY()
	ImageAppearMode ImageMode;

	UPROPERTY()
	FString PlayerName;
};
