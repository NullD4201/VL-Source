// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../ProjectInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "CPanelLiveContents.generated.h"

/**
 * 
 */
UCLASS()
class VCLASS_API UCPanelLiveContents : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonProduct;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonOutside;

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void ClickOutside();
};
