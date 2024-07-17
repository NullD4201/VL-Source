// Fill out your copyright notice in the Description page of Project Settings.


#include "CSceneComposition.h"

#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanelSlot.h"
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
	ScrollBoxContents = Cast<UScrollBox>(GetWidgetFromName("ContentsList"));

	ButtonCategoryMedia->OnClicked.AddDynamic(this, &UCSceneComposition::SetCategoryToMedia);
	ButtonCategoryActor->OnClicked.AddDynamic(this, &UCSceneComposition::SetCategoryToActor);
	ButtonLiveMode->OnClicked.AddDynamic(this, &UCSceneComposition::LiveMode);
	ButtonPreviewMode->OnClicked.AddDynamic(this, &UCSceneComposition::PreviewMode);
	ButtonAddScene->OnClicked.AddDynamic(this, &UCSceneComposition::AddScene);
	ButtonAddContent->OnClicked.AddDynamic(this, &UCSceneComposition::AddContent);

	bIsPreviewMode = false;
}

void UCSceneComposition::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	UScrollBoxSlot* _SceneSlot = Cast<UScrollBoxSlot>(ButtonAddScene->Slot);
	if (_SceneSlot)
	{
		_SceneSlot->SetPadding(FMargin(12, 12, 0, 0));
		_SceneSlot->SetSize(FSlateChildSize(ESlateSizeRule::Automatic));
		_SceneSlot->SetHorizontalAlignment(HAlign_Left);
		_SceneSlot->SetVerticalAlignment(VAlign_Top);

		FButtonStyle ButtonStyle;
		ButtonStyle.Normal.SetImageSize(FVector2D(258, 145));
		ButtonStyle.Hovered.SetImageSize(FVector2D(258, 145));
		ButtonStyle.Pressed.SetImageSize(FVector2D(258, 145));
		ButtonAddScene->SetStyle(ButtonStyle);
	}

	UScrollBoxSlot* _ContentButtonSlot = Cast<UScrollBoxSlot>(ButtonAddContent->Slot);
	if (_ContentButtonSlot)
	{
		_ContentButtonSlot->SetPadding(FMargin(16, 14, 0, 0));
		_ContentButtonSlot->SetSize(FSlateChildSize(ESlateSizeRule::Automatic));
		_ContentButtonSlot->SetHorizontalAlignment(HAlign_Left);
		_ContentButtonSlot->SetVerticalAlignment(VAlign_Top);

		FButtonStyle ButtonStyle;
		ButtonStyle.Normal.SetImageSize(FVector2D(260, (CurrentCategory == Media ? 146 : 243)));
		ButtonStyle.Hovered.SetImageSize(FVector2D(260, (CurrentCategory == Media ? 146 : 243)));
		ButtonStyle.Pressed.SetImageSize(FVector2D(260, (CurrentCategory == Media ? 146 : 243)));
		ButtonAddContent->SetStyle(ButtonStyle);
	}

	UCanvasPanelSlot* ScrollBoxContentsSlot = Cast<UCanvasPanelSlot>(ScrollBoxContents->Slot);
	if (ScrollBoxContentsSlot)
	{
		ScrollBoxContentsSlot->SetPosition(FVector2D(32, (CurrentCategory == Media ? 859 : 761)));
		ScrollBoxContentsSlot->SetSize(FVector2D(1498, (CurrentCategory == Media ? 190 : 288)));
	}
}

void UCSceneComposition::SetCategoryToMedia()
{
	ButtonCategoryMedia->SetIsEnabled(false);
	ButtonCategoryActor->SetIsEnabled(true);

	CurrentCategory = Media;

	ScrollBoxContents->ClearChildren();

	if (MediaList.Num() > 0)
	{
		ButtonAddContent->RemoveFromParent();
		for (int Number = 0; Number < MediaList.Num(); Number++)
		{
			UImage* MediaImage = MediaList[Number];
			ScrollBoxContents->AddChild(MediaImage);

			UScrollBoxSlot* ImageSlot = Cast<UScrollBoxSlot>(MediaImage->Slot);
			if (ImageSlot)
			{
				ImageSlot->SetPadding(FMargin(16, 14, 0, 0));
				ImageSlot->SetSize(FSlateChildSize(ESlateSizeRule::Automatic));
				ImageSlot->SetHorizontalAlignment(HAlign_Left);
				ImageSlot->SetVerticalAlignment(VAlign_Top);
				MediaImage->SetDesiredSizeOverride(FVector2D(260, 146));
			}

			MediaImage = nullptr;
		}
	}
	ScrollBoxContents->AddChild(ButtonAddContent);
}

