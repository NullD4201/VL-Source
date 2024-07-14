// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ProjectInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* TestButton;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* TestButton2;

protected:
	virtual void NativeConstruct() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& Geometry, const FPointerEvent& MouseEvent) override;
	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	UPROPERTY(meta=(BindWidget))
	class UImage* TestSlide1;

	UFUNCTION()
	void OnTestButtonClick();

	UFUNCTION()
	void OnTestButtonClick2();

private:
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* RootCanvasPanel;
	
	UImage* DraggedImage;

	bool bIsDragging;

	FVector2D DragOffset;

	AActor* ScreenActor1;
};
