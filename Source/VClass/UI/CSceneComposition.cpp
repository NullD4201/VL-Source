// Fill out your copyright notice in the Description page of Project Settings.


#include "CSceneComposition.h"

#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/ScrollBoxSlot.h"
#include "Misc/DefaultValueHelper.h"
#include "VClass/Data/VClassSaveGame.h"


void UCSceneComposition::NativeConstruct()
{
	Super::NativeConstruct();

	ButtonCategoryMedia = Cast<UButton>(GetWidgetFromName("Category_AddMedia"));
	ButtonCategoryActor = Cast<UButton>(GetWidgetFromName("Category_AddActor"));
	ButtonLiveMode = Cast<UButton>(GetWidgetFromName("LiveMode"));
	ButtonPreviewMode = Cast<UButton>(GetWidgetFromName("PreviewMode"));
	ButtonAddScene = Cast<UButton>(GetWidgetFromName("AddScene"));
	ButtonAddContent = Cast<UButton>(GetWidgetFromName("AddContent"));

	ButtonIndex0 = Cast<UButton>(GetWidgetFromName("Index0"));
	ButtonIndex1 = Cast<UButton>(GetWidgetFromName("Index1"));
	ButtonIndex2 = Cast<UButton>(GetWidgetFromName("Index2"));
	ButtonIndex3 = Cast<UButton>(GetWidgetFromName("Index3"));
	ButtonIndex4 = Cast<UButton>(GetWidgetFromName("Index4"));
	ButtonIndex5 = Cast<UButton>(GetWidgetFromName("Index5"));
	ButtonIndex6 = Cast<UButton>(GetWidgetFromName("Index6"));
	ButtonIndex7 = Cast<UButton>(GetWidgetFromName("Index7"));
	ButtonIndex8 = Cast<UButton>(GetWidgetFromName("Index8"));
	ButtonIndex9 = Cast<UButton>(GetWidgetFromName("Index9"));
	ButtonIndex10 = Cast<UButton>(GetWidgetFromName("Index10"));

	ButtonMedia1 = Cast<UButton>(GetWidgetFromName("BrowserMedia1"));
	ButtonMedia2 = Cast<UButton>(GetWidgetFromName("BrowserMedia2"));
	ButtonMedia3 = Cast<UButton>(GetWidgetFromName("BrowserMedia3"));
	ButtonMedia4 = Cast<UButton>(GetWidgetFromName("BrowserMedia4"));
	ButtonMedia5 = Cast<UButton>(GetWidgetFromName("BrowserMedia5"));
	ButtonMedia6 = Cast<UButton>(GetWidgetFromName("BrowserMedia6"));
	ButtonMedia7 = Cast<UButton>(GetWidgetFromName("BrowserMedia7"));
	ButtonMedia8 = Cast<UButton>(GetWidgetFromName("BrowserMedia8"));
	ButtonMedia9 = Cast<UButton>(GetWidgetFromName("BrowserMedia9"));
	ButtonMedia10 = Cast<UButton>(GetWidgetFromName("BrowserMedia10"));
	ButtonMedia11 = Cast<UButton>(GetWidgetFromName("BrowserMedia11"));

	ScrollBoxScenes = Cast<UScrollBox>(GetWidgetFromName("SceneList"));
	ScrollBoxContents = Cast<UScrollBox>(GetWidgetFromName("ContentsList"));
	ScrollBoxSceneHighlight = Cast<UScrollBox>(GetWidgetFromName("SceneHighlightScroll"));
	ScrollBoxMediaHighlight = Cast<UScrollBox>(GetWidgetFromName("MediaHighlightScroll"));
	ScrollBoxActorHighlight = Cast<UScrollBox>(GetWidgetFromName("ActorHighlightScroll"));

	ImageUIBackground1 = Cast<UImage>(GetWidgetFromName("UIBackground1"));
	ImageUIBackground2 = Cast<UImage>(GetWidgetFromName("UIBackground2"));
	ImageContentsBackground = Cast<UImage>(GetWidgetFromName("ContentsBackground"));

	CanvasPanelIndex = Cast<UCanvasPanel>(GetWidgetFromName("IndexPanel"));
	CanvasPanelContentsBrowserMedia = Cast<UCanvasPanel>(GetWidgetFromName("ContentsBrowserMedia"));

	ButtonCategoryMedia->OnClicked.AddDynamic(this, &UCSceneComposition::SetCategoryToMedia);
	ButtonCategoryActor->OnClicked.AddDynamic(this, &UCSceneComposition::SetCategoryToActor);
	ButtonLiveMode->OnClicked.AddDynamic(this, &UCSceneComposition::LiveMode);
	ButtonPreviewMode->OnClicked.AddDynamic(this, &UCSceneComposition::PreviewMode);
	ButtonAddScene->OnClicked.AddDynamic(this, &UCSceneComposition::AddScene);
	ButtonAddContent->OnClicked.AddDynamic(this, &UCSceneComposition::AddContent);

	ButtonIndex0->OnClicked.AddDynamic(this, &UCSceneComposition::SetIndexButtonContent);
	ButtonIndex1->OnClicked.AddDynamic(this, &UCSceneComposition::SetIndexButtonContent);
	ButtonIndex2->OnClicked.AddDynamic(this, &UCSceneComposition::SetIndexButtonContent);
	ButtonIndex3->OnClicked.AddDynamic(this, &UCSceneComposition::SetIndexButtonContent);
	ButtonIndex4->OnClicked.AddDynamic(this, &UCSceneComposition::SetIndexButtonContent);
	ButtonIndex5->OnClicked.AddDynamic(this, &UCSceneComposition::SetIndexButtonContent);
	ButtonIndex6->OnClicked.AddDynamic(this, &UCSceneComposition::SetIndexButtonContent);
	ButtonIndex7->OnClicked.AddDynamic(this, &UCSceneComposition::SetIndexButtonContent);
	ButtonIndex8->OnClicked.AddDynamic(this, &UCSceneComposition::SetIndexButtonContent);
	ButtonIndex9->OnClicked.AddDynamic(this, &UCSceneComposition::SetIndexButtonContent);
	ButtonIndex10->OnClicked.AddDynamic(this, &UCSceneComposition::SetIndexButtonContent);

	ButtonMedia1->OnClicked.AddDynamic(this, &UCSceneComposition::AddMedia);
	ButtonMedia2->OnClicked.AddDynamic(this, &UCSceneComposition::AddMedia);
	ButtonMedia3->OnClicked.AddDynamic(this, &UCSceneComposition::AddMedia);
	ButtonMedia4->OnClicked.AddDynamic(this, &UCSceneComposition::AddMedia);
	ButtonMedia5->OnClicked.AddDynamic(this, &UCSceneComposition::AddMedia);
	ButtonMedia6->OnClicked.AddDynamic(this, &UCSceneComposition::AddMedia);
	ButtonMedia7->OnClicked.AddDynamic(this, &UCSceneComposition::AddMedia);
	ButtonMedia8->OnClicked.AddDynamic(this, &UCSceneComposition::AddMedia);
	ButtonMedia9->OnClicked.AddDynamic(this, &UCSceneComposition::AddMedia);
	ButtonMedia10->OnClicked.AddDynamic(this, &UCSceneComposition::AddMedia);
	ButtonMedia11->OnClicked.AddDynamic(this, &UCSceneComposition::AddMedia);

	CanvasPanelContentsBrowserMedia->SetVisibility(ESlateVisibility::Hidden);
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

		FButtonStyle ButtonStyle = ButtonAddScene->GetStyle();
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

		FButtonStyle ButtonStyle = ButtonAddContent->GetStyle();
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

	UCanvasPanelSlot* ScrollBoxActorSlot = Cast<UCanvasPanelSlot>(ScrollBoxActorHighlight->Slot);
	if (ScrollBoxActorSlot)
	{
		ScrollBoxActorSlot->SetPosition(FVector2D(32, (CurrentCategory == Media ? 859 : 761)));
		ScrollBoxActorSlot->SetSize(FVector2D(1498, (CurrentCategory == Media ? 190 : 288)));
	}

	ScrollBoxSceneHighlight->SetScrollOffset(ScrollBoxScenes->GetScrollOffset());
	ScrollBoxMediaHighlight->SetScrollOffset(ScrollBoxContents->GetScrollOffset());
	ScrollBoxActorHighlight->SetScrollOffset(ScrollBoxContents->GetScrollOffset());
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
				
				FButtonStyle ButtonStyle = MediaImage->GetStyle();
				ButtonStyle.Normal.SetImageSize(FVector2D(260, 146));
				ButtonStyle.Hovered.SetImageSize(FVector2D(260, 146));
				ButtonStyle.Pressed.SetImageSize(FVector2D(260, 146));
				MediaImage->SetStyle(ButtonStyle);
			}

			MediaImage = nullptr;
		}
	}
	ScrollBoxContents->AddChild(ButtonAddContent);

	ScrollBoxMediaHighlight->SetVisibility(ESlateVisibility::Visible);
	ScrollBoxActorHighlight->SetVisibility(ESlateVisibility::Hidden);
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
				ButtonStyle.Normal.SetImageSize(FVector2D(260, 243));
				ButtonStyle.Hovered.SetImageSize(FVector2D(260, 243));
				ButtonStyle.Pressed.SetImageSize(FVector2D(260, 243));
				ActorImage->SetStyle(ButtonStyle);
			}

			ActorImage = nullptr;
		}
	}
	ScrollBoxContents->AddChild(ButtonAddContent);

	ScrollBoxMediaHighlight->SetVisibility(ESlateVisibility::Hidden);
	ScrollBoxActorHighlight->SetVisibility(ESlateVisibility::Visible);
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
	FString SceneHighlightName = "Dummy" + SceneName;
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

		ImageScene->SetCursor(EMouseCursor::Type::Hand);

		ImageScene->OnClicked.AddDynamic(this, &UCSceneComposition::FocusToScene);
	}

	if (SceneCount >= 0)
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
	ImageScene = nullptr;

	ScrollBoxScenes->ScrollToEnd();
}

