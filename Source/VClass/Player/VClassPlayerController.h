// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InputActionValue.h"
#include "../ProjectInfo.h"
#include "GameFramework/PlayerController.h"
#include "VClassPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class VCLASS_API AVClassPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AVClassPlayerController();

	float mMoveDir;

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	virtual void Tick(float DeltaSeconds) override;

protected:
	void OnMove(const FInputActionValue& InputActionValue);
	void OnLook(const FInputActionValue& InputActionValue);
	void OnInteract(const FInputActionValue& InputActionValue);
};
