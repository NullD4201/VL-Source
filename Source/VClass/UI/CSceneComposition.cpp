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

	ButtonIndex0 = Cast<UButton>(GetWidgetFromName("Button_0"));
	ButtonIndex1 = Cast<UButton>(GetWidgetFromName("Button_1"));
	ButtonIndex2 = Cast<UButton>(GetWidgetFromName("Button_2"));
	ButtonIndex3 = Cast<UButton>(GetWidgetFromName("Button_3"));
	ButtonIndex4 = Cast<UButton>(GetWidgetFromName("Button_4"));
	ButtonIndex5 = Cast<UButton>(GetWidgetFromName("Button_5"));
	ButtonIndex6 = Cast<UButton>(GetWidgetFromName("Button_6"));
	ButtonIndex7 = Cast<UButton>(GetWidgetFromName("Button_7"));
	ButtonIndex8 = Cast<UButton>(GetWidgetFromName("Button_8"));
	ButtonIndex9 = Cast<UButton>(GetWidgetFromName("Button_9"));
	ButtonIndex10 = Cast<UButton>(GetWidgetFromName("Button_10"));

	ScrollBoxScenes = Cast<UScrollBox>(GetWidgetFromName("SceneList"));
	ScrollBoxContents = Cast<UScrollBox>(GetWidgetFromName("ContentsList"));
	ScrollBoxSceneHighlight = Cast<UScrollBox>(GetWidgetFromName("SceneHighlightScroll"));
	ScrollBoxContentHighlight = Cast<UScrollBox>(GetWidgetFromName("ContentHighlightScroll"));

	ImageUIBackground1 = Cast<UImage>(GetWidgetFromName("UIBackground1"));
	ImageUIBackground2 = Cast<UImage>(GetWidgetFromName("UIBackground2"));
	ImageContentsBackground = Cast<UImage>(GetWidgetFromName("ContentsBackground"));
	ImageSceneHighlight = Cast<UImage>(GetWidgetFromName("SceneHighlight"));
	ImageContentHighlight = Cast<UImage>(GetWidgetFromName("ContentHighlight"));

	ButtonCategoryMedia->OnClicked.AddDynamic(this, &UCSceneComposition::SetCategoryToMedia);
	ButtonCategoryActor->OnClicked.AddDynamic(this, &UCSceneComposition::SetCategoryToActor);
	ButtonLiveMode->OnClicked.AddDynamic(this, &UCSceneComposition::LiveMode);
	ButtonPreviewMode->OnClicked.AddDynamic(this, &UCSceneComposition::PreviewMode);
	ButtonAddScene->OnClicked.AddDynamic(this, &UCSceneComposition::AddScene);
	ButtonAddContent->OnClicked.AddDynamic(this, &UCSceneComposition::AddContent);
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

	ScrollBoxSceneHighlight->SetScrollOffset(ScrollBoxScenes->GetScrollOffset());
	ScrollBoxContentHighlight->SetScrollOffset(ScrollBoxContents->GetScrollOffset());
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
			UButton* MediaImage = MediaList[Number];
			ScrollBoxContents->AddChild(MediaImage);

			UScrollBoxSlot* ImageSlot = Cast<UScrollBoxSlot>(MediaImage->Slot);
			if (ImageSlot)
			{
				ImageSlot->SetPadding(FMargin(16, 14, 0, 0));
				ImageSlot->SetSize(FSlateChildSize(ESlateSizeRule::Automatic));
				ImageSlot->SetHorizontalAlignment(HAlign_Left);
				ImageSlot->SetVerticalAlignment(VAlign_Top);
				
				FButtonStyle ButtonStyle;
				ButtonStyle.Normal.SetImageSize(FVector2D(260, 146));
				ButtonStyle.Hovered.SetImageSize(FVector2D(260, 146));
				ButtonStyle.Pressed.SetImageSize(FVector2D(260, 146));
				MediaImage->SetStyle(ButtonStyle);
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
			UButton* ActorImage = ActorList[Number];
			ScrollBoxContents->AddChild(ActorImage);

			UScrollBoxSlot* ImageSlot = Cast<UScrollBoxSlot>(ActorImage->Slot);
			if (ImageSlot)
			{
				ImageSlot->SetPadding(FMargin(16, 14, 0, 0));
				ImageSlot->SetSize(FSlateChildSize(ESlateSizeRule::Automatic));
				ImageSlot->SetHorizontalAlignment(HAlign_Left);
				ImageSlot->SetVerticalAlignment(VAlign_Top);
				
				FButtonStyle ButtonStyle;
				ButtonStyle.Normal.SetImageSize(FVector2D(260, 146));
				ButtonStyle.Hovered.SetImageSize(FVector2D(260, 146));
				ButtonStyle.Pressed.SetImageSize(FVector2D(260, 146));
				ActorImage->SetStyle(ButtonStyle);
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
	
	ImageUIBackground1->SetVisibility(bIsPreviewMode ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
	ImageContentsBackground->SetVisibility(bIsPreviewMode ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
	ScrollBoxContents->SetVisibility(bIsPreviewMode ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
	ButtonCategoryMedia->SetVisibility(bIsPreviewMode ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
	ButtonCategoryActor->SetVisibility(bIsPreviewMode ? ESlateVisibility::Hidden : ESlateVisibility::Visible);

	ButtonAddScene->SetVisibility(bIsPreviewMode ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
}

void UCSceneComposition::AddScene()
{
	ButtonAddScene->RemoveFromParent();
	FString SceneName = FString::Format(TEXT("Scene{0}"), { FString::FromInt(SceneCount) });
	FString SceneHighlightName = FString::Format(TEXT("DSH{0}"), { FString::FromInt(SceneCount) });
	ImageScene = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass(), *SceneName);
	ImageSceneHighlightDummy = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass(), *SceneHighlightName);
	
	ScrollBoxScenes->AddChild(ImageScene);
	ScrollBoxScenes->AddChild(ButtonAddScene);
	UScrollBoxSlot* ImageSlot = Cast<UScrollBoxSlot>(ImageScene->Slot);
	if (ImageSlot)
	{
		ImageSlot->SetPadding(FMargin(12, 12, 0, 0));
		ImageSlot->SetSize(FSlateChildSize(ESlateSizeRule::Automatic));
		ImageSlot->SetHorizontalAlignment(HAlign_Left);
		ImageSlot->SetVerticalAlignment(VAlign_Top);
				
		FButtonStyle ButtonStyle;
		ButtonStyle.Normal.SetImageSize(FVector2D(258, 145));
		ButtonStyle.Hovered.SetImageSize(FVector2D(258, 145));
		ButtonStyle.Pressed.SetImageSize(FVector2D(258, 145));
		ImageScene->SetStyle(ButtonStyle);

		ImageScene->OnClicked.AddDynamic(this, &UCSceneComposition::ButtonClickTest);
	}

	if (SceneCount > 0)
	{
		ScrollBoxSceneHighlight->AddChild(ImageSceneHighlightDummy);
		UScrollBoxSlot* ImageHighlightDummySlot = Cast<UScrollBoxSlot>(ImageSceneHighlightDummy->Slot);
		if (ImageHighlightDummySlot)
		{
			ImageHighlightDummySlot->SetPadding(FMargin(6, 0, 0, 0));
			ImageHighlightDummySlot->SetSize(FSlateChildSize(ESlateSizeRule::Automatic));
			ImageHighlightDummySlot->SetHorizontalAlignment(HAlign_Left);
			ImageHighlightDummySlot->SetVerticalAlignment(VAlign_Top);
			ImageSceneHighlightDummy->SetDesiredSizeOverride(FVector2D(270, 157));
		
			FSlateBrush Brush;
			Brush.DrawAs = ESlateBrushDrawType::RoundedBox;
			Brush.TintColor = FColor::Transparent;
			Brush.OutlineSettings.Color = FLinearColor::Transparent;
			Brush.OutlineSettings.Width = 6.0f;
			Brush.OutlineSettings.RoundingType = ESlateBrushRoundingType::Type::FixedRadius;
			ImageSceneHighlightDummy->SetBrush(Brush);
		}
		
		ImageSceneHighlightDummy = nullptr;
	}
	
	SceneList.Add(ImageScene);
	SceneCount++;

	ScrollBoxScenes->ScrollToEnd();
	ScrollBoxSceneHighlight->SetVisibility(ESlateVisibility::Visible);
}

void UCSceneComposition::AddContent()
{
	ButtonAddContent->RemoveFromParent();
	FString ContentName = FString::Format(TEXT("{0}{1}"), {(CurrentCategory == Media ? "Media" : "Actor"), *FString::FromInt((CurrentCategory == Media ? MediaCount : ActorCount))});
	ImageContent = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass(), *ContentName);
	
	ScrollBoxContents->AddChild(ImageContent);
	ScrollBoxContents->AddChild(ButtonAddContent);
	UScrollBoxSlot* ImageSlot = Cast<UScrollBoxSlot>(ImageContent->Slot);
	if (ImageContent)
	{
		ImageSlot->SetPadding(FMargin(16, 14, 0, 0));
		ImageSlot->SetSize(FSlateChildSize(ESlateSizeRule::Automatic));
		ImageSlot->SetHorizontalAlignment(HAlign_Left);
		ImageSlot->SetVerticalAlignment(VAlign_Top);
				
		FButtonStyle ButtonStyle;
		ButtonStyle.Normal.SetImageSize(FVector2D(260, (CurrentCategory == Media ? 146 : 243)));
		ButtonStyle.Hovered.SetImageSize(FVector2D(260, (CurrentCategory == Media ? 146 : 243)));
		ButtonStyle.Pressed.SetImageSize(FVector2D(260, (CurrentCategory == Media ? 146 : 243)));
		ImageContent->SetStyle(ButtonStyle);
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

void UCSceneComposition::ButtonClickTest()
{
}

void UCSceneComposition::ButtonClickParam(UButton* Button)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, Button->GetName());
}
