// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/EditableText.h>
#include <Components/CheckBox.h>
#include <Components/Button.h>
#include "EntryUI.generated.h"

/**
 * 
 */
UCLASS()
class VCLASS_API UEntryUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UEditableText* addressTextBox;
	UEditableText* portTextBox;
	UEditableText* seatnumTextBox;

	UCheckBox* hostCheckBox;
	UCheckBox* clientCheckBox;

	UButton* entryButton;

	bool isHost = false;
	
	UFUNCTION()
	void ToggleHostCheckBox(bool bIsChecked);

	UFUNCTION()
	void ToggleClientCheckBox(bool bIsChecked);

	UFUNCTION()
	void OnClickEntryButton();
};
