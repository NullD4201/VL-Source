// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../ProjectInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "CPanelMakerSpace.generated.h"

/**
 * 
 */
UCLASS()
class VCLASS_API UCPanelMakerSpace : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonOpenLiveContents;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonContentsHUB;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonNewContents;

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OpenContentsHUB();

	UFUNCTION()
	void OpenLiveContents();

	UFUNCTION()
	void OpenEditorHome();
};
