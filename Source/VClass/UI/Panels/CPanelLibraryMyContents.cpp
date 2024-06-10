// Fill out your copyright notice in the Description page of Project Settings.


#include "CPanelLibraryMyContents.h"


void UCPanelLibraryMyContents::NativeConstruct()
{
	Super::NativeConstruct();

	Image3DPreview = Cast<UImage>(GetWidgetFromName("3DPreviewImage"));
	ImageProfileBackground = Cast<UImage>(GetWidgetFromName("ProfileBackground"));
	ImageProfileForeground = Cast<UImage>(GetWidgetFromName("ProfileForeground"));
	
	ButtonMyAccount = Cast<UButton>(GetWidgetFromName("MyAccount"));
}
