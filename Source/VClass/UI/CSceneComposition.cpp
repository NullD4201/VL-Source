// Fill out your copyright notice in the Description page of Project Settings.


#include "CSceneComposition.h"

#include "Blueprint/WidgetTree.h"
#include "Components/ScrollBoxSlot.h"


void UCSceneComposition::NativeConstruct()
{
	Super::NativeConstruct();

	ButtonCategoryMedia = Cast<UButton>(GetWidgetFromName("Category_AddMedia"));
	ButtonCategoryActor = Cast<UButton>(GetWidgetFromName("Category_AddActor"));
	ButtonLiveMode = Cast<UButton>(GetWidgetFromName("LiveMode"));
	ButtonPreviewMode = Cast<UButton>(GetWidgetFromName("PreviewMode"));
	ButtonAddScene = Cast<UButton>(GetWidgetFromName("AddScene"));
	ButtonAddContent = Cast<UButton>(GetWidgetFromName("AddContent"));

	ScrollBoxScenes = Cast<UScrollBox>(GetWidgetFromName("SceneList"));
	ScrollBoxContents = Cast<UScrollBox>(GetWidgetFromName("ContetnsList"));

	ButtonCategoryMedia->OnClicked.AddDynamic(this, &UCSceneComposition::SetCategoryToMedia);
	ButtonCategoryActor->OnClicked.AddDynamic(this, &UCSceneComposition::SetCategoryToActor);
	ButtonLiveMode->OnClicked.AddDynamic(this, &UCSceneComposition::LiveMode);
	ButtonPreviewMode->OnClicked.AddDynamic(this, &UCSceneComposition::PreviewMode);
	ButtonAddScene->OnClicked.AddDynamic(this, &UCSceneComposition::AddScene);
	ButtonAddContent->OnClicked.AddDynamic(this, &UCSceneComposition::AddContent);

	bIsPreviewMode = false;
}

void UCSceneComposition::SetCategoryToMedia()
{
	ButtonCategoryMedia->SetIsEnabled(false);
	ButtonCategoryActor->SetIsEnabled(true);
}

void UCSceneComposition::SetCategoryToActor()
{
	ButtonCategoryMedia->SetIsEnabled(true);
	ButtonCategoryActor->SetIsEnabled(false);
}

void UCSceneComposition::LiveMode()
{
}

void UCSceneComposition::PreviewMode()
{
	bIsPreviewMode = !bIsPreviewMode;
}

void UCSceneComposition::AddScene()
{
	FString SceneName = FString::Format(TEXT("Scene{0}"), { FString::FromInt(SceneCount) });
	ImageScene = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass(), *SceneName);
	SceneList.Add(ImageScene);
	ScrollBoxScenes->InsertChildAt(SceneCount, ImageScene);
	UScrollBoxSlot* ImageSlot = Cast<UScrollBoxSlot>(ImageScene->Slot);
	if (ImageSlot)
	{
		ImageSlot->SetPadding(FMargin(12, 12, 0, 0));
		ImageSlot->SetSize(FSlateChildSize(ESlateSizeRule::Automatic));
		ImageSlot->SetHorizontalAlignment(HAlign_Left);
		ImageSlot->SetVerticalAlignment(VAlign_Top);
	}
	SceneCount++;
	ImageScene = nullptr;
}

void UCSceneComposition::AddContent()
{
}
