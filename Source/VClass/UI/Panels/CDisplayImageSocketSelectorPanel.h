// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "CDisplayImageSocketSelectorPanel.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSocketDefiniteCallback);

UCLASS()
class VCLASS_API UCDisplayImageSocketSelectorPanel : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct() override;

	UFUNCTION()
	void ImageToIndex0();
	UFUNCTION()
	void ImageToIndex1();
	UFUNCTION()
	void ImageToIndex2();

	FString MediaNameToDisplay;

	FOnSocketDefiniteCallback OnSocketDefinite;
	
protected:
	UPROPERTY(VisibleAnywhere)
	UButton* Index_0;
	UPROPERTY(VisibleAnywhere)
	UButton* Index_1;
	UPROPERTY(VisibleAnywhere)
	UButton* Index_2;
};
