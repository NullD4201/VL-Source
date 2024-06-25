// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MediaListItem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class VCLASS_API UMediaListItem : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetName(const FString& Name);
};
