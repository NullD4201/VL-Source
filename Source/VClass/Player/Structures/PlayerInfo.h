// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerInfo.generated.h"
/**
 * 
 */
USTRUCT(Atomic, BlueprintType)
struct FPlayerInfo
{
	GENERATED_USTRUCT_BODY();
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString name;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString sitNum;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString Key;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool isHost;
};
