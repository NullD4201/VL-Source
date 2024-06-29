// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ProjectInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "CPanelContents.generated.h"

/**
 * 
 */
UCLASS()
class VCLASS_API UCPanelContents : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonHome;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonLibrary;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonBrowse;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonOpenLiveContents;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonMakerSpace;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UUserWidget* WidgetLiveContents;

public:
	UFUNCTION()
	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void SetViewToHome();
	
	UFUNCTION()
	void SetViewToLibrary();
	
	UFUNCTION()
	void SetViewToBrowse();

	UFUNCTION()
	void OpenLiveContents();

	UFUNCTION()
	void OpenMakerSpace();
};
