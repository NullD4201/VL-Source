// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ProjectInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/ComboBoxString.h"
#include "Components/EditableTextBox.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class VCLASS_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	UCheckBox* mCheckHost;
	UCheckBox* mCheckClient;

	UEditableTextBox* mTextBoxAddress;
	UEditableTextBox* mTextBoxPort;

	UComboBoxString* mComboSeatLine;
	UComboBoxString* mComboSeatNumber;

	UButton* mButtonConnect;

	bool bIsHost = true;

	UFUNCTION()
	void ToggleCheckHost(bool bIsChecked);

	UFUNCTION()
	void ToggleCheckClient(bool bIsChecked);

	UFUNCTION()
	void OnClickButtonConnect();

	UFUNCTION()
	void OnAddressTextChanged(const FText& Text);

	UFUNCTION()
	void OnPortTextChanged(const FText& Text);

	UFUNCTION()
	void OnComboSeatLineChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void OnComboSeatNumberChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

private:
	bool bAddress = false;
	bool bPort = false;
	bool bSeatLine = false;
	bool bSeatNum = false;
};
