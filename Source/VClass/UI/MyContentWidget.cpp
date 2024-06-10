// Fill out your copyright notice in the Description page of Project Settings.


#include "MyContentWidget.h"


void UMyContentWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ContentThumbnailImage = Cast<UImage>(GetWidgetFromName("ContentThumbnail"));
	ContentInfoTitleText = Cast<UTextBlock>(GetWidgetFromName("ContentInfoTitle"));
	ContentInfoDetailText = Cast<UTextBlock>(GetWidgetFromName("ContentInfoDetail"));

	this->SetCursor(EMouseCursor::Type::Hand);
}

void UMyContentWidget::SetThumbnailImage(UTexture2D* Texture)
{
	ContentThumbnailImage->SetBrushFromTexture(Texture);
}

void UMyContentWidget::SetContentTitle(FName Text)
{
	ContentInfoTitleText->SetText(FText::FromName(Text));
}

void UMyContentWidget::SetContentDetail(FName Text)
{
	ContentInfoDetailText->SetText(FText::FromName(Text));
}
