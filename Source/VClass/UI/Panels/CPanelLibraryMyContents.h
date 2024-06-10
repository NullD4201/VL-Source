// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../ProjectInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "CPanelLibraryMyContents.generated.h"

/**
 * 
 */
UCLASS()
class VCLASS_API UCPanelLibraryMyContents : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UImage* Image3DPreview;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UImage* ImageProfileBackground;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UImage* ImageProfileForeground;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonMyAccount;

public:
	virtual void NativeConstruct() override;
};
