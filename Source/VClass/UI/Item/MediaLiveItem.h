// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "MediaLiveItem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class VCLASS_API UMediaLiveItem : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintImplementableEvent)
	void SetMediaName(const FString& newName);
};
