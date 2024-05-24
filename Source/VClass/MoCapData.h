// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MoCapData.generated.h"

/**
 * 
 */
USTRUCT(Atomic, BlueprintType)
struct FMoCapData
{
	GENERATED_USTRUCT_BODY();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<float> OSCFloats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> OSCAddress;
};
