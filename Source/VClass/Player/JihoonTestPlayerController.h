// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ProjectInfo.h"
#include "GameFramework/PlayerController.h"
#include "JihoonTestPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class VCLASS_API AJihoonTestPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AJihoonTestPlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player")
	int32 PlayerId;
};
