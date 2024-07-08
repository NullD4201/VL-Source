// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ProjectInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "SlideShowWidget.generated.h"

/**
 * 
 */
UCLASS()
class VCLASS_API USlideShowWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* TestButton;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* TestButton2;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnTestButtonClick();

	UFUNCTION()
	void OnTestButtonClick2();

private:
	AActor* ScreenActor1;
};