void UCSceneComposition::SetCategoryToActor()
{
	ButtonCategoryMedia->SetIsEnabled(true);
	ButtonCategoryActor->SetIsEnabled(false);

	CurrentCategory = Actor;

	ScrollBoxContents->ClearChildren();

	if (ActorList.Num() > 0)
	{
		ButtonAddContent->RemoveFromParent();
		for (int Number = 0; Number < ActorList.Num(); Number++)
		{
			UImage* ActorImage = ActorList[Number];
			ScrollBoxContents->AddChild(ActorImage);

			UScrollBoxSlot* ImageSlot = Cast<UScrollBoxSlot>(ActorImage->Slot);
			if (ImageSlot)
			{
				ImageSlot->SetPadding(FMargin(16, 14, 0, 0));
				ImageSlot->SetSize(FSlateChildSize(ESlateSizeRule::Automatic));
				ImageSlot->SetHorizontalAlignment(HAlign_Left);
				ImageSlot->SetVerticalAlignment(VAlign_Top);
				ActorImage->SetDesiredSizeOverride(FVector2D(260, 243));
			}

			ActorImage = nullptr;
		}
	}
	ScrollBoxContents->AddChild(ButtonAddContent);
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
	ButtonAddScene->RemoveFromParent();
	FString SceneName = FString::Format(TEXT("Scene{0}"), { FString::FromInt(SceneCount) });
	ImageScene = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass(), *SceneName);
	
	ScrollBoxScenes->AddChild(ImageScene);
	ScrollBoxScenes->AddChild(ButtonAddScene);
	UScrollBoxSlot* ImageSlot = Cast<UScrollBoxSlot>(ImageScene->Slot);
	if (ImageSlot)
	{
		ImageSlot->SetPadding(FMargin(12, 12, 0, 0));
		ImageSlot->SetSize(FSlateChildSize(ESlateSizeRule::Automatic));
		ImageSlot->SetHorizontalAlignment(HAlign_Left);
		ImageSlot->SetVerticalAlignment(VAlign_Top);
		ImageScene->SetDesiredSizeOverride(FVector2D(258, 145));
	}
	SceneList.Add(ImageScene);
	SceneCount++;
	ImageScene = nullptr;

	ScrollBoxScenes->ScrollToEnd();
}

void UCSceneComposition::AddContent()
{
	ButtonAddContent->RemoveFromParent();
	FString ContentName = FString::Format(TEXT("{0}{1}"), {(CurrentCategory == Media ? "Media" : "Actor"), *FString::FromInt((CurrentCategory == Media ? MediaCount : ActorCount))});
	ImageContent = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass(), *ContentName);
	
	ScrollBoxContents->AddChild(ImageContent);
	ScrollBoxContents->AddChild(ButtonAddContent);
	UScrollBoxSlot* ImageSlot = Cast<UScrollBoxSlot>(ImageContent->Slot);
	if (ImageContent)
	{
		ImageSlot->SetPadding(FMargin(16, 14, 0, 0));
		ImageSlot->SetSize(FSlateChildSize(ESlateSizeRule::Automatic));
		ImageSlot->SetHorizontalAlignment(HAlign_Left);
		ImageSlot->SetVerticalAlignment(VAlign_Top);
		ImageContent->SetDesiredSizeOverride(FVector2D(260, (CurrentCategory == Media ? 146 : 243)));
	}	
	if (CurrentCategory == Media)
	{
		MediaList.Add(ImageContent);
		MediaCount++;
	}
	else
	{
		ActorList.Add(ImageContent);
		ActorCount++;
	}
	ImageContent = nullptr;

	ScrollBoxContents->ScrollToEnd();
}
