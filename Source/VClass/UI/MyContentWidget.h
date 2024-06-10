// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ProjectInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "MyContentWidget.generated.h"

/**
 * 
 */
UCLASS()
class VCLASS_API UMyContentWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UImage* ContentThumbnailImage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTextBlock* ContentInfoTitleText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTextBlock* ContentInfoDetailText;

public:
	UFUNCTION()
	void SetThumbnailImage(UTexture2D* Texture);

	UFUNCTION()
	void SetContentTitle(FName Text);

	UFUNCTION()
	void SetContentDetail(FName Text);
};