void UCSceneComposition::AddContent()
{
	ButtonAddContent->RemoveFromParent();
	FString ContentName = FString::Format(TEXT("{0}{1}"), {(CurrentCategory == Media ? "Media" : "Actor"), *FString::FromInt((CurrentCategory == Media ? MediaCount : ActorCount))});
	FString ContentHighlightName = "Dummy" + ContentName;
	ImageContent = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass(), *ContentName);
	_Name = ContentHighlightName;
	
	ScrollBoxContents->AddChild(ImageContent);
	ScrollBoxContents->AddChild(ButtonAddContent);
	UScrollBoxSlot* ImageSlot = Cast<UScrollBoxSlot>(ImageContent->Slot);
	if (ImageSlot)
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

		FWidgetTransform ImageRenderTransform = ImageContent->GetRenderTransform();
		ImageRenderTransform.Scale = FVector2D(1, -1);
		ImageContent->SetRenderTransform(ImageRenderTransform);

		ImageContent->SetCursor(EMouseCursor::Type::Hand);

		ImageContent->OnClicked.AddDynamic(this, &UCSceneComposition::FocusToContent);
	}
	
	if (CurrentCategory == Media)
	{
		ImageMediaHighlightDummy = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass(), *ContentHighlightName);
		if (MediaCount >= 0)
		{
			ScrollBoxMediaHighlight->AddChild(ImageMediaHighlightDummy);
			UScrollBoxSlot* ImageHighlightDummySlot = Cast<UScrollBoxSlot>(ImageMediaHighlightDummy->Slot);
			if (ImageHighlightDummySlot)
			{
				ImageHighlightDummySlot->SetPadding(FMargin(4, 8, 0, 0));
				ImageHighlightDummySlot->SetSize(FSlateChildSize(ESlateSizeRule::Automatic));
				ImageHighlightDummySlot->SetHorizontalAlignment(HAlign_Left);
				ImageHighlightDummySlot->SetVerticalAlignment(VAlign_Top);
				ImageMediaHighlightDummy->SetDesiredSizeOverride(FVector2D(272, 158));
		
				FSlateBrush Brush = ImageMediaHighlightDummy->GetBrush();
				Brush.DrawAs = ESlateBrushDrawType::RoundedBox;
				Brush.TintColor = FColor::Transparent;
				Brush.OutlineSettings.Color = FLinearColor::Transparent;
				Brush.OutlineSettings.Width = 6.0f;
				Brush.OutlineSettings.RoundingType = ESlateBrushRoundingType::Type::FixedRadius;
				ImageMediaHighlightDummy->SetBrush(Brush);
			}
		}

		CanvasPanelContentsBrowserMedia->SetVisibility(ESlateVisibility::Visible);
		
		MediaList.Add(ImageContent);
		MediaCount++;
		
		ImageMediaHighlightDummy = nullptr;

		ScrollBoxMediaHighlight->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		ImageActorHighlightDummy = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass(), *ContentHighlightName);
		if (ActorCount >= 0)
		{
			ScrollBoxActorHighlight->AddChild(ImageActorHighlightDummy);
			UScrollBoxSlot* ImageHighlightDummySlot = Cast<UScrollBoxSlot>(ImageActorHighlightDummy->Slot);
			if (ImageHighlightDummySlot)
			{
				ImageHighlightDummySlot->SetPadding(FMargin(4, 8, 0, 0));
				ImageHighlightDummySlot->SetSize(FSlateChildSize(ESlateSizeRule::Automatic));
				ImageHighlightDummySlot->SetHorizontalAlignment(HAlign_Left);
				ImageHighlightDummySlot->SetVerticalAlignment(VAlign_Top);
				ImageActorHighlightDummy->SetDesiredSizeOverride(FVector2D(272, 255));
		
				FSlateBrush Brush = ImageActorHighlightDummy->GetBrush();
				Brush.DrawAs = ESlateBrushDrawType::RoundedBox;
				Brush.TintColor = FColor::Transparent;
				Brush.OutlineSettings.Color = FLinearColor::Transparent;
				Brush.OutlineSettings.Width = 6.0f;
				Brush.OutlineSettings.RoundingType = ESlateBrushRoundingType::Type::FixedRadius;
				ImageActorHighlightDummy->SetBrush(Brush);
			}
		}
		
		ActorList.Add(ImageContent);
		ActorCount++;
		
		ImageActorHighlightDummy = nullptr;
	
		ScrollBoxActorHighlight->SetVisibility(ESlateVisibility::Visible);
	}
	ImageContent = nullptr;

	ScrollBoxContents->ScrollToEnd();
}

