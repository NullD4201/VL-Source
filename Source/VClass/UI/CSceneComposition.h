// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ProjectInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/ScrollBox.h"
#include "CSceneComposition.generated.h"

/**
 * 
 */
UCLASS()
class VCLASS_API UCSceneComposition : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonCategoryMedia;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonCategoryActor;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonLiveMode;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonPreviewMode;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonAddScene;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonAddContent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonIndex0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonIndex1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonIndex2;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonIndex3;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonIndex4;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonIndex5;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonIndex6;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonIndex7;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonIndex8;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonIndex9;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonIndex10;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonMedia1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonMedia2;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonMedia3;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonMedia4;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonMedia5;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonMedia6;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonMedia7;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonMedia8;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonMedia9;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonMedia10;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonMedia11;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UScrollBox* ScrollBoxScenes;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UScrollBox* ScrollBoxContents;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UScrollBox* ScrollBoxSceneHighlight;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UScrollBox* ScrollBoxMediaHighlight;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UScrollBox* ScrollBoxActorHighlight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UImage* ImageUIBackground1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UImage* ImageUIBackground2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UImage* ImageContentsBackground;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCanvasPanel* CanvasPanelIndex;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCanvasPanel* CanvasPanelContentsBrowserMedia;

private:
	UButton* ImageScene;
	UButton* ImageContent;
	UImage* ImageSceneHighlightDummy;
	UImage* ImageMediaHighlightDummy;
	UImage* ImageActorHighlightDummy;

	FString _Name;

	TArray<UButton*> SceneList;
	TArray<UButton*> MediaList;
	TArray<UButton*> ActorList;

	bool bIsPreviewMode = false;

	int SceneCount = 0;
	int MediaCount = 0;
	int ActorCount = 0;

	enum CurrentContentCategory
	{
		Media,
		Actor,
	};

public:
	CurrentContentCategory CurrentCategory = Media;

	FSlateBrush CurrentContent;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	UFUNCTION()
	void SetCategoryToMedia(); 
	
	UFUNCTION()
	void SetCategoryToActor();

	UFUNCTION()
	void LiveMode();

	UFUNCTION()
	void PreviewMode();

	UFUNCTION()
	void AddScene();

	UFUNCTION()
	void AddContent();

	UFUNCTION()
	void FocusToScene();

	UFUNCTION()
	void FocusToContent();

	UFUNCTION()
	void SetButtonTexture(UButton* Button, UTexture* Texture);

	UFUNCTION()
	void ResetIndexPanel();

	UFUNCTION()
	void SetIndexButtonContent();

	UFUNCTION()
	void AddMedia();

	FScriptDelegate Delegate;
};
