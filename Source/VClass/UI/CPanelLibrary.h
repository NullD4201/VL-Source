// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ProjectInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "CPanelLibrary.generated.h"

/**
 * 
 */
UCLASS()
class VCLASS_API UCPanelLibrary : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UImage* AccountBackgroundImage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* TextureBackground;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonHome;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonContents;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonBrowse;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UImage* Image3DPreview;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonNotification1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonNotification2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonMyContents;

public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UUserWidget* PanelCurrent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UUserWidget* PanelEdit;

	UFUNCTION()
	void SetViewToHome();

	UFUNCTION()
	void SetViewToMyContents();
	
	UFUNCTION()
	void SetViewToContents();
	
	UFUNCTION()
	void SetViewToBrowse();
};
