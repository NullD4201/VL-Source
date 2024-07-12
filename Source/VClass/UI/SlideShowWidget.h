// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ProjectInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "SlideShowWidget.generated.h"

/**
 * 
 */
UCLASS()
class VCLASS_API USlideShowWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonTestSlide1;

	UPROPERTY(meta = (BindWidget))
	class UImage* _ImageSlideTemp;

	bool bIsDragging;

	UFUNCTION()
	void OnButtonPressed();

	UFUNCTION()
	void OnButtonReleased();

	UFUNCTION()
	void OnMouseLeftClick();
};
