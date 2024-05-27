// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DollarsMoCapFaceData.generated.h"

/**
 * 
 */
USTRUCT(Atomic, BlueprintType)
struct FDollarsMoCapFaceData
{
	GENERATED_USTRUCT_BODY();
public:
	float eyeBlinkLeft;
	float eyeLookDownLeft;
	float eyeLookInLeft;
	float eyeLookOutLeft;
	float eyeLookUpLeft;
	float eyeSquintLeft;
	float eyeWideLeft;

	float eyeBlinkRight;
	float eyeLookDownRight;
	float eyeLookInRight;
	float eyeLookOutRight;
	float eyeLookUpRight;
	float eyeSquintRight;
	float eyeWideRight;

	float jawForward;
	float jawLeft;
	float jawRight;
	float jawOpen;

	float mouthClose;
	float mouthFunnel;
	float mouthPucker;
	float mouthLeft;
	float mouthRight;
	float mouthSmileLeft;
	float mouthSmileRight;
	float mouthFrownLeft;
	float mouthFrownRight;
	float mouthDimpleLeft;
	float mouthDimpleRight;
	float mouthStretchLeft;
	float mouthStretchRight;
	float mouthRollLower;
	float mouthRollUpper;
	float mouthShrugLower;
	float mouthShrugUpper;
	float mouthPressLeft;
	float mouthPressRight;
	float mouthLowerDownLeft;
	float mouthLowerDownRight;
	float mouthUpperUpLeft;
	float mouthUpperUpRight;
	
	float browDownLeft;
	float browDownRight;
	float browInnerUp;
	float browOuterUpLeft;
	float browOuterUpRight;

	float cheekPuff;
	float cheekSquintLeft;
	float cheekSquintRight;

	float noseSneerLeft;
	float noseSneerRight;
	
	float tongueOut;
};
