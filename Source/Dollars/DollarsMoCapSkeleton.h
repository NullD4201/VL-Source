// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DollarsMoCapSkeleton.generated.h"

/**
 * 
 */
USTRUCT(Atomic, BlueprintType)
struct FDollarsMoCapSkeleton
{
	GENERATED_USTRUCT_BODY();
public:
	FVector pelvis;
	FVector spine;
	FVector chest;
	FVector neck;
	FVector head;
	FVector shoulder_l;
	FVector shoulder_r;
	FVector upperarm_l;
	FVector upperarm_r;
	FVector lowerarm_l;
	FVector lowerarm_r;
	FVector hand_l;
	FVector hand_r;
	FVector thigh_l;
	FVector thigh_r;
	FVector calf_l;
	FVector calf_r;
	FVector foot_l;
	FVector foot_r;
	FVector ball_l;
	FVector ball_r;
};
