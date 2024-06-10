// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ProjectInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/EditableTextBox.h"
#include "Components/Image.h"
#include "Components/MultiLineEditableTextBox.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "HomeUI.generated.h"

/**
 * 
 */
UCLASS()
class VCLASS_API UHomeUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonHome;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonLibrary;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonContents;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonSettings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCanvasPanel* PanelHome;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCanvasPanel* PanelLibrary;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCanvasPanel* PanelContents;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCanvasPanel* PanelSettings;

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION()
	void SetViewToHome();
	
	UFUNCTION()
	void SetViewToLibrary();
	
	UFUNCTION()
	void SetViewToContents();
	
	UFUNCTION()
	void SetViewToSettings();
};
