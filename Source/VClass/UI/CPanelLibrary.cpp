// Fill out your copyright notice in the Description page of Project Settings.


#include "CPanelLibrary.h"


void UCPanelLibrary::NativeConstruct()
{
	Super::NativeConstruct();

	Image3DPreview = Cast<UImage>(GetWidgetFromName("3DPreviewImage"));

	ButtonNotification1 = Cast<UButton>(GetWidgetFromName("Notification1"));
	ButtonNotification2 = Cast<UButton>(GetWidgetFromName("Notification2"));
	ButtonMyContents = Cast<UButton>(GetWidgetFromName("MyContents"));

	PanelCurrent = Cast<UCanvasPanel>(GetWidgetFromName("CurrentAccountLibraryPanel"));
	PanelEdit = Cast<UCanvasPanel>(GetWidgetFromName("EditAccountLibraryPanel"));
}