void UCSceneComposition::FocusToScene()
{
	CanvasPanelIndex->SetVisibility(ESlateVisibility::Visible);

	TArray<UWidget*> Widgets;
	WidgetTree->GetAllWidgets(Widgets);
	FString SceneName = "";
	for (UWidget* Widget : Widgets)
	{
		if (Widget && Widget->HasUserFocus(GetOwningPlayer()))
		{
			SceneName = Widget->GetName();
		}
	}

	UVClassSaveGame* SaveGame = Cast<UVClassSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Main"),0));

	TArray<FString> StringArray;
	for (FString String : SaveGame->SceneContentList)
	{
		String.ParseIntoArray(StringArray, TEXT(","), true);
		FString RefString = StringArray[1];
		int MediaIndex;
		FDefaultValueHelper::ParseInt(StringArray[2], MediaIndex);
	}
	
	int IndexNumberCount = 0;
	for (UWidget* Widget : CanvasPanelIndex->GetAllChildren())
	{
		UButton* Button = Cast<UButton>(Widget);
		if (Button)
		{
			if (Button->GetStyle().Normal.GetResourceObject())
			{
				FString AddressName = Button->GetStyle().Normal.GetResourceObject()->GetPathName();
				SaveGame->SceneContentList.Add("M," + AddressName + "," + FString::FromInt(IndexNumberCount));
			}
			
			IndexNumberCount++;
		}
	}

	for (int i = 0; i < SaveGame->SceneContentList.Num(); i++)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Blue, SaveGame->SceneContentList[i]);
	}

	ResetIndexPanel();

	if (SceneName != "")
	{
		for (UWidget* Widget : Widgets)
		{
			if (Widget->GetName().Contains("DummyScene"))
			{
				UImage* Image = Cast<UImage>(Widget);
				FSlateBrush Brush = Image->GetBrush();
				Brush.DrawAs = ESlateBrushDrawType::RoundedBox;
				Brush.TintColor = FColor::Transparent;
				if (Widget->GetName() == "Dummy" + SceneName)
					Brush.OutlineSettings.Color = FColor::Green;
				else
					Brush.OutlineSettings.Color = FColor::Transparent;
				Brush.OutlineSettings.Width = 6.0f;
				Brush.OutlineSettings.RoundingType = ESlateBrushRoundingType::Type::FixedRadius;
				Image->SetBrush(Brush);
			}
		}
	}
}

