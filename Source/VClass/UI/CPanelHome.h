// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ProjectInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "CPanelHome.generated.h"

/**
 * 
 */
UCLASS()
class VCLASS_API UCPanelHome : public UUserWidget
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
	UButton* ButtonBrowse;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonPrev;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonLeft;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonRight;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonNext;

public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCanvasPanel* PanelLibraryMyContents;
	
	UFUNCTION()
	void PrevClick();
	
	UFUNCTION()
	void LeftClick();
	
	UFUNCTION()
	void RightClick();
	
	UFUNCTION()
	void NextClick();

	UFUNCTION()
	void SetViewToHome();
	
	UFUNCTION()
	void SetViewToLibrary();
	
	UFUNCTION()
	void SetViewToContents();
	
	UFUNCTION()
	void SetViewToBrowse();
	
};
