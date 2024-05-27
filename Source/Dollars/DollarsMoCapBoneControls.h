// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DollarsMoCapBoneControls.generated.h"

/**
 * 
 */
USTRUCT(Atomic, BlueprintType)
struct FDollarsMoCapBoneControls
{
	GENERATED_USTRUCT_BODY();
public:
	FTransform pelvis;
	FTransform spine;
	FTransform chest;
	FTransform neck;
	FTransform head;
	FTransform shoulder_l;
	FTransform shoulder_r;
	FTransform upperarm_l;
	FTransform upperarm_r;
	FTransform lowerarm_l;
	FTransform lowerarm_r;
	FTransform hand_l;
	FTransform hand_r;
	FTransform thigh_l;
	FTransform thigh_r;
	FTransform calf_l;
	FTransform calf_r;
	FTransform foot_l;
	FTransform foot_r;
	FTransform ball_l;
	FTransform ball_r;
	FTransform index1_l, index2_l, index3_l;
	FTransform middle1_l, middle2_l, middle3_l;
	FTransform ring1_l, ring2_l, ring3_l;
	FTransform pinky1_l, pinky2_l, pinky3_l;
	FTransform thumb1_l, thumb2_l, thumb3_l;
	FTransform index1_r, index2_r, index3_r;
	FTransform middle1_r, middle2_r, middle3_r;
	FTransform ring1_r, ring2_r, ring3_r;
	FTransform pinky1_r, pinky2_r, pinky3_r;
	FTransform thumb1_r, thumb2_r, thumb3_r;
};
