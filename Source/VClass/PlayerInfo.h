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
	UPROPERTY(BlueprintReadWrite)
	FString name;

	UPROPERTY(BlueprintReadWrite)
	FString sitNum;

	UPROPERTY(BlueprintReadWrite)
	bool isHost;
};
