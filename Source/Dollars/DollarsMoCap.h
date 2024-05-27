// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DollarsMoCapBoneControls.h"
#include "DollarsMoCapFaceData.h"
#include "DollarsMoCapSkeleton.h"
#include "DollarsMoCap.generated.h"

/**
 * 
 */
USTRUCT(Atomic, BlueprintType)
struct FDollarsMoCap
{
	GENERATED_USTRUCT_BODY();
public:
	bool isReceived;

	FDollarsMoCapSkeleton skeleton;

	FDollarsMoCapBoneControls boneControls;

	float visibilityHead;
	float visibilityLeftHand;
	float visibilityRightHand;
	float visibilityHip;
	float visibilityLeftLeg;
	float visibilityRightLeg;

	FDollarsMoCapFaceData faceData;
};
