// Fill out your copyright notice in the Description page of Project Settings.


#include "CPanelHome.h"


void UCPanelHome::NativeConstruct()
{
	Super::NativeConstruct();

	ButtonPrev = Cast<UButton>(GetWidgetFromName("PrevButton"));
	ButtonLeft = Cast<UButton>(GetWidgetFromName("LeftButton"));
	ButtonRight = Cast<UButton>(GetWidgetFromName("RightButton"));
	ButtonNext = Cast<UButton>(GetWidgetFromName("NextButton"));

	PanelLibraryMyContents = Cast<UCanvasPanel>(GetWidgetFromName("MyContentsLibraryPanel"));
}

void UCPanelHome::PrevClick()
{
}

void UCPanelHome::LeftClick()
{
}

void UCPanelHome::RightClick()
{
}

void UCPanelHome::NextClick()
{
}