void UCSceneComposition::FocusToContent()
{
	TArray<UWidget*> Widgets;
	WidgetTree->GetAllWidgets(Widgets);
	FString ContentName = "";
	for (UWidget* Widget : Widgets)
	{
		if (Widget && Widget->HasUserFocus(GetOwningPlayer()))
		{
			ContentName = Widget->GetName();
			UButton* Button = Cast<UButton>(Widget);
			CurrentContent = Button->GetStyle().Normal;
		}
	}

	if (ContentName != "")
	{
		for (UWidget* Widget : Widgets)
		{
			if (Widget->GetName().Contains("DummyMedia") || Widget->GetName().Contains("DummyActor"))
			{
				UImage* Image = Cast<UImage>(Widget);
				FSlateBrush Brush = Image->GetBrush();
				Brush.TintColor = FColor::Transparent;
				if (Widget->GetName() == "Dummy" + ContentName)
					Brush.OutlineSettings.Color = FLinearColor::Green;
				else
					Brush.OutlineSettings.Color = FLinearColor::Transparent;
				Brush.OutlineSettings.Width = 6.0f;
				Brush.OutlineSettings.RoundingType = ESlateBrushRoundingType::Type::FixedRadius;
				Image->SetBrush(Brush);
			}
		}
	}
}

