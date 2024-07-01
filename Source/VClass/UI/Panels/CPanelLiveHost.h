// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/ScrollBox.h"
#include "../Item/MediaLiveItem.h"
#include "CPanelLiveHost.generated.h"

/**
 * 
 */
UCLASS()
class VCLASS_API UCPanelLiveHost : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Media Socket Selector")
	TSubclassOf<class UUserWidget> MediaSocketSelector_OneSided;
	UPROPERTY(EditAnywhere, Category = "Media Socket Selector")
	TSubclassOf<class UUserWidget> MediaSocketSelector_TwoSided;
	UPROPERTY(EditAnywhere, Category = "Media Socket Selector")
	TSubclassOf<class UUserWidget> MediaSocketSelector_Triple;
	UPROPERTY(EditAnywhere, Category = "Media Socket Selector")
	TSubclassOf<class UUserWidget> MediaSocketSelector_OneSided_Long;
	UPROPERTY(EditAnywhere, Category = "Media Socket Selector")
	TSubclassOf<class UUserWidget> MediaSocketSelector_Front_Wide;
	UPROPERTY(EditAnywhere, Category = "Media Socket Selector")
	TSubclassOf<class UUserWidget> MediaSocketSelector_Backward_Full;

	UPROPERTY(EditAnywhere, Category = "Slide Panel")
	TSubclassOf<class UMediaLiveItem> MediaListItem;
	

protected:
	UPROPERTY()
	UCanvasPanel* MotionPanel;
	UPROPERTY()
	UButton* SetSlide;
	UPROPERTY()
	UScrollBox* SlideList;

	UPROPERTY()
	UCanvasPanel* SlidePanel;
	
public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void SetMotionPanelVisibility(bool bIsVisible);

	UFUNCTION()
	void OpenSlideSettingPanel();

	void Init();
};
