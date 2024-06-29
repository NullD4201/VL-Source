// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ProjectInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "CPanelBrowse.generated.h"

/**
 * 
 */
UCLASS()
class VCLASS_API UCPanelBrowse : public UUserWidget
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
	UCanvasPanel* PanelVolumeBrowser;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCanvasPanel* PanelGraphicsBrowser;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonBrowseGraphics;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonBrowseVolume;

public:
	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void SetViewToHome();
	
	UFUNCTION()
	void SetViewToLibrary();
	
	UFUNCTION()
	void SetViewToContents();
	
	UFUNCTION()
	void BrowseVolume();
	
	UFUNCTION()
	void BrowseGraphics();
};
