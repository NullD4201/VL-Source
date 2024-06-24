// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ProjectInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "EditorModeWidget.generated.h"

/**
 * 
 */
UCLASS()
class VCLASS_API UEditorModeWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonFile;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonHome;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonAnimation;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonRecord;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UButton* ButtonPeople;

public:
	virtual void NativeConstruct() override;
};