void UCSceneComposition::SetButtonTexture(UButton* Button, UTexture* Texture)
{
	if (Button && Texture)
	{
		// Create a new brush and set the texture
		FSlateBrush Brush;
		Brush.SetResourceObject(Texture);

		// Assuming the button's appearance is modified through its style
		FButtonStyle ButtonStyle = Button->GetStyle();
		ButtonStyle.SetNormal(Brush);
		ButtonStyle.SetHovered(Brush);
		ButtonStyle.SetPressed(Brush);

		Button->SetStyle(ButtonStyle);
	}
}

void UCSceneComposition::ResetIndexPanel()
{
	for (UWidget* Widget : CanvasPanelIndex->GetAllChildren())
	{
		UButton* Button = Cast<UButton>(Widget);
		if (Button)
		{
			FButtonStyle ButtonStyle;
			ButtonStyle.Normal.SetResourceObject(nullptr);
			ButtonStyle.Pressed.SetResourceObject(nullptr);
			ButtonStyle.Hovered.SetResourceObject(nullptr);
			Button->SetStyle(ButtonStyle);
		}
	}
}

void UCSceneComposition::SetIndexButtonContent()
{
	TArray<UWidget*> Widgets;
	WidgetTree->GetAllWidgets(Widgets);
	for (UWidget* Widget : Widgets)
	{
		if (Widget && Widget->HasUserFocus(GetOwningPlayer()))
		{
			UButton* Button = Cast<UButton>(Widget);

			if (Button && CurrentContent.GetResourceObject() != nullptr)
			{
				FButtonStyle ButtonStyle = Button->GetStyle();
				ButtonStyle.SetNormal(CurrentContent);
				ButtonStyle.SetHovered(CurrentContent);
				ButtonStyle.SetPressed(CurrentContent);
				Button->SetStyle(ButtonStyle);
			}
		}
	}
}

void UCSceneComposition::AddMedia()
{
	TArray<UWidget*> Widgets;
	WidgetTree->GetAllWidgets(Widgets);
	for (UWidget* Widget : Widgets)
	{
		if (Widget && Widget->HasUserFocus(GetOwningPlayer()))
		{
			UButton* Button = Cast<UButton>(Widget);
			UButton* ContentButton = Cast<UButton>(GetWidgetFromName(FName(_Name.Replace(TEXT("Dummy"), TEXT("")))));

			if (ContentButton)
			{
				FButtonStyle ButtonStyle = ContentButton->GetStyle();
				ButtonStyle.SetNormal(Button->GetStyle().Normal);
				ButtonStyle.SetHovered(Button->GetStyle().Normal);
				ButtonStyle.SetPressed(Button->GetStyle().Normal);
				ContentButton->SetStyle(ButtonStyle);
			}
		}
	}

	CanvasPanelContentsBrowserMedia->SetVisibility(ESlateVisibility::Hidden);
}
