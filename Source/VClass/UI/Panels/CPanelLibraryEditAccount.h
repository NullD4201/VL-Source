// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../ProjectInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/Image.h"
#include "CPanelLibraryEditAccount.generated.h"

/**
 * 
 */
UCLASS()
class VCLASS_API UCPanelLibraryEditAccount : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UImage* ImageProfileBackground;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UImage* ImageProfileForeground;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UEditableTextBox* TextBoxFirstName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UEditableTextBox* TextBoxLastName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UEditableTextBox* TextBoxEmail;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UEditableTextBox* TextBoxMessage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonSubmit;

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void Sumbit();
};
