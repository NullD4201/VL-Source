// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Image.h>
#include "HostUIWidget.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class HostUIState : uint8 {
	HOST_PLAIN UMETA(DisplayName = "Plain"),
	HOST_GENERATEOBJ UMETA(DisplayName = "Generate Object Mode")
};

UCLASS()
class VCLASS_API UHostUIWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	HostUIState CurrentState;

	UFUNCTION(BlueprintCallable)
	void SetHostState(HostUIState newState);

	UFUNCTION(BlueprintCallable)
	void GetMouseToWidgetOffset(float& offsetLeft, float& offsetTop, float& offsetRight, float& offsetBottom);

	UFUNCTION(BlueprintCallable)
	void StartObjGeneration();

	UFUNCTION(BlueprintCallable)
	void EndObjGeneration();

public:
	UPROPERTY(BlueprintReadOnly)
	UImage* selectionImg;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> spawningActorClass;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OBJ_GENERATING_DISTANCE = 200.0f;

	UPROPERTY(BlueprintReadWrite)
	FVector2D dragStartPos;

	UPROPERTY(BlueprintReadWrite)
	FVector2D dragEndPos;

private:
	void OnGenerateObjectMode();
};
