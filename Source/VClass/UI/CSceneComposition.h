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
	UScrollBox* ScrollBoxScenes;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UScrollBox* ScrollBoxContents;

private:
	UImage* ImageScene;
	UImage* ImageContent;

	TArray<UImage*> SceneList;
	TArray<UImage*> MediaList;
	TArray<UImage*> ActorList;

	bool bIsPreviewMode;

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
};
