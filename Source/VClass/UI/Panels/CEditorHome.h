// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../ProjectInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/EditableText.h"
#include "Components/ScrollBox.h"
#include "VClass/UI/Item/MediaListItem.h"
#include "CEditorHome.generated.h"

/**
 * 
 */
UCLASS()
class VCLASS_API UCEditorHome : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCanvasPanel* PanelNewMedia;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonAddMedia;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UScrollBox* MediaListScrollBox;

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCanvasPanel* PanelMediaAdd;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonMediaUpload;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UEditableText* EditableTextMediaName;

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCanvasPanel* PanelAlignObject;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCanvasPanel* PanelShadowSetting;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonNewMedia;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonShape;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonAlignObjects;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonSetShadow;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonInteraction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonStageSetting;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonShadowON;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonShadowOFF;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonShadowDetail;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonAlign1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonAlign2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonAlign3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonAlign4;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonAlign5;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonAlign6;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UMediaListItem> MediaBlockClass;

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void SetPanelToNewMedia();
	
	UFUNCTION()
	void SetPanelToAlignObject();
	
	UFUNCTION()
	void SetPanelToShadowSetting();

	UFUNCTION()
	void PopMediaUploadPanel();

	UFUNCTION()
	void UploadMedia();

	UFUNCTION()
	void SetImageAppearModeToOneSided();
	UFUNCTION()
	void SetImageAppearModeToTwoSided();
	UFUNCTION()
	void SetImageAppearModeToTriple();
	UFUNCTION()
	void SetImageAppearModeToOneSidedLong();
	UFUNCTION()
	void SetImageAppearModeToFrontWide();
	UFUNCTION()
	void SetImageAppearModeToBackwardFull();

private:
	UPROPERTY()
	UButton* ActivatedImageButtonMode;
};
