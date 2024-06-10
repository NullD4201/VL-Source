// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../ProjectInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "CPanelLibraryCurrentAccount.generated.h"

/**
 * 
 */
UCLASS()
class VCLASS_API UCPanelLibraryCurrentAccount : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UImage* ImageProfileBackground;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UImage* ImageProfileForeground;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonEditProfile;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTextBlock* TextBlockProfileName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTextBlock* TextBlockProfileEmail;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTextBlock* TextBlockAboutMe;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTextBlock* TextBlockAboutDescription;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTextBlock* TextBlockPersonerCode;

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void EditProfile();
};
