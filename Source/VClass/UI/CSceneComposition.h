// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ProjectInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
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
	UScrollBox* ScrollBoxScenes;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UScrollBox* ScrollBoxContents;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UScrollBox* ScrollBoxSceneHighlight;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UScrollBox* ScrollBoxContentHighlight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UImage* ImageUIBackground1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UImage* ImageUIBackground2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UImage* ImageContentsBackground;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UImage* ImageSceneHighlight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UImage* ImageContentHighlight;

private:
	UButton* ImageScene;
	UButton* ImageContent;
	UImage* ImageSceneHighlightDummy;
	UImage* ImageContentHighlightDummy;

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
	void ButtonClickTest();

	UFUNCTION()
	void ButtonClickParam(UButton* Button);

	FScriptDelegate Delegate;
};
