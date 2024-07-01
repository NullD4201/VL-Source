// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "MediaLiveItem.generated.h"
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLiveItemClickedCallback, const FString&, paramString);

UCLASS(Blueprintable)
class VCLASS_API UMediaLiveItem : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct() override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void SetMediaName(const FString& newName);

	UFUNCTION()
	void OnClickDisplayButton();

	UPROPERTY(BlueprintReadWrite)
	FString MediaName;

	FLiveItemClickedCallback ClickedCallback;

protected:
	UPROPERTY()
	UButton* Display;
};
