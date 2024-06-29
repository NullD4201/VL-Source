// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ProjectInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/WidgetSwitcher.h"
#include "HomeUI.generated.h"

/**
 * 
 */
UCLASS()
class VCLASS_API UHomeUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCanvasPanel* PanelHome;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCanvasPanel* PanelLibrary;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCanvasPanel* PanelContents;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCanvasPanel* PanelBrowse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetSwitcher* WidgetSwitcherMain;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UButton* ButtonWindowMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UButton* ButtonWindowMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UButton* ButtonWindowClose;

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION()
	void MinimizeWindow();
	
	UFUNCTION()
	void MaximizeWindow();
	
	UFUNCTION()
	void CloseWindow();
};
